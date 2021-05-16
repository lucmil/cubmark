/*
 * This file is part of Cubature Benchmark.
 * Copyright (C) 2009 Łukasz Lis
 *
 * Cubature Benchmark is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cubature Benchmark is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cubature Benchmark.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CUBMARK_ADAPTIVE
#define CUBMARK_ADAPTIVE

#include <queue>
#include <deque>
#include <map>
#include <utility>
#include <memory>

#include <cubmark/config.h>
#include <cubmark/Method.h>

namespace cb
{

/** \brief Adaptive algorithm for non-adaptive cubature algorithms
 *
 * This is an \a adapter for existing Method classes.
 * The "worker" class is invoked on the region of integration.
 * If the worker method fails, the region is divided along both axes
 * and the worker object is invoked on each of the four subdivisions.
 *
 * Infinite limits are supported as long as the worker class supports them.
 *
 * \todo Check if the class could find a better result by searching the tree
 *       more thoroughly.
 *
 * \todo If all subdivisions return a successful result, but the sum of their
 *       error estimates E exceeds the required tolerance, then the subdivision
 *       with the largest error estimate should be subdivided further.
 *
 *       Let \f$ E = \sum E_i \f$ denote the error estimate of the final result,
 *       where E_i is the error of the result of the i-th subdivision.
 */
class Adaptive
:   public Method
{
public:
	/** \brief Default constructor
	 *
	 * \post Method object under the passed pointer will be deleted by
	 *       the Adaptive object.
	 *
	 * \param method pointer to worker object. Cannot be NULL.
	 * \param n Maximum number of subdivisions.
	 */
	Adaptive(Method* method, size_t subdivDepthLimit = 10000);
	~Adaptive();

	void setRelativeTolerance(double relativeTolerance);
	double getRelativeTolerance() const;

	void setAbsoluteTolerance(double absoluteTolerance);
	double getAbsoluteTolerance() const;

	void setBoundary(const Boundary& b);
	bool hasBoundary() const;

	void setIntegrand(IntegrandType f);
	IntegrandType getIntegrand() const;
	bool hasIntegrand() const;

	double compute();

	bool failed() const;
	unsigned long getCallCnt() const;
	double getAbsoluteErrorEstimate() const;
	double getRelativeErrorEstimate() const;
	void setCallLimit(unsigned long max_calls);
	unsigned long getCallLimit() const;

private:
	/** \brief Retrieve the midpoint of a range
	 *
	 * If the range is infinite then the "midpoint" will be at a point
	 * shifted by a constant value from the finite boudary or at 0.0
	 * \f[ f: (a,b) \rightarrow \frac{1}{2}(a + b) \f]
	 * \f[ f: (a,\infty) \rightarrow a + C \f]
	 * \f[ f: (-\infty,b) \rightarrow b - C \f]
	 * \f[ f: (-\infty,\infty) \rightarrow 0.0 \f]
	 *
	 * \param a Left range boundary (can be -inf)
	 * \param b Right range boundary (can be inf)
	 */
	double rangeMidpoint(double a, double b) const;

	/** \brief Get a node's level in the quadtree
	 *
	 * \param addr Quadtree node address
	 * \return Node level number
	 */
	size_t subdivDepth(size_t address) const;

	/** \brief Calculate the address of the parent node
	 *
	 * \param Quadtree node address
	 * \return Address of the parent
	 */
	size_t subdivParentAddress(size_t address) const;

	/** \brief Calculate the address of the first child node
	 *
	 * \param addr Quadtree node address
	 * \return Address of the first child node in the quadtree
	 */
	size_t subdivChildAddress(size_t address) const;

	/** \brief Is the node at \c addr a leaf?
	 *
	 * \param address Quadtree node address
	 */
	bool isLeaf(size_t address) const;

	/** \brief Is the node at \c addr a parent to a complete branch?
	 *
	 * A parent with less than four children is incomplete.
	 *
	 * \param address Quadtree node address
	 */
	bool isComplete(size_t address) const;

	/** \brief Remove redundant subdivision results
	 *
	 * This will remove results of nodes which won't be used in the final sum.
	 */
	void pruneCompleteNodes();

	/** \brief Queue subdivisions of a boundary for integration
	 */
	void queueSubdivisions(size_t address, const Boundary &boundary);

	/** \brief Calculate the best cubature from the results in the quadtree
	 *
	 * Both the cubature and absolute error are the sum of the quadtree's
	 * leaves.
	 */
	void gatherResults();

	/** \brief Dump the results in DOT format for debugging.
	 */
	void dumpResults();

	class NodeResult
	{
		NodeResult();
	public:
		NodeResult(double cubature, double absErrEst) :
			cubature(cubature),
			absErrEst(absErrEst)
		{
		}

		const double cubature;
		const double absErrEst;
	};


	typedef std::pair<size_t, Boundary> WorkUnitType;
	typedef std::pair<double, WorkUnitType>  WorkPrioType;

	class WorkPrioLess
	:	public std::less<WorkPrioType>
	{
	public:
		WorkPrioLess()
		{
		}

		bool operator()(const WorkPrioType& l, const WorkPrioType& r) const
		{
			return l.first < r.first;
		}
	};

	typedef std::priority_queue<WorkPrioType,
				std::deque<WorkPrioType>, WorkPrioLess>
			WorkQueueType;

	typedef std::map<size_t, NodeResult> ResultsType;

	std::unique_ptr<Method> worker;

	WorkQueueType workQueue;

	/** \brief Quadtree with evaluation results
	 *
	 * If a node has n < 4 children nodes, then those children should occupy n
	 * consecutive addresses beginning from the first child node.
	 *
	 * For example:
	 * Parent at 0, n = 3 children
	 * Children will be at : 1,2,3
	 * Not: 1,2,4 or 2,3,4
	 *
	 * Failure to adhere to this scheme will break isComplete and isLeaf.
	 */
	ResultsType results;

	double cubature;
	double absErrEst;
	unsigned long callCnt;
	unsigned long callLimit;
	size_t subdivLimit;

	static const unsigned long defaultCallLimit;
};

}
#endif//CUBMARK_ADAPTIVE


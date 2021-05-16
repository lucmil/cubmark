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

#ifndef CUBMARK_RESULT_H
#define CUBMARK_RESULT_H

#include <string>

namespace boost
{
	namespace serialization
	{
		class access;
	}
}

namespace cb
{

/** \brief Benchmark result for a given method and test case
 */
class Result
{
	/** \brief Constructor for result of a single sample
	 *
	 * \param caseIdx
	 * \param methodIdx
	 * \param I
	 * \param C
	 * \param relativeTolerance
	 * \param absoluteErrorEstimate
	 * \param failureFlag
	 * \param cpuTimeMs
	 * \param callCnt
	 */
	Result(size_t caseIdx, size_t methodIdx,
		double I, double C, double relativeTolerance,
		double absoluteErrorEstimate, bool failureFlag, double cpuTimeMs,
		unsigned long callCnt);

	friend class boost::serialization::access;
	friend class Benchmark;

public:

	/** \brief Default constructor
	 */
	Result();

	/** \brief Copy constructor
	 */
	Result(const Result&);

	/** \brief Destructor
	 */
	virtual ~Result();

	/** \brief Method efficiency
	 *
	 *  This value is determined by comparing the \u exact analytic result to
	 *  the method's result. The method's success/failure flag is ignored.
	 */
	bool isEfficient() const;

	/** \brief Error estimate efficiency
	 *
	 * Determines if the actual error fits within the error estimate reported by
	 * the method.
	 */
	bool isErrorEstimationEfficient() const;

	/** \brief Method robustness
	 *
	 * Determines if the method can properly flag it's evaluation as failed and
	 * successful. A fallible method is a method which reports false negatives
	 * and false positives.
	 */
	bool isRobust() const;

	/** \brief Was the incorrect result flagged as correct
	 *
	 * \returns true if either isFailedMinor() or isFailedMajor() return true
	 */
	bool isFailed() const;

	/** \brief Minor method fallibility
	 *
	 * Incorrect results flagged as successful, with the actual relative error
	 * within a single order of magnitude of the tolerance.
	 */
	bool isFallibleMinor() const;

	/** \brief Major method fallibility
	 *
	 * Incorrect results flagged as successful, with the actual relative error
	 * beyond an order of magnitude of the tolerance.
	 */
	bool isFallibleMajor() const;

	/** \brief Number of integrand calls
	 */
	double getCallCnt() const;

	/** \brief Cpu time [ms]
	 */
	double getCpuTime() const;

	/** \brief Estimated value of the integral
	 */
	double getResult() const;

	/** \brief Absolute error estimate of the  result
	 */
	double getAbsoluteErrorEstimate() const;

	/** \brief Absolute error estimate of the  result
	 */
	double getRelativeErrorEstimate() const;

	/** \brief Absolute error of the  result
	 */
	double getAbsoluteError() const;

	/** \brief Relative error of the  result
	 */
	double getRelativeError() const;

	/** \brief Target relative tolerance for this result
	 */
	double getRelativeTolerance() const;

	/** \brief Case index
	 */
	size_t getCase() const;

	/** \brief Method index
	 */
	size_t getMethod() const;

	/** \brief Return a terse result classification string
	 *
	 * Produce a terse string which classifies a result in several categories.
	 * Each character of the string represents a classification in a single category
	 *
	 * 1. <tt>{S|F}</tt> - Success / Failure (Positive / Negative result).
	 *
	 *    Determines how the method flagged the result.
	 *
	 * 2. <tt>{+|-|m|M}</tt> - Properly flagged / False negative / Minor failure /
	 *                         Major failure
	 *
	 *    Determines if the error was:
	 *    - within the requested tolerance or properly flagged as a failure
	 *    - within the requested tolerance but has been flagged as a failure
	 *    - within an order of magnitude of the requested tolerance,
	 *      but has been flagged as successful.
	 *    - beyond an order of magnitude of the requested tolerance,
	 *      but has been flagged as successful.
	 *
	 * 3. <tt>{e|E}</tt> - Real error smaller / greater than the method's estimate.
	 *
	 * Examples (this isn't a comprehensive list):
	 * - "S+e" - Successful result with a good error estimate.
	 * - "S+E" - Successful result. Error estimate failure.
	 * - "F+e" - Negative result. The method failed to achieve the
	 *           requested tolerance and reported a failure. The returned
	 *           Result.had a good error estimate.
	 * - "SmE" - Minor evaluation failure. The method failed but reported a
	 *           successful evaluation. The error estimate was off by less than
	 *           an order of magnitude.
	 * - "SJE" - Major failure. The method failed but reported a successful
	 *           evaluation. The error estimate was off by at least
	 *           an order of magnitude.
	 * - "S-e" - False negative result. The method failed to recognize a
	 *           successfully evaluated cubature. Error estimate within tolerance
	 *           suggests a bug in error reporting code.
	 *
	 * \param r A benchmark result.
	 * \return Classification string.
	 */
	std::string classification() const;

	Result& operator=(const Result&);

	template<class Archive>
	void serialize(Archive& archive, const unsigned int version);
private:
	size_t caseIdx;
	size_t methodIdx;
	bool efficiency;
	bool errorEstimationEfficiency;
	bool robustness;
	bool fallibilityMinor;
	bool fallibilityMajor;
	double callCnt;
	double cpuTime;
	double result;
	double absoluteErrorEstimate;
	double absoluteError;
	double relativeError;
	double relativeTolerance;
};

}
#endif//CUBMARK_RESULT_H

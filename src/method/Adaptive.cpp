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

#include <cmath>
#include <stdexcept>
#include <sstream>

#include <cubmark/Adaptive.h>

#include <cubmark/debug.h>
#include <cubmark/constants.h>
#include <cubmark/algorithm.h>

using std::isnan;
using std::isinf;

namespace cb
{

Adaptive::Adaptive(Method* worker, size_t subdivLimit) :
	worker(worker),
	cubature(NaN),
	absErrEst(NaN),
	callCnt(0),
	callLimit(defaultCallLimit),
	subdivLimit(subdivLimit)
{
	CHECK(worker, "NULL Method pointer passed as worker.");
	LOG(TRACE, "Subdivision count limit: " << subdivLimit);
}

Adaptive::~Adaptive()
{
}

void Adaptive::setRelativeTolerance(double relativeTolerance)
{
	return worker->setRelativeTolerance(relativeTolerance);
}

double Adaptive::getRelativeTolerance() const
{
	return worker->getRelativeTolerance();
}


void Adaptive::setAbsoluteTolerance(double absoluteTolerance)
{
	return worker->setAbsoluteTolerance(absoluteTolerance);
}

double Adaptive::getAbsoluteTolerance() const
{
	return worker->getAbsoluteTolerance();
}

void Adaptive::setBoundary(const Boundary& b)
{
	// Clear the work queue before changing the integration region
	if(workQueue.size() > 0)
	{
		WorkQueueType empty;
		std::swap(workQueue, empty);
	}
	if(b.isValid())
	{
		workQueue.push(std::make_pair(inf, std::make_pair(0, b)));
	}
}

bool Adaptive::hasBoundary() const
{
	return (workQueue.size() > 0);
}

bool Adaptive::hasIntegrand() const
{
	return worker->hasIntegrand();
}

Method::IntegrandType Adaptive::getIntegrand() const
{
	return worker->getIntegrand();
}

void Adaptive::setIntegrand(IntegrandType integrand)
{
	worker->setIntegrand(integrand);
}

double Adaptive::compute()
{
	size_t callCnt = 0;

	while(!workQueue.empty()
			&& callCnt < callLimit
			&& results.size() < subdivLimit)
	{
		const WorkUnitType workUnit(workQueue.top().second);
		const size_t address = workUnit.first;
		Boundary subdivBoundary = workUnit.second;

		worker->setBoundary(subdivBoundary);
		const double subdivCubature = worker->compute();
		results.insert(std::make_pair(address,
				NodeResult(subdivCubature, worker->getAbsoluteErrorEstimate())));

		callCnt += worker->getCallCnt();
		workQueue.pop();

		if(worker->failed())
		{
			queueSubdivisions(address, subdivBoundary);
		}

		if(results.size() >= subdivLimit)
		{
			const size_t resultCnt = results.size();
			pruneCompleteNodes();
			const size_t redundantCnt = (resultCnt - results.size());
			LOG(TRACE, "Pruned " << redundantCnt << " redundant nodes.");

			if(redundantCnt == 0)
			{
				LOG(TRACE, "Subdivision limit reached.");
			}
		}

	}
	gatherResults();
	this->callCnt = callCnt;
	return cubature;
}

double Adaptive::rangeMidpoint(double a, double b) const throw()
{
	/* NOTE
	 * This particular step length has been chosen because it's a pretty, round
	 * number (and I like round numbers).
	 * If it doesn't work then find a smarter way to determine a better value.
	 */
	const double inf_step = 32.;
	if(isinf(a))
	{
		CHECK(a < 0.0, "Invalid left boundary");
		if(isinf(b))
		{
			CHECK(b > 0.0, "Invalid left boundary");
			// (-inf,inf) - whole axis
			return 0.;
		}
		else
		{
			// (-inf,b] - negative half
			return (b - inf_step);
		}
	}
	else
	{
		if(isinf(b))
		{
			CHECK(b > 0.0, "Invalid left boundary");
			// [a,+inf) - positive half
			return (a + inf_step);
		}
		else
		{
			// [a,b] - finite range
			if(fabs(a-b) <= std::numeric_limits<double>::min())
			{
				// Division is impossible
				return NaN;
			}
			return (a + b)/2.;
		}
	}
}

bool Adaptive::failed() const
{
	const double relErrTol = this->getRelativeTolerance();
	const double absErrTol = this->getAbsoluteTolerance();

	return(isnan(cubature)
			|| (relErrTol != 0. && this->getRelativeErrorEstimate() > relErrTol)
			|| (absErrTol != 0. && this->getAbsoluteErrorEstimate() > absErrTol));
}

unsigned long Adaptive::getCallCnt() const
{
	return callCnt;
}

double Adaptive::getAbsoluteErrorEstimate() const
{
	return absErrEst;
}

double Adaptive::getRelativeErrorEstimate() const
{
	return ((cubature != 0.) ? absErrEst / cubature : NaN);
}

void Adaptive::setCallLimit(unsigned long callLimit)
{
	if(callLimit == 0)
	{
		this->callLimit = Adaptive::defaultCallLimit;
	}
	else
	{
		this->callLimit = callLimit;
	}
}

unsigned long Adaptive::getCallLimit() const
{
	return callLimit;
}

size_t Adaptive::subdivParentAddress(size_t address) const throw()
{
	return (address - 1)/4;
}

size_t Adaptive::subdivDepth(size_t address) const throw()
{
	return (size_t)floor(.5 * log2((double)(3*address + 2)));
}

size_t Adaptive::subdivChildAddress(size_t address) const throw()
{
	return 4 * address + 1;
}

bool Adaptive::isLeaf(size_t addr) const
{
	const size_t childAddress = subdivChildAddress(addr);
	ResultsType::const_iterator child = results.find(childAddress);

	for(size_t i = 0; i < 4; ++i)
	{
		if(child != results.end() && child->first == childAddress + i)
		{
			return false;
		}
		++child;
	}
	return true;
}

bool Adaptive::isComplete(size_t addr) const
{
	const size_t childAddress = subdivChildAddress(addr);
	ResultsType::const_iterator child = results.find(childAddress);

	for(size_t i = 0; i < 4; ++i)
	{
		if(child == results.end() || child->first != childAddress + i)
		{
			return false;
		}
		++child;
	}
	return true;
}

void Adaptive::pruneCompleteNodes()
{
	ResultsType::iterator i = results.begin();
	const ResultsType::iterator end = results.end();
	while(i != end)
	{
		if(isComplete(i->first))
		{
			ResultsType::iterator completeNode = i;
			++i;
			results.erase(completeNode);
		}
		else
		{
			++i;
		}
	}
}

void Adaptive::queueSubdivisions(const size_t address, const Boundary &boundary)
{
	const double a = boundary.l(0);
	const double b = boundary.u(0);
	const double c = boundary.l(1);
	const double d = boundary.u(1);
	const double xMidpoint = rangeMidpoint(a, b);
	const double kMidpoint = rangeMidpoint(c, d);
	const size_t childAddress = subdivChildAddress(address);

	const WorkUnitType quadrant0(childAddress + 0,
			Boundary(xMidpoint, b, kMidpoint, d));

	const WorkUnitType quadrant1(childAddress + 1,
			Boundary(xMidpoint, b, c, kMidpoint));

	const WorkUnitType quadrant2(childAddress + 2,
			Boundary(a, xMidpoint, c, kMidpoint));

	const WorkUnitType quadrant3(childAddress + 3,
			Boundary(a, xMidpoint, kMidpoint, d));

	const ResultsType::const_iterator parentResult(results.find(address));

	CHECK(parentResult != results.end(),
			"Parent region not calculated.");

	const double parentAbsErrEst(parentResult->second.absErrEst);

	workQueue.push(std::make_pair(parentAbsErrEst, quadrant0));
	workQueue.push(std::make_pair(parentAbsErrEst, quadrant1));
	workQueue.push(std::make_pair(parentAbsErrEst, quadrant2));
	workQueue.push(std::make_pair(parentAbsErrEst, quadrant3));
}

void Adaptive::gatherResults()
{
	KahanSum<double> cubature(0.0);
	KahanSum<double> absErrEst(0.0);

	ResultsType::const_iterator i;
	const ResultsType::const_iterator end = results.end();
	for(i = results.begin(); i != end; ++i)
	{
		const size_t addr = i->first;

		// Sum all leaves and parents of incomplete branches
		if(!isComplete(addr))
		{
			const NodeResult& subdivResult = i->second;
			cubature += subdivResult.cubature;
			absErrEst += subdivResult.absErrEst;
		}
	}
	this->cubature = cubature.getSum();
	this->absErrEst = absErrEst.getSum();
	results.clear();
}

void Adaptive::dumpResults()
{
	std::ostringstream graph;
	const char* colours[] = { "black", "red", "green" };

	ResultsType::const_iterator i;
	const ResultsType::const_iterator end = results.end();
	for(i = results.begin(); i != end; ++i)
	{
		const size_t addr = i->first;
		const size_t parentAddr = subdivParentAddress(addr);
		const NodeResult& result = i->second;
		size_t c = 0;

		if(isLeaf(addr))
		{
			c = 1;
		}
		else if(isComplete(addr))
		{
			c = 2;
		}

		graph << '\t' << addr << " ["
					"label=\"ID: " << addr << "\\n" << result.cubature
							<< "\\n(EE = " << result.absErrEst << ")\" "
					"color=" << colours[c]
				<< "];\n"
			   "\t" << addr << " -> " << parentAddr << ";\n";
	}
	graph << "}\n";

	LOG(TRACE, "Results quadtree:\n" << graph.str());
}

const unsigned long Adaptive::defaultCallLimit = 100000u;

}

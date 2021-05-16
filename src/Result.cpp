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

#include <cubmark/Result.h>

#include <cubmark/debug.h>
#include <cubmark/algorithm.h>
#include <cubmark/constants.h>

namespace cb
{

Result::Result() :
	caseIdx((size_t)-1),
	methodIdx((size_t)-1),
	efficiency(false),
	errorEstimationEfficiency(false),
	robustness(false),
	fallibilityMinor(false),
	fallibilityMajor(false),
	callCnt(0),
	cpuTime(0),
	result(0),
	absoluteErrorEstimate(0),
	absoluteError(0),
	relativeError(0),
	relativeTolerance(0)
{
}

Result::Result(const Result& source) :
	caseIdx(source.caseIdx),
	methodIdx(source.methodIdx),
	efficiency(source.efficiency),
	errorEstimationEfficiency(source.errorEstimationEfficiency),
	robustness(source.robustness),
	fallibilityMinor(source.fallibilityMinor),
	fallibilityMajor(source.fallibilityMajor),
	callCnt(source.callCnt),
	cpuTime(source.cpuTime),
	result(source.result),
	absoluteErrorEstimate(source.absoluteErrorEstimate),
	absoluteError(source.absoluteError),
	relativeError(source.relativeError),
	relativeTolerance(source.relativeTolerance)
{
}

Result::~Result()
{
}

Result::Result(size_t caseIdx, size_t methodIdx,
		double I, double C,
		double relativeTolerance,
		double absoluteErrorEstimate,
		bool failureFlag,
		double cpuTimeMs,
		unsigned long callCnt) :
	caseIdx(caseIdx),
	methodIdx(methodIdx),
	efficiency(false),
	errorEstimationEfficiency(false),
	robustness(false),
	fallibilityMinor(false),
	fallibilityMajor(false),
	callCnt((double)callCnt),
	cpuTime(cpuTimeMs),
	result(C),
	absoluteErrorEstimate(absoluteErrorEstimate),
	absoluteError(fabs(I - C)),
	relativeError(fabs(C / I - 1.0)),
	relativeTolerance(relativeTolerance)
{
	const double absoluteErrorTolerance = fabs(I * relativeTolerance);

	LOG(TRACE, "Result : " << C << " (+/-) " << absoluteError
			<< " [" << relativeError << "] "
			"Estimate: " << absoluteErrorEstimate);

	// Successful evaluation?
	if(absoluteError <= absoluteErrorTolerance)
	{
		LOG(TRACE, "Cubature properly computed");
		this->efficiency = true;
		this->robustness = !failureFlag;

		// Error flag should be clear
		if(failureFlag)
		{
			LOG(TRACE, "Error flag: false positive");
		}
	}
	else // Evaluation failed
	{
		LOG(TRACE, "Evaluation failed");
		this->efficiency = false;
		this->robustness = failureFlag;

		if(!failureFlag)
		{
			// Error reporting failed, determine to what degree
			if((log10(absoluteError) - log10(absoluteErrorTolerance)) < 1.0)
			{
				LOG(TRACE, "Error flag: minor false negative");
				this->fallibilityMinor = true;
			}
			else
			{
				LOG(TRACE, "Error flag: major false negative");
				this->fallibilityMajor = true;
			}
		}
	}

	// Compare error estimation performance
	if(absoluteError < absoluteErrorEstimate)
	{
		LOG(TRACE, "Error estimate failure");
		this->errorEstimationEfficiency = true;
	}
}

bool Result::isEfficient() const
{
	return this->efficiency;
}

bool Result::isErrorEstimationEfficient() const
{
	return this->errorEstimationEfficiency;
}

bool Result::isRobust() const
{
	return this->robustness;
}

bool Result::isFallibleMinor() const
{
	return this->fallibilityMinor;
}

bool Result::isFallibleMajor() const
{
	return this->fallibilityMajor;
}

bool Result::isFailed() const
{
	return this->isFallibleMinor() || this->isFallibleMajor();
}

double Result::getCallCnt() const
{
	return this->callCnt;
}

double Result::getCpuTime() const
{
	return this->cpuTime;
}

double Result::getResult() const
{
	return this->result;
}

double Result::getAbsoluteErrorEstimate() const
{
	return this->absoluteErrorEstimate;
}

double Result::getRelativeErrorEstimate() const
{
	if(feq0(result))
	{
		return this->absoluteErrorEstimate;
	}
	return this->absoluteErrorEstimate / fabs(result);
}

double Result::getAbsoluteError() const
{
	return this->absoluteError;
}

double Result::getRelativeError() const
{
	return this->relativeError;
}

double Result::getRelativeTolerance() const
{
	return this->relativeTolerance;
}

size_t Result::getCase() const
{
	return this->caseIdx;
}

size_t Result::getMethod() const
{
	return this->methodIdx;
}

std::string Result::classification() const
{
	std::string classification("E+D");
	bool reportedAsFailed = (isEfficient() != isRobust());

	classification[0] = reportedAsFailed  ? 'F' : 'S';

	if(isEfficient())
	{
		classification[1] = (isRobust() ? '+' : '-');
	}
	else if(isFallibleMinor())
	{
		classification[1] = 'm';
	}
	else if(isFallibleMajor())
	{
		classification[1] = 'M';
	}

	classification[2] = isErrorEstimationEfficient() ? 'e' : 'E';

	return classification;
}

Result& Result::operator=(const Result& source) {
	caseIdx = source.caseIdx;
	methodIdx = source.methodIdx;
	efficiency = source.efficiency;
	errorEstimationEfficiency = source.errorEstimationEfficiency;
	robustness = source.robustness;
	fallibilityMinor = source.fallibilityMinor;
	fallibilityMajor = source.fallibilityMajor;
	callCnt = source.callCnt;
	cpuTime = source.cpuTime;
	result = source.result;
	absoluteErrorEstimate = source.absoluteErrorEstimate;
	absoluteError = source.absoluteError;
	relativeError = source.relativeError;
	relativeTolerance = source.relativeTolerance;
	return *this;
}

}

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

#include <cubmark/ResultQuality.h>

#include <cubmark/ResultMedian.h>
#include <cubmark/ResultFormat.hpp>
#include <cubmark/Result.h>
#include <cubmark/constants.h>
#include <cubmark/algorithm.hpp>

namespace cb
{

ResultQuality::~ResultQuality()
{
}

void ResultQuality::write(ResultFormat& resultFormat) const
{
	resultFormat.write(this);
}

void ResultQuality::compute(SamplesRangeType sampleRange)
{
	using std::max;
	using std::min;
	double relErrMed = NaN;
	{
		ResultMedian<double> relErr(&Result::getRelativeError);
		relErr.compute(sampleRange);
		relErrMed = max(0.0, -log10(relErr.getFieldMedian()));
	}

	double relErrEstMed = NaN;
	{
		ResultMedian<double> relErrEst(&Result::getRelativeErrorEstimate);
		relErrEst.compute(sampleRange);
		relErrEstMed = max(0.0, -log10(relErrEst.getFieldMedian()));
	}

	double callCntMed = NaN;
	{
		ResultMedian<double> callCnt(&Result::getCallCnt);
		callCnt.compute(sampleRange);
		callCntMed = log(callCnt.getFieldMedian());
	}

	double epsilonMed = NaN;
	{
		std::deque<double> epsilon;
		SamplesType::iterator i(sampleRange.first);
		const SamplesType::iterator end(sampleRange.second);
		for(; i != end; ++i)
		{
			const double re = min(1.0, -log10(i->getRelativeError()));
			const double ree = min(1.0, -log10(i->getRelativeErrorEstimate()));
			epsilon.push_back(max(0.0, ree - re));
		}
		typedef std::deque<double>::iterator DeqIt;
		std::pair<DeqIt, DeqIt> medEl(median(epsilon.begin(), epsilon.end()));
		epsilonMed = max(0.0, (*medEl.first + *medEl.second)/2.0);
	}

	quality = (relErrMed + 1.0) * (relErrEstMed + 1.0 - epsilonMed) / callCntMed;

	LOG(TRACE, "REm: " << relErrMed
			<< " REEm: " << relErrEstMed
			<< " epsMed: " << epsilonMed
			<< " ccM: " << callCntMed
			<< " q: " << quality);

}

double ResultQuality::getQuality() const
{
	return quality;
}

}


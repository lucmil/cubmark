/*
 * This file is part of Cubature CaseResults.
 * Copyright (C) 2009 Łukasz Lis
 *
 * Cubature CaseResults is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cubature CaseResults is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cubature CaseResults.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cubmark/Result.h>
#include <cubmark/CaseResults.h>
#include <cubmark/SuiteSpecification.h>
#include <cubmark/CaseSpecification.h>

#include <cubmark/debug.h>

namespace cb
{

CaseResults::CaseResults()
{
}

CaseResults::CaseResults(const SuiteSpecification& suiteSpec) :
	sampleCnt(suiteSpec.getMethodCnt(), 0),
	sampleLimit(suiteSpec.getSampleLimit()),
	samples(sampleLimit * sampleCnt.size())
{
}

CaseResults::~CaseResults()
{
}

void CaseResults::addSample(const Result& sampleResult)
{
	const size_t methodIdx = sampleResult.getMethod();
	samples.at(methodIdx * sampleLimit + sampleCnt[methodIdx]) = sampleResult;
	++sampleCnt.at(methodIdx);
	CHECK(sampleCnt.at(methodIdx) <= sampleLimit, "Sample limit reached.");
}

const SamplesType& CaseResults::getSamples() const
{
	return samples;
}

ConstRangeType CaseResults::getMethodSamples(size_t methodIdx) const
{
	const SamplesType::const_iterator begin =
			samples.begin() + methodIdx * sampleLimit;

	const SamplesType::const_iterator end = begin + sampleCnt[methodIdx];
	return std::make_pair(begin, end);
}

SamplesRangeType CaseResults::getMethodSamples(size_t methodIdx)
{
	const SamplesType::iterator begin =
			samples.begin() + methodIdx * sampleLimit;

	const SamplesType::iterator end = begin + sampleCnt[methodIdx];
	return std::make_pair(begin, end);
}

void CaseResults::clear()
{
	samples.clear();
}

SamplesType::size_type CaseResults::getSize() const
{
	return samples.size();
}

size_t CaseResults::getSampleCnt(size_t methodIdx) const
{
	return sampleCnt.at(methodIdx);
}

}


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

#ifndef CUBMARK_CASE_RESULTS_H
#define CUBMARK_CASE_RESULTS_H

#include <vector>

#include <cubmark/types.h>

namespace boost
{
	namespace serialization
	{
		class access;
	}
}

namespace cb
{

class Result;
class SuiteSpecification;

/** \brief Benchmark result for a given method and test case
 */
class CaseResults
{
	friend class boost::serialization::access;

	/** \brief Constructor
	 */
	CaseResults(const SuiteSpecification& suiteSpecification);
	void addSample(const Result& sampleResult);
public:
	friend class SuiteResults;

	/** \brief Default constructor
	 */
	CaseResults();

	virtual ~CaseResults();

	const SamplesType& getSamples() const;
	size_t getSampleCnt(size_t methodIdx) const;
	ConstRangeType getMethodSamples(size_t methodIdx) const;
	SamplesRangeType getMethodSamples(size_t methodIdx);
	void clear();
	SamplesType::size_type getSize() const;

	template<class Archive>
	void serialize(Archive& archive, const unsigned int version);
private:
	std::vector<SamplesType::size_type> sampleCnt;
	SamplesType::size_type sampleLimit;
	SamplesType samples;
};

}
#endif//CUBMARK_CASE_RESULTS_H

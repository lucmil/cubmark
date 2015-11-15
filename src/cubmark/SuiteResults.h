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

#ifndef CUBMARK_SUITERESULTS_H
#define CUBMARK_SUITERESULTS_H

#include <deque>

#include <cubmark/SuiteSpecification.h>

namespace boost
{
	namespace serialization
	{
		class access;
	}
}

/**
 * \brief Main namespace of the Benchmark suite
 */
namespace cb
{

class Result;
class CaseResults;

/** \brief Container for Benchmark suite results.
 *
 * Each item contains results for all methods for a single case.
 */
class SuiteResults
{
	friend class boost::serialization::access;
public:
	SuiteResults();
	virtual ~SuiteResults();
	
	void setSpecification(const SuiteSpecification& suiteSpecification);
	void addSample(const Result& result);

	CaseResults& getCaseResults(size_t i);
	const SuiteSpecification& getSpecification() const;

	template<class Archive>
	void serialize(Archive& archive, const unsigned int version);
private:
	std::deque<CaseResults> suiteResults;
	SuiteSpecification suiteSpecification;
};

}

#endif//CUBMARK_SUITERESULTS_H



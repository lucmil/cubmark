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

#ifndef CUBMARK_SUITESPECIFICAITON_H
#define CUBMARK_SUITESPECIFICAITON_H

#include <vector>

#include <cubmark/Definition.h>
#include <cubmark/Boundary.h>

/**
 * \brief Main namespace of the Benchmark suite
 */
namespace cb
{

class CaseSpecification;

class SuiteSpecification
{
	friend class boost::serialization::access;
public:
	SuiteSpecification();

	void setTestFunctor(const Definition& definition);
	void setBoundary(const Boundary& boundary);
	void addMethod(const Definition& definition);
	void addCase(const CaseSpecification& caseSpec);
	void setSampleLimit(unsigned long sampleLimit);
	void setCallLimit(unsigned long callLimit);

	size_t getCaseCnt() const;
	size_t getMethodCnt() const;

	const Definition& getTestFunctor() const;
	const Boundary& getBoundary() const;
	const Definition& getMethod(size_t methodIdx) const;
	const CaseSpecification& getCase(size_t caseIdx) const;
	unsigned long getSampleLimit() const;
	unsigned long getCallLimit() const;

	bool isComplete() const;

	template<class Archive>
	void serialize(Archive& archive, const unsigned int version);
private:
	Definition testFunctor;
	Boundary boundary;
	size_t sampleLimit;
	size_t callLimit;
	std::vector<CaseSpecification> caseSpecs;
	std::vector<Definition> methods;
};

}

#endif//CUBMARK_SUITESPECIFICAITON_H



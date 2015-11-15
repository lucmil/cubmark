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

#include <cubmark/SuiteSpecification.h>
#include <cubmark/CaseSpecification.h>
#include <cubmark/Definition.h>
#include <cubmark/ViewBuilder.h>
#include <cubmark/TestFunctorBuilder.h>
#include <cubmark/Method.h>
#include <cubmark/Benchmark.h>
#include <cubmark/debug.h>

namespace cb
{

SuiteSpecification::SuiteSpecification() :
	sampleLimit(5),
	callLimit(100000)
{
}

void SuiteSpecification::setTestFunctor(const Definition& definition)
{
	this->testFunctor = definition;
}

void SuiteSpecification::setBoundary(const Boundary &boundary)
{
	LOG(TRACE, "Integration boundary override: "
		   "a = " << boundary.l(0) << " , b = " << boundary.u(0) << ","
		   "c = " << boundary.l(1) << " , d = " << boundary.u(1) << "]\n");

	this->boundary = boundary;
}

void SuiteSpecification::addMethod(const Definition& definition)
{
	methods.push_back(definition);
}

void SuiteSpecification::addCase(const CaseSpecification& caseSpec)
{
	caseSpecs.push_back(caseSpec);
}

void SuiteSpecification::setSampleLimit(unsigned long sampleLimit)
{
	this->sampleLimit = sampleLimit;
}

void SuiteSpecification::setCallLimit(unsigned long callLimit)
{
	this->callLimit = (callLimit) ? callLimit : 100000u ;
}

size_t SuiteSpecification::getCaseCnt() const
{
	return caseSpecs.size();
}

size_t SuiteSpecification::getMethodCnt() const
{
	return methods.size();
}

const Definition& SuiteSpecification::getTestFunctor() const
{
	return this->testFunctor;
}

const Boundary& SuiteSpecification::getBoundary() const
{
	return this->boundary;
}

const Definition& SuiteSpecification::getMethod(size_t methodIdx) const
{
	return this->methods[methodIdx];
}

const CaseSpecification& SuiteSpecification::getCase(size_t caseIdx) const
{
	return this->caseSpecs[caseIdx];
}

unsigned long SuiteSpecification::getCallLimit() const
{
	return this->callLimit;
}

unsigned long SuiteSpecification::getSampleLimit() const
{
	return this->sampleLimit;
}

bool SuiteSpecification::isComplete() const
{
	return (!this->testFunctor.getName().empty() && !this->caseSpecs.empty());
}

}

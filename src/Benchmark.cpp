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

#include <cubmark/constants.h>
#include <cubmark/debug.h>

#include <cubmark/Benchmark.h>
#include <cubmark/StopTimer.h>
#include <cubmark/Sample.h>
#include <cubmark/Result.h>
#include <cubmark/SuiteResults.h>
#include <cubmark/SuiteSpecification.h>
#include <cubmark/CaseSpecification.h>
#include <cubmark/TestFunctorFactory.h>
#include <cubmark/TestFunctorBuilder.h>
#include <cubmark/MethodFactory.h>
#include <cubmark/Method.h>

namespace cb
{

Benchmark::Benchmark(SuiteResults& suiteResults) :
	suiteResults(suiteResults),
	methods(suiteResults.getSpecification().getMethodCnt())
{
	initMethods();
	initTestFunctorBuilder();
}

Benchmark::~Benchmark()
{
}

void Benchmark::computeResults()
{
	const SuiteSpecification& suiteSpec = suiteResults.getSpecification();

	LOG(TRACE, "Running benchmark suite.");
	for(size_t c = 0; c < suiteSpec.getCaseCnt(); ++c)
	{
		for(size_t s = 0; s < suiteSpec.getSampleLimit(); ++s)
		{
			Sample sample = createSample(c);
			for(size_t m = 0; m < suiteSpec.getMethodCnt(); ++m)
			{
				runMethod(m, sample);
			}
		}
	}
}

Sample Benchmark::createSample(size_t caseIdx)
{
	Boundary boundary = this->getSampleBoundary();

	LOG(TRACE, "Sample boundary: ["
			<< boundary.l(0) <<", "
			<< boundary.u(0) << "]x["
			<< boundary.l(1) << ", "
			<< boundary.u(1) << "]");

	const Method::IntegrandType f = testFunctorBuilder->create();
	double exactIntegral = testFunctorBuilder->integral(boundary);
	return Sample(caseIdx, f, boundary, exactIntegral);
}

void Benchmark::initMethods()
{
	MethodFactory methodFactory;
	const SuiteSpecification& suiteSpec = suiteResults.getSpecification();
	for(size_t i = 0; i < methods.capacity(); ++i)
	{
		const Definition& definition = suiteSpec.getMethod(i);
		Method* method = methodFactory.getByDefinition(definition);
		method->setCallLimit(suiteSpec.getCallLimit());
		this->methods.push_back(method);
	}
}

void Benchmark::initTestFunctorBuilder()
{
	const SuiteSpecification& suiteSpec = suiteResults.getSpecification();
	TestFunctorFactory testFunctorFactory;
	const Definition& definition = suiteSpec.getTestFunctor();
	testFunctorBuilder.reset(
		testFunctorFactory.getByDefinition(definition));
}

Boundary Benchmark::getSampleBoundary() const
{
	const SuiteSpecification& suiteSpec = suiteResults.getSpecification();
	Boundary boundary(suiteSpec.getBoundary());

	if(!boundary.isValid())
	{
		// Use default boundary values
		boundary.fillIn(testFunctorBuilder->getDefaultBoundary());
	}
	// Boundary set with setBoundary() or no default boundary
	return boundary;
}

void Benchmark::runMethod(const size_t methodIdx, const Sample& testSample)
{
	LOG(TRACE, "Starting test case. I = " << testSample.I);

	const CaseSpecification& caseSpec =
			suiteResults.getSpecification().getCase(testSample.caseIdx);

	const double relativeTolerance = caseSpec.getRelativeTolerance();
	LOG(TRACE, "Relative error tolerance: " << relativeTolerance << "\n");

	Method& method = methods[methodIdx];
	method.setRelativeTolerance(relativeTolerance);
	method.setBoundary(testSample.boundary);
	method.setIntegrand(testSample.integrandPtr);

	StopTimer stopTimer;
	stopTimer.start();
	const double C = method.compute();
	stopTimer.stop();

	Result result(testSample.caseIdx, methodIdx, testSample.I,
			C, relativeTolerance,
			method.getAbsoluteErrorEstimate(),
			method.failed(),
			stopTimer.getTimeMs(),
			method.getCallCnt());

	LOG(TRACE, "Method #" << methodIdx
			<< (result.isEfficient() ? ": FAILURE " : " SUCCESS ")
			<< (result.isFallibleMinor() ? "FMINOR" : "")
			<< (result.isFallibleMajor() ? "FMAJOR" : ""));

	suiteResults.addSample(result);
}

}


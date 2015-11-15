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

#include <iostream>
#include <iomanip>
#include <algorithm>

#include <cubmark/TestpackViewBuilder.h>
#include <cubmark/TestFunctorFactory.h>
#include <cubmark/TestFunctorBuilder.h>

#include <cubmark/debug.h>
#include <cubmark/Result.h>
#include <cubmark/SuiteSpecification.h>
#include <cubmark/CaseResults.h>
#include <cubmark/SuiteResults.h>
#include <cubmark/FieldLess.hpp>
#include <cubmark/ResultMedian.hpp>
#include <cubmark/ResultQuantiles.hpp>
#include <cubmark/ResultAccumulate.hpp>
#include <cubmark/ResultAverage.hpp>

namespace cb
{

TestpackViewBuilder::TestpackViewBuilder() :
	fieldStatisticsSize(sizeof(fieldStatistics)/sizeof(ResultStatistic*))
{
	initFieldStatistics();
}

TestpackViewBuilder::~TestpackViewBuilder()
{
}

void TestpackViewBuilder::create(SuiteResults& suiteResults, std::ostream& out)
{
	using namespace std;

	const SuiteSpecification& suiteSpec(suiteResults.getSpecification());
	const size_t methodCnt = suiteSpec.getMethodCnt();
	const size_t caseCount = suiteSpec.getCaseCnt();
	const Definition& testFunctorDefinition(suiteSpec.getTestFunctor());

	TestFunctorFactory testFunctorFactory;
	std::auto_ptr<TestFunctorBuilder> testFunctor(
			testFunctorFactory.getByDefinition(testFunctorDefinition));

	Boundary boundary(suiteSpec.getBoundary());
	boundary.fillIn(testFunctor->getDefaultBoundary());

	out << "# Test function: "<< testFunctorDefinition.getName() <<'\n'
			<< "# Parameters: "<< testFunctorDefinition.getString() <<'\n'
			<< "# Boundary is infinite: "<< boundary.isInfinite() <<'\n'
			<< setprecision(2) <<"#";

	out << setw(fieldWidths[0] - 1) << fieldTitles[0];
	for(size_t i = 1; i < (sizeof(fieldWidths))/sizeof(fieldWidths[0]); ++i)
	{
		out << setw(fieldWidths[i]) << fieldTitles[i];
	}
	out << '\n';

	for(size_t i = 0; i < methodCnt; ++i)
	{
		out << "# Method: "<< suiteSpec.getMethod(i).getName() <<'\n';
		for(size_t j = 0; j < caseCount; ++j)
		{
			CaseResults& caseResults = suiteResults.getCaseResults(j);
			out.setf(ios_base::showpoint);
			writeCase(out, caseResults.getMethodSamples(i));
			out.unsetf(ios_base::showpoint);
		}
		out << '\n';
	}
}

void TestpackViewBuilder::parseParameter(const std::string& /*name*/,
		const std::string& /*value*/)
{
}

void TestpackViewBuilder::writeCase(std::ostream& out, const SamplesRangeType& samples)
{
	using std::ios_base;
	const std::streamsize oldPrecision = out.precision();

	/* Relative tolerance */
	out.setf(ios_base::scientific);
	out.precision(1);
	writeField(out, 0, samples);
	out.unsetf(ios_base::scientific);
	out.precision(oldPrecision);

	/* Rest up to the best result */
	for(size_t i = 1; i < fieldStatisticsSize; ++i)
	{
		writeField(out, i, samples);
	}

	out << '\n';
}

void TestpackViewBuilder::writeField(
		std::ostream& out, size_t fieldIdx, const SamplesRangeType& samples)
{
	ResultStatistic& resultStatistics = *fieldStatistics[fieldIdx];
	resultStatistics.compute(samples);
	out << std::setw(fieldWidths[fieldIdx]) << resultStatistics;
}

void TestpackViewBuilder::initFieldStatistics()
{
	fieldStatistics[0].reset(resultMedian(&Result::getRelativeTolerance));
	fieldStatistics[1].reset(resultQuantiles(3, &Result::getRelativeErrorEstimate));
	fieldStatistics[2].reset(resultQuantiles(3, &Result::getRelativeError));
	fieldStatistics[3].reset(resultAverage<double>(&Result::isRobust));
	fieldStatistics[4].reset(resultQuantiles(3, &Result::getCallCnt));
	fieldStatistics[5].reset(resultQuantiles(3, &Result::getCpuTime));
	fieldStatistics[6].reset(new ResultQuality);
	fieldStatistics[7].reset(resultAverage<double>(&Result::isFailed));
}

const int TestpackViewBuilder::fieldWidths[] =
{
	7, 25, 25, 8, 25, 25, 7, 8
};

const char *TestpackViewBuilder::fieldTitles[] =
{
	"RET", "EE", "RE", "ROB", "Calls", "Time", "Q", "Fail"
};

}

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

#include <cubmark/FullViewBuilder.h>

#include <cubmark/debug.h>
#include <cubmark/Result.h>
#include <cubmark/SuiteSpecification.h>
#include <cubmark/CaseResults.h>
#include <cubmark/SuiteResults.h>
#include <cubmark/FieldLess.hpp>
#include <cubmark/ResultMedian.hpp>
#include <cubmark/ResultAverage.hpp>

namespace cb
{

FullViewBuilder::FullViewBuilder() :
	fieldStatisticsSize(sizeof(fieldStatistics)/sizeof(ResultStatistic*))
{
	initFieldStatistics();
}

FullViewBuilder::~FullViewBuilder()
{
}

void FullViewBuilder::parseParameter(const std::string &, const std::string &)
{
}

void FullViewBuilder::create(SuiteResults& suiteResults, std::ostream& out)
{
	using namespace std;

	const SuiteSpecification& suiteSpec(suiteResults.getSpecification());
	const size_t methodCnt = suiteSpec.getMethodCnt();
	const size_t caseCount = suiteSpec.getCaseCnt();

	out << setprecision(10) << "#";

	for(size_t i = 0; i < (sizeof(fieldWidths))/sizeof(fieldWidths[0]); ++i)
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
			writeCase(out, caseResults.getMethodSamples(i));
		}
		out << '\n';
	}
}

void FullViewBuilder::writeCase(std::ostream& out, const SamplesRangeType& samples)
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

	writeLeastErrorResult(out, samples);
	out << '\n';
}

void FullViewBuilder::writeField(
		std::ostream& out, size_t fieldIdx, const SamplesRangeType& samples)
{
	ResultStatistic& resultStatistic = *fieldStatistics[fieldIdx];
	resultStatistic.compute(samples);
	out << std::setw(fieldWidths[fieldIdx]) << resultStatistic;
}

void FullViewBuilder::writeLeastErrorResult(
		std::ostream& out, const SamplesRangeType& samples)
{
	using std::ios_base;
	const std::streamsize oldPrecision = out.precision();

	less<double, &Result::getRelativeError> lessError;
	SamplesType::const_iterator best =
			std::min_element(samples.first, samples.second, lessError);

	out.setf(ios_base::scientific);
	out.precision(10);
	out << std::setw(fieldWidths[10]) << best->getResult();
	out << std::setw(fieldWidths[11]) << best->getAbsoluteErrorEstimate();
	out << std::setw(fieldWidths[12]) << best->getAbsoluteError();
	out << std::setw(fieldWidths[13]) << best->getRelativeError();
	out << std::setw(fieldWidths[14]) << best->classification();
	out.unsetf(ios_base::scientific);
	out.precision(oldPrecision);
}

void FullViewBuilder::initFieldStatistics()
{
	fieldStatistics[0].reset(resultMedian(&Result::getRelativeTolerance));
	fieldStatistics[1].reset(resultAverage<double>(&Result::isEfficient));
	fieldStatistics[2].reset(resultAverage<double>(&Result::isErrorEstimationEfficient));
	fieldStatistics[3].reset(resultAverage<double>(&Result::isRobust));
	fieldStatistics[4].reset(resultAverage<double>(&Result::isFallibleMinor));
	fieldStatistics[5].reset(resultAverage<double>(&Result::isFallibleMajor));
	fieldStatistics[6].reset(resultMedian(&Result::getCallCnt));
	fieldStatistics[7].reset(resultAverage(&Result::getCallCnt));
	fieldStatistics[8].reset(resultMedian(&Result::getCpuTime));
	fieldStatistics[9].reset(resultAverage(&Result::getCpuTime));
}

const int FullViewBuilder::fieldWidths[] = {
	6, 5, 5, 5, 5, 5, 11, 11, 8, 8, 18, 18, 18, 18, 5
};

const char *FullViewBuilder::fieldTitles[] = {
		"RET", "EFF", "EEP", "RBST", "UNRm", "UNRM", "CCNT", "CCAVG", "CPU",
		"CAVG", "Best Result", "Abs.E.E.", "Abs.Err.", "Rel.Err.", "CLASS"
};

const double FullViewBuilder::factors[] = {
	1.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0
};

}

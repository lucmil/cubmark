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

#include <iomanip>

#include <cubmark/HistogramViewBuilder.h>
#include <cubmark/IncompleteError.h>
#include <cubmark/InvalidNameError.h>

#include <cubmark/debug.h>
#include <cubmark/CaseResults.h>
#include <cubmark/SuiteResults.h>
#include <cubmark/SuiteSpecification.h>
#include <cubmark/Result.h>
#include <cubmark/ResultMedian.hpp>
#include <cubmark/ResultAverage.hpp>
#include <cubmark/ResultSelect.hpp>
#include <cubmark/algorithm.hpp>

namespace cb
{

HistogramViewBuilder::HistogramViewBuilder() :
	ViewBuilder(),
	xField(0),
	yField(0)
{
	initResultFields();
}

HistogramViewBuilder::~HistogramViewBuilder()
{
}

void HistogramViewBuilder::parseParameter(const std::string &name,
			const std::string &value)
{
	if(name == "x")
	{
		setXField(value);
	}
	else if(name == "y")
	{
		setYField(value);
	}
	else if(name == "caption")
	{
		LOG(TRACE, "Histogram caption: \"" << value << '"');
		caption = value;
	}
	else
	{
		LOG(FATAL, "No view option \"" << name << '"');
		throw InvalidNameError("Inalid view option.");
	}
}

void HistogramViewBuilder::setXField(const std::string &xFieldName)
{
	const FieldStatisticsType::const_iterator i = fieldStatistics.find(xFieldName);
	LOG(TRACE, "Histogram X axis: " << xFieldName);
	CHECK(i != fieldStatistics.end(),
			InvalidNameError("No case field by that name."));

	xLabel = i->first;
	xField = i->second;
}

void HistogramViewBuilder::setYField(const std::string &yFieldName)
{
	const FieldStatisticsType::const_iterator i = fieldStatistics.find(yFieldName);
	LOG(TRACE, "Histogram Y axis: " << yFieldName);
	CHECK(i != fieldStatistics.end(),
			InvalidNameError("No result field by that name."));

	yLabel = i->first;
	yField = i->second;
}

void HistogramViewBuilder::create(SuiteResults& suiteResults,
		std::ostream& ostream)
{
	using namespace std;

	CHECK(xField, IncompleteError("No X axis field chosen"));
	CHECK(yField, IncompleteError("No Y axis field chosen"));

	const SuiteSpecification& suiteSpec(suiteResults.getSpecification());
	const size_t methodCnt = suiteSpec.getMethodCnt();
	const size_t caseCnt = suiteSpec.getCaseCnt();

	if(!caption.empty())
	{
		ostream << "# Caption : "<< caption <<"\n";
	}

	ostream << "# X Label : "<< xLabel <<"\n"
			"# Y Label : "<< yLabel <<"\n"
			"Method";

	for(size_t m = 0; m < methodCnt; ++m)
	{
		ostream << '\t' << suiteSpec.getMethod(m).getName();
	}
	ostream << '\n';

	for(size_t i = 0; i < caseCnt; ++i)
	{
		CaseResults& caseResults = suiteResults.getCaseResults(i);
		SamplesRangeType xSamples = caseResults.getMethodSamples(0);
		xField->compute(xSamples);
		ostream << *xField;

		for(size_t j = 0; j < methodCnt; ++j)
		{
			SamplesRangeType ySamples = caseResults.getMethodSamples(j);
			yField->compute(ySamples);
			ostream << '\t' << *yField;
		}
		ostream << '\n';
	}
}

/** \todo These bits should be moved to a factory class
 */
void HistogramViewBuilder::initResultFields()
{
	SamplesType::iterator (*minError)(SamplesType::iterator, SamplesType::iterator) = 0;
	minError = &minField<double, &Result::getAbsoluteError> ;

	rfArr[0].reset(resultAverage<double>(&Result::isEfficient));
	rfArr[1].reset(resultMedian(&Result::isErrorEstimationEfficient));
	rfArr[2].reset(resultAverage<double>(&Result::isRobust));
	rfArr[3].reset(resultMedian(&Result::isFallibleMinor));
	rfArr[4].reset(resultMedian(&Result::isFallibleMajor));
	rfArr[5].reset(resultMedian(&Result::getCallCnt));
	rfArr[6].reset(resultMedian(&Result::getCpuTime));
	rfArr[7].reset(resultSelect(&Result::getResult, minError));
	rfArr[8].reset(resultSelect(&Result::getAbsoluteErrorEstimate, minError));
	rfArr[9].reset(resultSelect(&Result::getAbsoluteError, minError));
	rfArr[10].reset(resultSelect(&Result::getRelativeError, minError));
	rfArr[11].reset(resultSelect(&Result::getRelativeTolerance, minError));

	for(size_t i = 0; i < (sizeof rfArr)/(sizeof(rfArr[0])); ++i)
	{
		fieldStatistics.insert(std::make_pair(fieldNames[i], rfArr[i].get()));
	}
}

const char* HistogramViewBuilder::fieldNames[12] =
{
	"efficiency",
	"errorEstimateEff",
	"robustness",
	"failMinor",
	"failMajor",
	"callCnt",
	"cpuTime",
	"bestResult",
	"bestAbsErrEst",
	"bestAbsErr",
	"bestRelErr",
	"ret"
};

}

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

#ifndef CUBMARK_HISTOGRAMVIEWBUILDER_H
#define CUBMARK_HISTOGRAMVIEWBUILDER_H

#include <map>
#include <memory>

#include <cubmark/ViewBuilder.h>
#include <cubmark/ResultStatistic.h>

namespace cb
{

class HistogramViewBuilder :
	public ViewBuilder
{
public:
	HistogramViewBuilder();
	~HistogramViewBuilder();

	void parseParameter(const std::string &name,
			const std::string &value);

	void setXField(const std::string &xFieldName);
	void setYField(const std::string &yFieldName);

	void create(SuiteResults& results, std::ostream& ostream);

private:
	ResultStatistic *xField;
	ResultStatistic *yField;
	std::string xLabel;
	std::string yLabel;
	std::string caption;

	typedef std::map<std::string, ResultStatistic*> FieldStatisticsType;
	FieldStatisticsType fieldStatistics;

#ifdef HAVE_UNIQUE_PTR
	std::unique_ptr<ResultStatistic> rfArr[12];
#else
	std::auto_ptr<ResultStatistic> rfArr[12];
#endif

	static const char* fieldNames[12];
	void initResultFields();
};

}

#endif//CUBMARK_HISTOGRAMVIEWBUILDER_BUILDER_H

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

#ifndef CUBMARK_TESTPACKVIEWBUILDER_H
#define CUBMARK_TESTPACKVIEWBUILDER_H

#include <memory>

#include <cubmark/ViewBuilder.h>
#include <cubmark/ResultStatistic.h>

namespace cb
{

class TestpackViewBuilder :
	public ViewBuilder
{
public:
	TestpackViewBuilder();
	~TestpackViewBuilder();

	void create(SuiteResults& results, std::ostream& ostream);

private:
	void parseParameter(const std::string& name, const std::string& value);

	void writeCase(std::ostream& out, const SamplesRangeType& samples);
	void writeField(std::ostream& out, size_t fieldIdx,
			const SamplesRangeType& samples);

	const size_t fieldStatisticsSize;
	std::unique_ptr<ResultStatistic> fieldStatistics[8];
	void initFieldStatistics();

	/** \brief Field widths for each printed field
	 *
	 * Each of these has to be at least:
	 * - strlen(fieldTitles[i]) + 1
	 * - precision + 6 for scientific format
	 * - precision + 3 for fixed point format
	 * whichever is larger
	 */
	static const int fieldWidths[8];

	/** \brief Field titles
	 */
	static const char *fieldTitles[8];

	static const double factors[8];
};

}

#endif//CUBMARK_TESTPACKVIEWBUILDER_H

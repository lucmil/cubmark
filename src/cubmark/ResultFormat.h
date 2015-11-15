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

#ifndef CUBMARK_RESULT_FORMAT_H
#define CUBMARK_RESULT_FORMAT_H

#include <iosfwd>

namespace cb
{

class ResultStatistic;

template<class R>
class ResultMedian;

template<class R, class F>
class ResultQuantiles;

template<class R, class F>
class ResultAverage;

template<class R, class A>
class ResultSelect;

template<class R, class A>
class ResultAccumulate;

class ResultQuality;

/** \brief Pretty-printer for result statistics
 *
 * Visitor class for output
 */
class ResultFormat
{
public:
	ResultFormat(std::ostream& out);
	virtual ~ResultFormat();

	void write(const ResultStatistic* resultStatistic);

	template<class R>
	inline
	void write(const ResultMedian<R>* resultMedian);

	template<class R, class T>
	inline
	void write(const ResultQuantiles<R, T>* resultQuantiles);

	template<class R, class F>
	inline
	void write(const ResultAverage<R, F>* resultAverage);

	inline
	void write(const ResultQuality* resultQuality);

	template<class R, class A>
	inline
	void write(const ResultSelect<R, A>* resultSelect);

	template<class R, class F>
	inline
	void write(const ResultAccumulate<R, F>* resultAccumulate);
private:
	std::ostream& out;
};

std::ostream& operator<<(std::ostream& output, const ResultStatistic& result);

}

#endif//CUBMARK_RESULT_FORMAT_H


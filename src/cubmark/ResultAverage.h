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

#ifndef CUBMARK_RESULT_AVERAGE_H
#define CUBMARK_RESULT_AVERAGE_H

#include <cubmark/ResultStatistic.h>

namespace cb
{

template<class Ret, class F>
class ResultAverage :
	public ResultStatistic
{
public:
	typedef F (Result::*MemberPtr)() const;

	ResultAverage(MemberPtr memberFunction);
	~ResultAverage();

	void compute(SamplesRangeType samples);
	void write(ResultFormat& resultFormat) const;
	Ret getFieldAverage() const;
private:
	Ret fieldAverage;
	const MemberPtr memberFunction;
};

template<class T, class F>
inline
ResultAverage<T, F>* resultAverage(F (Result::*)() const);

template<class T>
inline
ResultAverage<T, T>* resultAverage(T (Result::*)() const);

}

#endif//CUBMARK_RESULT_AVERAGE_H


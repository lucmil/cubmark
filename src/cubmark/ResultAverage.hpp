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

#include <cubmark/ResultAverage.h>

#ifndef CUBMARK_RESULT_AVERAGE_HPP
#define CUBMARK_RESULT_AVERAGE_HPP

#include <limits>
#include <cstddef>

#include <cubmark/ResultFormat.hpp>

namespace cb
{

template<class Ret, class F>
ResultAverage<Ret, F>::ResultAverage(F (Result::*memberFunction)() const) :
	memberFunction(memberFunction)
{
}

template<class Ret, class F>
ResultAverage<Ret, F>::~ResultAverage()
{
}

template<class Ret, class F>
void ResultAverage<Ret, F>::write(ResultFormat& resultFormat) const
{
	resultFormat.write(this);
}

template<class Ret, class F>
void ResultAverage<Ret, F>::compute(SamplesRangeType samples)
{
	const ptrdiff_t sampleCnt = std::distance(samples.first, samples.second);
	Ret sum = 0;
	for(; samples.first != samples.second; ++samples.first)
	{
		sum += static_cast<Ret>((*(samples.first).*memberFunction)());
	}

	fieldAverage = sum / static_cast<Ret>(sampleCnt);
}

template<class Ret, class F>
Ret ResultAverage<Ret, F>::getFieldAverage() const
{
	return fieldAverage;
}

template<class T, class F>
ResultAverage<T, F>* resultAverage(F (Result::*memberFunction)() const)
{
	return new ResultAverage<T, F>(memberFunction);
}

template<class T>
ResultAverage<T, T>* resultAverage(T (Result::*memberFunction)() const)
{
	return resultAverage<T, T>(memberFunction);
}

}

#endif//CUBMARK_RESULT_AVERAGE_HPP


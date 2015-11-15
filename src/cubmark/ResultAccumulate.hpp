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

#include <cubmark/ResultAccumulate.h>

#ifndef CUBMARK_RESULTACCUMULATE_HPP
#define CUBMARK_RESULTACCUMULATE_HPP

#include <vector>
#include <cubmark/ResultFormat.hpp>

namespace cb
{

template<class Ret, class T>
ResultAccumulate<Ret, T>::ResultAccumulate(const Ret& init,
		T (Result::*memberFunction)() const) :
	init(init),
	accumulator(init),
	memberFunction(memberFunction)
{
}

template<class Ret, class T>
ResultAccumulate<Ret, T>::~ResultAccumulate()
{
}

template<class Ret, class T>
void ResultAccumulate<Ret, T>::write(ResultFormat& resultFormat) const
{
	resultFormat.write(this);
}

template<class Ret, class T>
void ResultAccumulate<Ret, T>::compute(SamplesRangeType samples)
{
	accumulator = init;
	for(; samples.first != samples.second; ++samples.first)
	{
		accumulator = accumulator +
				static_cast<Ret>((*(samples.first).*memberFunction)());
	}
}

template<class Ret, class T>
const Ret& ResultAccumulate<Ret, T>::getAccumulator() const
{
	return accumulator;
}

template<class Ret, class T>
inline
ResultAccumulate<Ret, T>* resultAccumulate(unsigned q, T (Result::*memberFunction)() const)
{
	return new ResultAccumulate<Ret, T>(q, memberFunction);
}

template<class T>
inline
ResultAccumulate<T, T>* resultAccumulate(unsigned q, T (Result::*memberFunction)() const)
{
	return resultAccumulate<T, T>(q, memberFunction);
}

}

#endif//CUBMARK_RESULTACCUMULATE_HPP


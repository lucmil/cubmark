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

#include <cubmark/ResultMedian.h>

#ifndef CUBMARK_RESULT_MEDIAN_HPP
#define CUBMARK_RESULT_MEDIAN_HPP

#include <cubmark/algorithm.hpp>
#include <cubmark/ResultFormat.hpp>

namespace cb
{

template<class Ret>
ResultMedian<Ret>::ResultMedian(Ret (Result::*memberFunction)() const) :
	fieldLess(memberFunction),
	memberFunction(memberFunction)
{
}

template<class Ret>
ResultMedian<Ret>::~ResultMedian()
{
}

template<class Ret>
void ResultMedian<Ret>::write(ResultFormat& resultFormat) const
{
	resultFormat.write(this);
}

template<class Ret>
void ResultMedian<Ret>::compute(SamplesRangeType samples)
{
	SamplesRangeType mElements =
			median(samples.first, samples.second, fieldLess);

	this->fieldMedian = Ret(computeMedian(mElements));
}

template<class Ret>
Ret ResultMedian<Ret>::getFieldMedian() const
{
	return fieldMedian;
}

template<class Ret>
Ret ResultMedian<Ret>::computeMedian(const SamplesRangeType& m)
{
	if(m.first == m.second)
	{
		// Median within set
		return (*(m.first).*memberFunction)();
	}
	else
	{
		// Median out of set
		return ((*(m.first).*memberFunction)()+(*(m.second).*memberFunction)())
				/ static_cast<Ret>(2);;
	}
}

template<class Ret>
inline
ResultMedian<Ret>* resultMedian(Ret (Result::*memberFunction)() const)
{
	return new ResultMedian<Ret>(memberFunction);
}

}

#endif//CUBMARK_RESULT_MEDIAN_HPP


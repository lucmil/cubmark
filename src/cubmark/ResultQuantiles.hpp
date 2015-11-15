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

#include <cubmark/ResultQuantiles.h>

#ifndef CUBMARK_RESULTQUANTILES_HPP
#define CUBMARK_RESULTQUANTILES_HPP

#include <vector>
#include <cubmark/algorithm.hpp>
#include <cubmark/ResultFormat.hpp>

namespace cb
{

template<class Ret, class T>
ResultQuantiles<Ret, T>::ResultQuantiles(unsigned q,
		T (Result::*memberFunction)() const) :
	q(q),
	fieldQuantiles(q-1, 0),
	fieldLess(memberFunction),
	memberFunction(memberFunction)
{
}

template<class Ret, class T>
ResultQuantiles<Ret, T>::~ResultQuantiles()
{
}

template<class Ret, class T>
void ResultQuantiles<Ret, T>::write(ResultFormat& resultFormat) const
{
	resultFormat.write(this);
}

template<class Ret, class T>
void ResultQuantiles<Ret, T>::compute(SamplesRangeType samples)
{
	std::vector<SamplesRangeType> qElements(
			quantiles(samples.first, samples.second, q, fieldLess));

	std::vector<SamplesRangeType>::const_iterator i = qElements.begin();
	typename std::vector<Ret>::iterator j = fieldQuantiles.begin();
	for(; i != qElements.end(); ++i, ++j)
	{
		*j = Ret(computeQuantile(*i));
	}
}

template<class Ret, class T>
const std::vector<Ret>& ResultQuantiles<Ret, T>::getFieldQuantiles() const
{
	return fieldQuantiles;
}

template<class Ret, class T>
Ret ResultQuantiles<Ret, T>::computeQuantile(const SamplesRangeType& q)
{
	return ((*(q.first).*memberFunction)()+(*(q.second).*memberFunction)())
			/ static_cast<Ret>(2);;
}

template<class Ret, class T>
inline
ResultQuantiles<Ret, T>* resultQuantiles(unsigned q, T (Result::*memberFunction)() const)
{
	return new ResultQuantiles<Ret, T>(q, memberFunction);
}

template<class T>
inline
ResultQuantiles<T, T>* resultQuantiles(unsigned q, T (Result::*memberFunction)() const)
{
	return resultQuantiles<T, T>(q, memberFunction);
}

}

#endif//CUBMARK_RESULTQUANTILES_HPP


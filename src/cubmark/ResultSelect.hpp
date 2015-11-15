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

#include <cubmark/ResultSelect.h>

#ifndef CUBMARK_RESULT_SELECT_HPP
#define CUBMARK_RESULT_SELECT_HPP

#include <cubmark/algorithm.hpp>
#include <cubmark/ResultFormat.hpp>

namespace cb
{

template<class Ret, class Algo>
ResultSelect<Ret, Algo>::ResultSelect(
		Ret (Result::*memberFunction)() const,
		Algo algorithm) :
	algorithm(algorithm),
	memberFunction(memberFunction)
{
}

template<class Ret, class Algo>
ResultSelect<Ret, Algo>::~ResultSelect()
{
}

template<class Ret, class Algo>
void ResultSelect<Ret, Algo>::write(ResultFormat& resultFormat) const
{
	resultFormat.write(this);
}

template<class Ret, class Algo>
Ret ResultSelect<Ret, Algo>::getSelectedField() const
{
	return selectedField;
}

template<class Ret, class Algo>
void ResultSelect<Ret, Algo>::compute(SamplesRangeType samples)
{
	SamplesType::iterator element =
			algorithm(samples.first, samples.second);

	this->selectedField = (*element.*memberFunction)();
}

template<class Ret, class Algo>
inline
ResultSelect<Ret, Algo>* resultSelect(
		Ret (Result::*memberFunction)() const,
		Algo algorithm)
{
	return new ResultSelect<Ret, Algo>(memberFunction, algorithm);
}

}

#endif//CUBMARK_RESULT_SELECT_HPP


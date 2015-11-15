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

#ifndef CUBMARK_RESULT_SELECT_H
#define CUBMARK_RESULT_SELECT_H

#include <cubmark/types.h>
#include <cubmark/ResultStatistic.h>
#include <cubmark/FieldLess.hpp>

namespace cb
{

template<class Ret, class Algo>
class ResultSelect :
	public ResultStatistic
{
public:
	typedef Ret (Result::*MemberPtr)() const;

	ResultSelect(MemberPtr memberFunction, Algo algorithm);
	~ResultSelect();

	void compute(SamplesRangeType samples);
	void write(ResultFormat& resultFormat) const;

	Ret getSelectedField() const;
private:
	Algo algorithm;
	Ret selectedField;
	const MemberPtr memberFunction;
};

template<class T, class A>
inline
ResultSelect<T, A>* resultFind(T (Result::*memberFunction)() const, A algorithm);

}

#endif//CUBMARK_RESULT_SELECT_H


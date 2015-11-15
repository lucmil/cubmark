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

#ifndef CUBMARK_RESULT_MEDIAN_H
#define CUBMARK_RESULT_MEDIAN_H

#include <cubmark/types.h>
#include <cubmark/ResultStatistic.h>
#include <cubmark/FieldLess.hpp>

namespace cb
{

template<class Ret>
class ResultMedian :
	public ResultStatistic
{
public:
	typedef Ret (Result::*MemberPtr)() const;

	ResultMedian(MemberPtr memberFunction);
	~ResultMedian();

	void compute(SamplesRangeType samples);
	void write(ResultFormat& resultFormat) const;
	Ret getFieldMedian() const;
private:
	Ret computeMedian(const SamplesRangeType& m);

	Ret fieldMedian;
	FieldLess<Ret> fieldLess;
	const MemberPtr memberFunction;
};

template<class T>
inline
ResultMedian<T>* resultMedian(T (Result::*)() const);
}

#endif//CUBMARK_RESULT_MEDIAN_H


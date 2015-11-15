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

#ifndef CUBMARK_RESULTQUANTILES_H
#define CUBMARK_RESULTQUANTILES_H

#include <cubmark/types.h>
#include <cubmark/ResultStatistic.h>
#include <cubmark/FieldLess.hpp>
#include <vector>

namespace cb
{

template<class Ret, class T>
class ResultQuantiles :
	public ResultStatistic
{
public:
	typedef T (Result::*MemberPtr)() const;

	ResultQuantiles(unsigned q, MemberPtr memberFunction);
	~ResultQuantiles();

	void compute(SamplesRangeType samples);
	void write(ResultFormat& resultFormat) const;
	const std::vector<Ret>& getFieldQuantiles() const;
private:
	Ret computeQuantile(const SamplesRangeType& m);

	unsigned q;
	std::vector<Ret> fieldQuantiles;
	FieldLess<T> fieldLess;
	const MemberPtr memberFunction;
};

template<class R, class T>
inline
ResultQuantiles<R, T>* resultQuantiles(unsigned q, T (Result::*)() const);

template<class T>
inline
ResultQuantiles<T, T>* resultQuantiles(unsigned q, T (Result::*)() const);

}

#endif//CUBMARK_RESULTQUANTILES_H


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

#include <cubmark/FieldLess.h>

#ifndef CUBMARK_FIELD_LESS_HPP
#define CUBMARK_FIELD_LESS_HPP

namespace cb
{

template<class Ret>
FieldLess<Ret>::FieldLess(FieldPtr memberFunction) :
	memberFunction(memberFunction)
{
}

template<class Ret>
inline
bool FieldLess<Ret>::operator()(const Result& l, const Result& r) const
{
	return std::less<Ret>()((l.*memberFunction)(), (r.*memberFunction)());
}

template<class Ret, Ret (Result::*MemFun)() const>
inline
bool less<Ret, MemFun>::operator()(const Result& l, const Result& r) const
{
	return std::less<Ret>()((l.*MemFun)(), (r.*MemFun)());
}

}

#endif//CUBMARK_FIELD_LESS_HPP


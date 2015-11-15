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

#ifndef CUBMARK_FIELD_LESS_H
#define CUBMARK_FIELD_LESS_H

#include <functional>

namespace cb
{

class Result;

/** \brief Comparison functor for use with STL algorithms
 */
template<class Ret, Ret (Result::*MemFun)() const>
class less
:	public std::binary_function<Result, Result, bool>
{
public:
	inline
	bool operator()(const Result& l, const Result& r) const;
};

/** \brief Comparison functor for use with STL algorithms
 */
template<class Ret>
class FieldLess
:	public std::binary_function<Result, Result, bool>
{
public:
	/** \brief Pointer to Result const member function.
	 */
	typedef Ret (Result::*FieldPtr)() const;

	/** \brief Constructor
	 *
	 * \param fieldPtr Pointer to a const member function of Result
	 */
	FieldLess(FieldPtr memberFunction);

	inline
	bool operator()(const Result& l, const Result& r) const;

	const FieldPtr memberFunction;
};

}

#endif//CUBMARK_FIELD_LESS_H


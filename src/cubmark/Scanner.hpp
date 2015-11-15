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

#ifndef CUBMARK_SCANNER_HPP
#define CUBMARK_SCANNER_HPP
#include <cubmark/Scanner.h>

namespace cb
{

template<class T, class S>
T Scanner<T, S>::scan(const S *str)
{
	T val;

	arg_stream.clear();
	arg_stream.str(str);
	arg_stream >> val;

	if(arg_stream.bad())
	{
		throw ParsingError("Error while reading argument.");
	}

	return val;
}

template<class T, class S>
T Scanner<T, S>::operator()(const std::basic_string<S> &str)
{
	return scan(str.c_str());
}

template<class T, class S>
T Scanner<T, S>::operator()(const S *str)
{
	return scan(str);
}

}

#endif//CUBMARK_SCANNER_HPP

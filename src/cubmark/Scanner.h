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

#ifndef CUBMARK_SCANNER_H
#define CUBMARK_SCANNER_H

#include <stdexcept>
#include <sstream>
#include <string>

namespace cb
{

template<class T, class S = char>
class Scanner
{
public:
	class ParsingError :
		public std::runtime_error
	{
	public:
		ParsingError(const char *what) :
			std::runtime_error(what)
		{
		}
	};

	T operator()(const std::basic_string<S> &str);
	T operator()(const S *str);
private:
	T scan(const S *str);
	std::basic_istringstream<S> arg_stream;
};

template<>
class Scanner<double, char>
{
public:
	class ParsingError :
		public std::runtime_error
	{
	public:
		ParsingError(const char *what) :
			std::runtime_error(what)
		{
		}
	};

	double operator()(const std::basic_string<char> &str);
	double operator()(const char *str);
private:
	double scan(const char *str);
};

}

#endif//CUBMARK_SCANNER_H

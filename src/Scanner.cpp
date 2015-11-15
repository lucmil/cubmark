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

#include <cubmark/Scanner.h>

extern "C"
{
#include <stdlib.h>
#include <errno.h>
#include <string.h>
}

namespace cb
{

double Scanner<double, char>::scan(const char *str)
{
	char *endptr = 0;

	errno = 0;
	double val = strtod(str, &endptr);
	unsigned l_errno = errno;
	if(l_errno)
	{
		throw ParsingError(strerror(l_errno));
	}

	if(endptr == str)
	{
		throw ParsingError("No digits found.");
	}

	return val;
}

double Scanner<double, char>::operator()(const std::basic_string<char> &str)
{
	return scan(str.c_str());
}

double Scanner<double, char>::operator()(const char *str)
{
	return scan(str);
}

}


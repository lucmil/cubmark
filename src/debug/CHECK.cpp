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

#include <cubmark/config.h>
#include <cubmark/CHECK.hpp>

#ifndef CUBMARK_NDEBUG
#ifdef CUBMARK_USE_EXCEPTIONS

namespace cb
{

void CHECK_(bool expression, const char *error_message, const char *prefix)
throw(std::runtime_error)
{
	CHECK_(expression, std::runtime_error(error_message), prefix);
}

}

#else //CUBMARK_USE_EXCEPTIONS

namespace cb
{

void CHECK_(bool expression, const char *error_message, const char *prefix)
throw()
{
	if(!expression)
	{
		LOG_RAW(FATAL, "Assertion failed at "<< prefix <<"\nError message: "
				<< error_message);
		std::terminate();
	}
}

}

#endif//CUBMARK_USE_EXCEPTIONS
#else //CUBMARK_NDEBUG

namespace cb
{

#ifdef  CUBMARK_USE_EXCEPTIONS

template<class E>
void CHECK_(bool, const E&, const char *)
throw(E)
{
}

#else //CUBMARK_USE_EXCEPTIONS

void CHECK_(bool a, const char *, const char *)
throw()
{
}

#endif//CUBMARK_USE_EXCEPTIONS

}

#endif//CUBMARK_NDEBUG


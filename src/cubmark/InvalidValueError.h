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

#ifndef CUBMARK_INVALIDVALUEERROR_H
#define CUBMARK_INVALIDVALUEERROR_H

#include <stdexcept>

namespace cb
{

/** \brief Parameter value is invalid
 *
 * Thrown whenever a parameter value could not be parsed or the parsed value
 * is invalid (i.e. out of allowed range).
 */
class InvalidValueError :
	public std::domain_error
{
public:
	InvalidValueError(const char *msg = "");
};

}
#endif//CUBMARK_INVALIDVALUEERROR_H

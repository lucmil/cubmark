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

#ifndef CUBMARK_TYPES_H
#define CUBMARK_TYPES_H

#include <deque>
#include <utility>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <random>
#else
#include <tr1/random>
#endif

/**
 * \brief Main namespace of the Benchmark suite
 */
namespace cb
{

class Result;
class CaseResults;

typedef std::deque<Result> SamplesType;
typedef std::pair<SamplesType::iterator, SamplesType::iterator>
		SamplesRangeType;
typedef std::pair<SamplesType::const_iterator, SamplesType::const_iterator>
		ConstRangeType;

#ifdef __GXX_EXPERIMENTAL_CXX0X__
namespace tr1 = std;
#else
namespace tr1 = std::tr1;
#endif

}

#endif//CUBMARK_TYPES_H


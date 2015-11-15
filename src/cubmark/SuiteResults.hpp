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

#include <cubmark/SuiteResults.h>

#ifndef CUBMARK_SUITERESULTS_HPP
#define CUBMARK_SUITERESULTS_HPP

#include <boost/serialization/deque.hpp>

/**
 * \brief Main namespace of the Benchmark suite
 */
namespace cb
{

template<class Archive>
void SuiteResults::serialize(Archive& archive, const unsigned int /*version*/)
{
	archive & this->suiteSpecification;
	archive & this->suiteResults;
}

}

#endif//CUBMARK_SUITERESULTS_HPP



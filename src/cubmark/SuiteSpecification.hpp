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

#include <cubmark/SuiteSpecification.h>

#ifndef CUBMARK_SUITESPECIFICAITON_HPP
#define CUBMARK_SUITESPECIFICAITON_HPP

#include <boost/serialization/vector.hpp>

/**
 * \brief Main namespace of the Benchmark suite
 */
namespace cb
{

template<class Archive>
void SuiteSpecification::serialize(Archive& archive, const unsigned int /*version*/)
{
	archive & testFunctor;
	archive & boundary;
	archive & sampleLimit;
	archive & callLimit;
	archive & caseSpecs;
	archive & methods;
}

}

#endif//CUBMARK_SUITESPECIFICAITON_HPP



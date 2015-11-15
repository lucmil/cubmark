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

#include <cubmark/Definition.h>

#ifndef CUBMARK_DEFINITION_HPP
#define CUBMARK_DEFINITION_HPP

/**
 * \brief Main namespace of the Benchmark suite
 */
namespace cb
{

template<class Archive>
void Definition::serialize(Archive& archive, const unsigned int /*version*/)
{
	archive & this->name;
	archive & this->parameters;
}

}

#endif//CUBMARK_DEFINITION_HPP



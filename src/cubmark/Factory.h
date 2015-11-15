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

#ifndef CUBMARK_FACTORY_H
#define CUBMARK_FACTORY_H

#include <string>
#include <map>

#include <cubmark/Definition.h>

namespace cb
{

template<class D, class P, class E>
class Factory
{
public:
	typedef std::map<std::string, E> MapType;

	P* getByDefinition(const Definition& definition) const;
	P* getByName(const std::string& name) const;
	P* getById(E id) const;
protected:
	MapType idMap;
};

}
#endif//CUBMARK_FACTORY_H

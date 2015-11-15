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

#include <cubmark/Factory.h>

#ifndef CUBMARK_FACTORY_HPP
#define CUBMARK_FACTORY_HPP

#include <cubmark/debug.h>

namespace cb
{

template<class D, class P, class E>
P* Factory<D, P, E>::getByDefinition(const Definition& definition) const
{
	P* builder = getByName(definition.getName());
	return builder;
}

template<class D, class P, class E>
P* Factory<D, P, E>::getByName(const std::string& name) const
{
	const typename MapType::const_iterator i = idMap.find(name);
	if(i != idMap.end())
	{
		return static_cast<const D* const>(this)->getById(i->second);
	}
	return 0;
}

template<class D, class P, class E>
P* Factory<D, P, E>::getById(E id) const
{
	return static_cast<const D* const>(this)->getById(id);
}

}

#endif//CUBMARK_FACTORY_HPP


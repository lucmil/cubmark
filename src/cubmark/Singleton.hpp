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

#include <cubmark/Singleton.h>

#ifndef CUBMARK_SINGLETON_HPP
#define CUBMARK_SINGLETON_HPP

namespace cb
{

template<class D>
Singleton<D>::Singleton()
{
}

template<class D>
D & Singleton<D>::getInstance()
{
	if(!instance.get())
	{
		instance.reset(new D);
	}
	return *instance.get();
}

template<class D>
std::unique_ptr<D> Singleton<D>::instance;

}

#endif//CUBMARK_SINGLETON_HPP

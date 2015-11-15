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

#include <cubmark/adapter/cxx0x/Adapter.h>

#ifndef CUBMARK_ADAPTER_VARIADIC_HPP
#define CUBMARK_ADAPTER_VARIADIC_HPP

#include <cubmark/adapter/cxx0x/AdapterFtorBase.hpp>

namespace cb
{

template<int K, class FO, class R, class ...A>
Adapter<K, FO, R, A...>::Adapter()
{
}

template<int K, class FO, class R, class ...A>
void Adapter<K, FO, R, A...>::setFunctor(const FO& functor)
{
	Adapter<K, FO, R, A...>::functor = functor;
}

template<int K, class FO, class R, class ...A>
typename FuncPtr<R, A...>::Type
Adapter<K, FO, R, A...>::getPtr() const
{
	return &Adapter<K, FO, R, A...>::adapter;
}

template<int K, class FO, class R, class ...A>
AdapterSlot* Adapter<K, FO, R, A...>::getNext() const
{
	if(K)
	{
		return static_cast<AdapterSlot*>(new Adapter<K-1, FO, R, A...>());
	}
	else
	{
		return 0;
	}
}

template<int K, class FO, class R, class ...A>
R Adapter<K, FO, R, A...>::adapter(A... a) throw()
{
	return Adapter<K, FO, R, A...>::functor(a...);
}

template<int K, class FO, class R, class ...A>
FO Adapter<K, FO, R, A...>::functor;

}
#endif//CUBMARK_ADAPTER_VARIADIC_HPP

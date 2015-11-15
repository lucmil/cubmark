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

#include <adapter/cxx0x/NullAdapter.h>

#ifndef CUBMARK_NULL_ADAPTER_HPP
#define CUBMARK_NULL_ADAPTER_HPP

namespace cb
{

template<class FO, class R, class ...A>
NullAdapter<FO, R, A...>::NullAdapter()
{
}

template<class FO, class R, class ...A>
AdapterSlot* NullAdapter<FO, R, A...>::getNext() const
{
	return 0;
}

template<class FO, class R, class ...A>
typename FuncPtr<R, A...>::Type NullAdapter<FO, R, A...>::getPtr() const
{
	return 0;
}

template<class FO, class R, class ...A>
void NullAdapter<FO, R, A...>::setFunctor(const FO& /*functor*/)
{
}

}
#endif//CUBMARK_NULL_ADAPTER_HPP

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

#ifndef CUBMARK_ADAPTERBASE_H
#define CUBMARK_ADAPTERBASE_H

#include <cubmark/adapter/AdapterSlot.h>
#include <cubmark/adapter/cxx0x/FuncPtr.h>

namespace cb
{

/** \brief Common interface dependent on function pointer type
 *
 * Every template instance of a particular function pointer type pair
 * implements this interface.
 *
 * \tparam FO functor class
 * \tparam PTR function pointer type
 */
template<class R, class ...A>
class AdapterBase :
	public AdapterSlot
{
public:
	virtual typename FuncPtr<R, A...>::Type getPtr() const = 0;
};

}
#endif//CUBMARK_ADAPTERBASE_H

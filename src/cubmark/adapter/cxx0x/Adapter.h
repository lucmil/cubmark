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

#ifndef CUBMARK_ADAPTER_VARIADIC_H
#define CUBMARK_ADAPTER_VARIADIC_H

#include <cubmark/adapter/cxx0x/AdapterFtorBase.h>
#include <cubmark/adapter/cxx0x/NullAdapter.h>

namespace cb
{

/** \brief Adapter class template for binary functions
 *
 * \tparam K template instance number
 * \tparam FO functor class
 * \tparam R function return type
 * \tparam A function argument type pack
 */
template<int K, class FO, class R, class ...A>
class Adapter
:   public AdapterFtorBase<FO, R, A...>
{
public:
	Adapter();
	typedef typename FuncPtr<R, A...>::Type FuncPtrType;

	void setFunctor(const FO& functor);
	FuncPtrType getPtr() const;
	AdapterSlot* getNext() const;

private:
	Adapter(const Adapter&);
	Adapter& operator=(const Adapter&);

	static R adapter(A...) throw();
	static FO functor;
};

/**
 * \brief Recursive template instantiation NullAdapter for binary function template
 */
template<class FO, class R, class ...A>
class Adapter<-1, FO, R, A...>
:   public NullAdapter<FO, R, A...>
{
};

}

#endif//CUBMARK_ADAPTER_VARIADIC_H

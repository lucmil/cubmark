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

#ifndef CUBMARK_ADAPTER_STL_HPP
#define CUBMARK_ADAPTER_STL_HPP

#include <cubmark/adapter/cxx0x/AdapterBase.h>
#include <cubmark/adapter/cxx0x/AdapterManager.hpp>

namespace cb
{

template<class FO, class R, class ...A>
void adapterSetFunctor(AdapterBase<R, A...>* adapter, const FO& functor)
{
	AdapterFtorBase<FO, R, A...>* slot =
			static_cast<AdapterFtorBase<FO, R, A...>*>(adapter);

	slot->setFunctor(functor);
}

template<class FO, class R, class ...A>
void adapter(AdapterBase<R, A...>*& ftorAdapter)
{
	AdapterManager<FO, R, A...>& manager =
			AdapterManager<FO, R, A...>::getInstance();

	ftorAdapter = static_cast<AdapterFtorBase<FO, R, A...>*>(manager.lockSlot());
}

template<class FO, class R, class ...A>
void adapter(AdapterFtorBase<FO, R, A...>*& ftorAdapter)
{
	AdapterManager<FO, R, A...>& manager =
			AdapterManager<FO, R, A...>::getInstance();

	ftorAdapter = static_cast<AdapterFtorBase<FO, R, A...>*>(manager.lockSlot());
}

/**
 * \brief Convienience function template for acquiring adapter locks to
 *        STL-style unary functors
 *
 * See cb::UnaryAdapter on how to instantiate a lock from the lock handle.
 * See \link adapter_function_template_stl.cpp \endlink for example code.
 *
 * \tparam UF unary functor class deduced from argument
 *            The class can be derived from std::unary_function.
 * \param f Functor instance
 */
template<class UF>
AdapterBase<typename UF::result_type, typename UF::argument_type>*
adapter(const UF& stlUnaryFunctor)
{
	typedef typename UF::result_type R;
	typedef typename UF::argument_type A;
	typedef AdapterFtorBase<UF, R, A> FtorBaseType;

	FtorBaseType* slot = 0;
	adapter(slot);
	slot->setFunctor(stlUnaryFunctor);
	return slot;
}

/**
 * \brief Convienience function template for acquiring adapter locks to
 *        STL-style binary functors
 *
 * See cb::BinaryAdapter on how to instantiate a lock from the lock handle.
 * See \link adapter_function_template_stl.cpp \endlink for example code.
 *
 * \tparam BF binary functor class deduced from argument
 *            The class can be derived from std::binary_function.
 * \param f Functor instance
 */
template<class BF>
AdapterBase<typename BF::result_type,
		typename BF::first_argument_type,
		typename BF::second_argument_type>*
adapter(const BF& stlBinaryFunctor)
{
	typedef typename BF::result_type R;
	typedef typename BF::first_argument_type A1;
	typedef typename BF::second_argument_type A2;
	typedef AdapterFtorBase<BF, R, A1, A2> FtorBaseType;

	FtorBaseType* slot = 0;
	adapter(slot);
	slot->setFunctor(stlBinaryFunctor);
	return slot;
}

}
#endif//CUBMARK_ADAPTER_STL_HPP

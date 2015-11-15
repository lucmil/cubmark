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

/** \file
 * \brief Convienience templates for lock template class deduction
 */
#ifndef CUBMARK_ADAPTER_TYPES_H
#define CUBMARK_ADAPTER_TYPES_H

#include <functional>

#ifdef __GXX_EXPERIMENTAL_CXX0X__
#include <cubmark/adapter/cxx0x/Adapter.h>
#include <cubmark/adapter/cxx0x/FuncPtr.h>
#else
#include <cubmark/adapter/Adapter.h>
#endif

namespace cb
{

/** \brief Convienence template for binary STL-like functors
 *
 * This template will deduce template parameters for an STL functor adapter
 *
 * Example usage:
 * \code
 * struct f : std::unary_functor<int, double> { * ... * };
 * UnaryAdapter<f>::Type fAdapter(adapter(f)));
 * double (*funcPtr)(int) = fAdapter.getPtr();
 * \endcode
 * \tparam FO functor class derived from std::unary_function
 */
template<class FO>
struct UnaryAdapter
{
	/** \brief Adapter interface for unary functor class FO
	 */
	typedef AdapterBase<
			typename FO::result_type,
			typename FO::argument_type> Type;

	/** \brief Adapter interface for unary functor class FO
	 */
	typedef AdapterFtorBase<FO,
			typename FO::result_type,
			typename FO::argument_type> FtorType;

	typedef typename FuncPtr<
			typename FO::result_type,
			typename FO::argument_type>::Type FuncPtrType;
};

/** \brief Convienence template for binary STL-like functors
 *
 * This template will deduce template parameters for an STL functor adapter
 *
 * Example usage:
 * \code
 * struct f : std::binary_functor<int, int, double> { ... };
 * BinaryAdapter<f>::Type fAdapter(adapter(f)));
 * double (*fPtr)(int) = fAdapter.getPtr();
 * \endcode
 *
 * \tparam FO functor class derived from std::binary_function
 */
template<class FO>
struct BinaryAdapter
{
	/** \brief Adapter interface for binary functor class FO
	 */
	typedef AdapterBase<
			typename FO::result_type,
			typename FO::first_argument_type,
			typename FO::second_argument_type> Type;

	/** \brief Adapter interface for binary functor class FO
	 */
	typedef AdapterFtorBase<FO,
			typename FO::result_type,
			typename FO::first_argument_type,
			typename FO::second_argument_type> FtorType;

	typedef typename FuncPtr<
			typename FO::result_type,
			typename FO::first_argument_type,
			typename FO::second_argument_type>::Type FuncPtrType;
};

}
#endif//CUBMARK_ADAPTER_TYPES_H

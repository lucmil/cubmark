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

#ifndef CUBMARK_ADAPTERTRAITS_H
#define CUBMARK_ADAPTERTRAITS_H

namespace cb
{

/** \brief Adapter traits
 *
 * Use a template specialization of AdapterTraits to override this value.
 *
 * For example, this snippet will allow you to use two different instances of the
 * cb::Constant functor simultaneously via two adapters
 * \code
 * namespace cb
 * {
 *
 * template<>
 * class AdapterTraits<Constant>
 * {
 * public:
 * 	enum LimitsType { SLOT_LIMIT = 2 };
 * };
 *
 * }
 *
 * ...
 * void somefunction()
 * {
 *     cb::Constant A(1), B(1);
 *     cb::BinaryAdapter<Constant>::FtorType a, b;
 *     cb::adapter(a, A);
 *     cb::adapter(b, B);
 *     (a->getPtr())(0, 0);
 *     (b->getPtr())(0, 0); // Would segfault if SLOT_LIMIT == 1
 * }
 * ...
 * \endcode
 *
 * \todo Method for determining number of required Adapters. A counter in
 *       cb::AdapterManager, conditionally compiled, could be useful.
 *
 * \tparam FO functor type of the adapter
 * \tparam R return type of the function
 * \tparam A... argument type pack of the function
 */
template<class FO, class R, class ...A>
class AdapterTraits
{
public:
	/** \brief Limits
	 */
	enum LimitsType
	{
		/** \brief Number generated functor adapters
		 *
		 * Set this to the maximum number of adapters used simultaneously.
		 */
		SLOT_LIMIT = 1
	};
};

}

#endif//CUBMARK_ADAPTERTRAITS_H

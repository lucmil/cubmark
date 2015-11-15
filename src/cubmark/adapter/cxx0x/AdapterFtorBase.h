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

#ifndef CUBMARK_ADAPTERFTORBASE_H
#define CUBMARK_ADAPTERFTORBASE_H

#include <cubmark/adapter/cxx0x/AdapterBase.h>

namespace cb
{

/** \brief Common functor type dependent methods
 *
 * This class contains code common for every template instance which depends on
 * the functor type.
 *
 * \tparam FO functor class
 * \tparam R function return value type
 * \tparam A argument type pack
 */
template<class FO, class R, class ...A>
class AdapterFtorBase :
	public AdapterBase<R, A...>
{
public:
	virtual void setFunctor(const FO& functor) = 0;
	void unlockSlot();
};

}
#endif//CUBMARK_ADAPTERFTORBASE_H

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

#ifndef CUBMARK_ADAPTERMANAGER_H
#define CUBMARK_ADAPTERMANAGER_H

#include <memory>

#include <cubmark/Singleton.hpp>
#include <cubmark/adapter/AdapterSlot.h>
#include <cubmark/adapter/AdapterManagerBase.h>

namespace cb
{

/** \brief Adapter manager template class
 *
 * \tparam FO functor class
 * \tparam R function return type
 * \tparam A function argument type pack
 */
template<class FO, class R, class ...A>
class AdapterManager :
	public AdapterManagerBase,
	public Singleton< AdapterManager<FO, R, A...> >
{
public:
	friend class Singleton< AdapterManager<FO, R, A...> >;
private:
	/**
	 * \brief Default constructor
	 */
	AdapterManager();

	/**
	 * \brief Copy constructor
	 */
	AdapterManager(const AdapterManager&);

	/**
	 * \brief Overloaded assignment operator
	 */
	AdapterManager& operator=(const AdapterManager&);
};

}
#endif//CUBMARK_ADAPTERMANAGER_H

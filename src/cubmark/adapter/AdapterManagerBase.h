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

#ifndef CUBMARK_ADAPTERMANAGERBASE_H
#define CUBMARK_ADAPTERMANAGERBASE_H

#include <stack>
#include <vector>

namespace cb
{

class AdapterSlot;

/** \brief Adapter manager template class
 *
 * Issues and frees locks to Adapters (Adapter instances) for a particular
 * combination of functor class and function pointer.
 * A "Adapter instance" is an instance of the cb::Adapter template.
 */
class AdapterManagerBase
{
public:
	/**
	 * \brief Desctructor
	 */
	virtual ~AdapterManagerBase();

	/**
	 * \brief Allocates an Adapter instance
	 *
	 * Locks an instance and binds a functor to it.
	 *
	 * \pre Functor class has a defined default constructor
	 * \pre Functor class has a defined overloaded assignment operator
	 *
	 * \param f_o Functor class instance
	 * \returns Adapter
	 */
	AdapterSlot* lockSlot();

	/**
	 * \brief Free a Adapter class instance
	 *
	 * Register a Adapter instance as unlocked and ready to re-use.
	 *
	 * \param adapter Adapter template class instance
	 */
	void unlockSlot(AdapterSlot* adapter);

protected:
	AdapterManagerBase(AdapterSlot* firstAdapter);
private:
	/**
	 * \brief Default constructor
	 */
	AdapterManagerBase();

	/**
	 * \brief Copy constructor
	 */
	AdapterManagerBase(const AdapterManagerBase&);

	/**
	 * \brief Overloaded assignment operator
	 */
	AdapterManagerBase& operator=(const AdapterManagerBase&);

	/**
	 * \brief Stack of currently available Adapter instances
	 */
	std::stack<AdapterSlot*, std::vector<AdapterSlot*> > freeSlots;
};

}
#endif//CUBMARK_ADAPTERMANAGERBASE_H

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
 * along with Cubature Benchmark.  If not, see .
 */

#include <cubmark/adapter/AdapterManagerBase.h>
#include <cubmark/adapter/AdapterSlot.h>

namespace cb
{

AdapterManagerBase::AdapterManagerBase(AdapterSlot* adapter)
{
	while(adapter)
	{
		freeSlots.push(adapter);
		adapter = adapter->getNext();
	};
}

AdapterManagerBase::~AdapterManagerBase()
{
	while(freeSlots.size())
	{
		delete freeSlots.top();
		freeSlots.pop();
	}
}

AdapterSlot* AdapterManagerBase::lockSlot()
{
	AdapterSlot* slot = 0;
	if(freeSlots.size())
	{
		slot = freeSlots.top();
		freeSlots.pop();
	}
	return slot;
}

void AdapterManagerBase::unlockSlot(AdapterSlot* adapter)
{
	freeSlots.push(adapter);
}

}

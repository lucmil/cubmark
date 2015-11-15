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

#ifndef CUBMARK_VIEWFACTORY_H
#define CUBMARK_VIEWFACTORY_H

#include <map>
#include <string>

#include <cubmark/config.h>
#include <cubmark/Definition.h>
#include <cubmark/Factory.hpp>

namespace cb
{

enum ViewIdType
{
	V_RAW,
	V_FULL,
	V_HISTOGRAM,
	V_TESTPACK
};

class ViewBuilder;

class ViewFactory :
	public Factory<ViewFactory, ViewBuilder, ViewIdType>
{
public:
	ViewFactory();
	ViewBuilder* getByDefinition(const Definition& definition) const;
	ViewBuilder* getById(ViewIdType viewId) const;
private:
	void initIdMap();
};

}
#endif//CUBMARK_VIEWFACTORY_H

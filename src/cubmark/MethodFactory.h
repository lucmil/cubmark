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

#ifndef CUBMARK_METHODFACTORY_H
#define CUBMARK_METHODFACTORY_H

#include <map>
#include <string>

#include <cubmark/config.h>
#include <cubmark/Definition.h>
#include <cubmark/Factory.hpp>

namespace cb
{

enum MethodIdType
{
	M_R2D2LRI,
	M_CUBPACKPP,
	M_ADAPT_R2D2LRI,
	M_HINTLIB,
	M_GSL_MONTECARLO,
	M_GAUSS_PRODUCT,
	M_DCUHRE
};

class Method;

/** \brief Factory class for Methods
 *
 * \todo Consider creating MethodBuilder classes to allow method-specific
 *       options in the UI (like changing rules in DCUHRE or HIntLib)
 */
class MethodFactory :
	public Factory<MethodFactory, Method, MethodIdType>
{
public:
	MethodFactory();
	Method* getByDefinition(const Definition& definition) const;
	Method* getById(MethodIdType methodId) const;
private:
	void initIdMap();
};

}
#endif//CUBMARK_METHODFACTORY_H

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

#include <cubmark/MethodFactory.h>
#include <cubmark/InvalidNameError.h>
#include <cubmark/TraceMethod.h>

#if     defined(CUBMARK_HAS_R2D2LRI)
#include <cubmark/Adaptive.h>
#include <cubmark/R2d2lri.h>
#endif

#if     defined(CUBMARK_HAS_CUBPACK)
#include <cubmark/Cubpack.h>
#endif

#if     defined(CUBMARK_HAS_HINTLIB)
#include <cubmark/HIntLib.h>
#endif

#if     defined(CUBMARK_HAS_GSL)
#include <cubmark/MonteCarlo.h>
#include <cubmark/Qag2D.h>
#endif

#if     defined(CUBMARK_HAS_DCUHRE)
#include <cubmark/Dcuhre.h>
#endif

#include <cubmark/debug.h>

namespace cb
{

MethodFactory::MethodFactory()
{
	initIdMap();
}

Method* MethodFactory::getByDefinition(const Definition& definition) const
{
	typedef Factory<MethodFactory, Method, MethodIdType> SuperType;
	Method* method = SuperType::getByDefinition(definition);
	CHECK(method, InvalidNameError("Invalid method name."));
	return method;
}

Method* MethodFactory::getById(MethodIdType id) const
{
	Method *method = 0;
	switch(id)
	{
#if     defined(CUBMARK_HAS_R2D2LRI)
		case M_R2D2LRI:
		method = new cb::R2d2lri();
		break;

		case M_ADAPT_R2D2LRI:
		method = new R2d2lri();
		method = new cb::Adaptive(method);
		break;
#endif//defined(CUBMARK_HAS_R2D2LRI)

#if     defined(CUBMARK_HAS_CUBPACK)
		case M_CUBPACKPP:
		method = new cb::Cubpack();
		break;
#endif//defined(CUBMARK_HAS_CUBPACK)

#if     defined(CUBMARK_HAS_HINTLIB)
		case M_HINTLIB:
		method = new cb::HIntLib();
		break;
#endif//defined(CUBMARK_HAS_HINTLIB)

#if     defined(CUBMARK_HAS_GSL)
		case M_GSL_MONTECARLO:
		method = new cb::MonteCarlo();
		break;

		case M_GAUSS_PRODUCT:
		method = new cb::Qag2D();
		break;
#endif//defined(CUBMARK_HAS_GSL)

#if     defined(CUBMARK_HAS_DCUHRE)
		case M_DCUHRE:
		method = new cb::Dcuhre();
		break;
#endif//defined(CUBMARK_HAS_DCUHRE)

		default:
		method = 0;
		break;
	}
	CHECK(method, InvalidNameError("Method interface not compiled in."));

#ifndef CUBMARK_NDEBUG
	/* Add tracing shim if if tracing is enabled */
	const LogManager& log = LogManager::getInstance();
	if(log.getLogLevel() == LogManager::LVL_TRACE)
	{
		TraceMethod* tracingShim = new TraceMethod(method);
		method = tracingShim;
	}
#endif//CUBMARK_NDEBUG

	return method;
}

void MethodFactory::initIdMap()
{
	idMap["r2d2lri"] = M_R2D2LRI;
	idMap["adaptive-r2d2lri"] = M_ADAPT_R2D2LRI;
	idMap["cubpack++"] = M_CUBPACKPP;
	idMap["hintlib"] = M_HINTLIB;
	idMap["dcuhre"] = M_DCUHRE;
	idMap["montecarlo"] = M_GSL_MONTECARLO;
	idMap["qag2d"] = M_GAUSS_PRODUCT;
}

}

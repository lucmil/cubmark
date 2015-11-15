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

#include <stdexcept>

#include <cubmark/ViewFactory.h>
#include <cubmark/FullViewBuilder.h>
#include <cubmark/HistogramViewBuilder.h>
#include <cubmark/TestpackViewBuilder.h>
#include <cubmark/RawViewBuilder.h>
#include <cubmark/InvalidNameError.h>
#include <cubmark/debug.h>

namespace cb
{

ViewFactory::ViewFactory()
{
	initIdMap();
}

ViewBuilder* ViewFactory::getByDefinition(const Definition& definition) const
{
	typedef Factory<ViewFactory, ViewBuilder, ViewIdType> SuperType;
	ViewBuilder* viewBuilder = SuperType::getByDefinition(definition);
	CHECK(viewBuilder, InvalidNameError("Invalid view name."));
	viewBuilder->parseDefinition(definition);
	return viewBuilder;
}

ViewBuilder* ViewFactory::getById(ViewIdType id) const
{
	ViewBuilder* viewBuilder = 0;
	switch(id)
	{
		case V_RAW:			viewBuilder = new RawViewBuilder;		break;
		case V_FULL:		viewBuilder = new FullViewBuilder;		break;
		case V_HISTOGRAM:	viewBuilder = new HistogramViewBuilder;	break;
		case V_TESTPACK:	viewBuilder = new TestpackViewBuilder;	break;
	}
	return viewBuilder;
}

void ViewFactory::initIdMap()
{
	idMap["raw"] = V_RAW;
	idMap["full"] = V_FULL;
	idMap["histogram"] = V_HISTOGRAM;
	idMap["testpack"] = V_TESTPACK;
}

}

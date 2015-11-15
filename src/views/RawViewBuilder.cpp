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

#include <boost/archive/binary_oarchive.hpp>

#include <cubmark/RawViewBuilder.h>
#include <cubmark/debug.h>
#include <cubmark/SuiteResults.hpp>
#include <cubmark/SuiteSpecification.hpp>
#include <cubmark/CaseSpecification.hpp>
#include <cubmark/Definition.hpp>
#include <cubmark/Boundary.hpp>
#include <cubmark/Result.hpp>
#include <cubmark/CaseResults.hpp>

namespace cb
{

RawViewBuilder::RawViewBuilder()
{
}

RawViewBuilder::~RawViewBuilder()
{
}

void RawViewBuilder::parseParameter(const std::string& /*name*/,
			const std::string &/*value*/)
{
}

void RawViewBuilder::create(SuiteResults& suiteResults, std::ostream& ostream)
{
	// Your OS turns \n into \r\n ? Tough luck. Get a real OS.
	boost::archive::binary_oarchive oa(ostream);
	oa & suiteResults;
}

}

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

#include <cubmark/RD28Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/algorithm.h>
#include <cubmark/debug.h>

namespace cb
{

RD28Builder::RD28Builder() :
	defaultBoundary(2.0, 1.0, -inf, -1)
{
}

Method::IntegrandType RD28Builder::create()
{
	return &RD28Builder::compute;
}

double RD28Builder::integral(const Boundary& boundary)
{
	CHECK( feq(boundary.l(0), 2.0) && feq(boundary.u(0), 1.0)
			&& boundary.l(1) == -inf && feq(boundary.u(1), -1.0),
			"Unsupported boundary.");

	return -1.0;
}

const Boundary& RD28Builder::getDefaultBoundary()
{
	return defaultBoundary;
}

void RD28Builder::parseParameter(const std::string& /*name*/,
		const std::string& /*value*/)
{
}

double RD28Builder::compute(double /*x*/, double y) throw()
{
	return pow(y, -2.0);
}

}

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

#include <cubmark/RD29Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/algorithm.h>
#include <cubmark/debug.h>

namespace cb
{

RD29Builder::RD29Builder() :
	defaultBoundary(1.0, 2.0, 1.0, inf)
{
}

Method::IntegrandType RD29Builder::create()
{
	return &RD29Builder::compute;
}

double RD29Builder::integral(const Boundary& boundary)
{
	CHECK( feq(boundary.l(0), 1.0) && feq(boundary.u(0), 2.0)
			&& boundary.u(1) == inf && feq(boundary.l(1), 1.0),
			"Unsupported boundary.");

	return exp(1) - 1;
}

const Boundary& RD29Builder::getDefaultBoundary()
{
	return defaultBoundary;
}

void RD29Builder::parseParameter(const std::string& /*name*/,
		const std::string& /*value*/)
{
}

double RD29Builder::compute(double x, double y) throw()
{
	return exp(x - y);
}

}

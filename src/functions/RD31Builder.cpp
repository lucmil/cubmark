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

#include <cubmark/RD31Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/algorithm.h>
#include <cubmark/debug.h>

namespace cb
{

RD31Builder::RD31Builder() :
	defaultBoundary(-10.0, inf, 5.0, inf)
{
}

Method::IntegrandType RD31Builder::create()
{
	return &RD31Builder::compute;
}

double RD31Builder::integral(const Boundary& boundary)
{
	CHECK(boundary.u(0) == inf && boundary.u(1) == inf,
			"Unsupported boundary.");

	return 0.25*PI;
}

const Boundary& RD31Builder::getDefaultBoundary()
{
	return defaultBoundary;
}

void RD31Builder::parseParameter(const std::string& /*name*/,
		const std::string& /*value*/)
{
}

double RD31Builder::compute(double x, double y)
{
	return 1.0/pow(x*x + y*y + 20.0 * x - 10.0 * y + 126.0, 2.0);
}

}

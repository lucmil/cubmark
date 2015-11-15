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

#include <cubmark/RD35Builder.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/algorithm.h>
#include <cubmark/debug.h>

namespace cb
{

RD35Builder::RD35Builder() :
	defaultBoundary(-inf, inf, -inf, inf)
{
}

Method::IntegrandType RD35Builder::create()
{
	return &RD35Builder::compute;
}

double RD35Builder::integral(const Boundary& boundary)
{
	CHECK(boundary.u(0) == inf && boundary.u(1) == inf,
			"Unsupported boundary.");

	return 2.0*PI;
}

const Boundary& RD35Builder::getDefaultBoundary()
{
	return defaultBoundary;
}

void RD35Builder::parseParameter(const std::string& /*name*/,
		const std::string& /*value*/)
{
}

double RD35Builder::compute(double x, double y) throw()
{
	return exp(-0.5*(x*x +y*y));
}

}

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

#include <cubmark/HIntLibIntegrand.h>

#include <cubmark/debug.h>
#include <cubmark/constants.h>

namespace cb
{

HIntLibIntegrand::HIntLibIntegrand(int dimension) :
	Integrand(dimension),
	integrand(&HIntLibIntegrand::noop),
	callCnt(0)
{
	CHECK(dimension == 2, "Supports only 2 dimensional functions.");
}

HIntLibIntegrand::~HIntLibIntegrand()
{
}

void HIntLibIntegrand::setIntegrand(Method::IntegrandType integrand)
{
	CHECK(integrand != 0, "NULL function pointer passed");
	this->integrand = integrand;
}

Method::IntegrandType HIntLibIntegrand::getIntegrand() const
{
	return (integrand == &HIntLibIntegrand::noop) ? 0 : integrand;
}

unsigned long HIntLibIntegrand::getCallCnt() const
{
	return callCnt;
}

void HIntLibIntegrand::resetCallCnt()
{
	callCnt = 0;
}

HIntLib::real HIntLibIntegrand::operator()(const HIntLib::real x[])
{
	++callCnt;
	return integrand(x[0], x[1]);
}

double HIntLibIntegrand::noop(double, double)
{
	CHECK(1, std::logic_error("Called with no integrand pointer set."));

	return sNaN;
}

}

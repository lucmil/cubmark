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

#include <HIntLib/rule75genzmalik.h>

using HIntLib::Rule75GenzMalik;

#include <cubmark/debug.h>
#include <cubmark/constants.h>
#include <cubmark/HIntLib.h>

namespace cb
{

HIntLib::HIntLib(EmbeddedRuleFactory *rf) :
	integrand(2),
	evaluationSuccess(false),
	callLimit(100000u),
	relErrTol(0.),
	absErrTol(0.),
	region(2), // HIntLib 2D Hypercube
	integrator(rf ? rf : Rule75GenzMalik::getFactory())
{
}

HIntLib::~HIntLib()
{
}

void HIntLib::setRelativeTolerance(double relErrTol)
{
	this->relErrTol = static_cast<real>(relErrTol);
}

double HIntLib::getRelativeTolerance() const
{
	return relErrTol;
}

void HIntLib::setAbsoluteTolerance(double absErrTol)
{
	this->absErrTol = static_cast<real>(absErrTol);
}

double HIntLib::getAbsoluteTolerance() const
{
	return absErrTol;
}

void HIntLib::setBoundary(const Boundary& boundary)
{
	CHECK(!boundary.isInfinite(),
			"HIntLib does not support infinite boundaries");

	this->boundary = boundary;
}

bool HIntLib::hasBoundary() const
{
	return boundary.isValid();
}

bool HIntLib::hasIntegrand() const
{
	return integrand.getIntegrand();
}

Method::IntegrandType HIntLib::getIntegrand() const
{
	return integrand.getIntegrand();
}

void HIntLib::setIntegrand(IntegrandType integrand)
{
	this->integrand.setIntegrand(integrand);
	this->integrand.resetCallCnt();
}

double HIntLib::compute()
{
	region.set(0, boundary.l(0), boundary.u(0));
	region.set(1, boundary.l(1), boundary.u(1));

	Integrator::Status status = integrator.integrate(integrand, region,
			callLimit, absErrTol, relErrTol, result);

	switch(status)
	{
		case Integrator::ABS_ERROR_REACHED:
		case Integrator::REL_ERROR_REACHED:
		evaluationSuccess = true;
		break;

		default:
		evaluationSuccess = false;
		break;
	}

	return result.getEstimate();
}

bool HIntLib::failed() const
{
	return !evaluationSuccess;
}

unsigned long HIntLib::getCallCnt() const
{
	return integrand.getCallCnt();
}

double HIntLib::getAbsoluteErrorEstimate() const
{
	return static_cast<double>(result.getError());
}

double HIntLib::getRelativeErrorEstimate() const
{
	return static_cast<double>(result.getRelError());
}

void HIntLib::setCallLimit(unsigned long callLimit)
{
	this->callLimit = static_cast<Index>(callLimit);
}

unsigned long HIntLib::getCallLimit() const
{
	return static_cast<Index>(callLimit);
}


}

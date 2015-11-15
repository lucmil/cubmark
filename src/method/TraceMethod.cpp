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

#include <cubmark/debug.h>

#include <cubmark/TraceMethod.h>

namespace cb
{

TraceMethod::TraceMethod(Method* methodInstance) :
	methodInstance(methodInstance)
{
	CHECK(methodInstance, "NULL pointer passed");
}

TraceMethod::~TraceMethod()
{
}

void TraceMethod::setRelativeTolerance(double relativeTolerance)
{
	LOG(TRACE, "Set RET: " << relativeTolerance);
	methodInstance->setRelativeTolerance(relativeTolerance);
}

double TraceMethod::getRelativeTolerance() const
{
	return methodInstance->getRelativeTolerance();
}

void TraceMethod::setAbsoluteTolerance(double absoluteTolerance)
{
	LOG(TRACE, "Set AET: " << absoluteTolerance);
	methodInstance->setAbsoluteTolerance(absoluteTolerance);
}

double TraceMethod::getAbsoluteTolerance() const
{
	return methodInstance->getAbsoluteTolerance();
}

void TraceMethod::setBoundary(const Boundary& boundary)
{
	LOG(TRACE, "Set boundary: "
			"a = " << boundary.l(0) << ", b = " << boundary.u(0) << ", "
			"c = " << boundary.l(1) << ", d = " << boundary.u(1));

	methodInstance->setBoundary(boundary);
}

bool TraceMethod::hasBoundary() const
{
	return methodInstance->hasBoundary();
}

void TraceMethod::setIntegrand(IntegrandType f)
{
	LOG(TRACE, "Set integrand.");
	methodInstance->setIntegrand(f);
}

Method::IntegrandType TraceMethod::getIntegrand() const
{
	return methodInstance->getIntegrand();
}

bool TraceMethod::hasIntegrand() const
{
	return methodInstance->hasIntegrand();
}

double TraceMethod::compute()
{
	LOG(TRACE, "Starting evaluation.");
	CHECK((methodInstance->getAbsoluteTolerance() > 0.
					|| this->getRelativeTolerance() > 0.),
			"No tolerance set");

	CHECK(methodInstance->hasBoundary(), "Integral boundary not set");
	CHECK(methodInstance->hasIntegrand(), "No integrand set");

	return methodInstance->compute();
}

bool TraceMethod::failed() const
{
	return methodInstance->failed();
}

unsigned long TraceMethod::getCallCnt() const
{
	return methodInstance->getCallCnt();
}

double TraceMethod::getAbsoluteErrorEstimate() const
{
	return methodInstance->getAbsoluteErrorEstimate();
}

double TraceMethod::getRelativeErrorEstimate() const
{
	return methodInstance->getRelativeErrorEstimate();
}

void TraceMethod::setCallLimit(unsigned long callLimit)
{
	LOG(TRACE, "Set integrand funciton call limit: " << callLimit);
	methodInstance->setCallLimit(callLimit);
}

unsigned long TraceMethod::getCallLimit() const
{
	return methodInstance->getCallLimit();
}

}

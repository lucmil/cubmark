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

#include <cmath>
#include <gsl/gsl_errno.h>

#include <cubmark/constants.h>
#include <cubmark/Qag2D.h>

namespace cb
{

Qag2D::Qag2D() :
	absErrTol(0.),
	relErrTol(0.),
	absErrEst(NaN),
	relErrEst(NaN),
	callCnt(0),
	callLimit(defaultCallLimit),
	integrand(0)
{
}

Qag2D::~Qag2D()
{
}

void Qag2D::setRelativeTolerance(double relErrTol)
{
	this->relErrTol = relErrTol;
}

double Qag2D::getRelativeTolerance() const
{
	return relErrTol;
}

void Qag2D::setAbsoluteTolerance(double absErrTol)
{
	this->absErrTol = absErrTol;
}

double Qag2D::getAbsoluteTolerance() const
{
	return absErrTol;
}

void Qag2D::setBoundary(const Boundary& boundary)
{
	this->boundary = boundary;

}

bool Qag2D::hasBoundary() const
{
	return boundary.isValid();
}

bool Qag2D::hasIntegrand() const
{
	return Qag2D::integrand != 0;
}

Method::IntegrandType Qag2D::getIntegrand() const
{
	return integrand;
}

void Qag2D::setIntegrand(IntegrandType integrand)
{
	this->integrand = integrand;
}

double Qag2D::compute()
{
	gsl_error_handler_t *handler = gsl_set_error_handler_off();
	// Result and absolute error estimate
	double r = NaN;
	size_t callLimitPerDim = (size_t)(sqrt((double)callLimit)/61.0);
	if(callLimitPerDim == 0)
	{
		callLimitPerDim = 1;
	}

	for(size_t i = 0; i < 2; ++i)
	{
		QagRule& rule = ruleChain.getRule(i);
		rule.setDivisionLimit(callLimitPerDim);
		rule.setEpsabs(absErrTol);
		rule.setEpsrel(relErrTol);
	}

	QagRule& xRule = ruleChain.getRule(0);
	QagRule& yRule = ruleChain.getRule(1);

	xRule.setBoundary(boundary.l(0), boundary.u(0));
	yRule.setBoundary(boundary.l(1), boundary.u(1));

	ruleChain.setIntegrand(integrand);
	r = ruleChain.compute();
	absErrEst = xRule.getAbsoluteErrorEstimate();
	relErrEst = absErrEst / fabs(r);

	gsl_set_error_handler(handler);

	return r;
}

bool Qag2D::failed() const
{
	for(size_t i = 0; i < 2; ++i)
	{
		const QagRule& rule = ruleChain.getRule(i);
		if(rule.failed())
		{
			return true;
		}
	}
	return false;
}

unsigned long Qag2D::getCallCnt() const
{
	return ruleChain.getCallCnt();
}

double Qag2D::getAbsoluteErrorEstimate() const
{
	return absErrEst;
}

double Qag2D::getRelativeErrorEstimate() const
{
	return relErrEst;
}

void Qag2D::setCallLimit(unsigned long callLimit)
{
	if(callLimit == 0)
	{
		this->callLimit = Qag2D::defaultCallLimit;
	}
	else
	{
		this->callLimit = callLimit;
	}
}

unsigned long Qag2D::getCallLimit() const
{
	return callLimit;
}

const size_t Qag2D::defaultCallLimit = 100000u;

}

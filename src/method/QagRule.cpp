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

#include <gsl/gsl_errno.h>

#include <cubmark/QagRule.h>

#include <cubmark/debug.h>
#include <cubmark/constants.h>

namespace cb
{

QagRule::QagRule() :
	ws(0),
	gsl_status(-1),
	a(NaN),
	b(NaN),
	epsabs(0.),
	epsrel(0.),
	result(a),
	abserr(a)
{
	F.function = 0;
	F.params = 0;
}

QagRule::~QagRule()
{
	if(ws)
	{
		gsl_integration_workspace_free(ws);
	}
}

void QagRule::setDivisionLimit(size_t maxDiv)
{
	CHECK(maxDiv != 0, "Cannot set subinterval limit to zero.");
	if(!ws)
	{
		ws = gsl_integration_workspace_alloc(maxDiv);
	}
	else if(ws->limit != maxDiv)
	{
		gsl_integration_workspace_free(ws);
		ws = gsl_integration_workspace_alloc(maxDiv);
	}
}

void QagRule::setBoundary(double a, double b)
{
	this->a = a;
	this->b = b;
	rule = chooseRule(a, b);
}

void QagRule::setEpsabs(double epsabs)
{
	this->epsabs = epsabs;
}

void QagRule::setEpsrel(double epsrel)
{
	this->epsrel = epsrel;
}

void QagRule::setIntegrand(QagIntegrandType integrand)
{
	F.function = integrand;
}

double QagRule::compute()
{
	gsl_status = (this->*rule)();
	return result;
}

bool QagRule::failed() const
{
	return gsl_status;
}

double QagRule::getAbsoluteErrorEstimate() const
{
	return abserr;
}

QagRule::RuleType QagRule::chooseRule(double a, double b) const
{
	if(isinf(a) && isinf(b))
	{
		return &QagRule::qagi;
	}
	else if(isinf(a))
	{
		return &QagRule::qagil;
	}
	else if(isinf(b))
	{
		return &QagRule::qagiu;
	}
	else
	{
		return &QagRule::qag;
	}
}

int QagRule::qag()
{
	return gsl_integration_qag (&F, a, b, epsabs, epsrel, ws->limit,
			GSL_INTEG_GAUSS61, ws, &result, &abserr);
}

int QagRule::qagi()
{
	return gsl_integration_qagi (&F, epsabs, epsrel, ws->limit, ws,
			&result, &abserr);
}

int QagRule::qagiu()
{
	return gsl_integration_qagiu (&F, a, epsabs, epsrel, ws->limit, ws,
			&result, &abserr);
}

int QagRule::qagil()
{
	return gsl_integration_qagil (&F, b, epsabs, epsrel, ws->limit, ws,
			&result, &abserr);
}

}

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
#include <cmath>

#include <cubmark/adapter/adapter.h>
#include <cubmark/debug.h>
#include <cubmark/constants.h>

#include <cubmark/MonteCarlo.h>

using std::isnan;
using std::isinf;

namespace cb
{

MonteCarlo::MonteCarlo() :
	absErrTol(0.),
	relErrTol(0.),
	absErrEst(NaN),
	relErrEst(NaN),
	gsl_status(0),
	callCnt(0),
	callLimit(defaultCallLimit)
{
	F.f = &MonteCarlo::gslAdapter;
	F.dim = 2;
	F.params = 0;
	rng = gsl_rng_alloc(gsl_rng_default);
	state = gsl_monte_plain_alloc(2);
}

MonteCarlo::~MonteCarlo()
{
	gsl_monte_plain_free(state);
	gsl_rng_free(rng);
}

void MonteCarlo::setRelativeTolerance(double relErrTol)
{
	this->relErrTol = relErrTol;
}

double MonteCarlo::getRelativeTolerance() const
{
	return this->relErrTol;
}

void MonteCarlo::setAbsoluteTolerance(double absErrTol)
{
	this->absErrTol = absErrTol;
}

double MonteCarlo::getAbsoluteTolerance() const
{
	return this->absErrTol;
}

void MonteCarlo::setBoundary(const Boundary& boundary)
{
	if(boundary.isValid())
	{
		CHECK(!boundary.isInfinite(),
				"Plain MC does not support infinite region boundaries.");

		xl[0] = boundary.l(0);
		xu[0] = boundary.u(0);
		xl[1] = boundary.l(1);
		xu[1] = boundary.u(1);
	}
	else
	{
		xl[0] = NaN;
		xu[0] = NaN;
		xl[1] = NaN;
		xu[1] = NaN;
	}
}

bool MonteCarlo::hasBoundary() const
{
	return !(isnan(xl[0]) || isnan(xu[0]) || isnan(xl[1]) || isnan(xu[1]));
}

bool MonteCarlo::hasIntegrand() const
{
	return MonteCarlo::integrand != 0;
}

Method::IntegrandType MonteCarlo::getIntegrand() const
{
	return integrand;
}

void MonteCarlo::setIntegrand(IntegrandType f)
{
	integrand = f;
}

double MonteCarlo::compute()
{
	// Result and absolute error estimate
	double r = NaN;
	const size_t S = 5000;
	double sum = 0.;
	double q = 0.;
	size_t i = (size_t)-1;
	const double vol = (xu[0] - xl[0])*(xu[1] - xl[1]);

	for(i = 1; i < callLimit/S+1; ++i)
	{
		gsl_status = gsl_monte_plain_integrate(&F, xl, xu, 2, S, rng, state, &r,
				&absErrEst);
		sum += r;

		// Recover the variance
		q += pow(absErrEst / vol, 2.) * (double)S;

		r = sum/(double)i;
		absErrEst = vol * sqrt(q/static_cast<double>(S*i));
		relErrEst = absErrEst/r;

		if(gsl_status || relErrEst < relErrTol || absErrEst < absErrTol)
		{
			break;
		}
	}

	callCnt = i*S;

	if(gsl_status)
	{
		throw std::runtime_error(gsl_strerror(gsl_status));
	}

	return r;
}

bool MonteCarlo::failed() const
{
	return (callCnt >= callLimit &&
			(relErrEst > relErrTol || absErrEst > absErrTol));
}

unsigned long MonteCarlo::getCallCnt() const
{
	return callCnt;
}

double MonteCarlo::getAbsoluteErrorEstimate() const
{
	return absErrEst;
}

double MonteCarlo::getRelativeErrorEstimate() const
{
	return relErrEst;
}

void MonteCarlo::setCallLimit(unsigned long callLimit)
{
	if(callLimit == 0)
	{
		this->callLimit = MonteCarlo::defaultCallLimit;
	}
	else
	{
		this->callLimit = callLimit;
	}
}

unsigned long MonteCarlo::getCallLimit() const
{
	return callLimit;
}


double MonteCarlo::gslAdapter(double* x, size_t, void*)
{
	return MonteCarlo::integrand(x[0], x[1]);
}

Method::IntegrandType MonteCarlo::integrand = 0;
const size_t MonteCarlo::defaultCallLimit = 200000u;

}

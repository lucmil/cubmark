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
#include <limits>
#include <stdexcept>

#include <cubmark/adapter/adapter.h>
#include <cubmark/constants.h>
#include <cubmark/debug.h>
#include <cubmark/Dcuhre.h>
#include <cubmark/DcuhreIntegrand.h>
#include <cubmark/Dcuhre_prototypes.h>

namespace cb
{

Dcuhre::Dcuhre() :
	absErrTol(0.),
	relErrTol(0.),
	absErrEst(NaN),
	relErrEst(NaN),
	callCnt(0),
	callLimit(defaultCallLimit),
	integrand()
{
}

Dcuhre::~Dcuhre()
{
}

void Dcuhre::setRelativeTolerance(double relErrTol)
{
	this->relErrTol = relErrTol;
}

double Dcuhre::getRelativeTolerance() const
{
	return relErrTol;
}

void Dcuhre::setAbsoluteTolerance(double absErrTol)
{
	this->absErrTol = absErrTol;
}

double Dcuhre::getAbsoluteTolerance() const
{
	return absErrTol;
}

void Dcuhre::setBoundary(const Boundary& boundary)
{
	CHECK(!boundary.isInfinite(),
			std::domain_error("DCUHRE does not support infinite boundaries."));

	this->boundary = boundary;
}

bool Dcuhre::hasBoundary() const
{
	return boundary.isValid();
}

bool Dcuhre::hasIntegrand() const
{
	return this->integrand != 0;
}

Method::IntegrandType Dcuhre::getIntegrand() const
{
	return this->integrand;
}

void Dcuhre::setIntegrand(IntegrandType integrand)
{
	this->integrand = (integrand) ? integrand : &nop;
}

double Dcuhre::compute()
{
	IntegrandAdapterType* integrandAdapter = 0;
	// See DCUHRE documentation for explanation of these parameters
	int NDIM = 2;
	int NFUN = 1;
	int MINPTS = 0;

	int KEY = 0;
	const int NUM = 65;
	const int MAXSUB = (callLimit-NUM)/(2*NUM) + 1;
	int NW = MAXSUB*(2*NDIM+2*NFUN+2) + 17*NFUN + 1;

	double A[2] = { boundary.l(0), boundary.l(0) };
	double B[2] = { boundary.u(1), boundary.u(1) };

	int RESTAR = 0;
	double RESULT = NaN;
	double* WORK = new double[NW];

	adapter(integrandAdapter);
	AdapterLock lock(integrandAdapter);
	adapterSetFunctor(integrandAdapter, DcuhreIntegrand(this->integrand));

	dcuhre_(&NDIM, &NFUN, A, B, &MINPTS, &callLimit, integrandAdapter->getPtr(),
			&absErrTol, &relErrTol, &KEY, &NW, &RESTAR, &RESULT, &absErrEst,
			&callCnt, &iFail, WORK);

	relErrEst = absErrEst / fabs(RESULT);

	delete[] WORK;

	if(isnan(RESULT))
	{
		iFail = -1;
	}
	return RESULT;
}

bool Dcuhre::failed() const
{
	return iFail;
}

unsigned long Dcuhre::getCallCnt() const
{
	return callCnt;
}

double Dcuhre::getAbsoluteErrorEstimate() const
{
	return absErrEst;
}

double Dcuhre::getRelativeErrorEstimate() const
{
	return relErrEst;
}

void Dcuhre::setCallLimit(unsigned long callLimit)
{
	CHECK(callLimit <= static_cast<unsigned long>(std::numeric_limits<int>::max()),
			"Maximum call limit for DCUHRE exceeded");

	if(callLimit == 0)
	{
		this->callLimit = Dcuhre::defaultCallLimit;
	}
	else
	{
		this->callLimit = static_cast<int>(callLimit);
	}
}

unsigned long Dcuhre::getCallLimit() const
{
	return callLimit;
}

const int Dcuhre::defaultCallLimit = 100000;

double Dcuhre::nop(double, double)
{
	return NaN;
}

}

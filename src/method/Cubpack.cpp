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

#include <cubmark/Cubpack.h>

#include <cubmark/debug.h>
#include <cubmark/constants.h>
#include <cubmark/algorithm.h>

namespace cb
{

Cubpack::Cubpack() :
	evaluationFailed(false),
	callCnt(0),
	callLimit(DefaultMaxEval),
	relErrTol(0.),
	absErrTol(0.),
	integrand(0)
{
}

Cubpack::~Cubpack()
{
}

void Cubpack::setRelativeTolerance(double relErrTol)
{
	if(relErrTol != 0.)
	{
		this->relErrTol = relErrTol;
	}
	else
	{
		this->relErrTol = DefaultRelErrReq;
	}
}

double Cubpack::getRelativeTolerance() const
{
	return relErrTol;
}

void Cubpack::setAbsoluteTolerance(double absErrTol)
{
	if(absErrTol != 0.)
	{
		this->absErrTol = absErrTol;
	}
	else
	{
		this->absErrTol = DefaultAbsErrReq;
	}
}

double Cubpack::getAbsoluteTolerance() const
{
	return absErrTol;
}

/* TODO Refactor this monstrosity */
void Cubpack::setBoundary(const Boundary& boundary)
{
	if(!boundary.isValid())
	{
		region.reset(0);
		return;
	}

	const double a = boundary.l(0);
	const double b = boundary.u(0);
	const double c = boundary.l(1);
	const double d = boundary.u(1);
	const bool aIsInfinite = (fabs(a) == inf);
	const bool bIsInfinite = (fabs(b) == inf);
	const bool cIsInfinite = (fabs(c) == inf);
	const bool dIsInfinite = (fabs(d) == inf);
	boundarySign = computeBoundarySign(boundary);

	/* Check if infinite boundaries have alternating signs */
	if(aIsInfinite && bIsInfinite && cIsInfinite && dIsInfinite)
	{
		CHECK((a == -b) && (c == -d),
				"Infinite boundaries have to have alternating sign");

		region.reset(new PLANE());
	}
	else if(aIsInfinite && bIsInfinite)
	{
		CHECK((a == -b),
				"Infinite boundaries have to have alternating sign");

		if(cIsInfinite || dIsInfinite)
		{
			/* (-+inf,+-inf)x[c,+-inf) - PLANE HALF (TWO PLANE SECTORS)
			 * or
			 * (-+inf,+-inf)x(-+inf,d] - PLANE HALF (TWO PLANE SECTORS) */
		}
		/* (-+inf,+-inf)x[c,d] - PLANE STRIP */
		throw std::logic_error("Unsupported boundary");
	}
	else if(cIsInfinite && dIsInfinite)
	{
		CHECK((c == -d), "Infinite boundaries have to have alternating sign");

		if(aIsInfinite || bIsInfinite)
		{
			/* [a,+-inf)x(-+inf,+-inf) - PLANE HALF (TWO PLANE SECTORS)
			 * or
			 * (-+inf,b]x(-+inf,+-inf) - PLANE HALF (TWO PLANE SECTORS) */
		}
		else
		{
			/* [a,b]x(-+inf,+-inf) - PLANE STRIP */
			region.reset(new INFINITE_STRIP(Point(a, 0.), Point(b, 0.)));
		}
	}
	else if(aIsInfinite != bIsInfinite && cIsInfinite != dIsInfinite)
	{
		/* PLANE SECTOR */
		if(bIsInfinite && dIsInfinite)
		{
			/* [a,+-inf)x[c,+-inf) */
			region.reset(new PLANE_SECTOR(Point(a, c), 0.0, 0.0, 0.5*PI));
		}
		else if(aIsInfinite && dIsInfinite)
		{
			/* (+-inf,b]x[c,+-inf) */
			region.reset(new PLANE_SECTOR(Point(b, c), 0.0, 0.5*PI, PI));
		}
		else if(aIsInfinite && cIsInfinite)
		{
			/* (+-inf,b]x(+-inf,d] */
			region.reset(new PLANE_SECTOR(Point(b, d), 0.0, PI, 1.5*PI));
		}
		else
		{
			/* [a,+-inf)x(+-inf,d] */
			region.reset(new PLANE_SECTOR(Point(a, d), 0.0, 1.5*PI, 2.0*PI));
		}
	}
	else if(aIsInfinite != bIsInfinite)
	{
		/* [a,+-inf)x[c,d] SEMI-INFINITE STRIP
		 * or
		 * (-+inf,b]x[c,d] SEMI-INFINITE STRIP
		 */
		throw std::logic_error("Unsupported boundary");
	}
	else if(cIsInfinite != dIsInfinite)
	{
		/* [a,b]x[c,+-inf) SEMI-INFINITE STRIP
		 * or
		 * [a,b]x(-+inf,d] SEMI-INFINITE STRIP
		 */
		if(cIsInfinite)
		{
			region.reset(
					new SEMI_INFINITE_STRIP(Point(a, d), Point(b, d)));
		}
		else
		{
			region.reset(
					new SEMI_INFINITE_STRIP(Point(b, c), Point(a, c)));
		}
	}
	else
	{
		/*
		 * [a,b]x[c,d] RECTANGLE
		 */
		region.reset(new RECTANGLE(Point(a,c), Point(a,d), Point(b,c)));
	}
}

bool Cubpack::hasBoundary() const
{
	return region.get() != 0;
}

void Cubpack::setIntegrand(IntegrandType integrand)
{
	this->integrand = integrand;
}

Cubpack::IntegrandType Cubpack::getIntegrand() const
{
	return integrand;
}

bool Cubpack::hasIntegrand() const
{
	return integrand != 0;
}

double Cubpack::computeBoundarySign(const Boundary& boundary) const
{
	const int s_x = fcmp(boundary.l(0), boundary.u(0));
	const int s_y = fcmp(boundary.l(1), boundary.u(1));
	return ((s_x == s_y) ? 1.0 : -1.0);
}

double Cubpack::compute()
{
	Boolean success = False;
	real result = sNaN;
	real absErrEst = inf;

	UnaryAdapter<CubpackIntegrand>::Type* integrandAdapter =
			adapter(CubpackIntegrand(this->getIntegrand()));

	AdapterLock lock(integrandAdapter);

	UnaryAdapter<CubpackIntegrand>::FuncPtrType integrandPtr =
			integrandAdapter->getPtr();

	cntr.Start();

	Integrate(integrandPtr, *region, result, absErrEst, success,
			static_cast<real>(absErrTol), static_cast<real>(relErrTol), callLimit);

	cntr.Stop();
	callCnt = cntr.Read();
	cntr.Reset();

	this->absErrEst = static_cast<double>(absErrEst);
	this->evaluationFailed = (bool)(success == False);

	return boundarySign * result;
}

bool Cubpack::failed() const
{
	return evaluationFailed;
}

unsigned long Cubpack::getCallCnt() const
{
	return callCnt;
}

double Cubpack::getAbsoluteErrorEstimate() const
{
	return region->AbsoluteError();
}

double Cubpack::getRelativeErrorEstimate() const
{
	throw std::logic_error("Relative error estimation is unsupported");
	return sNaN;
}

void Cubpack::setCallLimit(unsigned long callLimit)
{
	if(callLimit == 0)
	{
		this->callLimit = DefaultMaxEval;
	}
	else
	{
		this->callLimit = callLimit;
	}
}

unsigned long Cubpack::getCallLimit() const
{
	return callLimit;
}

}

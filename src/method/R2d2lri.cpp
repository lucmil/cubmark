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

#include <cubmark/adapter/adapter.h>

#include <cubmark/debug.h>
#include <cubmark/constants.h>

#include <cubmark/R2d2lri.h>

namespace cb
{

using std::isinf;
using std::isnan;

template<class R, class ...A>
class AdapterTraits<Constant, R, A...>
{
public:
	enum LimitsType { SLOT_LIMIT = 2 };
};

R2d2lri::R2d2lri() :
	integrand(0),
	a(NaN),
	b(NaN),
	g(adapter(Constant(NaN))),
	h(adapter(Constant(NaN)))
{
}

R2d2lri::~R2d2lri()
{
	g->unlockSlot();
	h->unlockSlot();
}

void R2d2lri::setRelativeTolerance(double relativeTolerance)
{
	if(relativeTolerance != 0.)
	{
		di.set_rel_tol(relativeTolerance);
	}
	else
	{
		// Reset to default
		di.set_rel_tol(DEFAULT_REL_TOL);
	}
}

double R2d2lri::getRelativeTolerance() const
{
	return di.get_rel_tol();
}


void R2d2lri::setAbsoluteTolerance(double absoluteTolerance)
{
	if(absoluteTolerance != 0.)
	{
		di.set_abs_tol(absoluteTolerance);
	}
	else
	{
		// Reset to default
		di.set_abs_tol(DEFAULT_ABS_TOL);
	}
}

double R2d2lri::getAbsoluteTolerance() const
{
	return di.get_abs_tol();
}

void R2d2lri::setBoundary(const Boundary& boundary)
{
	if(boundary.isValid())
	{
		const double a = boundary.l(0);
		const double b = boundary.u(0);
		this->a = isinf(a) ? copysign(INFINITE, a) : a;
		this->b = isinf(b) ? copysign(INFINITE, b) : b;

		adapterSetFunctor(g, Constant(boundary.l(1)));
		adapterSetFunctor(h, Constant(boundary.u(1)));

		if(this->hasIntegrand())
		{
			this->setIntegrand(this->getIntegrand());
		}
	}
	else
	{
		this->a = NaN;
		this->b = NaN;
	}
}

bool R2d2lri::hasBoundary() const
{
	return !(isnan(a) || isnan(b));
}

bool R2d2lri::hasIntegrand() const
{
	return integrand != 0;
}

Method::IntegrandType R2d2lri::getIntegrand() const
{
	return integrand;
}

void R2d2lri::setIntegrand(IntegrandType f)
{
	if(this->hasBoundary())
	{
		di.set_new_integral(a, b, g->getPtr(), h->getPtr(), f);
	}
	integrand = f;
}

double R2d2lri::compute()
{
	return di.evaluate();
}

bool R2d2lri::failed() const
{
	return di.error_flag() > 0;
}

unsigned long R2d2lri::getCallCnt() const
{
	return di.evals();
}

double R2d2lri::getAbsoluteErrorEstimate() const
{
	return di.abs_err_est();
}

double R2d2lri::getRelativeErrorEstimate() const
{
	return di.rel_err_est();
}

/* This doesn't seem to work. Tried setting a limit of 1000 in
 * the Adaptive template class, just before the evaluation and
 * the algorithm went well over 10k calls. (the maximum possible number for this
 * algorithm is about 22k calls.
 */
void R2d2lri::setCallLimit(unsigned long max_calls)
{
	if(max_calls == 0 || max_calls > (unsigned long)DEFAULT_MAX_POINTS)
	{
		di.set_max_evals(DEFAULT_MAX_POINTS);
	}
	else
	{
		di.set_max_evals((int)max_calls);
	}
}

unsigned long R2d2lri::getCallLimit() const
{
	return di.get_max_evals();
}


}

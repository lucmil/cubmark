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

#ifndef CUBMARK_MONTECARLO
#define CUBMARK_MONTECARLO

#include <cubmark/types.h>
#include <cubmark/Method.h>

#include <gsl/gsl_monte_plain.h>

namespace cb
{

/** \brief GSL MonteCarlo algorithm Adapter
 */
class MonteCarlo
:   public Method
{
public:
	MonteCarlo();
	~MonteCarlo();

	void setRelativeTolerance(double relativeTolerance);
	double getRelativeTolerance() const;

	void setAbsoluteTolerance(double absoluteTolerance);
	double getAbsoluteTolerance() const;

	void setBoundary(const Boundary& boundary);
	bool hasBoundary() const;

	void setIntegrand(IntegrandType integrand);
	IntegrandType getIntegrand() const;
	bool hasIntegrand() const;

	double compute();

	bool failed() const;
	unsigned long getCallCnt() const;
	double getAbsoluteErrorEstimate() const;
	double getRelativeErrorEstimate() const;
	void setCallLimit(unsigned long callLimit);
	unsigned long getCallLimit() const;

private:
	double absErrTol;
	double relErrTol;
	double xl[2];
	double xu[2];
	double absErrEst;
	double relErrEst;
	int gsl_status;
	size_t callCnt;
	size_t callLimit;

	gsl_monte_plain_state* state;
	gsl_monte_function F;
	gsl_rng* rng;

	static IntegrandType integrand;
	static double gslAdapter(double*, size_t dim, void* params);
	static const size_t defaultCallLimit;
};

}
#endif//CUBMARK_MONTECARLO

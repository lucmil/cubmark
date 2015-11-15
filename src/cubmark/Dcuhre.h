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

#ifndef CUBMARK_DCUHRE
#define CUBMARK_DCUHRE

#include <cubmark/Boundary.h>
#include <cubmark/Method.h>
#include <cubmark/types.h>
#include <cubmark/DcuhreIntegrand.h>

namespace cb
{

/** \brief
 */
class Dcuhre
:   public Method
{
public:
	Dcuhre();
	~Dcuhre();
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
	typedef AdapterFtorBase<DcuhreIntegrand, void, int*, double*, int*, double*>
			IntegrandAdapterType;

	int iFail;
	double absErrTol;
	double relErrTol;
	double absErrEst;
	double relErrEst;
	Boundary boundary;
	int callCnt;
	int callLimit;
	IntegrandType integrand;

	static double nop(double, double);
	static const int defaultCallLimit;
};

}
#endif//CUBMARK_DCUHRE

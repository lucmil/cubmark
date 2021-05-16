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

#ifndef CUBMARK_CUBPACK
#define CUBMARK_CUBPACK

#include <memory>
#include <cubpack.h>

#include <cubmark/adapter/adapter.h>
#include <cubmark/Method.h>
#include <cubmark/CubpackIntegrand.h>

namespace cb
{

/** \brief Cubpack++ algorithm Adapter
 */
class Cubpack
:   public Method
{
public:
	Cubpack();
	~Cubpack();

	void setRelativeTolerance(double relativeTolerance);
	double getRelativeTolerance() const;

	void setAbsoluteTolerance(double absoluteTolerance);
	double getAbsoluteTolerance() const;

	void setBoundary(const Boundary& b);
	bool hasBoundary() const;

	void setIntegrand(IntegrandType f);
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
	double computeBoundarySign(const Boundary& boundary) const;
	double boundarySign;

	bool evaluationFailed;
	unsigned long callCnt;
	unsigned long callLimit;

	double relErrTol;
	double absErrTol;
	double relErrEst;
	double absErrEst;
	IntegrandType integrand;

	std::unique_ptr<COMPOUND_REGION> region;
	EvaluationCounter cntr;
};

}
#endif//CUBMARK_CUBPACK

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

#ifndef CUBMARK_QAG2D
#define CUBMARK_QAG2D

#include <cubmark/Boundary.h>
#include <cubmark/Method.h>
#include <cubmark/RuleChain2D.h>

namespace cb
{

/** \brief QAG and QAGI product  algorithm Adapter
 *
 * Integrate a 2D function using a tensor product of the QAG algorithms from the
 * GSL library.
 *
 * Integrates in the YX order.
 * It would be equivalent to evulating an integral of the form:
 * \f[
 * \int_a^b \left\{ \int_c^d f(x,y) dy \right\} dx
 * \f]
 * Where \f$ D = [a,b] \times [c,d] \f$ is the integration region.
 */
class Qag2D
:   public Method
{
public:
	Qag2D();
	~Qag2D();
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
	int gsl_status;
	double absErrTol;
	double relErrTol;
	double absErrEst;
	double relErrEst;
	Boundary boundary;
	size_t callCnt;
	size_t callLimit;
	IntegrandType integrand;

	RuleChain2D ruleChain;

	static const size_t defaultCallLimit;
};

}
#endif//CUBMARK_QAG2D

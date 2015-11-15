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

#ifndef CUBMARK_QAGRULE
#define CUBMARK_QAGRULE

#include <gsl/gsl_integration.h>

namespace cb
{

/** \brief Integration rule for a single dimension.
 *
 * This class chooses QAG algorithm variant for integration based on the
 * type of boundary set.
 */
class QagRule
{
public:
	typedef double (*QagIntegrandType)(double, void *);

	/** \brief Constructor
	 */
	QagRule();

	/** \brief Destructor
	 */
	~QagRule();

	/** \brief Set the limit of subdivisions in this dimension
	 *
	 * \param max_div Maximum number of subdivisions
	 */
	void setDivisionLimit(size_t maxDiv);

	/** \brief Set the integration boundary
	 *
	 * \param a Lower boundary
	 * \param b Upper boundary
	 */
	void setBoundary(double a, double b);

	/** \brief Set the desired absolute error tolerance
	 *
	 * \param epsabs Maximum absolute error
	 */
	void setEpsabs(double epsabs);

	/** \brief Set the desired relative error tolerance
	 *
	 * \param epsrel Maximum relative error
	 */
	void setEpsrel(double epsrel);

	/** \brief Set the integrand to use
	 *
	 * \param integrand Function to integrate.
	 */
	void setIntegrand(QagIntegrandType integrand);

	/** \brief Evaluate the integral for this dimension
	 *
	 * Use getAbsoluteErrorEstimate() to get the results error estimate in this
	 * dimension.
	 *
	 * \return Cubature value in this dimension.
	 */
	double compute();

	/** \brief Has the evaluation failed in this dimension.
	 *
	 * \return Evaluation failed.
	 */
	bool failed() const;

	/** \brief Get the absolute error estimate
	 *
	 * \return Absoluter error estimate of the last result.
	 */
	double getAbsoluteErrorEstimate() const;
private:
	typedef int (QagRule::* RuleType)() ;

	RuleType rule;
	gsl_function F;
	gsl_integration_workspace *ws;
	int gsl_status;
	double a;
	double b;
	double epsabs;
	double epsrel;
	double result;
	double abserr;

	/** \brief Choose a QAG variant for the given boundary
	 */
	RuleType chooseRule(double a, double b) const;

	/** \brief Integrates with gsl_integration_qag
	 *
	 * \return gsl_status
	 */
	int qag();

	/** \brief Integrates with gsl_integration_qagi
	 *
	 * \return gsl_status
	 */
	int qagi();

	/** \brief Integrates with gsl_integration_qagiu
	 *
	 * \return gsl_status
	 */
	int qagiu();

	/** \brief Integrates with gsl_integration_qagil
	 *
	 * \return gsl_status
	 */
	int qagil();
};

}

#endif//CUBMARK_QAGRULE

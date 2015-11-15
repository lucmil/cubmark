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

#ifndef CUBMARK_RULECHAIN
#define CUBMARK_RULECHAIN

#include <cubmark/QagRule.h>
#include <cubmark/Method.h>

namespace cb
{

template<int>
class ActionDispatch;

/** \brief Rule chain for multi-dimensional quadrature product integration
 *
 * NOTE: This class doesn't support more than 2 dimensions at this moment.
 *
 * However it could be easily extended to handle N dimensions if the function
 * type of cb::Method::IntegrandType were to be modified to use arrays.
 * Then only evaluateIntegrand would require modififcation.
 */
template<int DIM = 2>
class RuleChain
{
public:
	friend class ActionDispatch<DIM>;

	/** \brief Constructor
	 */
	RuleChain();

	/** \brief Set the integrand.
	 *
	 * \param integrand Integrand to use for the evaluation
	 */
	void setIntegrand(Method::IntegrandType integrand);

	/** \brief Access a rule object for a dimension.
	 *
	 * \param dimension
	 */
	QagRule& getRule(size_t dimension);


	/** \brief Access a rule object for a dimension.
	 *
	 * \param dimension
	 */
	const QagRule& getRule(size_t dimension) const;

	/** \brief Get the number of integrand calls used by the last evaluation
	 *
	 * \returns Number of integrand calls or 0 (no evaluation took place)
	 */
	unsigned long getCallCnt() const;

	/**
	 * \brief Evaluate the cubature
	 *
	 * \pre A boundary had been set with QagRule::setBoundary() for each rule in
	 *      the chain
	 * \pre Integrand had been set with setIntegrand()
	 * \pre Absolute or/and relative error tolerance had been set for each
	 *      rule in the chain with QagRule::setEpsabs() and QagRule::setEpsrel()
	 *
	 * \returns Cubature value
	 */
	double compute();

private:
	typedef double (RuleChain::* ActionType)(double);

	ActionType ruleActions[DIM];
	QagRule rules[DIM];

	/** \brief Currently evaluated rule (dimension)
	 */
	unsigned rulePos;

	/** \brief Array holding point coordinates
	 */
	double x[DIM-1];

	/** \brief Number of integrand evaluations.
	 */
	unsigned long callCnt;

	Method::IntegrandType integrand;

	/** \brief Calls integrand with the coordinates stored in x
	 *
	 * \param y Coordinate value for the last dimension
	 */
	double evaluateIntegrand(double y);

	/** \brief Stores the point coordinate and calls the next rule in the chain
	 *
	 * \param a Coordinate value for the current dimension
	 */
	double storeAndCallNext(double a);

	/** \brief Call a function appropriate for the current dimension.
	 *
	 * Calls storeAndCallNext() or evaluateIntegrand().
	 *
	 * \param a Coordinate value for the current dimension
	 */
	double ruleActionDispatch(double a);

	/** \brief Initialize rule actions
	 */
	void initRuleActions();
};

}
#endif//CUBMARK_RULECHAIN

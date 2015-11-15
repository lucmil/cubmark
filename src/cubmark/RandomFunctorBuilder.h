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

#ifndef CUBMARK_RANDOM_FUNCTOR_BUILDER_H
#define CUBMARK_RANDOM_FUNCTOR_BUILDER_H

#include <string>

#include <cubmark/TestFunctorBuilder.h>
#include <cubmark/urng.h>

namespace cb
{

template<class, class ...>
class AdapterBase;

class RandomFunctorBuilder :
	public TestFunctorBuilder
{
public:
	/** \brief Destructor
	 */
	~RandomFunctorBuilder();

	/** \brief Get default boundary for this functor
	 */
	const Boundary& getDefaultBoundary();
	virtual Method::IntegrandType create();
	virtual void parseParameter(const std::string& name, const std::string& value);

	/**
	 * \defgroup DifficultyFactor Difficulty factor handling
	 *
	 * Manipulate the difficulty setting.
	 */

	/*@{*/

	/** \brief Exponent parameter
	 *
	 * Denoted as \f$ \varepsilon \f$ in literature.
	 *
	 * \param exponent New value of the exponent
	 * \return Reference to this object
	 */
	virtual RandomFunctorBuilder& exponent(double exponent);

	/** \brief Difficulty parameter
	 *
	 * Denoted as \f$ h \f$ in literature.
	 *
	 * \param difficulty New value of the difficulty parameter
	 * \return Reference to this object
	 */
	virtual RandomFunctorBuilder& difficulty(double difficulty);
	/*@}*/

protected:
	/** \brief Constructor
	 *
	 * \param defaultBoundary
	 */
	RandomFunctorBuilder(const Boundary& defaultBoundary = Boundary());

	/**
	 * \defgroup RandomParameters Setters for random parameters
	 *
	 * These methods are called every time a parameter is about to change.
	 * They are declared virtual to allow subclasses to act on those changes for
	 * special purposes. For example, to use C as the upper boundary values
	 * instead of scaling, like the G1 test function.
	 *
	 * If you override any of these, remember to forward the call back to it's
	 * superclass or the vectors won't be updated (unless you do \i not want
	 * them to change).
	 */

	/*@{*/

	/** \brief Set R parameter
	 *
	 * \param R new value
	 * \return Reference to this object
	 */
	virtual RandomFunctorBuilder& R(double R);

	/** \brief Set a scaling parameter
	 *
	 * \param C new value
	 * \param dim dimension of the scaling parameter
	 * \return Reference to this object
	 */
	virtual RandomFunctorBuilder& C(double C, unsigned long dim);

	/** \brief Set a DPS parameter
	 *
	 * Set a coordinate of the Displaced Point of Symmetry.
	 *
	 * \param x0 new value
	 * \param dim dimension of the displacement
	 * \return Reference to this object
	 */
	virtual RandomFunctorBuilder& x0(double x0, unsigned long dim);

	/** \brief Randomize parameters
	 *
	 * Difficulty factor and exponent remain unchanged.
	 */
	void randomizeParameters();

	/** \brief Divide all parameters by the difficulty factor
	 */
	void scaleParameters();
	/*@}*/

	virtual void setupAdapter() = 0;

	/** \brief Calculate the current difficulty factor
	 * \ingroup DifficultyFactor
	 *
	 * \return Difficulty factor
	 */
	double difficultyFactor() const;

	/** \brief General purpose parameter
	 * \ingroup RandomParameters
	 */
	double dR;

	/** \brief Scaling vector
	 * \ingroup RandomParameters
	 */
	double dC[2];

	/** \brief Point of Symmetry
	 * \ingroup RandomParameters
	 */
	double dx0[2];

	/** \brief Default boundary
	 */
	Boundary defaultBoundary;

	/** \brief Functor adapter
	 */
	AdapterBase<double, double, double>* ftorAdapter;
private:
	double dExponent;
	double dDifficulty;
	std::uniform_real_distribution<double> random01;
	static const std::string parameterNames[];
};

}
#endif//CUBMARK_RANDOM_FUNCTOR_BUILDER_H

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

#include <algorithm>
#include <cstddef>

#include <cubmark/adapter/adapter.h>
#include <cubmark/RandomFunctorBuilder.h>
#include <cubmark/Scanner.hpp>

namespace cb
{

RandomFunctorBuilder::RandomFunctorBuilder(const Boundary& defaultBoundary) :
	dR(1),
	defaultBoundary(0.0, 1.0, 0.0, 1.0),
	ftorAdapter(0),
	dExponent(0.0),
	dDifficulty(2.0)
{
	if(defaultBoundary.isValid())
	{
		this->defaultBoundary = defaultBoundary;
	}

	for(size_t i = 0; i < 2; ++i)
	{
		dC[i] = 1.0;
		dx0[i] = 0.0;
	}
}

RandomFunctorBuilder::~RandomFunctorBuilder()
{
	if(ftorAdapter)
	{
		ftorAdapter->unlockSlot();
	}
}

Method::IntegrandType RandomFunctorBuilder::create()
{
	randomizeParameters();
	scaleParameters();
	setupAdapter();
	return this->ftorAdapter->getPtr();
}

RandomFunctorBuilder& RandomFunctorBuilder::R(double dR)
{
	this->dR = dR;
	return *this;
}

RandomFunctorBuilder& RandomFunctorBuilder::C(double C_dim, unsigned long dim)
{
	this->dC[dim] = C_dim;
	return *this;
}

RandomFunctorBuilder& RandomFunctorBuilder::x0(double x0_dim, unsigned long dim)
{
	this->dx0[dim] = x0_dim;
	return *this;
}

RandomFunctorBuilder& RandomFunctorBuilder::exponent(double dExponent)
{
	this->dExponent = dExponent;
	return *this;
}

RandomFunctorBuilder& RandomFunctorBuilder::difficulty(double dDifficulty)
{
	this->dDifficulty = dDifficulty;
	return *this;
}

double RandomFunctorBuilder::difficultyFactor() const
{
	return (dC[0] + dC[1])* pow(2.0, dExponent) / dDifficulty;
}

void RandomFunctorBuilder::parseParameter(const std::string& name,
		const std::string& value)
{
	const ptrdiff_t paramPos = std::distance(&parameterNames[0],
			std::find(&parameterNames[0], &parameterNames[7], name));

	if(paramPos < 7)
	{
		Scanner<double> scanDbl;
		const double parameterValue = scanDbl(value);
		switch(paramPos)
		{
			case 0: R(parameterValue); break;
			case 1: C(parameterValue, 0); break;
			case 2: C(parameterValue, 1); break;
			case 3: x0(parameterValue, 0); break;
			case 4: x0(parameterValue, 1); break;
			case 5: exponent(parameterValue); break;
			case 6: difficulty(parameterValue); break;
		}
	}
	else
	{
		throw std::invalid_argument("No such parameter");
	}
}

void RandomFunctorBuilder::randomizeParameters()
{
	for(size_t i = 0; i < 2; ++i)
	{
		C(random01(urng01), i);
		x0(random01(urng01), i);
	}
	R(random01(urng01));
}

void RandomFunctorBuilder::scaleParameters()
{
	const double f = difficultyFactor();
	for(size_t i = 0; i < 2; ++i)
	{
		dC[i] /= f;
	}
	dR /= f;
}

const Boundary& RandomFunctorBuilder::getDefaultBoundary()
{
	return defaultBoundary;
}

const std::string RandomFunctorBuilder::parameterNames[] = {
	"R",
	"C_x",
	"C_y",
	"x_0",
	"y_0",
	"e",
	"h"
};

}

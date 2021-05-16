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

#include <cmath>
#include <stdexcept>

#include <boost/tokenizer.hpp>

#include <cubmark/Boundary.h>

#include <cubmark/constants.h>
#include <cubmark/algorithm.h>
#include <cubmark/debug.h>

#include <cubmark/Scanner.hpp>

using std::isnan;
using std::isinf;

namespace cb
{

Boundary::Boundary() :
	limits(2, std::make_pair(0, 0)),
	placeholders(2, std::make_pair(true, true))
{
}

Boundary::Boundary(const std::string& boundaryStr) :
	limits(2, std::make_pair(0, 0)),
	placeholders(2, std::make_pair(true, true))
{
	parseBoundaryStr(boundaryStr);
}

Boundary::Boundary(double a, double b, double c, double d) :
	limits(2, std::make_pair(0, 0)),
	placeholders(2, std::make_pair(true, true))
{
	CHECK(!isnan(a) && !isnan(b), "NaN used as outer integration boundary ");
	CHECK(!isnan(c) && !isnan(d), "NaN used as inner integration boundary ");

	setLimits(0, std::make_pair(a, b));
	setLimits(1, std::make_pair(c, d));
}

bool Boundary::isValid() const
{
	for(size_t i = 0; i < limits.size(); ++i)
	{
		if(placeholders[i].first || placeholders[i].second)
		{
			return false;
		}
	}
	return true;
}

bool Boundary::isInfinite() const
{
	for(size_t i = 0; i < limits.size(); ++i)
	{
		if(isinf(u(i)) || isinf(l(i)))
		{
			return true;
		}
	}
	return false;
}

bool Boundary::isPlane() const
{
	for(size_t i = 0; i < limits.size(); ++i)
	{
		if(!isinf(u(i)) || !isinf(l(i)))
		{
			return false;
		}
	}
	return true;
}

bool Boundary::isRegular() const
{
	const double dx = u(0) - l(0);
	for(size_t i = 1; i < limits.size(); ++i)
	{
		if(feq(dx, u(i) + l(i)))
		{
			return false;
		}
	}
	return true;
}

void Boundary::fillIn(const Boundary& source)
{
	for(size_t i = 0; i < limits.size(); ++i)
	{
		if(placeholders[i].first && !source.placeholders[i].first)
		{
			this->setL(i, source.l(i));
		}
		if(placeholders[i].second && !source.placeholders[i].second)
		{
			this->setU(i, source.u(i));
		}
	}
}

const std::pair<double, double>& Boundary::getLimits(size_t dim) const
{
	return limits.at(dim);
}

double Boundary::u(size_t dim) const
{
	return getLimits(dim).second;
}

double Boundary::l(size_t dim) const
{
	return getLimits(dim).first;
}

void Boundary::setLimits(size_t dim, const std::pair<double, double>& limits)
{
	this->limits.at(dim) = limits;
	this->placeholders.at(dim) = std::make_pair(false, false);
}

void Boundary::setU(size_t dim, double u)
{
	this->limits.at(dim).second = u;
	this->placeholders.at(dim).second = false;
}

void Boundary::setL(size_t dim, double l)
{
	this->limits.at(dim).first = l;
	this->placeholders.at(dim).first = false;
}

void Boundary::parseBoundaryStr(const std::string& boundaryStr)
{
	typedef boost::tokenizer<boost::char_separator<char> > TokenizerType;
	boost::char_separator<char> commaSep(",", 0, boost::keep_empty_tokens);
	TokenizerType tokenizer(boundaryStr, commaSep);

	TokenizerType::iterator token;
	const TokenizerType::iterator end = tokenizer.end();
	size_t i = 0;
	Scanner<double> scanDouble;
	for(token = tokenizer.begin(); token != end; ++token, ++i)
	{
		if(token->size())
		{
			const double limit = scanDouble(*token);
			const size_t dim = i/2;
			if(i % 2 == 0)
			{
				this->setL(dim, limit);
			}
			else
			{
				this->setU(dim, limit);
			}
		}
	}

}

}

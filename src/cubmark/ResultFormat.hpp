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


#include <cubmark/ResultFormat.h>

#ifndef CUBMARK_RESULT_FORMAT_HPP
#define CUBMARK_RESULT_FORMAT_HPP

#include <iostream>
#include <sstream>
#include <vector>

#include <cubmark/ResultAverage.h>
#include <cubmark/ResultMedian.h>
#include <cubmark/ResultQuantiles.h>
#include <cubmark/ResultQuality.h>
#include <cubmark/ResultSelect.h>

namespace cb
{

template<class R, class F>
inline
void ResultFormat::write(const ResultAverage<R, F>* resultAverage)
{
	std::stringstream sstr;
	sstr.width(out.width());
	sstr.setf(std::ios::fixed);
	sstr.setf(std::ios::showpoint);
	sstr.precision(1);
	sstr << resultAverage->getFieldAverage();
	out << sstr.str();
}

template<>
inline
void ResultFormat::write(const ResultAverage<double, bool>* resultAverage)
{
	std::stringstream sstr;
	sstr.width(out.width());
	sstr.precision(0);
	sstr.setf(std::ios::fixed);
	sstr << resultAverage->getFieldAverage() * 100.0 << '%';
	out << sstr.str();
}

template<class R, class T>
inline
void ResultFormat::write(const ResultQuantiles<R, T>* resultQuantiles)
{
	std::stringstream sstr;
	sstr.copyfmt(out);
	sstr.width(0);
	sstr.setf(std::ios_base::scientific);
	const std::vector<R>& quantiles(resultQuantiles->getFieldQuantiles());
	typename std::vector<R>::const_iterator i = quantiles.begin();
	sstr << "{ ";
	if(i != quantiles.end())
	{	
		sstr << (*i);
		while(++i != quantiles.end())
		{
			sstr << " " << (*i);
		}
	}
	sstr << " }";
	out << sstr.str();
}

template<class R>
inline
void ResultFormat::write(const ResultMedian<R>* resultMedian)
{
	out << resultMedian->getFieldMedian();
}

template<>
inline
void ResultFormat::write(const ResultMedian<bool>* resultMedian)
{
	out << (resultMedian->getFieldMedian() ? "PASS" : "FAIL");
}

inline
void ResultFormat::write(const ResultQuality* resultQuality)
{
	out << resultQuality->getQuality();
}

template<class R, class A>
inline
void ResultFormat::write(const ResultSelect<R, A>* resultSelect)
{
	out << resultSelect->getSelectedField();
}

template<class R, class F>
inline
void ResultFormat::write(const ResultAccumulate<R, F>* resultAccumulate)
{
	out << resultAccumulate->getAccumulator();
}

}

#endif //CUBMARK_RESULT_FORMAT_HPP

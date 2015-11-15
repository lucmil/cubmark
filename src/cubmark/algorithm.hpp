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

#include <cubmark/algorithm.h>

#ifndef CUBMARK_ALGORITHM_HPP
#define CUBMARK_ALGORITHM_HPP

#include <cstddef>
#include <cubmark/debug.h>

namespace cb
{

template<class It, class LessOp>
std::pair<It, It> median(It begin, It end, LessOp lessOp)
{
	return quantiles(begin, end, 2, lessOp)[0];
}

template<class It>
std::pair<It, It> median(It begin, It end)
{
	return quantiles(begin, end, 2, std::less<typename It::value_type>())[0];
}

template<class T>
std::pair<T*, T*> median(T* begin, T* end, std::less<T> lessOp = std::less<T>())
{
	return median<T*, std::less<T> >(begin, end, lessOp);
}

template<class It, class LessOp>
std::vector< std::pair<It, It> >
quantiles(It begin, It end, unsigned q, LessOp lessOp)
{
	CHECK(q > 1, "q has to be greater or equal 2");
	const size_t seqLen = std::distance(begin, end);
	CHECK(seqLen > 0, "Empty sequence");
	const double rankDelta = (double)seqLen / q;

	std::vector< std::pair<It, It> > quantiles;
	quantiles.reserve(q-1);

	It quantilePrev = begin;
	for(size_t i = 1; i < q && quantilePrev != end; ++i)
	{
		const double rank = (double)i * rankDelta;
		const double rankRounded = round(rank);
		const ptrdiff_t jump = (ptrdiff_t)rankRounded - (quantilePrev - begin) - 1;
		It quantile  = quantilePrev + jump;
		std::nth_element(quantilePrev, quantile, end, lessOp);
		++quantilePrev;

		std::pair<It, It> q(quantile, quantile);
		// is quantile outside the sequence?
		if(feq(rank, rankRounded))
		{
			++q.second;
		}
		quantiles.push_back(q);
		quantilePrev = q.second;
	}
	return quantiles;
}

template<class T>
std::vector< std::pair<T*, T*> >
quantiles(T* begin, T* end, unsigned q, std::less<T> lessOp = std::less<T>())
{
	return quantiles<T*, std::less<T> >(begin, end, q, lessOp);
}

}

#endif//CUBMARK_ALGORITHM_HPP


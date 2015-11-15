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

#ifndef CUBMARK_ALGORITHM_H
#define CUBMARK_ALGORITHM_H

#include <utility>
#include <algorithm>
#include <vector>

#include <cubmark/FieldLess.h>
#include <cubmark/constants.h>

namespace cb
{

/** \brief Calculate the median element of a sequence
 *
 * This algorithm is as fast as std::nth_element.
 * (which is implied to have O(n) time complexity but reorders the sequence)
 *
 * \param begin Beginning of the sequence
 * \param end End of a sequence
 * \param lessOp Instance of an ordering operator
 * \tparam It RandomAccessIterator
 * \tparam LessOp ordering operator
 * \returns Iterators pointing to elements that make up the median
 *          or make_pair(median, end)
 */
template<class It, class LessOp>
std::pair<It, It> median(It begin, It end, LessOp lessOp);

template<class It>
std::pair<It, It> median(It begin, It end);

/** \brief Calculate the q-quantiles of a sequence
 *
 * This algorithm is as fast as std::nth_element.
 * (which is implied to have O(n) time complexity but reorders the sequence)
 *
 * \param begin Beginning of the sequence
 * \param end End of a sequence
 * \param q
 * \param lessOp Instance of an ordering operator
 * \tparam It RandomAccessIterator
 * \tparam LessOp ordering operator
 * \returns vector of pairs of iterators, each pointing to a quantile or
 * 		elements surrounding the median (see cb::median)
 */
template<class It, class LessOp>
std::vector< std::pair<It, It> >
quantiles(It begin, It end, unsigned q, LessOp lessOp = std::less<typename It::value_type>());

template<class T>
std::vector< std::pair<T*, T*> >
quantiles(T* begin, T* end, unsigned q, std::less<T> lessOp = std::less<T>());

template<class Ret, Ret (Result::*MemFun)() const, class It>
inline
It minField(It begin, It end)
{
	return std::min_element(begin, end, less<Ret, MemFun>());
}

/** \brief Calculate the Kahan sum of a floating point sequence
 *
 * \param init
 * \param begin beginning of a sequence
 * \param end end of a sequence
 * \tparam It input iterator of a floating point type sequence
 */
template<class Fp>
class KahanSum
{
public:
	typedef Fp value_type;
	explicit
	KahanSum(Fp init = 0.0) :
		loBits(0.0),
		sum(init)
	{
	}

	KahanSum& operator=(const KahanSum& that)
	{
		if(this != &that)
		{
			this->loBits = that.loBits;
			this->sum = that.sum;
		}

		return *this;
	}

	KahanSum& operator=(Fp init)
	{
		this->loBits = 0.0;
		this->sum = init;

		return *this;
	}

	KahanSum& operator+=(Fp element)
	{
		// Compensate for the bits last on the last added element
		element -= loBits;
		const Fp t = sum + element;
		const Fp hiBits = t - sum;
		loBits = hiBits - element;
		sum = t;
		return *this;
	}

	Fp getSum() const
	{
		return sum;
	}
private:
	Fp loBits;
	Fp sum;
};

/** \brief Compare two floating point numbers
 *
 * Based on gsl_fcmp copyright (C) 20002 Gert Van den Eynde
 *
 * Which in turn is based on
 * fcmp 1.2.2 Copyright (c) 1998-2000 Theodore C.  Belding
 */
template<class F>
inline
int fcmp(const F x1, const F x2)
{
	int exponent;

	/* Find exponent of largest absolute value */

	{
		F max = std::max(fabs(x1), fabs(x2));
		std::frexp (max, &exponent);
	}

	/* Form a neighborhood of size  2 * delta */

	const F delta = std::ldexp (cb::eps, exponent);
	const F difference = x1 - x2;

	if (difference > delta)       /* x1 > x2 */
	{
		return 1;
	}
	else if (difference < -delta) /* x1 < x2 */
	{
		return -1;
	}
	else                          /* -delta <= difference <= delta */
	{
		return 0;                 /* x1 ~=~ x2 */
	}
}

template<class F>
inline
bool feq(const F x1, const F x2)
{
	return fcmp(x1, x2) == 0;
}

template<class F>
inline
int fcmp0(const F x)
{
	if(x > eps)
	{
		return 1;
	}
	else if(x < -eps)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

template<class F>
inline
bool feq0(const F x1)
{
	return fcmp0(x1) == 0;
}

}

#endif//CUBMARK_ALGORITHM_H


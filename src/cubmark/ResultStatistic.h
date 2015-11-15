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

#ifndef CUBMARK_RESULT_STATISTIC_H
#define CUBMARK_RESULT_STATISTIC_H

#include <cubmark/types.h>

namespace cb
{

class ResultFormat;

/** \brief Sample result processing interface
 *
 * Delegate class for calculations
 */
class ResultStatistic
{
public:
	virtual ~ResultStatistic();

	/** \brief Compute a statistic for a sequence of samples
	 *
	 * \param samples Samples to use for the statistic
	 */
	virtual void compute(SamplesRangeType samples) = 0;

	/** \brief Pretty-print the result using a visitor
	 *
	 * \todo To avoid implementing this in every subclass consider writing a
	 * 		 class template to mixin the definition.
	 *
	 * \param format Printing visitor
	 */
	virtual void write(ResultFormat& format) const;
};

}

#endif//CUBMARK_RESULT_STATISTIC_H


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

#ifndef CUBMARK_RESULTQUALITY_H
#define CUBMARK_RESULTQUALITY_H

#include <cubmark/ResultStatistic.h>
#include <cubmark/ResultFormat.h>
#include <cubmark/types.h>

namespace cb
{

/** \brief Calculates the quality value, as defined by A. Genz
 */
class ResultQuality :
	public ResultStatistic
{
	double quality;
public:
	virtual ~ResultQuality();

	/** \brief Compute the quality value for a sequence of samples
	 *
	 * \param samples Samples to use for the statistic
	 */
	void compute(SamplesRangeType samples);

	virtual void write(ResultFormat& resultFormat) const;

	/** \brief Get calculated quality of the samples
	 *
	 * \returns quality
	 */
	double getQuality() const;
};

}

#endif//CUBMARK_RESULTQUALITY_H


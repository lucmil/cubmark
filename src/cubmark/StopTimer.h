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

#ifndef CUBMARK_STOPTIMER_H
#define CUBMARK_STOPTIMER_H

extern "C"
{
#include <sys/times.h>
}

namespace cb
{

/** \brief Class for runtime measuring
 */
class StopTimer
{
public:
	/**
	 * \brief Default constructor
	 */
	StopTimer();

	/**
	 * \brief Start the timer
	 */
	void start();

	/**
	 * \brief Stop the timer
	 *
	 * The interval between call to start() and stop can be retrieved with
	 * getTime() and getTimeMs().
	 */
	void stop();

	/** \brief Get the last measured interval
	 *
	 * between the last call to start() and stop()
	 *
	 * \returns Time in CPU cycles
	 */
	unsigned long getTime() const;

	/** \brief Get the last measured interval
	 *
	 * between the last call to start() and stop()
	 *
	 * \returns Time in milliseconds
	 */
	double getTimeMs() const;

	/** \brief Get the total time measured
	 *
	 * Sum of all time intervals measured by this object.
	 *
	 * \returns Time in CPU cycles
	 */
	unsigned long getTotalTime() const;

	/** \brief Get the total time measured
	 *
	 * Sum of all time intervals measured by this object.
	 *
	 * \returns Time in milliseconds
	 */
	double getTotalTimeMs() const;
private:
	/**
	 * \brief Total time measured
	 *
	 * CPU cycles
	 */
	unsigned long total;

	/**
	 * \brief Last measured interval
	 *
	 * CPU cycles
	 */
	unsigned long last;

	/**
	 * \brief Start() mark
	 */
	tms mark;

	/**
	 * \brief Clock tics per second
	 */
	static const long clocksPerSecond;
};

}
#endif//CUBMARK_STOPTIMER_H

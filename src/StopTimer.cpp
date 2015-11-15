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

#include <stdexcept>

extern "C"
{
#include <unistd.h>
}

#include <cubmark/StopTimer.h>
#include <cubmark/debug.h>

namespace cb
{

StopTimer::StopTimer() :
	total(0),
	last(0)
{
	mark.tms_utime = 0;
	mark.tms_stime = 0;
	mark.tms_cutime = 0;
	mark.tms_cstime = 0;
}

void StopTimer::start()
{
	times(&mark);
}

void StopTimer::stop()
{
	tms stop = {0,0,0,0};
	if (times(&stop) == (clock_t)-1)
	{
		throw std::runtime_error("Couldn't get CPU time.");
	}
	if(stop.tms_utime >= mark.tms_utime)
	{
		last = (unsigned long)(stop.tms_utime - mark.tms_utime);
	}
	else
	{
		// Timer overflowed
		last = (unsigned long)(stop.tms_utime);
		last += (unsigned long)((clock_t)-2 - mark.tms_utime);
	}
	total += last;
}

unsigned long StopTimer::getTotalTime() const
{
	return total;
}

double StopTimer::getTotalTimeMs() const
{
	return (double)total * 1000 /(double)clocksPerSecond;
}

unsigned long StopTimer::getTime() const
{
	return last;
}

double StopTimer::getTimeMs() const
{
	return (double)last * 1000 /(double)clocksPerSecond;
}

const long StopTimer::clocksPerSecond(sysconf(_SC_CLK_TCK));

}


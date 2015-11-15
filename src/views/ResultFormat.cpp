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

#include <cubmark/ResultFormat.hpp>
#include <cubmark/debug.h>

namespace cb
{

ResultFormat::ResultFormat(std::ostream& out) :
	out(out)
{
}

ResultFormat::~ResultFormat()
{
}

void ResultFormat::write(const ResultStatistic* /*resultStatistic*/)
{
	LOG(WARN, "Unknown ResultStatistic type.");
}

std::ostream& operator<<(std::ostream& output, const ResultStatistic& result)
{
	ResultFormat defaultFormat(output);
	result.write(defaultFormat);
	return output;
}

}


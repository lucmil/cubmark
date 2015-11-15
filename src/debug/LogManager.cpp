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

#include <cubmark/LogManager.h>

#include <iostream>
#include <stdexcept>

namespace cb
{

LogManager::LogManager() :
	logStream(&std::cerr),
	curLogLevel(LVL_INFO),
	isBusy(false)
{
	if(this != &LogManager::instance)
	{
		throw std::logic_error(
				"Only one cb::LogManager instance is allowed.");
	}
}

void LogManager::setLogLevel(LogLevelType l)
{
	if(isBusy)
	{
		throw std::runtime_error(
				"Can't change log level while stream is busy.");
	}

	curLogLevel = l;
}

LogManager::LogLevelType LogManager::getLogLevel()
const
{
	return curLogLevel;
}

void LogManager::setOstream(std::ostream& os)
{
	if(isBusy)
	{
		throw std::runtime_error(
				"Can't change logging stream while stream is busy.");
	}

	logStream->flush();
	logStream = &os;
}

std::ostream& LogManager::getStream(LogLevelType l)
{
	if(isBusy)
	{
		throw std::runtime_error("Stream is busy.");
	}


	if(curLogLevel >= l)
	{
		isBusy = true;
		return *logStream;
	}
	return null;
}

void LogManager::closeStream(std::ostream& os)
{
	if((&os != logStream) && (&os != &null))
	{
		throw std::runtime_error(
				"Tried to close a stream different then used by the log manager.");
	}

	logStream->flush();
	if(&os != &null)
	{
		isBusy = false;
	}
}

LogManager& LogManager::getInstance()
{
	return instance;
}

LogManager LogManager::instance;

}


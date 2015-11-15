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

/** \file
 * \brief Log manager facilities
 */
#ifndef CUBMARK_LOGMANAGER_H
#define CUBMARK_LOGMANAGER_H

#include <iosfwd>
#include <cubmark/NullOstream.h>

namespace cb
{

/** \brief Simple log manager
 *
 * Small logging class with the ability of logging messages of 4 different
 * priorities and choice of output stream.
 *
 * The default output stream for logs is std::cerr.
 *
 * The user interface consists of three macros:
 * LOG, LOG_STREAM, LOG_LEVEL
 */
class LogManager
{
public:
	/** \brief Basic constructor
	 *
	 * Can be called only once.
	 */
	LogManager();

	/** \brief Instance access
	 *
	 * \returns the LogManager instance.
	 */
	static LogManager& getInstance();

	/** \brief Available message priorities
	 * The available log levels are (in order of priority):
	 * - LVL_FATAL - unrecovarable error which usually aborts the program
	 * - LVL_WARN - recovarable error which affects
	 * - LVL_INFO - general, terse run-time information
	 * - LVL_TRACE - detailed debugging information
	 *
	 * Default logging priority level is LVL_INFO
	 */
	enum LogLevelType
	{
		LVL_FATAL = 0,
		LVL_WARN = 1,
		LVL_INFO = 2,
		LVL_TRACE = 3
	};

	/** \brief Set the logging level
	 *
	 * \param l message log level to pass through
	 */
	void setLogLevel(LogLevelType l);

	/** \brief Get current logging level
	 *
	 * \returns Current logging level
	 */
	LogLevelType getLogLevel() const;

	/** \brief Retrieve a logging stream to send a message.
	 *
	 * Note: Null streams are never held.
	 * The stream has to be closed as soon as the message is sent.
	 *
	 * \pre Log stream is not held
	 * \post Log stream is held
	 * \param l Priority of the message
	 * \returns Log stream or an instance of NullOstream
	 */
	std::ostream& getStream(LogLevelType l);

	/** \brief Set the stream where to send the logs
	 *
	 * \pre Current log stream not held
	 * \param os New stream to send logs to
	 */
	void setOstream(std::ostream& ostream);

	/** \brief Close (release) a stream after sending a message
	 *
	 * \param os Stream returned by getStream()
	 */
	void closeStream(std::ostream& ostream);
private:
	NullOstream<std::ostream::char_type, std::ostream::traits_type> null;

	std::ostream *logStream;
	LogLevelType curLogLevel;
	bool isBusy;

	static LogManager instance;
};

#define _Q(x) #x
#define Q(x) _Q(x)
#define CUBMARK_LOG_PREFIX __FILE__ ":" Q(__LINE__) ": "

#define LOG_RAW(lvl, msg) \
		{\
			std::ostream& os(\
					cb::LogManager::getInstance().getStream(\
						cb::LogManager::LVL_##lvl)); \
			os << msg << '\n'; \
			cb::LogManager::getInstance().closeStream(os); \
		}

/** \brief Send a message to the log
 *
 * The message can be a chain stream output operatios.
 * Example:
 * \code
 * LOG(INFO, "The application ran for "<< x <<" seconds\n");
 * \endcode
 *
 * \param lvl Message priority
 * \param msg Message
 */
#define LOG(lvl, msg) LOG_RAW(lvl, CUBMARK_LOG_PREFIX << msg)

/** \brief Set the logging output stream
 * \param os New output stream
 */
#define LOG_STREAM(os) \
		cb::LogManager::getInstance().setOstream(os)

/** \brief Set the logging level
 * \param lvl Minimum priority of messages which should be sent to the log
 */
#define LOG_LEVEL(lvl) \
		cb::LogManager::getInstance().setLogLevel(lvl)

/** \brief Set the logging level
 * \param lvl FATAL, WARN, INFO, TRACE
 */
#define LOG_DEFAULT_LEVEL(lvl) \
		LOG_LEVEL(cb::LogManager::LVL_##lvl)

}
#endif//CUBMARK_LOGMANAGER_H

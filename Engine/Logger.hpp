#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

#ifndef __FUNCTION__
#define __FUNCTION__ "?"
#endif

/*
 * @credit This macro thanks to Guichan code.
 *
 * A macro used to create a standard exception object.
 * What it basicly does is that it creates a new exception
 * and automatically sets the filename and line number where
 * the exception occured by using other compiler macros.
 */
#define LOG(mess) Logger::log(mess)
#define LOG_TO_CONSOLE(mess) Logger::log(mess, true)
#define ERROR(mess) Logger::error(mess, __FUNCTION__, __FILE__, __LINE__)

/**
 * @brief The logger allows output to be displayed to the console.
 * To use simply include Logger.hpp and call LOG() or ERROR() with
 * the log or error message, respectively.
 */
class Logger
{
	public:
	virtual ~Logger();

	/**
	 * @brief Display an error with the specified location information.
	 * @param error The error message.
	 * @param function The erroring function.
	 * @param filename The erroring filename.
	 * @param line The erroring line.
	 */
	static void error(const std::string& error, const std::string& function = "00:00()", const std::string& filename = "00.xpp", unsigned int line = 0);

	/**
	 * @brief Log an informational message.
	 * @param message The message.
	 * @param force Force the log message to the console.
	 */
	static void log(const std::string& message, bool force = false);

	protected:
	// The game logger.
	static Logger mLogger;

	// The output log file.
	std::ofstream m_logFile;

	private:
    /**
     * @brief Constructs a logger. The logger outputs messages, warnings and errors to inform the user.
     */
    Logger();

	/**
	 * @brief Display the provided string.
	 * @param s The string message to display.
	 * @param force Force the log message to the console.
	 */
	void mLog(const std::string& s, bool force = false);
};

#endif

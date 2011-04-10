#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <stdexcept>

#include "../guichan.hpp"

/**
 * @brief The logger is accessed via Logger::log() to store information to the logfile.
 *
 * The logger is mainly intended to provide messages to the user (via command line) but
 * can additionally be used for warnings or errors.
 */
class Logger
{
	public:
	virtual ~Logger();

	/**
	 * @brief Checks to see if a logger is created and deletes the object.
	 */
	static void terminate();

	/**
	 * @brief A guichan error.
	 * @param e The error.
	 */
	static void error(const gcn::Exception& e);

	/**
	 * @brief A domain error.
	 * @param e The error.
	 */
	static void error(const std::domain_error& e);

	/**
	 * @brief An invalid argument error.
	 * @param e The error.
	 */
	static void error(const std::invalid_argument& e);

	/**
	 * @brief A length error.
	 * @param e The error.
	 */
	static void error(const std::length_error& e);

	/**
	 * @brief An out of range error.
	 * @param e The error.
	 */
	static void error(const std::out_of_range& e);

	/**
	 * @brief A logic error.
	 * @param e The error.
	 */
	static void error(const std::logic_error& e);

	/**
	 * @brief A range error.
	 * @param e The error.
	 */
	static void error(const std::range_error e);

	/**
	 * @brief An overflow error.
	 * @param e The error.
	 */
	static void error(const std::overflow_error& e);

	/**
	 * @brief An underflow error.
	 * @param e The error.
	 */
	static void error(const std::underflow_error& e);

	/**
	 * @brief A runtime error.
	 * @param e The error.
	 */
	static void error(const std::runtime_error& e);

	/**
	 * @brief A general std error.
	 * @param e The error.
	 */
	static void error(const std::exception& e);

	/**
	 * @brief A non-exception error.
	 * @param error The error.
	 */
	static void error(const std::string& error);

	/**
	 * @brief Log an informational message.
	 * @param message The message.
	 */
	static void log(const std::string& message);

	/**
	 * @brief Log a warning.
	 * @param warning The warning.
	 */
	static void warn(const std::string& warning);

	protected:
	/**
	 * The game logger.
	 */
	static Logger* mLogger;

    /**
     * @brief Log a message.
     * @param message The message to log.
     *
     * @note The logger is created in the first call to this method.
     */
	static void mLog(const std::string& message);

	/**
	 * The output log file.
	 */
	std::ofstream m_logFile;

	private:
    /**
     * @brief Constructs a logger. The logger outputs messages, warnings and errors to inform the user.
     */
    Logger();

	/**
	 * @brief Display the provided string.
	 * @param s The string message to display.
	 */
	void m_output(const std::string& s);

	/**
	 * The log file.
	 */
	static const char* FILE_LOG;
};

#endif

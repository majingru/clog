#include "clog.h"
#include <iostream>
#include <ctime>
#include <sstream>

namespace clog
{
    static const char *LEVELS[3] = {"DEBUG", "INFO", "ERROR"};

    static std::string current_time()
    {
        time_t t = time(NULL);
        struct tm *tt;
        tt = localtime(&t);
        std::stringstream ss;
        ss << (tt->tm_year + 1900) << "-" << tt->tm_mon << "-" << tt->tm_mday << " " << tt->tm_hour << ":" << tt->tm_min << ":" << tt->tm_sec;
        return ss.str();
    }

    Logger &Logger::operator<<(NulLog end)
    {
        if (out == nullptr)
        {
            std::cout << std::endl;
        }
        else
        {
            *out << std::endl;
        }
        return *this;
    }

    template <typename T>
    Logger &Logger::operator<<(T t)
    {

        if (out != nullptr)
        {
            *out << t;
        }
        else
        {
            std::cout << t;
        }

        return *this;
    }

    bool is_enable(LogLevel level)
    {
        return level >= Logger::instance()->getLevel();
    }

    void set_log_level(std::string level)
    {
        LogLevel level_;
        if (level == "debug" || level == "DEBUG" || level == "Debug")
        {
            level_ = clog::DEBUG_;
        }
        if (level == "info" || level == "INFO" || level == "Info")
        {
            level_ = clog::INFO_;
        }
        if (level == "ERROR" || level == "ERROR" || level == "ERROR")
        {
            level_ = clog::ERROR_;
        }
        Logger::instance()->setLogLevel(level_);
    }

    void set_log_file(std::string log_file)
    {
        Logger::instance()->setLogFile(log_file);
    }

    Logger &log_log(LogLevel level, const char *file, const char *func, int line)
    {
        std::string s(file);
        size_t i = s.find_last_of('\\');
        if (i == 0)
        {
            i = s.find_last_of('/');
        }

        if (i != 0)
        {
            s = s.substr(i + 1, s.length() - i);
        }

        *Logger::instance() << current_time() << " - " << LEVELS[level] << " - [" << s << ":" << func << ":" << line << "] - ";
        return *Logger::instance();
    }

    bool NulLog::operator==(Logger &log)
    {
        return true;
    }
} // namespace clog

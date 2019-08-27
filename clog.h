/**
  * clog header. simple log lib for cpp , require C++11. 
  * author : majingru@oneapm.com
  * date :  2019-08-27 16:26:18 
  * version:  1.0
  * copyright (C) 2008-2019 oneapm.com. all rights reserved.    
  */
#pragma once
#include <string>
#include <memory>
#include <fstream>

namespace clog {
    enum LogLevel{DEBUG_, INFO_, ERROR_};

    class NulLog;

    class Logger {

    private:
        Logger() = default;
        virtual ~Logger() = default;

        LogLevel level_;
        std::shared_ptr<std::ofstream> out;
    public:
        static Logger *instance()
        {
            static Logger ol;
            return &ol;
        }

        Logger &operator<<(NulLog);

        template <typename T>
        Logger &operator<<(T t);

        void setLogFile(std::string log_file)
        {
            out.reset(new std::ofstream);
            out->open(log_file, std::ofstream::app);
        }

        void setLogLevel(LogLevel level)
        {
            level_ = level;
        }

        LogLevel getLevel()
        {
            return level_;
        }
    };

    class NulLog
    {
    public:
        bool operator==(Logger &);
    };
    static NulLog endl;

    bool is_enable(LogLevel level);

    void set_log_level(std::string level);

    void set_log_file(std::string file);

    Logger &log_log(LogLevel level, const char *file, const char *func, int line);   
    
} // namespace clog


#define LOG_LOG(LEVEL) clog::NulLog() == clog::log_log(LEVEL, __FILE__, __func__, __LINE__)
#define LogDebug clog::is_enable(clog::DEBUG_) && LOG_LOG(clog::DEBUG_)
#define LogInfo clog::is_enable(clog::INFO_) && LOG_LOG(clog::INFO_)
#define LogError clog::is_enable(clog::ERROR_) && LOG_LOG(clog::ERROR_)

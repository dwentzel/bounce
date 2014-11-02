/*
 * LogManager.h
 *
 *  Created on: 31 maj 2013
 *      Author: daniel
 */

#ifndef BOUNCE_LOGMANAGER_H_
#define BOUNCE_LOGMANAGER_H_

#include <memory>
#include <vector>
#include "logger.h"


namespace bounce {
    
    class LogOutput {
    public:
        virtual ~LogOutput() = 0;
        virtual void output(const std::wstring& message) = 0;
    };
    
    inline LogOutput::~LogOutput() {}
    
    class StdoutLogOutput : public LogOutput {
    public:
        virtual void output(const std::wstring& message);
    };
    
    inline void StdoutLogOutput::output(const std::wstring& message)
    {
        std::wcout << message;
    }
    
    class LogStreamBuffer : public std::wstringbuf {
    private:
        std::vector<std::unique_ptr<LogOutput>> outputs_;
    public:
        virtual int sync()
        {
            std::wstring data = str();
            //                std::wcout << str();
            
            for (std::vector<std::unique_ptr<LogOutput>>::iterator i = outputs_.begin(); i != outputs_.end(); ++i) {
                (*i)->output(data);
            }
            
            str(L"");
            return 0;
        }
        
        void AddOutput(std::unique_ptr<LogOutput> output) {
            outputs_.push_back(std::move(output));
        }
    };
    
    class LogStream : public std::wostream {
    private:
        
        LogStreamBuffer buffer_;
        
    public:
        LogStream();
        
        void AddOutput(std::unique_ptr<LogOutput> output);
        
    };
    
    inline LogStream::LogStream() : std::wostream(&buffer_) {}
    
    inline void LogStream::AddOutput(std::unique_ptr<LogOutput> output)
    {
        buffer_.AddOutput(std::move(output));
    }
    
    inline std::wostream& operator<<(std::wostream& out, const std::string& str)
    {
        std::copy(str.begin(), str.end(), std::ostream_iterator<char, wchar_t>(out));
        return out;
    }
    
    //std::LogStream&
    
    class LogManager {
    private:
        LogManager() : logger_(nullptr), max_log_level_(LOG_LEVEL_DEBUG)
        {
            log_stream_.AddOutput(std::unique_ptr<LogOutput>(new StdoutLogOutput()));
        }
        
        LogManager(const LogManager&) = delete;
        ~LogManager();
        
        void operator=(const LogManager&);
        
        std::unique_ptr<Logger> logger_;
        
        LogStream log_stream_;
        
        LogLevel max_log_level_;
        
    public:
        static LogManager& instance() {
            static LogManager instance;
            return instance;
        }
        
        LogLevel max_log_level() const
        {
            return max_log_level_;
        }
        
        void max_log_level(LogLevel log_level)
        {
            max_log_level_ = log_level;
        }
        
        void set_logger(Logger* logger);
        
        std::wostream& Log(const LogLevel& log_level)
        {
            //            log_stream_ << log_level;
            
            return log_stream_;
        }
    };
    
    
    inline LogManager::~LogManager() {
        //delete logger;
    }
    
}
#endif // BOUNCE_LOGMANAGER_H_

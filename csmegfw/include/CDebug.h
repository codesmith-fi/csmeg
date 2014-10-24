#ifndef CDEBUG_H
#define CDEBUG_H

#include <iostream>
#include <sstream>
#include <boost/noncopyable.hpp>

namespace csmeg
{
    namespace Debug
    {
        enum class DebugLogLevel : int
        {
            INFO = 0,
            WARN = 1,
            ERROR = 2
        };

        class CLoggerSettings : public boost::noncopyable
        {
        public:
            static CLoggerSettings& instance() {
                static CLoggerSettings csi;
                return csi;
            }

            DebugLogLevel getLogLevel() const {
                return m_logLevel;
            }

            void setLogLevel(DebugLogLevel level) {
                m_logLevel = level;
            }

        private:
            CLoggerSettings() : m_logLevel(DebugLogLevel::ERROR) { };

        private: // data
            DebugLogLevel m_logLevel;
        };

        class CLogger : public boost::noncopyable
        {
        public:
            CLogger(DebugLogLevel severity = DebugLogLevel::ERROR) {
                m_buffer.clear();
                std::string sevStr;
                if(severity == DebugLogLevel::ERROR) {
                    sevStr = "ERROR";
                } else if(severity == DebugLogLevel::WARN) {
                    sevStr = "WARN";
                } else {
                    sevStr = "INFO";
                }
                m_buffer << sevStr << ": ";
            }

            ~CLogger() {
                m_buffer << std::endl;
                std::cerr << m_buffer.str();
            }

            template <typename T>
            CLogger& operator<<(T const & value) {
                m_buffer << value;
                return *this;
            }

            static void setLogLevel(DebugLogLevel level)
            {
                CLoggerSettings::instance().setLogLevel(level);
            }

            private:
                std::ostringstream m_buffer;
        };
    }
 }

using namespace csmeg::Debug;

#define LOG_INFO() \
    if(CLoggerSettings::instance().getLogLevel() <= DebugLogLevel::INFO) CLogger(DebugLogLevel::INFO)
#define LOG_WARN() \
    if(CLoggerSettings::instance().getLogLevel() <= DebugLogLevel::WARN) CLogger(DebugLogLevel::WARN)
#define LOG_ERROR() \
    if(CLoggerSettings::instance().getLogLevel() <= DebugLogLevel::ERROR) CLogger(DebugLogLevel::ERROR)

#endif // CDEBUG_H

#ifndef CDEBUG_H
#define CDEBUG_H

#include <ostream>
#include <boost/noncopyable.hpp>
/*
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
*/

namespace csmeg
{
    namespace Debug
    {
        class CDebug : public boost::noncopyable
        {
        public:
            static CDebug& Instance() {
                static CDebug instance;
                return instance;
            }

            void SetLogLevel()
            {
            }

            private:
                CDebug() { };
            private:
        //        std::ostream m_output;
        };
    }
}
#endif // CDEBUG_H

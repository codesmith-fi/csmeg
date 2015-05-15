#ifndef CSMEGEXCEPTION_H
#define CSMEGEXCEPTION_H

#include <string>
#include <sstream>

namespace csmeg
{
    class CSmegException
    {
        public:
            CSmegException() : m_reason("no reason")
            {
            }

            CSmegException(const std::string& msg) : m_reason(msg)
            {
            }

            CSmegException(const std::string& msg, int param1)
            {
                std::ostringstream sserr;
                sserr << msg << param1;
                m_reason = sserr.str();
            }

            CSmegException(const std::string& msg, const std::string& param1)
            {
                std::ostringstream sserr;
                sserr << msg << param1;
                m_reason = sserr.str();
            }

            std::string what() const
            {
                return m_reason;
            }

        private:
            std::string m_reason;

    };

} // namespace csmeg

#endif // CSMEGEXCEPTION_H

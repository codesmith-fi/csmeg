#ifndef CSMEGEXCEPTION_H
#define CSMEGEXCEPTION_H

#include <stdexcept>
#include <string>

namespace csmeg
{

class CSmegException : public std::runtime_error
{
    public:
        CSmegException(const std::string& what_arg) : std::runtime_error(what_arg)
        {
        }
};

} // namespace csmeg

#endif // CSMEGEXCEPTION_H

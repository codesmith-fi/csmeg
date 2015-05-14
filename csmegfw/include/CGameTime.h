#ifndef CGAMETIME_H
#define CGAMETIME_H

#include <inttypes.h>

namespace csmeg
{

class CGameTime
{
    public:
        CGameTime();
        CGameTime(const CGameTime& other);
        virtual ~CGameTime();

        CGameTime& operator=(const CGameTime& other);
        CGameTime& operator+=(const CGameTime& rhs);
        CGameTime& operator-=(const CGameTime& rhs);
    public: // New methods
        void reset();
        void update();

        uint32_t getTotalMsec() const { return m_CurrentTicks - m_StartTicks; }
        uint32_t getElapsedMsec() const { return m_CurrentTicks - m_PreviousTicks; }
        float getElapsedSeconds() const { return static_cast<float>(getElapsedMsec()) / 1000.0f; }

    protected:
    private: // Data
        uint32_t m_StartTicks;
        uint32_t m_CurrentTicks;
        uint32_t m_PreviousTicks;
};

} // namespace csmeg

#endif // CGAMETIME_H

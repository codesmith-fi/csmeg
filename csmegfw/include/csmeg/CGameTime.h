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
        void Reset();
        void Update();

        uint32_t TotalMsec() const;
        uint32_t ElapsedMsec() const;
        float ElapsedSeconds() const;

    protected:
    private: // Data
        uint32_t m_StartTicks;
        uint32_t m_CurrentTicks;
        uint32_t m_PreviousTicks;
};

} // namespace csmeg

#endif // CGAMETIME_H

#ifndef CGAMETIME_H
#define CGAMETIME_H

//#include <SDL2/SDL.h>
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

        uint32_t Total() const;
        uint32_t Elapsed() const;

    protected:
    private: // Data
        uint32_t m_StartTicks;
        uint32_t m_CurrentTicks;
        uint32_t m_PreviousTicks;
};

} // namespace csmeg

#endif // CGAMETIME_H

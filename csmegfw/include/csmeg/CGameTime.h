#ifndef CGAMETIME_H
#define CGAMETIME_H

#include <SDL2/SDL.h>

namespace csmeg
{

class CGameTime
{
    public:
        CGameTime();
        virtual ~CGameTime();
        CGameTime(const CGameTime& other);
        CGameTime& operator=(const CGameTime& other);
    public: // New methods
        void Reset();
        void Update();

        Uint32 Total() const;
        Uint32 Elapsed() const;
    protected:
    private: // Data
        Uint32 m_StartTicks;
        Uint32 m_CurrentTicks;
        Uint32 m_PreviousTicks;
};

} // namespace csmeg

#endif // CGAMETIME_H

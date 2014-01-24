#ifndef CGAME_H
#define CGAME_H

#include <csmeg/CGameTime.h>
#include <csmeg/CDrawableGameObject.h>

namespace csmeg
{
    class CGame : public CDrawableGameObject
    {
        public: // Constructors and destructor
            CGame();
            virtual ~CGame();
        public: // New methods
            void Run();
            void Stop();
        private: // From CGameObject
            bool Initialize();
            void Release();
        private:
            bool m_IsRunning;
            CGameTime m_GameTime;
    };
}
#endif // CGAME_H

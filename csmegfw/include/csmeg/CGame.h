#ifndef CGAME_H
#define CGAME_H

#include <csmeg/CGameTime.h>

namespace csmeg
{
    class CGame
    {
        public: // Constructors and destructor
            CGame();
            virtual ~CGame();
        public: // New methods
            void Run();
            void Stop();
        protected: // New virtual methods
            virtual void OnRender(const CGameTime& gameTime) const;
            virtual void OnUpdate(const CGameTime& gameTime);
            virtual bool OnInitialize();
            virtual void OnRelease();

        private:
            bool m_IsRunning;
            bool m_IsInitialized;
            CGameTime m_GameTime;
    };
}
#endif // CGAME_H

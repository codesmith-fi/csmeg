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
            virtual void OnDraw(const CGameTime& gameTime) const = 0;
            virtual void OnUpdate(const CGameTime& gameTime) = 0;
            virtual bool OnInitialize() = 0;
            virtual void OnRelease() = 0;
        private: // New methods
            void Draw(const CGameTime& gameTime) const;
            void Update(const CGameTime& gameTime);
            bool Initialize();
            void Release();

        private:
            bool m_IsRunning;
            bool m_IsInitialized;
            CGameTime m_GameTime;
    };
}
#endif // CGAME_H

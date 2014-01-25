#ifndef CGAME_H
#define CGAME_H

#include <csmeg/CGameTime.h>
#include <csmeg/CDrawableGameObject.h>
#include <csmeg/CEvents.h>

namespace csmeg
{
    // Forward declarations
    class CGraphicsContext;

    /**
     * Game base class
     */
    class CGame : public CDrawableGameObject
    {
        public: // Constructors and destructor
            CGame();
            virtual ~CGame();

        public: // New methods
            void Run();
            void Stop();

            CGameTime& GameTime() { return *m_GameTime; }
            CEvents& Events() { return *m_Events; }

        public: // Getters
            CGraphicsContext& GraphicsContext() const;

        private: // From CGameObject
            bool Initialize();
            void Release();

        private:
            CGraphicsContext* m_GraphicsContext;
            CEvents* m_Events;
            CGameTime* m_GameTime;

            bool m_IsRunning;
            int m_MinimumUpdateInterval;
    };
}
#endif // CGAME_H

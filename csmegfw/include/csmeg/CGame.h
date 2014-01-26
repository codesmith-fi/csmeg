#ifndef CGAME_H
#define CGAME_H

#include <csmeg/CGameTime.h>
#include <csmeg/CDrawableGameObject.h>
#include <csmeg/CEvents.h>
#include <csmeg/MInputEventListener.h>

namespace csmeg
{
    // Forward declarations
    class CGraphicsContext;

    /**
     * Game base class
     */
    class CGame : public CDrawableGameObject, public MInputEventListener
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

        protected: // From MInputEventListener
            void OnEvent(SDL_Event& event);

        private:
            void SetupGame();
            void FreeGame();

        private:
            CGraphicsContext* m_GraphicsContext;
            CEvents* m_Events;
            CGameTime* m_GameTime;

            bool m_IsRunning;
            bool m_GameIsSetup;
            int m_MinimumUpdateInterval;
    };
}
#endif // CGAME_H

#ifndef CGAME_H
#define CGAME_H

#include <CGameTime.h>
#include <CDrawableGameObject.h>
#include <CEvents.h>
#include <CGraphicsContext.h>
#include <MInputEventListener.h>
#include <thread>

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
            void run();
            void stop();

            CGameTime& getGameTime() { return *m_GameTime; }
            CEvents& getEvents() { return *m_Events; }

        public: // Getters
            CGraphicsContext& getGraphicsContext() const;

        protected: // From MInputEventListener
            void onEvent(SDL_Event& event);

        private:
            void setupGame();
            void freeGame();

            void renderThreadMain() const;

        private:
            std::thread m_renderThread;
            CGraphicsContext* m_GraphicsContext;
            CEvents* m_Events;
            CGameTime* m_GameTime;

            bool m_IsRunning;
            bool m_GameIsSetup;
            int m_MinimumUpdateInterval;
    };
}
#endif // CGAME_H

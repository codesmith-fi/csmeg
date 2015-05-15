#ifndef CGAME_H
#define CGAME_H

#include <CGameTime.h>
#include <CDrawableGameObject.h>
#include <CGraphicsContext.h>
#include <MInputEventListener.h>

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
            void run();
            void stop();

			void setFpsLimit(uint32_t fpsLimit);

            CGameTime& getGameTime() { return *m_GameTime; }

        public: // Getters
            CGraphicsContext& getGraphicsContext() const;

        protected: // events
            virtual void onEvent(SDL_Event& event);

        private:
            void setupGame();
            void freeGame();
            void processEvents();
            void processDraw() const;
            void renderThreadMain() const;

        private:
            CGraphicsContext* m_GraphicsContext;
            CGameTime* m_GameTime;

            bool m_IsRunning;
            bool m_GameIsSetup;
            uint32_t m_MinimumUpdateInterval;
    };
}
#endif // CGAME_H

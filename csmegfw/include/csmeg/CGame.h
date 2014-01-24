#ifndef CGAME_H
#define CGAME_H

#include <csmeg/CGameTime.h>
#include <csmeg/CDrawableGameObject.h>

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
        public: // Getters
            CGraphicsContext& GraphicsContext() const;

        private: // From CGameObject
            bool Initialize();
            void Release();

        private:
            CGraphicsContext* m_GraphicsContext;
            bool m_IsRunning;
            CGameTime m_GameTime;
    };
}
#endif // CGAME_H

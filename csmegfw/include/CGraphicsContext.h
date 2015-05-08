#ifndef CSURFACE_H
#define CSURFACE_H

#include <CObjectBase.h>
#include <SDL2/SDL_video.h>

namespace csmeg
{

class CGraphicsContext : public CObjectBase
{
    enum {
        DefaultWindowWidth = 640,
        DefaultWindowHeight = 400,
    };

    public:
        CGraphicsContext();
        CGraphicsContext(int X, int Y);

        virtual ~CGraphicsContext();

        int getWidth() const
        {
            return m_Width;
        }

        int getHeight() const
        {
            return m_Height;
        }

        void setSize(int X, int Y);

        void setFullScreen(bool enabled);
        void setVsync(bool enabled);
        void clearScreen();
        void updateScreen();

    protected: // from CObjectBase
        bool onInitialize();
        void onRelease();

    private: // new methods
        void freeContext();

    private: // unimplemented
        CGraphicsContext& operator=(const CGraphicsContext& other);
        CGraphicsContext(const CGraphicsContext& other);

    private:
        SDL_Window* m_Window;
        SDL_GLContext m_GLContext;

        int m_Width;
        int m_Height;
		bool m_VSyncEnabled;
};

}

#endif // CSURFACE_H

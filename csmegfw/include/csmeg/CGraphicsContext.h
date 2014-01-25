#ifndef CSURFACE_H
#define CSURFACE_H

#include <csmeg/CObjectBase.h>
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
        CGraphicsContext(int width, int height);

        virtual ~CGraphicsContext();

        int Width() const
        {
            return m_Width;
        }

        int Height() const
        {
            return m_Height;
        }

    protected: // from CObjectBase
        bool OnInitialize();
        void OnRelease();

    private:
        SDL_Window* m_Window;
        SDL_GLContext m_GLContext;

        int m_Width;
        int m_Height;
};

}

#endif // CSURFACE_H

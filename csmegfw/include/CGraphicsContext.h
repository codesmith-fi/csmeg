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

        int Width() const
        {
            return m_Width;
        }

        int Height() const
        {
            return m_Height;
        }

        void SetSize(int X, int Y);

    protected: // from CObjectBase
        bool onInitialize();
        void onRelease();
        void FreeContext();

    private: // unimplemented
        CGraphicsContext& operator=(const CGraphicsContext& other);
        CGraphicsContext(const CGraphicsContext& other);

    private:
        SDL_Window* m_Window;
        SDL_GLContext m_GLContext;

        int m_Width;
        int m_Height;
};

}

#endif // CSURFACE_H

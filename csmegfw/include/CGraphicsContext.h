#ifndef CSURFACE_H
#define CSURFACE_H

#include <CObjectBase.h>
#include <Color.h>
#include <CShaderProgram.h>

#include <SDL2/SDL_video.h>
#include <memory>

namespace csmeg
{
    class TRectangle;

    class CGraphicsContext : public CObjectBase
    {
        enum
        {
            DefaultWindowWidth = 640,
            DefaultWindowHeight = 400,
        };

    public:
        CGraphicsContext();
        CGraphicsContext(int X, int Y);

        virtual ~CGraphicsContext();

        int getWidth() const { return m_Width; }
        int getHeight() const { return m_Height; }

        void setSize(int X, int Y);

        void setFullScreen(bool enabled);
        void setVsync(bool enabled);
        void clearScreen();
        void updateScreen();
        void setBackgroundColor(const Color& color);

        // drawing
        void drawRectangle(const TRectangle& rect, const Color& color);

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
        Color m_backgroundColor;
        int m_Width;
        int m_Height;
        bool m_VSyncEnabled;
        std::unique_ptr<renderer::CShaderProgram> m_shaderProgram;
        GLuint m_vertexBuffer;
    };

}

#endif // CSURFACE_H

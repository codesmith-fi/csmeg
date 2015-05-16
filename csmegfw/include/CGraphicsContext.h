#ifndef CSURFACE_H
#define CSURFACE_H

#include <CObjectBase.h>
#include <CShaderProgram.h>
#include <CQuadRenderer.h>
#include <CRenderBatch.h>
#include <Texture2D.h>
#include <Color.h>

#include <glm/vec4.hpp>
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
        void updateView(const glm::mat4& viewMatrix);
        void setBackgroundColor(const Color& color);

        renderer::CRenderBatch& DefaultRenderer();

        // drawing
        //void drawRectangle(const TRectangle& rectangle, const Color& color);

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
        std::shared_ptr<renderer::CQuadRenderer> m_quadRenderer;
        std::shared_ptr<renderer::CRenderBatch> m_batchRenderer;
        Color m_backgroundColor;

        glm::mat4 m_viewMatrix;
        glm::mat4 m_projectionMatrix;

        int m_Width;
        int m_Height;
        bool m_VSyncEnabled;
    };
}

#endif // CSURFACE_H

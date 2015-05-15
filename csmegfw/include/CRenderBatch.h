#pragma once

#include <CQuadRenderer.h>
#include <TRectangle.h>
#include <Color.h>
#include <GL/glew.h>
#include <memory>

namespace csmeg
{
    class TRectangle;
    class Color;

    namespace renderer
    {
        class CShaderProgram;
        class Texture2D;

        class CRenderBatch        
        {
        private: 
            struct BatchRenderInfo
            {
                BatchRenderInfo(CQuadRenderer::RenderMethod m, Texture2D* t, const TRectangle& r, const Color& c, float rot)
                    : method(m), texture(t), rectangle(r), color(c), rotation(rot)
                {
                }
                CQuadRenderer::RenderMethod method;
                Texture2D* texture;
                TRectangle rectangle;
                Color color;
                float rotation;
            };

        public:
            CRenderBatch();
            virtual ~CRenderBatch();

            void begin();
            void render(CQuadRenderer::RenderMethod method, Texture2D* texture, const TRectangle& rect, float rot, const Color& color);
            void end();

            void setRenderer(std::shared_ptr<CQuadRenderer> r);

        private:
            std::shared_ptr<CQuadRenderer> m_quadRenderer;
            std::vector<BatchRenderInfo> m_batch;
        };
    }
}


#include "CRenderBatch.h"
#include "CShaderProgram.h"
#include "Texture2D.h"
#include "TRectangle.h"
#include "Color.h"
#include "CSmegException.h"

using csmeg::TRectangle;
using csmeg::Color;
using namespace csmeg::renderer;

CRenderBatch::CRenderBatch() : m_quadRenderer(), m_batch()
{
}

CRenderBatch::~CRenderBatch()
{
}

void CRenderBatch::begin()
{
    if(!m_quadRenderer) {
        throw CSmegException("CRenderBatch: No quad renderer set");
    }
    m_batch.clear();
    m_batch.reserve(10);
}

void CRenderBatch::end()
{
    if(!m_quadRenderer) {
        throw CSmegException("CRenderBatch: No quad renderer set");
    }

    if(m_batch.size() > 0) {
        BatchRenderInfo& first = m_batch[0];
        m_quadRenderer->setMethodAndTexture(first.method, first.texture);
        for(auto& r : m_batch) {
            m_quadRenderer->render(r.rectangle, r.rotation, r.color);
        }
    }
}

void CRenderBatch::render(CQuadRenderer::RenderMethod method, Texture2D* texture, const TRectangle& rect, float rot, const Color& color)
{
    m_batch.emplace_back(BatchRenderInfo(method, texture, rect, color, rot));
}

void CRenderBatch::setRenderer(std::shared_ptr<CQuadRenderer> r)
{
    m_quadRenderer = r;
}

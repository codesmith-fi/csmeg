#include "CTesterGame.h"
#include <iostream>
#include <ContentManager.h>
#include <CDebug.h>

using namespace std;

CTesterGame::CTesterGame() : m_Counter(0)
{
    LOG_INFO() << "CTesterGame created.";
}

CTesterGame::~CTesterGame()
{
    LOG_INFO() << "CTesterGame destroyed.";
}

void CTesterGame::onLoadContent()
{
    LOG_INFO() << "Performing LoadContent";
    ContentManager::instance().textureFolder("textures");
    ContentManager::instance().loadTexture("jupiter.png", true);
    m_texture = ContentManager::instance().getTexture("jupiter.png");

}

void CTesterGame::onUnloadContent()
{
    LOG_INFO() << "Performing UnloadContent";
}

void CTesterGame::onDraw() const
{
    getGraphicsContext().clearScreen();

    renderer::CRenderBatch& r = getGraphicsContext().DefaultRenderer();

    glm::vec2 pos(200.0f, 100.f);
    TRectangle rect(200.0f, 100.0f, 50.0f, 50.0f);
    r.begin();
    for(int i = 0; i < 5; i++) {
        if(i % 2) {
            r.render(renderer::CQuadRenderer::RenderMethod::TEXTURED, m_texture.get(), rect, 0.0f, Color(Color::Palette::White));
        }
        else {
            r.render(renderer::CQuadRenderer::RenderMethod::FLATCOLOR, m_texture.get(), rect, 0.0f, Color(Color::Palette::White));
        }
        rect.move(glm::vec2(30.0f, 30.0f));
        rect.grow(TVector2(10, 10));
    }
    r.end();
    getGraphicsContext().updateScreen();
}

void CTesterGame::onUpdate(const CGameTime& gameTime)
{
}

void CTesterGame::onEvent(SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN) {
        const SDL_KeyboardEvent& keyEvent = event.key;
        if(keyEvent.state == SDL_PRESSED) {
            LOG_INFO() << "Keypressed: " << keyEvent.keysym.sym;
            if(keyEvent.keysym.sym == SDLK_ESCAPE ) {
                stop();
            }
        }
    }
}

bool CTesterGame::onInitialize()
{
    LOG_INFO() << "Performing Initialize()";

	setFpsLimit(100);
    getGraphicsContext().setSize(1024, 768);
    getGraphicsContext().setFullScreen(true);
    getGraphicsContext().setVsync(true);
	getGraphicsContext().setBackgroundColor(Color(0.2f, 0.2f, 0.2f));
    return true;
}

void CTesterGame::onRelease()
{
    LOG_INFO() << "Performing Release()";
}

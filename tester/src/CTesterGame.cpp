#include "CTesterGame.h"
#include <iostream>
#include <ContentManager.h>
#include <MathUtil.h>

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

    m_rot = 0.0f;
}

void CTesterGame::onUnloadContent()
{
    LOG_INFO() << "Performing UnloadContent";
}

void CTesterGame::onDraw() const
{
    getGraphicsContext().clearScreen();

    renderer::CRenderBatch& r = getGraphicsContext().DefaultRenderer();

//    glm::vec2 pos(200.0f, 100.f);
    TRectangle rect(0.0f, 0.0f, 50.0f, 50.0f);
    r.begin();
    for(int i = 0; i < 5; i++) {
        if(i % 2) {
            r.render(renderer::CQuadRenderer::RenderMethod::TEXTURED, m_texture.get(), rect, m_rot, Color(Color::Palette::White));
        }
        else {
            r.render(renderer::CQuadRenderer::RenderMethod::FLATCOLOR, m_texture.get(), rect, m_rot, Color(Color::Palette::White));
        }
        rect.move(glm::vec2(30.0f, 30.0f));
        rect.grow(TVector2(10, 10));
    }
    r.end();
}

void CTesterGame::onUpdate(const CGameTime& gameTime)
{
    // rotate 45 degrees per second
    m_rot += 45 * math::DEG_TO_RAD * gameTime.getElapsedSeconds();
    float camRot = 15 * math::DEG_TO_RAD * gameTime.getElapsedSeconds();
    m_camera.rotate(camRot);
    getGraphicsContext().updateView(m_camera.get());
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

	setFpsLimit(60);
    getGraphicsContext().setSize(640, 480);
    m_camera = renderer::TCamera2D(
        TVector2(-320, -240),
        TVector2(320, 240),
        0.0f,
        1.0f);

    getGraphicsContext().setFullScreen(true);
    getGraphicsContext().setVsync(true);
	getGraphicsContext().setBackgroundColor(Color(0.2f, 0.2f, 0.2f));
    return true;
}

void CTesterGame::onRelease()
{
    LOG_INFO() << "Performing Release()";
}

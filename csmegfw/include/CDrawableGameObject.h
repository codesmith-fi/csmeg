#ifndef CDRAWABLEGAMEOBJECT_H
#define CDRAWABLEGAMEOBJECT_H

#include <CGameObject.h>

namespace csmeg
{

class CGameTime;

class CDrawableGameObject : public CGameObject
{
    public:
        CDrawableGameObject();
        virtual ~CDrawableGameObject();
    public:
        void draw(const CGameTime& gameTime) const;

        void setRenderInterval(int intervalMsec);
        int getRenderInterval() const;

    protected: // From CGameObject
        void onLoadContent();
        void onUnloadContent();
        void onUpdate(const CGameTime& /* gameTime */);

    protected: // New virtual methods
        virtual void onDraw(const CGameTime& gameTime) const = 0;

    private:
        CUpdateTicker m_DrawUpdater;
};

} // namespace csmeg

#endif // CDRAWABLEGAMEOBJECT_H
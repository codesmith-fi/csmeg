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
        void draw() const;

    protected: // From CGameObject
        void onLoadContent();
        void onUnloadContent();
        void onUpdate(const CGameTime& /* gameTime */);

    protected: // New virtual methods
        virtual void onDraw() const = 0;

    private:
};

} // namespace csmeg

#endif // CDRAWABLEGAMEOBJECT_H

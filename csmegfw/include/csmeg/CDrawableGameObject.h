#ifndef CDRAWABLEGAMEOBJECT_H
#define CDRAWABLEGAMEOBJECT_H

#include <csmeg/CGameObject.h>

namespace csmeg
{

class CGameTime;

class CDrawableGameObject : public CGameObject
{
    public:
        CDrawableGameObject();
        virtual ~CDrawableGameObject();
    public:
        void Draw(const CGameTime& gameTime) const;
    protected:
        virtual void OnDraw(const CGameTime& gameTime) const = 0;
    private:
};

} // namespace csmeg

#endif // CDRAWABLEGAMEOBJECT_H

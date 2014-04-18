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

        void SetDrawFPS(int fps);
        int DrawFPS() const;

    protected: // New virtual methods
        virtual void OnDraw(const CGameTime& gameTime) const = 0;

    private:
        /**
         * Slot for CUpdateDispatcher to process update requests
         */
        void ProcessUpdate(const CGameTime& gameTime);


    private:
        boost::signals2::connection m_DrawUpdaterConnection;
        CUpdateDispatcher m_DrawUpdater;
};

} // namespace csmeg

#endif // CDRAWABLEGAMEOBJECT_H

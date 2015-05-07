#ifndef CGAMEOBJECT_H
#define CGAMEOBJECT_H

#include <CObjectBase.h>
#include <CUpdateTicker.h>

namespace csmeg
{

class CGameTime;

class CGameObject : public CObjectBase
{
    public: // Constructors and destructor
        CGameObject();
        virtual ~CGameObject();

    public: // New methods
        void update(const CGameTime& gameTime);
        void loadContent();
        void unloadContent();

    protected: // New virtual methods
        virtual void onLoadContent() = 0;
        virtual void onUnloadContent() = 0;
        virtual void onUpdate(const CGameTime& /* gameTime */) = 0;

    protected: // From CObjectBase
        virtual bool onInitialize() { return true; };
        virtual void onRelease() { };

    private: // Data
};

} // namespace csmeg

#endif // CGAMEOBJECT_H

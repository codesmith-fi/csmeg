#ifndef CGAMEOBJECT_H
#define CGAMEOBJECT_H

#include <csmeg/CObjectBase.h>

namespace csmeg
{

class CGameTime;

class CGameObject : public CObjectBase
{
    /**
     * Class constants
     */
    enum {
        FPSUnlimited = 0
    };

    public: // Constructors and destructor
        CGameObject();
        virtual ~CGameObject();

    public: // New methods
        void SetUpdateFPS(int fps);
        int UpdateFPS() const;

        void Update(const CGameTime& gameTime);

    protected: // New virtual methods
        virtual void OnUpdate(const CGameTime& gameTime) { }
        virtual bool OnInitialize() { return true; }
        virtual void OnRelease() { }
        virtual void OnLoadContent() { }
        virtual void OnUnloadContent() { }

    protected:
        bool NeedsUpdate(const CGameTime& gameTime);

    private: // Data
        int m_FPS;
        int m_UpdateIntervalMsec;
        int m_UpdateCounterMsec;
};

} // namespace csmeg

#endif // CGAMEOBJECT_H

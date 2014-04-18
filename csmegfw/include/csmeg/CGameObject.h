#ifndef CGAMEOBJECT_H
#define CGAMEOBJECT_H

#include <csmeg/CObjectBase.h>
#include <csmeg/CUpdateDispatcher.h>

namespace csmeg
{

class CGameTime;

class CGameObject : public CObjectBase
{
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

    private:
        void ProcessUpdate(const CGameTime& gameTime);

    private: // Data
        boost::signals2::connection m_UpdaterConnection;
        CUpdateDispatcher m_Updater;
};

} // namespace csmeg

#endif // CGAMEOBJECT_H

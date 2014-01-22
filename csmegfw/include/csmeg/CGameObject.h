#ifndef CGAMEOBJECT_H
#define CGAMEOBJECT_H

namespace csmeg
{

class CGameTime;

class CGameObject
{
    public: // Constructors and destructor
        CGameObject();
        virtual ~CGameObject();

    public: // New methods
        void Update(const CGameTime& gameTime);
        void Initialize();
        void Release();

    protected: // New virtual methods
        virtual void OnUpdate(const CGameTime& gameTime) = 0;
        virtual void OnInitialize() = 0;
        virtual void OnRelease() = 0;

    private: // Data
};

} // namespace csmeg

#endif // CGAMEOBJECT_H

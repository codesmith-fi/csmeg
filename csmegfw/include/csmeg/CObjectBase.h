#ifndef COBJECTBASE_H
#define COBJECTBASE_H

namespace csmeg
{

/**
 * Base class for all objects that can be initialized
 *
 * Can't be instantiated, must be derived
 */
class CObjectBase
{
    public:
        enum {
            CSMResultAllOk = 0
        };

    public:
        CObjectBase();
        virtual ~CObjectBase();

    public: // New methods
        bool Initialize();
        void Release();
        bool IsInitialized() const { return m_IsInitialized; }
        int LastError() const { return m_LastError; }
    protected: // New virtual methods
        virtual bool OnInitialize() = 0;
        virtual void OnRelease() = 0;
        virtual void SetError(int newError) { m_LastError = newError; }

    private: // data
        bool m_IsInitialized;
        int m_LastError;
};

} // namespace csmeg

#endif // COBJECTBASE_H

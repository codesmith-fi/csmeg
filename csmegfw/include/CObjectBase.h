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
        bool initialize();
        void release();
        bool isInitialized() const { return m_IsInitialized; }
        int getLastError() const { return m_LastError; }

    protected: // New virtual methods
        virtual bool onInitialize() = 0;
        virtual void onRelease() = 0;
        virtual void setError(int newError) { m_LastError = newError; }

    private: // data
        bool m_IsInitialized;
        int m_LastError;
};

} // namespace csmeg

#endif // COBJECTBASE_H

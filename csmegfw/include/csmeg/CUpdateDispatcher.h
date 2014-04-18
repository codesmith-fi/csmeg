#ifndef CUPDATEDISPATCHER_H
#define CUPDATEDISPATCHER_H

#include <csmeg/IUpdateable.h>
#include <boost/signals2.hpp>

namespace csmeg {

class CGameTime;

class CUpdateDispatcher : public IUpdateable
{
    /**
     * Type defines for CUpdateDispatcher
     */
    private:
        typedef boost::signals2::signal<void (const CGameTime&)> UpdateNeededSignal;
    public:
        typedef UpdateNeededSignal::slot_type UpdateNeededSlot;

    public: // New class methods
        CUpdateDispatcher(int fps = 0);
        virtual ~CUpdateDispatcher();

        void SetFPS(int fps);
        int FPS() const { return m_FPS; }

    public: // From IUpdateable
        void Update(const CGameTime& gameTime);

    public: // New methods
        boost::signals2::connection connect(const UpdateNeededSlot &slot);

    protected: // From IUpdateable
        void OnUpdate(const CGameTime& gameTime);

    private: // New methods
        bool NeedsUpdate(const CGameTime& gameTime);

    private:
        UpdateNeededSignal m_signalUpdateNeeded;
        int m_FPS;
        int m_UpdateIntervalMsec;
        int m_UpdateCounterMsec;
};

} // namespace csmeg
#endif // CUPDATEDISPATCHER_H

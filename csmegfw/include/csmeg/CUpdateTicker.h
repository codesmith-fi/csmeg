#ifndef CUPDATEDISPATCHER_H
#define CUPDATEDISPATCHER_H

namespace csmeg {

#define CSMEG_DEFAULT_UPDATE_INTERVAL_MSEC 20

class CGameTime;

class CUpdateTicker
{
    public: // New class methods
        CUpdateTicker(int intervalMsec);
        virtual ~CUpdateTicker();

        void setUpdateInterval(int msec);
        int getUpdateInterval() const;
        double getFPS() const { return m_FPS; }

        bool tick(const CGameTime& gameTime);

    private:
        int m_UpdateInterval;
        int m_UpdateCounter;
        double m_FPS;
};

} // namespace csmeg
#endif // CUPDATEDISPATCHER_H

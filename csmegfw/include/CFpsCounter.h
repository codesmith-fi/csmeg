#ifndef CFPSCOUNTER_H
#define CFPSCOUNTER_H

#include <vector>

namespace csmeg
{

class CGameTime;

class CFpsCounter
{
    public:
        CFpsCounter();
        virtual ~CFpsCounter();

        void update(const CGameTime& gameTime);
        float getFps() const;
    protected:
    private:
        std::vector<unsigned int> m_Samples;
        unsigned int m_Count;
        int m_Current;
        unsigned int m_SampleCount;
        float m_Fps;
};

}
#endif // CFPSCOUNTER_H

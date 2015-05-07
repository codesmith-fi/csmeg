#ifndef CFPSCOUNTER_H
#define CFPSCOUNTER_H

#include <vector>
#include <stdint.h>

namespace csmeg
{

class CGameTime;

class CFpsCounter
{
    public:
        CFpsCounter();
        virtual ~CFpsCounter();

        void update(uint32_t elapsedMsec);
        float getFps() const;
    protected:
    private:
        std::vector<unsigned int> m_Samples;
        uint32_t m_Count;
        int32_t m_Current;
        uint32_t m_SampleCount;
        float m_Fps;
};

}
#endif // CFPSCOUNTER_H

#include "CFpsCounter.h"
#include "CGameTime.h"
#include "CDebug.h"

namespace csmeg
{

CFpsCounter::CFpsCounter() : m_Samples(), m_Count(0), m_Current(0), m_SampleCount(3), m_Fps(0.0f)
{
}

CFpsCounter::~CFpsCounter()
{
}

void CFpsCounter::update(uint32_t elapsedMsec)
{
    m_Current+=elapsedMsec;
    m_Count++;
    if(m_Current >= 1000) {
        m_Samples.emplace_back(m_Count);

        if(m_Samples.size() > m_SampleCount) {
            m_Samples.erase(m_Samples.begin());
        }

        int c = 0;
        m_Fps = 0.0f;
        for(auto& sample : m_Samples) {
            m_Fps += sample * 1.0f;
            c++;
        }
        m_Fps = m_Fps / c;

        LOG_INFO() << "Fps: " << m_Fps << " f:" << m_Count << " c:" << c;

        m_Current = 0;
        m_Count = 0;
    }
}

float CFpsCounter::getFps() const
{
    return m_Fps;
}

}

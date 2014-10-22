#ifndef CEVENTS_H
#define CEVENTS_H

#include <csmeg/CObjectBase.h>
#include <csmeg/MInputEventListener.h>
#include <SDL2/SDL_events.h>
#include <vector>

namespace csmeg
{

/**
 * Simple SDL event dispatcher
 */
class CEvents : public CObjectBase
{
    public:
        CEvents();
        virtual ~CEvents();
    public: // New methods
        void Update();
        void AddEventListener(MInputEventListener* listener);

    protected: // From CObjectBase
        bool onInitialize();
        void onRelease();

    private: // Data
        MInputEventListener* m_eventListener;
};

} // namespace csmeg
#endif // CEVENTS_H

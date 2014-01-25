#ifndef MINPUTEVENTLISTENER_H
#define MINPUTEVENTLISTENER_H

namespace csmeg
{

template<class EventClass>
class MInputEventListener
{
    public:
        virtual void OnEvent(EventClass& event) = 0;
    private:
        ~MInputEventListener() {}
};

}
#endif // MINPUTEVENTLISTENER_H

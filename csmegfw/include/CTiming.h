#ifndef CTIMING_H
#define CTIMING_H

#include <inttypes.h>

namespace csmeg
{

class CTiming
{

    public:
        CTiming();
        virtual ~CTiming();

        static uint32_t TicksMsec();
        static void DelayMsec(uint32_t waitMsec);
};

}

#endif // CTIMING_H

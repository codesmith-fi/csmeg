#ifndef CTIMING_H
#define CTIMING_H

#include <csmeg/CObjectBase.h>
#include <inttypes.h>

namespace csmeg
{

class CTiming : public CObjectBase
{
    public:
        virtual ~CTiming();
    public:
        static CTiming& Instance()
        {
            static CTiming instance;
            return instance;
        }

        uint32_t TicksMsec() const;
    protected: // From CObjectBase
        bool OnInitialize();
        void OnRelease();

    private:
        CTiming();
        CTiming(const CTiming&);
        CTiming& operator=(const CTiming&);
};

}

#endif // CTIMING_H

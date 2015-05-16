#pragma once
#include <math.h>

namespace csmeg
{
    namespace math
    {
        static const float PI =             3.14159265358979323846f;
        static const float PI_2 =           1.57079632679489661923f;
        static const float PI_4 =           0.78539816339744830962f;
        static const float PI_180 =         0.01745329251994329577f;
        static const float DEG_TO_RAD =     0.01745329251994329577f;
        static const float RAD_TO_DEG =     57.2957795130823208768f;

        class Math
        {
        public:
            Math()
            {
            }

            virtual ~Math()
            {
            }
        };
   } // namespace math
} // namespace csmeg

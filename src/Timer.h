#ifndef GP8_TIMER_H
#define GP8_TIMER_H

#include <cstdint>

class Timer {
public:
        Timer ();
        void start (uint32_t interval);
        bool isExpired () const;

protected:
        uint32_t startTime;
        uint32_t interval;
};

#endif //__TIMER_H__

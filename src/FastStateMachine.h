/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef FASTSTATEMACHINE_H
#define FASTSTATEMACHINE_H

#include "Timer.h"

class InfraRedBeam;
class StopWatch;

#define BEAM_INTERRUPTION_EVENT 3000

class FastStateMachine {
public:
        enum State { INIT, READY, RUNNING, STOP };

        static FastStateMachine *singleton ()
        {
                static FastStateMachine s;
                return &s;
        }

        void run ();

        void setIr (InfraRedBeam *i) { this->ir = i; }
        void setStopWatch (StopWatch *s) { this->stopWatch = s; }

private:
        State state = INIT;
        InfraRedBeam *ir = nullptr;
        StopWatch *stopWatch = nullptr;
        Timer startTimeout;
};

#endif // FASTSTATEMACHINE_H

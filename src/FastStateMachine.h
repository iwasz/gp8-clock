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
struct IDisplay;
class Buzzer;
class History;
class Button;
struct ICircullarQueueStorage;
struct IRandomAccessStorage;

#define BEAM_INTERRUPTION_EVENT 3000

class FastStateMachine {
public:
        enum State { INIT, GP8_READY, GP8_RUNNING, GP8_STOP, LOOP_READY, LOOP_RUNNING, LOOP_STOP, HI_CLEAR_READY, RES_CLEAR_READY };

        static FastStateMachine *singleton ()
        {
                static FastStateMachine s;
                return &s;
        }

        void run ();

        void setIr (InfraRedBeam *i) { this->ir = i; }
        void setStopWatch (StopWatch *s) { this->stopWatch = s; }
        void setDisplay (IDisplay *d) { this->display = d; }
        void setBuzzer (Buzzer *b) { this->buzzer = b; }
        void setHistory (History *h) { this->history = h; }
        void setButton (Button *b) { this->button = b; }

private:
        void ready_entryAction (bool loop = false);
        void running_entryAction ();
        void stop_entryAction ();
        void hiClearReady_entryAction ();
        void resultsClearReady_entryAction ();

private:
        State state = INIT;
        InfraRedBeam *ir = nullptr;
        StopWatch *stopWatch = nullptr;
        Timer startTimeout;
        IDisplay *display = nullptr;
        Buzzer *buzzer = nullptr;
        History *history = nullptr;
        Button *button = nullptr;
};

#endif // FASTSTATEMACHINE_H

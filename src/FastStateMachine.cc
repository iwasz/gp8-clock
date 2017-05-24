/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "FastStateMachine.h"
#include "Buzzer.h"
#include "Debug.h"
#include "History.h"
#include "InfraRedBeam.h"
#include "StopWatch.h"
#include "T145003.h"

/*****************************************************************************/

void FastStateMachine::run ()
{
        uint8_t i = display->getIcons ();

        if (!ir->isBeamPresent ()) {
                display->setIcons (i | T145003::MINUS_SIGN);
        }
        else {
                display->setIcons (i & ~T145003::MINUS_SIGN);
        }

        switch (state) {
        case INIT:
                if (ir->isBeamPresent ()) {
                        state = READY;
                }
                break;

        case READY:
                if (ir->isBeamInterrupted ()) {
                        state = RUNNING;
                        running_entryAction ();
                }
                break;

        case RUNNING:
                if (ir->isBeamPresent () && ir->isBeamInterrupted () && startTimeout.isExpired ()) {
                        state = STOP;
                        stop_entryAction ();
                }

                break;

        case STOP:
                if (ir->isBeamPresent () && ir->isBeamInterrupted () && startTimeout.isExpired ()) {
                        state = RUNNING;
                        running_entryAction ();
                }
                break;

        default:
                break;
        }
}

/*****************************************************************************/

void FastStateMachine::running_entryAction ()
{
        stopWatch->reset ();
        stopWatch->start ();
        buzzer->beep (100, 0, 1);
        startTimeout.start (BEAM_INTERRUPTION_EVENT);
}

/*****************************************************************************/

void FastStateMachine::stop_entryAction ()
{
        stopWatch->stop ();
        startTimeout.start (BEAM_INTERRUPTION_EVENT);
        int dif = stopWatch->getTime () - history->getHiScore ();

        if (dif < 0) {
                buzzer->beep (1000, 0, 1);
        }
        else {
                int slots = (dif / 50) + 1;

                if (slots > 5) {
                        slots = 5;
                }

                buzzer->beep (70, 50, slots);
        }

        history->store (stopWatch->getTime ());
        history->printHistory ();
}

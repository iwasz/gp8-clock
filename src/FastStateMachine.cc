/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "FastStateMachine.h"
#include "InfraRedBeam.h"
#include "StopWatch.h"

void FastStateMachine::run ()
{
        switch (state) {
        case INIT:
                if (ir->isBeamPresent ()) {
                        state = READY;
                }
                break;

        case READY:
                if (ir->isBeamInterrupted ()) {
                        state = RUNNING;
                        stopWatch->reset ();
                        stopWatch->start ();
                        startTimeout.start (BEAM_INTERRUPTION_EVENT);
                }
                break;

        case RUNNING:
                if (ir->isBeamInterrupted () && startTimeout.isExpired ()) {
                        state = STOP;
                        stopWatch->stop ();
                        startTimeout.start (BEAM_INTERRUPTION_EVENT);
                }

                break;

        case STOP:
                if (ir->isBeamPresent () && ir->isBeamInterrupted () && startTimeout.isExpired ()) {
                        state = RUNNING;
                        stopWatch->reset ();
                        stopWatch->start ();
                        startTimeout.start (BEAM_INTERRUPTION_EVENT);
                }
                break;

        default:
                break;
        }
}

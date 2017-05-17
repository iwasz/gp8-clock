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
#include "T145003.h"

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
                        stopWatch->reset ();
                        stopWatch->start ();
                        startTimeout.start (BEAM_INTERRUPTION_EVENT);
                }
                break;

        case RUNNING:
                if (ir->isBeamPresent () && ir->isBeamInterrupted () && startTimeout.isExpired ()) {
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

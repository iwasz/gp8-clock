/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "FastStateMachine.h"
#include "Button.h"
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
                ready_entryAction ();

                if (ir->isBeamPresent ()) {
                        state = GP8_READY;
                }

                if (button->getPressClear ()) {
                        state = LOOP_READY;
                        ready_entryAction (true);
                }

                break;

        case GP8_READY:
                if (ir->isBeamInterrupted ()) {
                        state = GP8_RUNNING;
                        running_entryAction ();
                }

                if (button->getPressClear ()) {
                        state = LOOP_READY;
                        ready_entryAction (true);
                }

                break;

        case GP8_RUNNING:
                if (ir->isBeamPresent () && ir->isBeamInterrupted () && startTimeout.isExpired ()) {
                        state = GP8_STOP;
                        stop_entryAction ();
                }

                break;

        case GP8_STOP:
                if (ir->isBeamPresent () && ir->isBeamInterrupted () && startTimeout.isExpired ()) {
                        state = GP8_RUNNING;
                        running_entryAction ();
                }

                if (button->getPressClear ()) {
                        state = LOOP_READY;
                        ready_entryAction (true);
                }

                break;

        case LOOP_READY:
                if (ir->isBeamPresent () && ir->isBeamInterrupted ()) {
                        state = LOOP_RUNNING;
                        running_entryAction ();
                }

                if (button->getPressClear ()) {
                        state = HI_CLEAR_READY;
                        hiClearReady_entryAction ();
                }

                break;

        case LOOP_RUNNING:
                if (ir->isBeamPresent () && ir->isBeamInterrupted () && startTimeout.isExpired ()) {
                        state = LOOP_STOP;
                        stop_entryAction ();
                }

                break;

        case LOOP_STOP:
                if (ir->isBeamPresent () && ir->isBeamInterrupted () && startTimeout.isExpired ()) {
                        state = LOOP_RUNNING;
                        running_entryAction ();
                }

                if (button->getPressClear ()) {
                        state = HI_CLEAR_READY;
                        hiClearReady_entryAction ();
                }

                break;

        case HI_CLEAR_READY:
                if (button->getLongPressClear ()) {
                        buzzer->beep (200, 0, 1);
                        history->clearHiScore ();
                }

                if (button->getPressClear ()) {
                        state = RES_CLEAR_READY;
                        resultsClearReady_entryAction ();
                }
                break;

        case RES_CLEAR_READY:
                if (button->getLongPressClear ()) {
                        buzzer->beep (200, 0, 1);
                        history->clearResults ();
                }

                if (button->getPressClear ()) {
                        buzzer->beep (10, 10, 1);
                        state = INIT;
                }
                break;

        default:
                break;
        }
}

/*****************************************************************************/

void FastStateMachine::ready_entryAction (bool loop)
{
        display->setDigit (0, 0);
        display->setDigit (1, 0);
        display->setDigit (2, 0);
        display->setDigit (3, 0);
        display->setDigit (4, 0);
        display->setDots (T145003::DOT5 | T145003::DOT3);

        if (loop) {
                buzzer->beep (10, 10, 1);
                display->setIcons (T145003::TOP_LEFT_ARROW);
        }
        else {
                display->setIcons (T145003::BOTTOM_LEFT_ARROW);
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

void FastStateMachine::hiClearReady_entryAction ()
{
        buzzer->beep (10, 10, 1);
        display->setDigit (0, 0x0c);
        display->setDigit (1, T145003::LETTER_L);
        display->setDigit (2, T145003::LETTER_r);
        display->setDigit (3, T145003::LETTER_H);
        display->setDigit (4, 0x01);
        display->setDots (T145003::DOT3);
        display->setIcons (0);
}

/*****************************************************************************/

void FastStateMachine::resultsClearReady_entryAction ()
{
        buzzer->beep (10, 10, 1);
        display->setDigit (0, 0x0c);
        display->setDigit (1, T145003::LETTER_L);
        display->setDigit (2, T145003::LETTER_r);
        display->setDigit (3, T145003::LETTER_r);
        display->setDigit (4, 0x0e);
        display->setDots (T145003::DOT3);
        display->setIcons (0);
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

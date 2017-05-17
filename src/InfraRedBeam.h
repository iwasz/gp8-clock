/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef INFRAREDBEAM_H
#define INFRAREDBEAM_H

#include <cstdint>
#include <stm32f0xx_hal.h>

extern "C" void TIM3_IRQHandler ();

/**
 * How much update events since last rise (noOfUpdateEventsSinceLastRise) indicates
 * that light path is cut. Roughly proportional to ms (???)
 * TODO Is 50 not to much?
 */
#define UPDATE_EVENT_TRESHOLD 50
#define BEAM_GONE 25000

class InfraRedBeam {
public:
        static InfraRedBeam *singleton ()
        {
                static InfraRedBeam i;
                return &i;
        }

        void init ();

        /// If any IR signal rise was observed at all.
        bool isBeamPresent () { return beamPresent; }
        bool isBeamInterrupted () { return noOfUpdateEventsSinceLastRise > UPDATE_EVENT_TRESHOLD; }

private:
        friend void TIM3_IRQHandler ();
        void onInterrupt ();
        TIM_HandleTypeDef timHandle;
        uint32_t noOfUpdateEventsSinceLastRise = 0;

        bool beamPresent = false;
};

#endif // INFRAREDBEAM_H

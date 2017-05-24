/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GP8_STOP_WATCH_ADC_H
#define GP8_STOP_WATCH_ADC_H

#include <stm32f0xx_hal.h>

class AdcChannel;

/**
 * @brief The Adc class
 * TODO Suboptimal, shold use DMA or interrupts.
 */
class Adc {
public:
        ~Adc () { delete[] channels; }

        static Adc *instance (int maxChannelsNo = 1) { return new Adc (maxChannelsNo); }
        void init ();

        /**
         * CAUTION channels must be added in order i.e. first goes the channel with the
         * lowest number you use, then higher and so on (to be fixed someday).
         */
        void addChannel (AdcChannel *channel);
        void run ();

private:
        Adc (int maxChannelsNo = 1) : channelsNum (0), maxChannelsNo (maxChannelsNo) { channels = new AdcChannel *[maxChannelsNo]; }
        friend class AdcChannel;
        ADC_HandleTypeDef hadc;
        AdcChannel **channels;
        int channelsNum;
        int maxChannelsNo;
};

#endif // ADC_H

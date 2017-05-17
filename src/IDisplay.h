/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IDISPLAY_H
#define IDISPLAY_H

#include <cstdint>

struct IDisplay {
        virtual ~IDisplay () {}
        virtual void setDigit (uint8_t number, uint8_t setDigit) = 0;

        virtual uint8_t getDots () const = 0;
        virtual void setDots (uint8_t bitmask) = 0;

        virtual uint8_t getIcons () const = 0;
        virtual void setIcons (uint8_t bitmask) = 0;

        /**
         * @brief batteryLevel 0 : blinking frame, 1 : frame, 2 : frame & 1 bar, 3 : frame & 2 bars
         * @param level
         */
        virtual void setBatteryLevel (uint8_t level) = 0;

        virtual void refresh () = 0;
};

#endif // IDISPLAY_H

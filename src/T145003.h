/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef T145003_H
#define T145003_H

#include "IDisplay.h"
#include "ILcdDdriver.h"

/**
 * @brief The T145003 class controlls a Chinese weight scale LCD which I found on AliExpress once.
 */
class T145003 : public IDisplay {
public:
        enum Dots { DOT5 = 0x01, DOT4 = 0x02, DOT3 = 0x04, DOT2 = 0x08 };
        enum Icons { BOTTOM_LEFT_ARROW = 0x01, TOP_LEFT_ARROW = 0x02, TOP_RIGHT_AROW = 0x04, MINUS_SIGN = 0x08 };
        enum Batery { FRAME = 0x01, BAR0 = 0x02, BAR1 = 0x04, BAR2 = 0x08, BAR3 = 0x10 };

        virtual ~T145003 () {}
        static T145003 *singleton ();

        virtual void init ();

        /**
         * @brief digit Displays a digit
         * @param position 0-4. 0 means least significant digit, 4 means most.
         * @param digit A digit.
         */
        void setDigit (uint8_t position, uint8_t setDigit);

        void setDots (uint8_t bitmask);
        uint8_t getDots () const { return dots; }

        void setIcons (uint8_t bitmask);
        uint8_t getIcons () const { return icons; }

        /**
         * @brief batteryLevel 0 : blinking frame, 1 : frame, 2 : frame & 1 bar, 3 : frame & 2 bars
         * @param level
         */
        void setBatteryLevel (uint8_t level);

        void refresh ();

        void setLcdDriver (ILcdDriver *d) { driver = d; }
        void setBacklight (bool b);
        bool getBacklight () const;

private:
        ILcdDriver *driver = nullptr;
        uint8_t buffer[6];
        uint8_t digits[5] = { 0, 0, 0, 0, 0 };
        uint8_t dots = 0;
        uint8_t icons = 0;
        uint8_t batteryLevel = 0;
        bool needsRefresh = true;

        const uint8_t font[16] = {
                0x01 | 0x02 | 0x04 | 0x10 | 0x40 | 0x80,        // 0
                0x02 | 0x04,                                    // 1
                0x01 | 0x02 | 0x20 | 0x40 | 0x80,               // 2
                0x01 | 0x02 | 0x20 | 0x04 | 0x80,               // 3
                0x10 | 0x20 | 0x02 | 0x04,                      // 4
                0x01 | 0x10 | 0x20 | 0x04 | 0x80,               // 5
                0x01 | 0x10 | 0x20 | 0x04 | 0x40 | 0x80,        // 6
                0x01 | 0x02 | 0x04,                             // 7
                0x01 | 0x02 | 0x04 | 0x10 | 0x20 | 0x40 | 0x80, // 8
                0x01 | 0x02 | 0x04 | 0x10 | 0x20 | 0x80,        // 9
                0x01 | 0x02 | 0x04 | 0x10 | 0x20 | 0x40,        // A
                0x04 | 0x10 | 0x20 | 0x40 | 0x80,               // b
                0x01 | 0x10 | 0x40 | 0x80,                      // C
                0x04 | 0x02 | 0x20 | 0x40 | 0x80,               // d
                0x01 | 0x10 | 0x20 | 0x40 | 0x80,               // E
                0x01 | 0x10 | 0x20 | 0x40                       // F
        };

        const uint8_t batteryFont[6] = {
                0x00,                            // Empty
                0x80,                            // Frame
                0x80 | 0x08,                     // Frame & 1 bar
                0x80 | 0x08 | 0x04,              // 2 bars
                0x80 | 0x08 | 0x04 | 0x02,       // 3 bars
                0x80 | 0x08 | 0x04 | 0x02 | 0x01 // all bars

        };
};

#endif // T145003_H

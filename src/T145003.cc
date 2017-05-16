/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "T145003.h"

T145003 *T145003::singleton ()
{
        static T145003 lcd;
        return &lcd;
}

void T145003::setDigit (uint8_t position, uint8_t digit)
{
        digits[position] = digit;
        needsRefresh = true;
}

void T145003::setDots (uint8_t bitmask)
{
        dots = bitmask;
        needsRefresh = true;
}

void T145003::setTriangles (uint8_t bitmask)
{
        triangles = bitmask;
        needsRefresh = true;
}

void T145003::setBatteryLevel (uint8_t level)
{
        batteryLevel = level;
        needsRefresh = true;
}

void T145003::refresh ()
{
        if (!needsRefresh) {
                return;
        }

        needsRefresh = false;
        buffer[0] = batteryFont[batteryLevel];

        for (int i = 0; i < 5; ++i) {
                buffer[i + 1] = font[digits[i]];
        }

        if (dots & DOT5) {
                buffer[2] |= 0x08;
        }

        if (dots & DOT4) {
                buffer[3] |= 0x08;
        }

        if (dots & DOT3) {
                buffer[4] |= 0x08;
        }

        if (dots & DOT2) {
                buffer[5] |= 0x08;
        }

        /*---------------------------------------------------------------------------*/

        if (triangles & TOP_RIGHT) {
                buffer[0] |= 0x40;
        }

        if (triangles & MINUS) {
                buffer[0] |= 0x20;
        }

        if (triangles & TOP_LEFT) {
                buffer[0] = 0x10;
        }

        if (triangles & BOTTOM_LEFT) {
                buffer[1] |= 0x08;
        }

        driver->sendData (0, buffer, sizeof (buffer));
}

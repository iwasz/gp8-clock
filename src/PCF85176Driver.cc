/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "PCF85176Driver.h"
#include <cstring>

PCF85176Driver *PCF85176Driver::singleton ()
{
        static PCF85176Driver driver;
        return &driver;
}

void PCF85176Driver::init (uint8_t bias, uint8_t planesNumber, bool on)
{
        uint8_t command = NEXT_COMMAND | COMMAND_MODE_SET;
        command |= ((bias == 2) ? (BIAS_1_2) : (BIAS_1_3));
        command |= ((on) ? (DISPLAY_ON) : (DISPLAY_OF));
        command |= PLANES_4; // TODO
        link->send (&command, 1);
}

void PCF85176Driver::sendData (uint8_t address, uint8_t *data, uint8_t len)
{
        uint8_t tmp[21];
        tmp[0] = address;
        memcpy (tmp + 1, data, len);
        link->send (tmp, len + 1);
}

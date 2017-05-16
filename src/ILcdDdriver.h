/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ILCDDDRIVER_H
#define ILCDDDRIVER_H

#include <cstdint>

struct ILcdDriver {
        virtual ~ILcdDriver () {}

        /**
         * @brief init
         * @param bias 2 == 1/2, 3 == 1/3 etc
         * @param planesNumber 1 == static operation, 2 == 2 planes, 3 == 3 planes etc
         * @param on If turned on or not
         */
        virtual void init (uint8_t bias, uint8_t planesNumber, bool on) = 0;

        /**
         * @brief sendData Sends display data
         * @param address
         * @param data
         * @param len
         */
        virtual void sendData (uint8_t address, uint8_t *data, uint8_t len) = 0;
};
#endif // ILCDDDRIVER_H

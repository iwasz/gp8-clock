/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ILCDDATALINK_H
#define ILCDDATALINK_H

#include <cstdint>

struct ILcdDataLink {
        virtual ~ILcdDataLink () {}
        virtual void send (uint8_t *data, uint8_t len) = 0;
};

#endif // ILCDDATALINK_H

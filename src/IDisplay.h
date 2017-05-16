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
};

#endif // IDISPLAY_H

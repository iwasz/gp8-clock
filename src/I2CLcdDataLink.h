/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef I2CLCDDATALINK_H
#define I2CLCDDATALINK_H

#include "ILcdDataLink.h"
#include <stm32f0xx_hal.h>

class I2CLcdDataLink : public ILcdDataLink {
public:
        virtual ~I2CLcdDataLink () {}
        static I2CLcdDataLink *singleton ();
        void init ();
        void send (uint8_t *data, uint8_t len);

private:
        I2C_HandleTypeDef i2cHandle;
};

#endif // I2CLCDDATALINK_H

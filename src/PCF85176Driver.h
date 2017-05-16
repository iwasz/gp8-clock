/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PCF85176DRIVER_H
#define PCF85176DRIVER_H

#include "ILcdDataLink.h"
#include "ILcdDdriver.h"

#define NEXT_COMMAND 0x80
#define COMMAND_MODE_SET 0x40
#define DISPLAY_ON 0x08
#define DISPLAY_OF 0x00
#define BIAS_1_2 0x04
#define BIAS_1_3 0x00
#define PLANES_1 0x01
#define PLANES_2 0x02
#define PLANES_3 0x03
#define PLANES_4 0x00

class PCF85176Driver : public ILcdDriver {
public:
        virtual ~PCF85176Driver () {}
        static PCF85176Driver *singleton ();
        void init (uint8_t bias, uint8_t planesNumber, bool on);
        void sendData (uint8_t address, uint8_t *data, uint8_t len);
        void setDataLink (ILcdDataLink *l) { link = l; }

private:
        ILcdDataLink *link = nullptr;
};

#endif // PCF85176DRIVER_H

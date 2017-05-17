#ifndef __DEBUG_DRIVER_H__
#define __DEBUG_DRIVER_H__

#include <cstdint>
#include <cstdlib>
#include <stm32f0xx_hal.h>

class Debug {
public:
        static Debug *singleton ();
        void init (uint32_t speed);

        void print (const char *str);
        void print (uint8_t *data, size_t len);
        void print (int);

private:
        UART_HandleTypeDef huart;
};

#endif //__CMD_UART_H__

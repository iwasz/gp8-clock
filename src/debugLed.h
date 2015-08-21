/*
 * debugLed.h
 *
 *  Created on: May 26, 2015
 *      Author: liwaszkiewicz
 */

#ifndef SRC_DEBUGLED_H_
#define SRC_DEBUGLED_H_

typedef enum {
        D2, D3, D4, D5
} LedTypeDef;


void debugLedInit (LedTypeDef led);
void debugLedOn (LedTypeDef led);
void debugLedOff (LedTypeDef led);
void debugLedToggle (LedTypeDef led);

#endif /* SRC_DEBUGLED_H_ */

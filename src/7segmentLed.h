/*
 * 7segmentLed.h
 *
 *  Created on: Aug 21, 2015
 *      Author: liwaszkiewicz
 */

#ifndef SRC_7SEGMENTLED_H_
#define SRC_7SEGMENTLED_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * How many 7-segment displays do we have:
 */
#define DISPLAYS_NO 5

/*
 *  _      a
 * |_|   f   b
 * |_|.    g
 *       e   c   dp
 *         d
 */
enum {
        SEGMENT7_A = 1 << 0,
        SEGMENT7_F = 1 << 1,
        SEGMENT7_B = 1 << 2,
        SEGMENT7_G = 1 << 3,
        SEGMENT7_E = 1 << 4,
        SEGMENT7_C = 1 << 5,
        SEGMENT7_D = 1 << 6,
        SEGMENT7_DP = 1 << 7
};




/**
 * Initialization.
 */
extern void segment7Init ();

/**
 * Low level control.
 * Turn off all segments of a single display (displayNo strating from 0), and then lit only those
 * segments that are provided in second argument (segments).
 */
extern void segment7Set (uint8_t displayNo, uint8_t segments);

/**
 * Low level control.
 * Return hat segments are lit in a display.
 */
extern uint8_t segment7Get (uint8_t displayNo);


/**
 * Turn on the displays whatever brightnes they are set to.
 */
extern void segment7On ();

/**
 * Turn OFF the displays whatever brightnes they are set to.
 */
extern void segment7Off ();

/**
 * Check whether displays are on or off.
 */
extern bool segment7IsOn ();

/**
 * Brightness 0-10
 */
extern void segment7SetBrightness (uint8_t i);


/**
 * Brightness 0-10
 */
extern uint8_t segment7GetBrightness ();


#endif /* SRC_7SEGMENTLED_H_ */

/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef WEIGHT_SCALE_LCD_H
#define WEIGHT_SCALE_LCD_H

#define PLATES_NUM 4
#define SEGMENTS_PER_PLATE_NUM 12

extern void wslcdInit ();
extern void wslcdRefresh ();
extern void wslcdSetDigit (uint8_t digitNo, uint8_t d);

#endif // WEIGHT_SCALE_LCD_H

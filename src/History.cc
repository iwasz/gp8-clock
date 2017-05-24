/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "History.h"
#include "Debug.h"
#include <algorithm>

/*****************************************************************************/

void History::store (uint16_t t)
{
        history[actualHistoryBegin] = t;
        ++actualHistoryBegin;
        actualHistoryBegin %= historyMaxSize;

        if (historySize < historyMaxSize) {
                ++historySize;
        }

        storeHiScoreIf (t);
}

/*****************************************************************************/

void History::storeHiScoreIf (uint16_t t) { hiScore = std::min (hiScore, t); }

/*****************************************************************************/

void History::printHistory ()
{
        Debug *d = Debug::singleton ();
        d->print ("*");
        d->print (hiScore);
        d->print ("\n");

        for (int i = 0; i < historySize; ++i) {
                int idx;

                if (historySize == historyMaxSize) {
                        idx = (actualHistoryBegin + i) % historyMaxSize;
                }
                else {
                        idx = i;
                }

                uint16_t tim = *(history + idx);
                d->print (tim);
                d->print ("\n");
        }

        d->print ("\n");
}

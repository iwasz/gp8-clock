/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "History.h"
#include "Debug.h"
#include "utils.h"
#include <algorithm>
#include <stm32f0xx_hal.h>

/*****************************************************************************/

void History::store (uint16_t t)
{
        historyStorage->store (reinterpret_cast<uint8_t *> (&t), 2, 0);
        storeHiScoreIf (t);
}

/*****************************************************************************/

void History::storeHiScoreIf (uint16_t t)
{
        if (t < hiScore) {
                hiScore = t;
                hiScoreStorage->store (reinterpret_cast<uint8_t *> (&t), 2, 0);
        }
}

/*****************************************************************************/

void History::printHistory ()
{
        Debug *d = Debug::singleton ();
        d->print ("Hi ");
        d->printTime (hiScore);
        d->print ("\n");
        d->print ("\n");

        for (int i = 0; i < 32; ++i) {
                uint16_t tim = *reinterpret_cast<uint16_t const *> (historyStorage->read (nullptr, sizeof (uint16_t), 0, i));
                d->printTime (tim);
                d->print ("\n");
        }
        d->print ("\n");
}

/*****************************************************************************/

void History::init () { hiScore = *reinterpret_cast<uint16_t const *> (hiScoreStorage->read (nullptr, sizeof (uint16_t), 0)); }

/*****************************************************************************/

void History::clearHiScore ()
{
        hiScoreStorage->clear ();
        hiScore = std::numeric_limits<uint16_t>::max ();
}

/*****************************************************************************/

void History::clearResults () { historyStorage->clear (); }

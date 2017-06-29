/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GP8_HISTORY_H
#define GP8_HISTORY_H

#include <cstdint>
#include <limits>
#include <storage/ICircullarQueueStorage.h>
#include <storage/IRandomAccessStorage.h>

class History {
public:
        static History *singleton ()
        {
                static History h;
                return &h;
        }

        void init ();
        void store (uint16_t t);

        uint16_t getHiScore () const { return hiScore; }
        void printHistory ();

        void setHistoryStorage (ICircullarQueueStorage *value) { historyStorage = value; }
        void setHiScoreStorage (IRandomAccessStorage *value) { hiScoreStorage = value; }

        void clearHiScore ();
        void clearResults ();

private:
        void storeHiScoreIf (uint16_t t);

private:
        uint16_t hiScore = std::numeric_limits<uint16_t>::max ();
        IRandomAccessStorage *hiScoreStorage = nullptr;
        ICircullarQueueStorage *historyStorage = nullptr;
};

#endif // HISTORY_H

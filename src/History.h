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

class History {
public:
        static History *singleton (uint8_t historySize)
        {
                static History h (historySize);
                return &h;
        }

        ~History () { delete[] history; }

        void store (uint16_t t);

        uint16_t const *getHistory () const;
        uint8_t getHistorySize () const { return historySize; }

        uint16_t getHiScore () const { return hiScore; }
        void printHistory ();

private:
        History (uint8_t historySize) : historyMaxSize (historySize) { history = new uint16_t[historySize]; }
        void storeFlash (uint16_t t, uint32_t address) {}
        void readFlash (uint32_t address) {}
        void storeHiScoreIf (uint16_t t);

private:
        uint8_t historyMaxSize;

        uint16_t *history;
        uint16_t hiScore = std::numeric_limits<uint16_t>::max ();

        uint8_t actualHistoryBegin = 0;
        uint8_t historySize = 0;
};

#endif // HISTORY_H

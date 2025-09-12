#include "clock.h"
#include <stdio.h>
#include "LRUMethod.h"

void updatePageTable(page*, page, page, int);

int clockHand = 0;

// Run replacement algorithm Clock
page replacePageClock(page* pageTable, int pageNumber, char rw, int numFrames) {
    // Check if page is already in memory
    for (int i = 0; i < numFrames; i++) {
        if (pageTable[i].pageNo == pageNumber) {
            // Page found, set use bit to 1
            pageTable[i].use = 1;
            return pageTable[i];
        }
    }

    // Page not found, find a victim
    while (pageTable[clockHand].use == 1) {
        // If use bit is 1, set to 0 and continue
        pageTable[clockHand].use = 0;
        clockHand = (clockHand + 1) % numFrames;
    }

    // Victim found
    page victim = pageTable[clockHand];
    clockHand = (clockHand + 1) % numFrames;

    // Prepare new page
    page newPage;
    newPage.pageNo = pageNumber;
    newPage.use = 1; // Set use bit to 1 for the new page
    newPage.modified = (rw == 'W') ? 1 : 0;

    updatePageTable(pageTable, victim, newPage, numFrames);

    return victim;
}

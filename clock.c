#include "clock.h"
#include <stdio.h>

int clockHand = 0;

// Run replacement algorithm Clock
page replacePageClock(page* pageTable, int pageNumber, char rw, int numFrames) {
    // Page not found, find a victim
    while (pageTable[clockHand].use == 1) {
        // If use bit is 1, set to 0 and continue
        pageTable[clockHand].use = 0;
        clockHand = (clockHand + 1) % numFrames;
    }

    // Victim found
    page victim = pageTable[clockHand];
    
    // Prepare new page
    page newPage;
    newPage.pageNo = pageNumber;
    newPage.use = 1; // Set use bit to 1 for the new page
    newPage.modified = 0;
    if (rw == 'W') {
        newPage.modified = 1;
    }

    // Replace victim with new page
    pageTable[clockHand] = newPage;

    // Move clock hand to next position
    clockHand = (clockHand + 1) % numFrames;

    return victim;
}

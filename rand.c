#include "rand.h"
#include <stdlib.h>
#include <time.h>

// Ensure srand() is only seeded once
static int seeded = 0;

page replacePageRand(page* pageTable, int pageNumber, char rw, int numFrames) {
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    for (int i = 0; i < numFrames; i++) {
        if (pageTable[i].pageNo == pageNumber) {
            // Page already present, just update modified bit if necessary
            if (rw == 'W') {
                pageTable[i].modified = 1;
            }
            return pageTable[i];  
        }
    }

    int victimIndex = rand() % numFrames;
    page victim = pageTable[victimIndex];

    page newPage;
    newPage.pageNo = pageNumber;
    newPage.modified = (rw == 'W') ? 1 : 0;
    newPage.use = 0; 

    pageTable[victimIndex] = newPage;

    return victim; 
}

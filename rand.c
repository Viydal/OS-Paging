#include "rand.h"
#include <stdlib.h>
#include <time.h>

//Ensure srand() is only seeded once for consistency
static int seeded = 0;

page replacePageRand(page* pageTable, int pageNumber, char rw, int numFrames) {
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    // Check if page is already in memory?
    for (int i = 0; i < numFrames; i++) {
        if (pageTable[i].pageNo == pageNumber) {
            // Page already present, just update the changed part
            if (rw == 'W') {
                pageTable[i].modified = 1;
            }
            return pageTable[i];  //no victim!
        }
    }

    //Pick a random frame to be victim
    int victimIndex = rand() % numFrames;
    page victim = pageTable[victimIndex];

    //Prepare new page to load
    page newPage;
    newPage.pageNo = pageNumber;
    newPage.modified = (rw == 'W') ? 1 : 0;
    newPage.use = 0; 

    // Replace pageTable[victimIndex] 
    pageTable[victimIndex] = newPage;

    return victim;  //return the newly evicted page
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LRUMethod.h"
#include "page.h"

enum repl { RANDOM, FIFO, LRU, CLOCK };
int createMMU(int);
int checkInMemory(int);
int allocateFrame(int, char);
page selectVictim(int, enum repl);
const int pageoffset = 12; /* Page size is fixed to 4 KB */
int numFrames;
page *pageTable;
page *stack;

/* Creates the page table structure to record memory allocation */
int createMMU(int frames) {
    // Initialise page table
    pageTable = (page *)malloc(frames * sizeof(page));

    // Error handling
    if (pageTable == NULL) {
        printf("Page table hasn't been initialised properly");
        exit(-1);
    }

    // Set all values to -1 initially
    for (int i = 0; i < numFrames; i++) {
        pageTable[i].pageNo = -1;
        pageTable[i].modified = -1;
    }

    // Initialise stack
    stack = (page *)malloc(frames * sizeof(page));

    // Set all values to -1 initially
    for (int i = 0; i < numFrames; i++) {
        stack[i].pageNo = -1;
        stack[i].modified = -1;
    }
    return 0;
}

/* Checks for residency: returns frame no or -1 if not found */
int checkInMemory(int page_number) {
    int result = -1;
    // Error handling
    if (pageTable == NULL) {
        printf("Page table hasn't been initialised properly");
        exit(-1);
    }

    // Find the page in the page table
    for (int i = 0; i < numFrames; i++) {
        // printf("%d, %d | ", pageTable[i].pageNo, page_number);
        if (pageTable[i].pageNo == page_number) {
            result = i;
            break;
        }
    }
    printf("\n");

    // Return index of page number
    return result;
}

/* allocate page to the next free frame and record where it put it */
int allocateFrame(int page_number, char rw) {
    page newPage;
    newPage.pageNo = page_number;
    newPage.modified = 0;
    if (rw == 'W') {
        newPage.modified = 1;
    }

    int location;
    for (int i = 0; i < numFrames; i++) {
        // If spot is free set to relevant information
        if (pageTable[i].pageNo == -1) {
            pageTable[i] = newPage;
            location = i;
            break;
        }
    }

    return location;
}

/* Selects a victim for eviction/discard according to the replacement algorithm,
 * returns chosen frame_no  */
page selectVictim(int page_number, enum repl mode) {
    page victim;

    // Implement individual page replacement algorithms here
    if (mode == 0) {  // Page replacement method - Random

    } else if (mode == 1) {  // Page replacement method - FIFO

    } else if (mode == 2) {  // Page replacement method - LRU
        victim = replacePageLRU(pageTable, stack, page_number, numFrames);
        for (int i = 0; i < numFrames; i++) {
            pageTable[i] = stack[i];
        }
    } else if (mode == 3) {  // Page replacement method - CLOCK

    } else {
        printf("Invalid page replacement algorithm.\n");
        exit(-1);
    }
    return (victim);
}

main(int argc, char *argv[]) {
    char *tracename;
    int page_number, frame_no, done;
    int do_line, i;
    int no_events, disk_writes, disk_reads;
    int debugmode;
    enum repl replace;
    int allocated = 0;
    int victim_page;
    unsigned address;
    char rw;
    page Pvictim;
    FILE *trace;
    if (argc < 5) {
        printf(
            "Usage: ./memsim inputfile numberframes replacementmode debugmode "
            "\n");
        exit(-1);
    } else {
        tracename = argv[1];
        trace = fopen(tracename, "r");
        if (trace == NULL) {
            printf("Cannot open trace file %s \n", tracename);
            exit(-1);
        }
        numFrames = atoi(argv[2]);
        if (numFrames < 1) {
            printf("Frame number must be at least 1\n");
            exit(-1);
        }
        if (strcmp(argv[3], "lru\0") == 0)
            replace = LRU;
        else if (strcmp(argv[3], "rand\0") == 0)
            replace = RANDOM;
        else if (strcmp(argv[3], "clock\0") == 0)
            replace = CLOCK;
        else if (strcmp(argv[3], "fifo\0") == 0)
            replace = FIFO;
        else {
            printf("Replacement algorithm must be rand/fifo/lru/clock  \n");
            exit(-1);
        }

        if (strcmp(argv[4], "quiet\0") == 0)
            debugmode = 0;
        else if (strcmp(argv[4], "debug\0") == 0)
            debugmode = 1;
        else {
            printf("Replacement algorithm must be quiet/debug  \n");
            exit(-1);
        }
    }

    done = createMMU(numFrames);
    if (done == -1) {
        printf("Cannot create MMU");
        exit(-1);
    }
    no_events = 0;
    disk_writes = 0;
    disk_reads = 0;

    do_line = fscanf(trace, "%x %c", &address, &rw);
    while (do_line == 2) {
        page_number = address >> pageoffset;

        page newPage;
        newPage.pageNo = page_number;
        newPage.modified = 0;
        if (rw == 'W') {
            newPage.modified = 1;
        }
        updateStack(stack, newPage, numFrames);

        // Print stack
        printStack(stack, numFrames);

        frame_no = checkInMemory(page_number); /* ask for physical address */
        if (frame_no == -1) {
            disk_reads++; /* Page fault, need to load it into memory */
            if (debugmode) printf("Page fault %8d \n", page_number);
            if (allocated < numFrames) /* allocate it to an empty frame */
            {
                frame_no = allocateFrame(page_number, rw);
                allocated++;
            } else {
                Pvictim = selectVictim(
                    page_number,
                    replace); /* returns page number of the victim  */
                frame_no = checkInMemory(
                    page_number); /* find out the frame the new page is in */
                if (Pvictim.modified) /* need to know victim page and modified  */
                {
                    printf("write MADE\n");
                    disk_writes++;
                    if (debugmode) printf("Disk write %8d \n", Pvictim.pageNo);
                } else if (debugmode)
                    printf("Discard    %8d \n", Pvictim.pageNo);
            }
        }
        if (rw == 'R') {
            if (debugmode) printf("reading    %8d \n", page_number);
        } else if (rw == 'W') {
            // mark page in page table as written - modified
            if (debugmode) printf("writing    %8d \n", page_number);
        } else {
            printf("Badly formatted file. Error on line %d\n", no_events + 1);
            exit(-1);
        }

        no_events++;
        do_line = fscanf(trace, "%x %c", &address, &rw);
    }

    printf("total memory frames:  %d\n", numFrames);
    printf("events in trace:      %d\n", no_events);
    printf("total disk reads:     %d\n", disk_reads);
    printf("total disk writes:    %d\n", disk_writes);
    printf("page fault rate:      %.4f\n", (float)disk_reads / no_events);
}

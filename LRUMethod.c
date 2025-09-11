#include "LRUMethod.h"
#include <stdio.h>

void updateStack(page*, page, int);
void updatePageTable(page*, page, page, int);
void printStack(page*, int);

// Run replacement algorithm LRU
page replacePageLRU(page* pageTable, page* stack, int pageNumber, char rw, int numFrames) {
    // Update page table
    for (int i = 0; i < numFrames - 1; i++) {
        if (pageTable[i + 1].pageNo == -1) {
            pageTable[i] = stack[0];
        }
    }

	page lastPage = stack[numFrames - 1];
	for (int i = 0; i < numFrames; i++) {
		if (stack[i + 1].pageNo == -1) {
			lastPage = stack[i];
		}
	}

    page newPage;
    newPage.pageNo = pageNumber;
    newPage.modified = 0;
    if (rw == 'W') {
        newPage.modified = 1;
    }

    updateStack(stack, newPage, numFrames);
    updatePageTable(pageTable, lastPage, newPage, numFrames);
    
	// printf("last page with number: %d\n", lastPage.pageNo);
	return lastPage;
}

void updateStack(page* stack, page pageToAdd, int numFrames) {
    // Check if page exists in the stack, if it does move to top of stack
    int replaceIndex = -1;
    for (int i = 0; i < numFrames; i++) {
		// printf("stack[i].pageNo = %d, pageToAdd.pageNo = %d\n", stack[i].pageNo, pageToAdd.pageNo);
        if (stack[i].pageNo == pageToAdd.pageNo) {
            replaceIndex = i;
            break;
        }
    }

    // Add page to stack
    if (replaceIndex == -1) {  // New page
        for (int i = numFrames; i >= 0; i--) {
            stack[i] = stack[i - 1];
        }
        stack[0] = pageToAdd;
    } else {
        for (int i = replaceIndex; i >= 0; i--) {
            stack[i] = stack[i - 1];
        }
        stack[0] = pageToAdd;
    }
}

void updatePageTable(page* pageTable, page pageToReplace, page newPage, int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (pageTable[i].pageNo == pageToReplace.pageNo) {
            pageTable[i] = newPage;
            break;
        }
    }
}

void printStack(page* stack, int numFrames) {
	printf("\n");
	for (int i = 0; i < numFrames; i++) {
		printf("%d, modified: %d | ", stack[i].pageNo, stack[i].modified);
	}
	printf("- END\n");
}
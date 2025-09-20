#ifndef PAGE_H
#define PAGE_H

typedef struct {
    int pageNo;
    int modified;
    int use; // For clock alg
} page;

#endif
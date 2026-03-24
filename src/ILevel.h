#ifndef ILEVEL_H
#define ILEVEL_H

#include <raylib.h>

typedef struct {
    int n;
    void (*render)(Camera3D camera);
} ILevel;

#endif

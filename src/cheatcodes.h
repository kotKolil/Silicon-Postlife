#include <stdint.h>

#ifndef LEVELLOADER_H
#define LEVELOADER_H

typedef struct Camera3D Camera3D;
typedef struct actor actor;

void scan_char(int *levelCurrent, Camera3D *camera, actor *player);

 
#endif

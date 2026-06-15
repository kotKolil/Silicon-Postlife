#include <stdint.h>

#ifndef LEVELLOADER_H
#define LEVELOADER_H

typedef struct Camera3D Camera3D;

void LoadLevel(int *CurrentLevel, Camera3D *camera);
void InitLevels();

extern uint8_t levelN;
extern uint8_t levelMax;
 
#endif

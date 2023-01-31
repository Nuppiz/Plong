#ifndef TEXT_H
#define TEXT_H

#include "Incl_std.h"

void loadFont();
void drawSymbol(int x, int y, int i, uint8_t color);
int  drawText(int x, int y, char* string, uint8_t color);

#endif /* TEXT_H */

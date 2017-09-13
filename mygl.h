#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

typedef struct Color {
	float R,G,B,A;
} Color;
typedef struct Pos {
	int x, y;
} Pos;
extern void drawLineA(Pos * p0, Pos * p1, Color * c, Color * c2);
extern void drawLine(Pos * p0, Pos * p1, Color * c);
extern void drawTriangle(Pos * p0, Color * c0, Pos * p1, Color * c1, Pos * p2, Color * c2);
#endif // _MYGL_H_


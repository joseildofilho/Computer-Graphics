#include "main.h"
#include <stdio.h>
#include <stdlib.h>
/*-----------------------------------------------------------------------------
	Warning: Quando usar a função tenha certeza que os valores estão dentro dos padrões de RGB
			que são : 0 <= R <= 255, 0 <= G <= 255, 0 <= B <= 255
			e para os : 0 <= x <= IMAGE_WIDTH E 0 <= Y <= IMAGE_HEIGHT.
			Os testes para validarem os parametros não são feitos pois, 
			reduzem um pouco o desempenho da função e em virtude que assumi
			que sabesse onde está sendo escrita na memoria.
			O Alpha desta chamada será por padrão no maximo.
-----------------------------------------------------------------------------*/
void putPixel(int x, int y, Color * c)
{
	FBptr[4*x + 4*y*IMAGE_WIDTH] = c->R;
	FBptr[4*x + 4*y*IMAGE_WIDTH + 1] = c->G;
	FBptr[4*x + 4*y*IMAGE_WIDTH + 2] = c->B;
	FBptr[4*x + 4*y*IMAGE_WIDTH + 3] = c->A;
}
/*-----------------------------------------------------------------------------
	Este metodo é a versão do Bresenham simples, ela funciona, poem apenas 
		para um octante da tela, ou seja apenas para os angulos entre
		0º e 45º ou tangete de 0 a 1.
-----------------------------------------------------------------------------*/
void drawLine(int x0, int y0, int x1, int y1,Color * c)
{
	int x, 
	e = 0,
	y = y0,
	dx = x1 - x0,
	dy = y1 - y0;
	for(x = x0; x < x1; x++) {
		putPixel(x,y,c);
		e += dy;
		if( e << 1 >= dx) {
			y ++;
			e -= dx;
		}
	}
}
/*-----------------------------------------------------------------------------
	Este é o Bresenham completo funciona para todo o plano.
-----------------------------------------------------------------------------*/
void drawLineA(Pos * p0, Pos * p1, Color * c1, Color * c2)
{
	int dx = p1->x - p0->x,
	dy = p1->y - p0->y,
	e,
	ix = 1, iy = 1,
	x, y,i;

	Color * c = (struct Color *) malloc(sizeof(Color));
	c->R = c1->R;
	c->G = c1->G;
	c->B = c1->B;
	c->A = c1->A;
	
	if(dx < 0) ix = -ix;
	if(dy < 0) iy = -iy;
	dx = abs(dx);
	dy = abs(dy);	
	float dR = (c2->R - c->R),dG = (c2->G - c->G), dB = (c2->B - c->B), dA = (c2->A - c->A);

	x = p0->x;
	y = p0->y;
	if (dx > dy) {
		e = (dy << 1) - dx;
		dR /= dx; dG /= dx; dB /= dx; dA /= dx;
		for(i = 0; i < dx; i++) {
			
			c->R += dR;
			c->G += dG;
			c->B += dB;
			c->A += dA;
			putPixel(x,y,c);
			if(e < 0)
				e += dy << 1;
			else {
				y += iy;
				e += (dy - dx) << 1;
			}
			x += ix;
		}
	} else {
		e = (dx << 1) - dy;
		dR /= dy; dG /= dy; dB /= dy; dA /= dy;
                for(i = 0; i < dy; i++) {
			c->R += dR;
			c->G += dG;
			c->B += dB;
			c->A += dA;

                        putPixel(x,y,c);
                        if(e < 0)
                                e += dx << 1;
                        else {
                                x += ix;
                                e += (dx - dy) << 1;
                        }
			y += iy;
                }
	}
}
void drawTriangle(Pos * p0, Color * c0, Pos * p1, Color * c1, Pos * p2, Color * c2) {
	drawLineA(p0,p1,c0,c1);
	drawLineA(p1,p2,c1,c2);
	drawLineA(p2,p0,c2,c0);
}
//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	/*int i,j;
	for(i = 0; i < IMAGE_WIDTH;i+=4) {
		for(j = 0; j < IMAGE_HEIGHT; j+=4) {
			putPixel(i,j,110,100,253);
		}
	}*/
	Color * co;
	co = (struct Color *) malloc(sizeof(Color));
	co->R = 0;
	co->G = 0;
	co->B = 255;
	co->A = 255;
	Color * co2;
	co2 = (struct Color *) malloc(sizeof(Color));
	co2->R = 0;
	co2->G = 255;
	co2->B = 0;
	co2->A = 255;
	Color * co3 = (struct Color *) malloc(sizeof(Color));
	co3->R = 255;
	co3->G = 0;
	co3->B = 0;
	co3->A = 255;
	Pos * p0 = (struct Pos *) malloc(sizeof(Pos));
	Pos * p1 = (struct Pos *) malloc(sizeof(Pos));
	Pos * p2 = (struct Pos *) malloc(sizeof(Pos));

	p0->x = 50;
	p0->y = 50;
	p1->x = 500;
	p1->y = 500;
	p2->x = 300;
	p2->y = 50;
	/*
	p0->x = 0;
	p0->y = 0;
	p1->x = IMAGE_WIDTH;
	p1->y = IMAGE_HEIGHT;
	drawLineA(p0,p1,co,co2);
	p0->x = IMAGE_WIDTH * 0.25;
	p1->x = IMAGE_WIDTH * 0.75;
	drawLineA(p0,p1,co2,co3);

	p0->x = IMAGE_WIDTH * 0.5;
	p1->x = IMAGE_WIDTH * 0.5;

	drawLineA(p0,p1,co3,co);
	
	p0->x = IMAGE_WIDTH * 0.75;
	p1->x = IMAGE_WIDTH * 0.25;

	drawLineA(p0,p1,co,co2);

	p0->x = IMAGE_WIDTH;
	p1->x = 0;
	drawLineA(p0,p1,co2,co3);
	p0->y = IMAGE_WIDTH * 0.25;
	p1->y = IMAGE_WIDTH * 0.75;
	drawLineA(p0,p1,co3,co2);
	p0->y = IMAGE_WIDTH * 0.5;
	p1->y = IMAGE_WIDTH * 0.5;
	drawLineA(p0,p1,co2,co);
	p0->y = IMAGE_WIDTH * 0.75;
	p1->y = IMAGE_WIDTH * 0.25;
	drawLineA(p0,p1,co2,co);
	*/
	drawTriangle(p0,co,p1,co2,p2,co3);
	p0->y = 0;
	p1->y = 0;
	drawLineA(p0,p1,co,co2);
	p0->y = 0;
	p1->y = 1;
	drawLineA(p0,p1,co,co2);
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}


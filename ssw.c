#include "SDL2/SDL.h" // draw from local resource pool
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_events.h"
#include <stdlib.h>

#define uchar unsigned char 
#define uint unsigned int 

struct cxt {
SDL_Window *win;
SDL_Event event;
};

struct cache {
char t;
char b;
int txt;
int x;
int y;
};

struct cxt context[20];

unsigned long LHEX(char v[7]){
int r, g, b;
r = 16*(v[1] - 48 - (((v[1] - 48)>>5)*39)) + v[2] - 48 - (((v[2] - 48)>>5)*39);
g = 16*(v[3] - 48 - (((v[3] - 48)>>5)*39)) + v[4] - 48 - (((v[4] - 48)>>5)*39);
b = 16*(v[5] - 48 - (((v[5] - 48)>>5)*39)) + v[6] - 48 - (((v[6] - 48)>>5)*39);
return b + (g<<8) + (r<<16);
}

unsigned long HEX(char v[7]){
int r, g, b;
r = 16*(v[1] - 48 - (((v[1] - 48)>>4)*7)) + v[2] - 48 - (((v[2] - 48)>>4)*7);
g = 16*(v[3] - 48 - (((v[3] - 48)>>4)*7)) + v[4] - 48 - (((v[4] - 48)>>4)*7);
b = 16*(v[5] - 48 - (((v[5] - 48)>>4)*7)) + v[6] - 48 - (((v[6] - 48)>>4)*7);
return b + (g<<8) + (r<<16);
}

unsigned long RGB(int r, int g, int b){
return b + (g<<8) + (r<<16);
}

void XI(char isRoot, const char *title, const char *subtitle, int w, int h, int sx, int sy, char d) {
	if (!SDL_WasInit(32)) {
	SDL_Init(32);
	}
context[d].win = SDL_CreateWindow("Snek", sx, sy, w, h, 0);
context[d].event.type = 0x200;
SDL_PushEvent(&context[d].event);
}

void RegionFill(int x, int y, int w, int h, unsigned long color, char d) {

int he, wi;
SDL_GetWindowSize(context[d].win, &wi, &he);
if (w==wi&&h==he) {
SDL_UpdateWindowSurface(context[d].win);
} 
SDL_Rect r;
r.x = x;
r.y = y;
r.w = w;
r.h = h;
SDL_FillRect(SDL_GetWindowSurface(context[d].win), &r, SDL_MapRGB(SDL_GetWindowSurface(context[d].win)->format, color>>16, (color>>8)&255, color&255));
}


void RegionScarf(int x, int y, int w, int h, unsigned long color, char d) {
SDL_Rect r;
r.x = x - 1;
r.y = y - 1;
r.w = 1;
r.h = h + 2;
SDL_FillRect(SDL_GetWindowSurface(context[d].win), &r, SDL_MapRGB(SDL_GetWindowSurface(context[d].win)->format, color>>16, (color>>8)&255, color&255));
r.h = 1;
r.w = w + 2;
SDL_FillRect(SDL_GetWindowSurface(context[d].win), &r, SDL_MapRGB(SDL_GetWindowSurface(context[d].win)->format, color>>16, (color>>8)&255, color&255));
r.x = w + x;
r.h = h + 2;
r.w = 1;
SDL_FillRect(SDL_GetWindowSurface(context[d].win), &r, SDL_MapRGB(SDL_GetWindowSurface(context[d].win)->format, color>>16, (color>>8)&255, color&255));
r.x = x;
r.y = h + y;
r.w = w + 2;
r.h = 1;
SDL_FillRect(SDL_GetWindowSurface(context[d].win), &r, SDL_MapRGB(SDL_GetWindowSurface(context[d].win)->format, color>>16, (color>>8)&255, color&255));
}


void Eve(struct cache *cc, char d) {
cc->t =   0;
cc->b =   0;
cc->txt = 0;
cc->x =   0;
cc->y =   0;
SDL_WaitEvent(&context[d].event);
	if (context[d].event.type==0x100) {
	SDL_DestroyWindow(context[d].win);
	SDL_Quit();
	}
	if (context[d].event.type==0x200||context[d].event.type==0x400) {
	cc->t = 3;
	}
	if (context[d].event.type==0x300||context[d].event.type==0x301) {
	cc->t = 1;
		if (context[d].event.key.keysym.scancode==82) {
		cc->txt = 65362;
		}
		if (context[d].event.key.keysym.scancode==79) {
		cc->txt = 65363;
		}
		if (context[d].event.key.keysym.scancode==81) {
		cc->txt = 65364;
		}
		if (context[d].event.key.keysym.scancode==80) {
		cc->txt = 65361;
		}
		if (context[d].event.key.keysym.scancode<31) {
		cc->txt = context[d].event.key.keysym.scancode + 93;
		}
	}
}

int Pend(char d) {
	if (SDL_PollEvent(&context[d].event)==NULL) {
	return 0;
	} else {
	return 1;
	}
}

unsigned int WW(char d) {
int w, h;
SDL_GetWindowSize(context[d].win, &w, &h);
return w;
}

unsigned int WH(char d) {
int w, h;
SDL_GetWindowSize(context[d].win, &w, &h);
return h;
}

void Clean(char d) {
SDL_DestroyWindow(context[d].win);
SDL_Quit();
}

void XX(char opt) {
exit(opt);
}




float FISR(float n) { // this is not my code
	float xhalf = 0.5f * n;
	int i = *(int*)&n;            // store floating-point bits in integer
	i = 0x5f375a85 - (i >> 1);    // initial guess for Newton's method
	n = *(float*)&i;              // convert new bits into float
	n = n*(1.5f - xhalf*n*n);     // One round of Newton's method
	return n;
} // this is not my code

int adjpow(uint n) {
int p;
char i = sizeof(p)*8-1;
	while ((n&((~0)<<i))==0) {
	i--;
	}
i--;
return ((n>>i)+((n>>i)&1))<<i;
}

void drawcurve(unsigned long rgb, uint *x, uint *y, uchar n, int sec, int size, char win) {
float xslice[255]; // static array sizes
float yslice[255];
float t, tc, totx, toty;
tc = (float)1.0/adjpow(size);
int xc;
int yc;

	for (t = 0; (uint)t==0; t+=tc) {
	xslice[0] = 1;
	yslice[0] = 1;
	xc = 1;
		while (xc < n) {
		xslice[xc] = t * xslice[xc - 1] * (n - xc) / xc;
		yslice[xc] = xslice[xc];
		xc++;
		}
	xc = 0;
		while (xc < n) {
		xslice[xc]*=x[xc];
		yslice[xc]*=y[xc];
		xc++;
		}
	totx=xslice[n - 1];
	toty=yslice[n - 1];
	xc = 0;
		while (xc < n - 1) {
			for (yc = 0; yc < n - xc - 1; yc++) {
			xslice[xc]*=(1 - t);
			yslice[xc]*=(1 - t);
			}
		totx+=xslice[xc];
		toty+=yslice[xc];
		xc++;
		}

		xc = -1*sec/2;
		while (xc < sec/2 + 1) {
		yc = (sec*sec/4-xc*xc)*FISR(sec*sec/4-xc*xc);
		RegionFill((uint)(totx+xc), (uint)(toty-yc), 1, (uint)(2*yc), rgb, win);
		xc++;
		}
	}
}

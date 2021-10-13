#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include <stdlib.h>

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
// SDL_UpdateWindowSurface(context[d].win);
}


void RegionScarf(int x, int y, int h, int w, unsigned long color, char d) {
SDL_Rect r;
r.x = x - 1;
r.y = y - 1;
r.w = w + 2;
r.h = h + 2;
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

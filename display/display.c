/*
 * display.c
 *
 *  Created on: 6 Jun 2013
 *      Author: nick

Copyright (c) 2013, dharc ltd.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
 */

#include <dsb/module.h>
#include <dsb/errors.h>
#include <dsb/nid.h>
#include <dsb/wrap.h>
#include <dsb/globals.h>
#include <dsb/names.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <stdio.h>

static struct Module dispmod;
static NID_t base;

SDL_Surface *screen;

DSB_NAME(X1);
DSB_NAME(Y1);
DSB_NAME(X2);
DSB_NAME(Y2);
DSB_NAME(Type);
DSB_NAME(Width);
DSB_NAME(Height);

int disp_init(const NID_t *b)
{
	int width;
	int height;

	DSB_INIT(X1,x1);
	DSB_INIT(Y1,y1);
	DSB_INIT(X2,x2);
	DSB_INIT(Y2,y2);
	DSB_INIT(Type,type);
	DSB_INIT(Width,width);
	DSB_INIT(Height,height);

	//Get display object
	dsb_getnzn(b,"display",&base);
	if (dsb_nid_eq(&base,&Null) == 1)
	{
		//Make it if it doesn't exist.
		dsb_new(b,&base);
		dsb_setnzn(b,"display",&base);
	}

	if (dsb_getnni(&base,Width,&width) != 0)
	{
		//Not a number so set to default.
		width = 640;
		dsb_setnni(&base,Width,width);
	}
	if (dsb_getnni(&base,Height,&height) != 0)
	{
		height = 480;
		dsb_setnni(&base,Height,height);
	}

	printf("Init SDL display\n");
	SDL_Init(SDL_INIT_VIDEO);

	screen = SDL_SetVideoMode(width,height,16,SDL_HWSURFACE);

	if (screen == 0)
	{
		printf("Could not create display\n");
		return -1;
	}

	SDL_WM_SetCaption("DSB Display","DSB");

	return SUCCESS;
}

int disp_final()
{
	SDL_Quit();
	return SUCCESS;
}

static int disp_drawline(const NID_t *line)
{
	int x1,x2,y1,y2 = 0;
	int ret;
	ret =  dsb_getnni(line,X1,&x1);
	ret += dsb_getnni(line,Y1,&y1);
	ret += dsb_getnni(line,X2,&x2);
	ret += dsb_getnni(line,Y2,&y2);

	if (ret > 0) return 0;

	aalineRGBA(screen,x1,y1,x2,y2,255,0,0,255);

	return 0;
}

int disp_update()
{
	//Test Line Draw
	SDL_LockSurface(screen);

	disp_drawline(&base);

	SDL_UnlockSurface(screen);
	SDL_UpdateRect(screen,0,0,100,100);

	return 0;
}

/*
 * Module registration structure.
 */
struct Module *dsb_module_info()
{
	dispmod.init = disp_init;
	dispmod.update = disp_update;
	dispmod.final = disp_final;
	dispmod.ups = 40;
	return &dispmod;
}


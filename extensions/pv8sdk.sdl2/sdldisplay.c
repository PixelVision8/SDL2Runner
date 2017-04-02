// Microsoft Public License (MS-PL) - Copyright (C) Shawn Rakowski
// This file is subject to the terms and conditions defined in
// file 'LICENSE', which is part of this source code package.

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "display.h"
#include "sdldisplay.h"

typedef struct sdlDisplay {
    display base; // must be first
    int winWidth;
    int winHeight;
    int dispWidth;
    int dispHeight;
    SDL_Window *window;
    SDL_Renderer *renderer;
} sdlDisplay;

static void sdlDisplay_Destroy(SdlDisplay self);
static void sdlDisplay_Init(SdlDisplay self);
static void sdlDisplay_Dispose(SdlDisplay self);

SdlDisplay sdlDisplay_Create(int winWidth, int winHeight, int dispWidth, int dispHeight)
{
    SdlDisplay self = NULL;

    self = (SdlDisplay)calloc(1, sizeof(sdlDisplay));
    if (self == NULL)
        return NULL;

    self->base.destroy = sdlDisplay_Destroy;
    self->base.init = sdlDisplay_Init;

    self->winWidth = winWidth;
    self->winHeight = winHeight;
    self->dispWidth = dispWidth;
    self->dispHeight = dispHeight;

    return self;
}

static void sdlDisplay_Destroy(SdlDisplay self)
{
    assert(self);
    sdlDisplay_Dispose(self);
    memset(self, 0, sizeof(sdlDisplay));
    free(self);
}

static void sdlDisplay_Init(SdlDisplay self)
{
    assert(self);
    sdlDisplay_Dispose(self);
    int result = SDL_CreateWindowAndRenderer(self->winWidth, self->winHeight, 0, &self->window, &self->renderer);
    if (result < 0) // TODO: deal with this
        return;

    SDL_RenderSetLogicalSize(self->renderer, self->dispWidth, self->dispHeight);
}

static void sdlDisplay_Dispose(SdlDisplay self)
{
    assert(self);
    if (self->renderer != NULL)
    {
        SDL_DestroyRenderer(self->renderer);
        self->renderer = NULL;
    }
    if (self->window != NULL)
    {
        SDL_DestroyWindow(self->window);
        self->window = NULL;
    }
}
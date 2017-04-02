// Microsoft Public License (MS-PL) - Copyright (C) Shawn Rakowski
// This file is subject to the terms and conditions defined in
// file 'LICENSE', which is part of this source code package.

#include <assert.h>
#include <stdlib.h>
#include "util.h"
#include "chip.h"
#include "displaychip.h"

typedef struct displayChip {
    chip base; // must be first
} displayChip;

static void displayChip_Destroy(DisplayChip self);

DisplayChip displayChip_Create()
{
    DisplayChip self = NULL;

    self = (DisplayChip)calloc(1, sizeof(displayChip));
    if (self == NULL)
        return NULL;

    strncpy(self->base.name, nameof(DisplayChip), sizeof(self->base.name) - 1);
    self->base.destroy = displayChip_Destroy;

    return self;
}

static void displayChip_Destroy(DisplayChip self)
{
    assert(self);
    memset(self, 0, sizeof(displayChip));
    free(self);
}

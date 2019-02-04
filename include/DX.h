#ifndef DX_H
#define DX_H

/* Config */
#define DX_MAX_ENTITIES (32)
#define DX_MAX_SYSTEMS (8)
#define DX_DEBUG (1)
// #undef DX_DEBUG 

/* Std */
#include <stdlib.h>
#include <stdio.h>

/* Util */
#include "DX_Vector.h"

/* Base Entity */
#include "entities/DX_Entity.h"
/* Base System */
#include "systems/DX_System.h"
/* Components */
#include "components/DX_ID.h"
#include "components/DX_CTransform.h"
#include "components/DX_CSprite.h"
#include "components/DX_CPhysics.h"

/* World */
#include "DX_World.h"

/* Base */
#include "DX_main.h"

/* Entities */
#include "entities/DX_ERect.h" // <-- Lol

/* Systems */
#include "systems/DX_SRender.h"

#endif // DX_H
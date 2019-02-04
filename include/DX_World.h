#ifndef DX_WORLD_H
#define DX_WORLD_H
/* Container  */
typedef struct DX_World
{	
	DX_Entity entities[DX_MAX_ENTITIES];

	DX_CTransform transform[DX_MAX_ENTITIES];
	DX_CPhysics physics[DX_MAX_ENTITIES];
	DX_CSprite sprite[DX_MAX_ENTITIES];

	DX_System systems[DX_MAX_SYSTEMS];
} DX_World;
#endif
#ifndef DX_ERECT_H
#define DX_ERECT_H
/* Entity prefab that gets queued into a world's Render System. */

DX_Entity* DX_CreateERect( DX_World* world, int x, int y, int w, int h )
{
	DX_Entity* e = DX_CreateEntity(world); 
	int id = e->id;

	DX_AddComponent( world, e, DX_CTRANSFORM|DX_CSPRITE );
	world->transform[id].x = x;
	world->transform[id].y = y;
	world->transform[id].w = w;
	world->transform[id].h = h;
	
	return e;
}
#endif
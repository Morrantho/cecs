#ifndef DX_SRENDER_H
#define DX_SRENDER_H
void DX_SRender( DX_World* world, int sysId )
{
	DX_System* sys = &world->systems[sysId];
	DX_Vector* vec = sys->entities;
	int size       = vec->size;

	for( int i=0; i < size; i++ )
	{

		int* entP = (int*) DX_GetVector( vec, i );

		printf( "%d %p\n", i, entP );

		// if(entP == NULL) continue;

		// unsigned int ent   = *entP;
		// world->transform[ent].x += 128;
		// printf("%s %d %s %d\n", "Ent ID:",ent,"Vec Size:", size );
	}
}
#endif // DX_SRENDER_H
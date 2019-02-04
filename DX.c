#include "include/DX.h"

/* Tests */

int main( int argc, char** argv )
{
	/* Creating a world + Init */
	DX_World world;
	DX_InitWorld( &world );

	/* Registering a system into a world with a specific mask and function pointer / callback */
	int renderSys = DX_CreateSystem( &world, DX_CTRANSFORM|DX_CSPRITE, DX_SRender );
	/* Creating a predefined entity into the world */
	DX_Entity* rect  = DX_CreateERect( &world, 16, 16, 32, 32 );

	/*	Simulate Game Loop / ticking while adding + removing components. */	
	int ticks = 16;

	while( ticks > 0 )
	{
		/* Call each systems Run Callback / function pointer */
		for( int i=0; i < DX_MAX_SYSTEMS; i++ )
			if( world.systems[i].Run != NULL)
				world.systems[i].Run( &world, i );

		if(ticks == 6)
		{
			/* 
				Removing this component causes the "rect" entity to remove from the RenderSystem, 
				since its mask no longer matches the system's mask. 
			*/
			DX_RemoveComponent( &world, rect, DX_CTRANSFORM );
		}
		else if(ticks == 10)
		{
			/* Creating another entity to show dynamic system updates. */
			DX_Entity* rectTwo = DX_CreateERect( &world, 64,64,128,128 );
		}

		ticks--;
	}

	/* Cleanup */
	DX_DestroyWorld( &world );
	return 0;
}
#ifndef DX_MAIN_H
#define DX_MAIN_H

void DX_InitWorld( DX_World* world )
{
	/* Entities */
	for(int i=0; i < DX_MAX_ENTITIES; i++)
	{
		world->entities[i].id = i;
		world->entities[ i ].mask = 0;
	}

	/* Systems */
	for( int i=0; i < DX_MAX_SYSTEMS; i++)
	{
		world->systems[i].Run = NULL;
		world->systems[i].mask = 0;
		world->systems[i].entities = NULL;
	}
}

void DX_DestroyWorld( DX_World* world )
{
	printf("%s\n","---CLEANING SYSTEM VECTORS---");
	for(int i=0; i < DX_MAX_SYSTEMS; i++)
	{
		if( world->systems[i].entities != NULL )
		{
			DX_DestroyVector( world->systems[i].entities );
			world->systems[i].entities = NULL;

			#ifdef DX_DEBUG
			printf("%s %d\n", "Freed entity vector on system:", i );
			#endif
		}
	}
	printf("%s\n","---SYSTEMS CLEANED---");
}

DX_Entity* DX_CreateEntity( DX_World* world )
{
	for(int i=0; i < DX_MAX_ENTITIES; i++)
		if( world->entities[i].mask == 0 )	
			return &world->entities[i];

	return NULL;
}

// Queues a system in the world with the specified mask and callback. Returns its index in the world's system array.
int DX_CreateSystem( DX_World* world, int mask, void ( *cb )( DX_World* world, int index ) )
{
	for( int i=0; i < DX_MAX_SYSTEMS; i++)
	{
		if( world->systems[i].mask == 0 || world->systems[i].Run == NULL )
		{
			world->systems[i].mask = mask;
			world->systems[i].Run = cb;
			#ifdef DX_DEBUG
				printf("%s %d\n", "System Queued at index:", i);
			#endif
			return i;
		}
	}

	#ifdef DX_DEBUG
		printf("%s \n","System capacity reached for this world.");
	#endif
	return DX_MAX_ENTITIES;
}

void DX_DestroyEntity( DX_World* world, DX_Entity* ent )
{
	world->entities[ ent->id ].mask = 0;
}

int DX_HasComponent( DX_World* world, DX_Entity* ent, int component )
{
	return ( world->entities[ ent->id ].mask & component ) == component;
}

void DX_AddComponent( DX_World* world, DX_Entity* ent, int component )
{
	#ifdef DX_DEBUG
		if( DX_HasComponent( world, ent, component ) )
		{
			printf("%s %d %s %d\n", "Entity:",ent->id,"Already has component:", component);
			return;
		}
	#endif
	/* Update the entities' mask */
	world->entities[ ent->id ].mask |= component;

	/* Search for systems this entity might match */
	for( int i=0; i < DX_MAX_SYSTEMS; i++)
	{
		int sysMask = world->systems[i].mask;
		int entMask = world->entities[ ent->id ].mask;
		int result  = sysMask & entMask;

		/* We found a match, place this entity into that system for operation. */
		if( result == sysMask && result != 0 )
		{
			#ifdef DX_DEBUG
				printf("%s %d %s %d\n", "Registered Entity:", ent->id, " Into System:", i);
			#endif
			if( world->systems[i].entities == NULL )
				world->systems[i].entities = DX_CreateVector();
			/* 
				Push this entity ID into the correct systems entity vector 
				Storing ids instead of masks, because its already obvious the entity mask matches the systems.
			*/
			DX_PushVector( world->systems[i].entities, ent );
			return;
		}
	}
}

void DX_RemoveComponent( DX_World* world, DX_Entity* ent, int component )
{
	#ifdef DX_DEBUG
		if( !DX_HasComponent(world,ent,component) )
		{
			printf("%s %d\n", "This entity doesn't have component:", component);
			return;		
		}
	#endif

	world->entities[ ent->id ].mask ^= component;

	for( int i=0; i < DX_MAX_SYSTEMS; i++)
	{
		int sysMask = world->systems[i].mask;
		int entMask = world->entities[ ent->id ].mask;
		int result  = sysMask & entMask;

		/* We found no matches, remove this entity from any system it no longer matches. */
		if( result != sysMask && result != 0 )
		{
			if( world->systems[i].entities != NULL ) // This system's entity vector was defined previously.
			{
				/* Try to find a matching entity id, so we can remove it from the system's entity vector.  */
				for(int j = 0; j < world->systems[i].entities->size; j++)
				{			
					int* e = DX_GetVector( world->systems[i].entities, j );
					
					// /* We've found the entity to remove. */
					if( *e == ent->id )
					{
					// 	 Try popping and praying for no segfaults. 
						DX_PopVectorI( world->systems[i].entities, j );
						#ifdef DX_DEBUG
							printf("%s %d %s %d\n", "Unregistered Entity:", ent->id, " From System:", i);
						#endif
					}
				}
			}
		}		
	}
}
#endif // DX_MAIN_H
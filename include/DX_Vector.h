#ifndef DX_VECTOR_H
#define DX_VECTOR_H

/* Hand Rolled Dynamic Vector. */

#include <stdlib.h>

typedef struct DX_Vector
{
	int size; // Total Capacity.
	void** data;
} DX_Vector;

DX_Vector* DX_CreateVector()
{
	DX_Vector* vec = (DX_Vector*) malloc( sizeof( DX_Vector* ) );
	if( !vec ) return NULL;
	vec->size = 0;
	vec->data = malloc( sizeof( void* ) );
	if( !vec->data ) return NULL;
	return vec;
}

/* Don't forget to wipe */
void DX_DestroyVector( DX_Vector* vec )
{
	for(int i=0; i < vec->size; i++)
	{
		free(vec->data[i]);
		vec->data[i] = NULL;
	}
	free(vec->data);
	vec->data = NULL;

	free(vec);
	vec = NULL;
}

DX_Vector* DX_ResizeVector( DX_Vector* vec, int size )
{
	if( size <= 0 ) size = 0;
	vec->data = realloc( vec->data, size * sizeof( void* ) );
	if(vec->data == NULL){ return NULL; }
	vec->size = size;

	return vec;
}

DX_Vector* DX_GrowVector( DX_Vector* vec )
{
	return DX_ResizeVector( vec, vec->size+1 );
}

DX_Vector* DX_ShrinkVector( DX_Vector* vec )
{
	return DX_ResizeVector(vec, vec->size-1);
}

void* DX_GetVector( DX_Vector* vec, int index )
{
	return vec->data[ index ];
}

void DX_SetVector( DX_Vector* vec, int index, void* data )
{
	if( index < 0 || index > vec->size) return;
	vec->data[index] = data;
}

void DX_PushVector( DX_Vector* vec, void* data )
{
	vec = DX_GrowVector( vec ); // We need to realloc.
	vec->data[ vec->size-1 ] = NULL;
	vec->data[ vec->size-1 ] = data;
}

/* 
	Frees + NULLs last index. 
	DX_GetVector( vec, vec->size-1 ) it before popping, if you still need it. 
*/
void DX_PopVector( DX_Vector* vec )
{
	vec = DX_ShrinkVector( vec );
}

/* Performs O(1) overwrite with last index and desired index, then trims the end. Order doesn't matter. */
void DX_PopVectorI( DX_Vector* vec, int index)
{
	if(index < 0 || index > vec->size) return;
	vec->data[ index ] = vec->data[ vec->size-1 ];
	vec = DX_ShrinkVector(vec);
}
#endif
#ifndef DX_SYSTEM_H
#define DX_SYSTEM_H
typedef struct DX_System
{
	int mask;
	DX_Vector* entities; // Cast elements to int*, since this only stores masks. 
	void (*Run)();
} DX_System;
#endif // DX_SYSTEM_H
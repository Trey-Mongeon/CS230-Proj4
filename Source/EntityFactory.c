//------------------------------------------------------------------------------
//
// File Name:	EntityFactory.c
// Author(s):	Trey Mongeon (tmongeon), Doug Schilling (dschilling)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "EntityFactory.h"
#include "Stream.h"
#include "Entity.h"
#include "Sprite.h"
#include "Transform.h"
#include "Physics.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
// Build a single instance of the specified entity.
// (HINT: See project instructions.)
// Params:
//	 filename = The name of the file to be deserialized.
// Returns:
//	 If the filename is valid
//	   then return a pointer to a new instance of the specified entity,
//	   else NULL.
Entity* EntityFactoryBuild(const char* filename)
{
	if (filename)
	{
		Stream stream = StreamOpen(filename);

		if(stream)
		{
			const char* token = StreamReadToken(stream);

			if (!strncmp("Entity", token, _countof("Entity")))
			{
				Entity *entityPtr = EntityCreate();
				EntityRead(entityPtr, stream);
				StreamClose(&stream);
				return entityPtr;
			}
		}
		StreamClose(&stream);
	}
	return NULL;
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------


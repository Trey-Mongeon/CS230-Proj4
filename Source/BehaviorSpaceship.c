//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceship.c
// Author(s):	Trey Mongeon (tmongeon), Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S25
//
// Copyright � 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorSpaceship.h"
#include "Behavior.h"
#include "DGL.h"
#include "Entity.h"
#include "Transform.h"
#include "Physics.h"
#include "Vector2D.h"

#define PI 3.14159

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

enum spaceshipState
{
	cSpaceshipInvalid = -1,
	cSpaceshipIdle,
	cSpaceshipThrust
};

static const float spaceshipAcceleration = 150.0f;
static const float spaceshipSpeedMax = 500.0f;
static const float spaceshipTurnRateMax = (float)PI / 1.5f;
static const float spaceshipWeaponCooldownTime = 0.034f;
static const float spaceshipWeaponBulletSpeed = 750.0f;


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

static void BehaviorSpaceshipOnInit(Behavior* behavior);
static void BehaviorSpaceshipOnUpdate(Behavior* behavior, float dt);
static void BehaviorSpaceshipOnExit(Behavior* behavior);
static void BehaviorSpaceshipUpdateRotation(Behavior* behavior, float dt);
static void BehaviorSpaceshipUpdateVelocity(Behavior* behavior, float dt);
static void BehaviorSpaceshipUpdateWeapon(Behavior* behavior, float dt);
static void BehaviorSpaceshipSpawnBullet(Behavior* behavior);


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (Spaceship) behavior component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
Behavior* BehaviorSpaceshipCreate(void)
{
	Behavior* spaceshipBehavior = calloc(1, sizeof(Behavior));
	if (spaceshipBehavior)
	{
		spaceshipBehavior->stateCurr = cSpaceshipInvalid;
		spaceshipBehavior->stateNext = cSpaceshipInvalid;

		spaceshipBehavior->onInit = BehaviorSpaceshipOnInit;
		spaceshipBehavior->onUpdate = BehaviorSpaceshipOnUpdate;
		spaceshipBehavior->onExit = BehaviorSpaceshipOnExit;
	}
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void BehaviorSpaceshipOnInit(Behavior* behavior)
{
	UNREFERENCED_PARAMETER(behavior);
}


static void BehaviorSpaceshipOnUpdate(Behavior* behavior, float dt)
{
	switch (behavior->stateCurr)
	{
		case cSpaceshipIdle:

			BehaviorSpaceshipUpdateRotation(behavior, dt);
			BehaviorSpaceshipUpdateWeapon(behavior, dt);

			if (DGL_Input_KeyDown(VK_UP))
			{
				behavior->stateNext = cSpaceshipThrust;

			}
			break;

		case cSpaceshipThrust:

			BehaviorSpaceshipUpdateRotation(behavior, dt);
			BehaviorSpaceshipUpdateVelocity(behavior, dt);
			BehaviorSpaceshipUpdateWeapon(behavior, dt);

			if (!DGL_Input_KeyDown(VK_UP))
			{
				behavior->stateNext = cSpaceshipIdle;
			}
			break;
	}
}


static void BehaviorSpaceshipOnExit(Behavior* behavior)
{
	UNREFERENCED_PARAMETER(behavior);
}


static void BehaviorSpaceshipUpdateRotation(Behavior* behavior, float dt)
{
	if (DGL_Input_KeyDown(VK_LEFT))
	{
		Physics* parentPhysics = EntityGetPhysics(behavior->parent);

		float rotVel = PhysicsGetRotationalVelocity(parentPhysics);


	}
}


static void BehaviorSpaceshipUpdateVelocity(Behavior* behavior, float dt)
{
	Transform* parentTransform = EntityGetTransform(behavior->parent);

	Physics* parentPhysics = EntityGetPhysics(behavior->parent);

	if (parentTransform && parentPhysics)
	{
		float shipRot = TransformGetRotation(parentTransform);

		Vector2D vecFromShipRot;
		Vector2DFromAngleRad(&vecFromShipRot, shipRot);

		Vector2D *velocity = PhysicsGetVelocity(parentPhysics);

		Vector2DScaleAdd(velocity, &vecFromShipRot, spaceshipAcceleration, velocity);

		float speed = Vector2DLength(velocity);

		if (speed > spaceshipSpeedMax)
		{
			Vector2DScale(velocity, velocity, spaceshipSpeedMax / speed);
		}
		PhysicsSetVelocity(parentPhysics, velocity);
	}
	
}


static void BehaviorSpaceshipUpdateWeapon(Behavior* behavior, float dt)
{

}


static void BehaviorSpaceshipSpawnBullet(Behavior* behavior)
{

}
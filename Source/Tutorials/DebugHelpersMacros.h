#pragma once
#include "DrawDebugHelpers.h"

#define DRAW_SPHERE_CHALLENGE(ItemLocation, DebugSphereColor) \
	if(World) \
	{ \
		DrawDebugSphere(World, ItemLocation, 30.f, 24, DebugSphereColor, true, -1.f); \
	}

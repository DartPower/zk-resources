// Footsteps
// Main Source

// Includes
#include <stdio.h>
#include <stdfix.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
#include "util.h"
#include "main.h"

// Scripts
Z_SCRIPT(SCR_FOOTSTEPS) ENTER void Footsteps (void)
{
	// Variables
	char *flat, *token;
	__str langdef, sound;
	accum volume, vx, vy, speed;
	int delay;
	
	while (true)
	{
		if (!ACS_GetActorZ(0) - ACS_GetActorFloorZ(0))
		{
			flat = ACSStrToChar(ACS_StrParam("%LS", s"STEP_FLATS"));
			token = strtok(flat, ":");
			
			vx = ACS_GetActorVelX(0);
			vy = ACS_GetActorVelY(0);
			speed = ACS_FixedSqrt(vx * vx + vy * vy) / 16k;
			if (speed > 1k)
				speed = 1k;
			
			delay = 35k - (25 * speed);
			volume = speed;
			
			while (token != NULL)
			{
				if (ACS_CheckActorFloorTexture(0, ctoacstr(token)))
				{
					langdef = ACS_StrParam("STEP_%S", ctoacstr(token));
					sound = ACS_StrParam("%LS", langdef);
					if (!ACS_StrICmp(langdef, sound))
						sound = ACS_StrParam("%LS", s"STEP_DEFAULT");
				}
				token = strtok(NULL, ":");
			}
			
			ACS_ActivatorSound(sound, (127k * volume) >> 16);
			sound = ACS_StrParam("%LS", s"STEP_DEFAULT");
		}
		if (delay > 1)
			ACS_Delay(delay);
		else
			ACS_Delay(1);
	}
}
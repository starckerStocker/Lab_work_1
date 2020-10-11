#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	enable = 1;
	counter = 0;
	speed = 0;
	
	fb_regulator.dt = 0.02;
	fb_regulator.k_i = 16;
	fb_regulator.k_p = 0.64;
	fb_regulator.max_abs_value = 24;
	
	fb_motor_1.dt = 0.02;
	fb_motor_1.ke = 16;
	fb_motor_1.Tm = 0.04;
	
	fb_motor_2.dt = 0.02;
	fb_motor_2.ke = 16;
	fb_motor_2.Tm = 0.04;
}

void _CYCLIC ProgramCyclic(void)
{
	if(enable == 1)
	{
		counter += 10;
		if(counter >= 10000 && counter <= 15000) speed = 5;
		else speed = 0;
	}
	else speed = 0;
	
	fb_regulator.e = speed - fb_motor_1.w;
	FB_Regulator(&(fb_regulator));
	
	fb_motor_1.u = fb_regulator.u*fb_motor_1.ke;
	fb_motor_2.u = speed*fb_motor_2.ke;
	FB_Motor(&(fb_motor_1));
	FB_Motor(&(fb_motor_2));
}

void _EXIT ProgramExit(void)
{
	// Insert code here 
	
}


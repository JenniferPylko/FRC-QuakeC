.vector axes;
.vector axes2;
.float button0;
.float button1;
.float button2;
.float button3;
.float button4;
.float button5;
.float button6;
.float button7;
.float button8;
.float button9;
.float button10;
.float button11;
.float button12;

entity JOYSTICKS[6];

entity joystick_spawnfunc(float device)
{
	entity e = self;
	e = spawn();
	e.dev_id = device;
	e.classname = "joystick_component";
	JOYSTICKS[device] = e;
	return e;
}

COMPONENT_HOOKFUNCTION(joystick_buildcomponentsname)
{
	ret_string = strcat(ret_string,":joystick");
	return FALSE;
}

COMPONENT_HOOKFUNCTION(joystick_update)
{
	float i;
	for(i = 0; i < 6; ++i)
	{
		if(JOYSTICKS[i])
		{
			
			JOYSTICKS[i].axes = builtin_joystick_func(JOYSTICKS[i].dev_id);
			JOYSTICKS[i].axes2 = builtin_joystick_func2(JOYSTICKS[i].dev_id);
			JOYSTICKS[i].button0 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,0);
			JOYSTICKS[i].button1 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,1);
			JOYSTICKS[i].button2 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,2);
			JOYSTICKS[i].button3 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,3);
			JOYSTICKS[i].button4 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,4);
			JOYSTICKS[i].button5 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,5);
			JOYSTICKS[i].button6 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,6);
			JOYSTICKS[i].button7 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,7);
			JOYSTICKS[i].button8 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,8);
			JOYSTICKS[i].button9 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,9);
			JOYSTICKS[i].button10 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,10);
			JOYSTICKS[i].button11 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,11);
			JOYSTICKS[i].button12 = builtin_joystick_buttonfunc(JOYSTICKS[i].dev_id,12);
		}
	}
	return FALSE;
}

COMPONENT_DEFINITION(component_joystick)
{
	COMPONENT_HOOK(BuildComponentsName, joystick_buildcomponentsname, CBC_ORDER_ANY);
	COMPONENT_HOOK(RobotGlobalThink, joystick_update, CBC_ORDER_FIRST);
	return FALSE;
}

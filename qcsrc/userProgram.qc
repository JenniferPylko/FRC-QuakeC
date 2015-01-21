entity joystick;

COMPONENT_HOOKFUNCTION(user_robotName)
{
	ret_string = strcat("YOUR ROBOT NAME HERE",ret_string);
	return FALSE;
}

COMPONENT_HOOKFUNCTION(user_robotInit)
{
	joystick = joystick_spawnfunc(0);
	return FALSE;
}

COMPONENT_HOOKFUNCTION(user_globalThink)
{
	return FALSE;
}

COMPONENT_DEFINITION(program_user)
{
	COMPONENT_HOOK(BuildComponentsName, user_robotName, CBC_ORDER_ANY);
	COMPONENT_HOOK(RobotInit, user_robotInit, CBC_ORDER_LAST);
	COMPONENT_HOOK(RobotGlobalThink, user_globalThink, CBC_ORDER_LAST);
	return FALSE;
}

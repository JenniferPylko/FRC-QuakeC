.vector() js_angles;

vector js_anglefunc()
{
	return builtin_joystick_func(self.dev_id);
}

entity joystick_spawnfunc()
{
	self.classname = "joystick_component";
	self.js_angles = js_anglefunc;
}

COMPONENT_HOOKFUNCTION(joystick_buildcomponentsname)
{
	ret_string = strcat(ret_string,":joystick");
	return FALSE;
}

COMPONENT_DEFINITION(component_joystick)
{
	COMPONENT_HOOK(BuildComponentsName, joystick_buildcomponentsname, CBC_ORDER_ANY);
	COMPONENT_ONADD
	{
	
	}
	return FALSE;
}

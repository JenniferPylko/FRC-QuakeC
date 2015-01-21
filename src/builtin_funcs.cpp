#include "kzqcvm.h"
#include "data.h"
#include "devicevectors.hpp"
#include <iostream>

using namespace kzqcvm;
using namespace std;

bool vm_spawn(Kzqcvm* qcvm, int builtinNum)
{
	EntityPointer ret = qcvm->GetReturnEntityPointer();
	ret.Set(qcvm->CreateEntity(qcvm->ENTITY_REUSE_DELAY));
	return true;
}

bool vm_remove(Kzqcvm* qcvm, int builtinNum)
{
	EntityPointer parm1 = qcvm->GetParameterEntityPointer(0);
	qcvm->DeleteEntity(parm1.Get(), 0.0f);
	return true;
}

bool vm_backtrace(Kzqcvm* vm, int funcnum)
{
	StringPointer s = vm->GetParameterStringPointer(0);
	cerr << "Warn: not actually backtracing, here's the error message: " << s.Get() << endl;
	return true;
}

bool vm_error(Kzqcvm* vm, int funcnum)
{
	StringPointer s = vm->GetParameterStringPointer(0);
	cerr << s.Get().GetValue() << endl;
	return true;
}

bool vm_print(Kzqcvm* vm, int funcnum)
{
	StringPointer s = vm->GetParameterStringPointer(0);
	cout << s.Get().GetValue();
	return true;
}

bool vm_strcat(Kzqcvm* vm, int funcnum)
{
	StringPointer s1 = vm->GetParameterStringPointer(0);
	StringPointer s2 = vm->GetParameterStringPointer(1);
	StringPointer ret = vm->GetReturnStringPointer();
	ret.Set(vm->TempString(string(s1.Get().GetValue())+string(s2.Get().GetValue())));
	return true;
}

bool vm_joystick_builtin(Kzqcvm* vm, int funcnum)
{
	if(joysticks[vm->GetParameterFloatPointer(0)] == NULL)
	{
		joysticks[vm->GetParameterFloatPointer(0)] = Joystick::GetStickForPort(vm->GetParameterFloatPointer(0));
	}
	vm->GetReturnVectorPointer().Set(0,joysticks[vm->GetParameterFloatPointer(0)]->GetX());
	vm->GetReturnVectorPointer().Set(1,joysticks[vm->GetParameterFloatPointer(0)]->GetY());
	vm->GetReturnVectorPointer().Set(2,joysticks[vm->GetParameterFloatPointer(0)]->GetZ());
	return true;
}

bool vm_vtos(Kzqcvm* vm, int funcnum)
{
	VectorPointer vp = vm->GetParameterVectorPointer(0);
	vm->GetReturnStringPointer().Set(vm->TempString(to_string(vp.Get(0))+to_string(vp.Get(1))+to_string(vp.Get(2))));
	return true;
}

bool vm_ftos(Kzqcvm* vm, int funcnum)
{
	FloatPointer fp = vm->GetParameterFloatPointer(0);
	vm->GetReturnStringPointer().Set(vm->TempString(to_string(fp.Get())));
	return true;
}

bool vm_printf(Kzqcvm* vm, int funcnum)
{
	FloatPointer fp = vm->GetParameterFloatPointer(0);
	cout << fp.Get();
	return true;
}

bool vm_printv(Kzqcvm* vm, int funcnum)
{
	VectorPointer vp = vm->GetParameterVectorPointer(0);
	cout << "'" << vp.Get(0) << " " << vp.Get(1) << " " << vp.Get(2) << "'";
	return true;
}

bool vm_joystick_builtin2(Kzqcvm* vm, int funcnum)
{
	if(joysticks[vm->GetParameterFloatPointer(0)] == NULL)
	{
		joysticks[vm->GetParameterFloatPointer(0)] = Joystick::GetStickForPort(vm->GetParameterFloatPointer(0));
	}
	vm->GetReturnVectorPointer().Set(0,joysticks[vm->GetParameterFloatPointer(0)]->GetRawAxis(3));
	vm->GetReturnVectorPointer().Set(1,joysticks[vm->GetParameterFloatPointer(0)]->GetRawAxis(4));
	vm->GetReturnVectorPointer().Set(2,joysticks[vm->GetParameterFloatPointer(0)]->GetRawAxis(5));
	return true;
}

bool vm_joystick_buttonfunc(Kzqcvm* vm, int funcnum)
{
	if(joysticks[vm->GetParameterFloatPointer(0)] == NULL)
	{
		joysticks[vm->GetParameterFloatPointer(0)] = Joystick::GetStickForPort(vm->GetParameterFloatPointer(0));
	}
	vm->GetReturnFloatPointer().Set(joysticks[vm->GetParameterFloatPointer(0)]->GetRawButton(vm->GetParameterFloatPointer(1)));
	return true;
}

void register_builtins(Kzqcvm* vm)
{
	vm->AddBuiltin(vm_spawn, 1);
	vm->AddBuiltin(vm_remove, 2);
	vm->AddBuiltin(vm_backtrace, 3);
	vm->AddBuiltin(vm_error, 4);
	vm->AddBuiltin(vm_print, 5);
	vm->AddBuiltin(vm_strcat, 6);
	vm->AddBuiltin(vm_joystick_builtin, 7);
	vm->AddBuiltin(vm_vtos, 8);
	vm->AddBuiltin(vm_ftos, 9);
	vm->AddBuiltin(vm_printf, 10);
	vm->AddBuiltin(vm_printv, 11);
	vm->AddBuiltin(vm_joystick_builtin2, 12);
	vm->AddBuiltin(vm_joystick_buttonfunc, 13);
}

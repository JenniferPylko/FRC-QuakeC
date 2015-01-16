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
		joysticks[vm->GetParameterFloatPointer(0)] = new Joystick(vm->GetParameterFloatPointer(0));
	}
	joysticks[vm->GetParameterFloatPointer(0)]->GetX();
}

void register_builtins(Kzqcvm* vm)
{
	vm->AddBuiltin(vm_spawn, 1);
	vm->AddBuiltin(vm_remove, 2);
	vm->AddBuiltin(vm_backtrace, 3);
	vm->AddBuiltin(vm_error, 4);
	vm->AddBuiltin(vm_print, 5);
	vm->AddBuiltin(vm_strcat, 6);
}

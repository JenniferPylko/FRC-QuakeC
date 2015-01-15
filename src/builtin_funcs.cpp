#include "kzqcvm.h"
#include "data.h"
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
}

bool vm_error(Kzqcvm* vm, int funcnum)
{
	StringPointer s = vm->GetParameterStringPointer(0);
	cerr << s.Get() << endl;
}

bool vm_print(Kzqcvm* vm, int funcnum)
{
	StringPointer s = vm->GetParameterStringPointer(0);
	cout << s.Get();
}

void register_builtins(Kzqcvm* vm)
{
	vm->AddBuiltin(vm_spawn, 1);
	vm->AddBuiltin(vm_remove, 2);
	vm->AddBuiltin(vm_backtrace, 3);
	vm->AddBuiltin(vm_error, 4);
}

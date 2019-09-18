// Copyright (c) 2013-2019 7Mersenne All Rights Reserved.

#include "SeptemCore.h"

#define LOCTEXT_NAMESPACE "FSeptemCoreModule"

void FSeptemCoreModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FSeptemCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSeptemCoreModule, SeptemCore)
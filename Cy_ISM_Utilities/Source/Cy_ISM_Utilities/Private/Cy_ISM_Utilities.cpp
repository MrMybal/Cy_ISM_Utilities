// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cy_ISM_Utilities.h"

#define LOCTEXT_NAMESPACE "FCy_ISM_UtilitiesModule"

void FCy_ISM_UtilitiesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCy_ISM_UtilitiesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCy_ISM_UtilitiesModule, Cy_ISM_Utilities)
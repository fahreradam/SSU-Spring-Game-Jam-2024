// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CleanupClash/CleanupClashGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCleanupClashGameMode() {}
// Cross Module References
	CLEANUPCLASH_API UClass* Z_Construct_UClass_ACleanupClashGameMode();
	CLEANUPCLASH_API UClass* Z_Construct_UClass_ACleanupClashGameMode_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_CleanupClash();
// End Cross Module References
	void ACleanupClashGameMode::StaticRegisterNativesACleanupClashGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACleanupClashGameMode);
	UClass* Z_Construct_UClass_ACleanupClashGameMode_NoRegister()
	{
		return ACleanupClashGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ACleanupClashGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACleanupClashGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_CleanupClash,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACleanupClashGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACleanupClashGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "CleanupClashGameMode.h" },
		{ "ModuleRelativePath", "CleanupClashGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACleanupClashGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACleanupClashGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACleanupClashGameMode_Statics::ClassParams = {
		&ACleanupClashGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACleanupClashGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ACleanupClashGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ACleanupClashGameMode()
	{
		if (!Z_Registration_Info_UClass_ACleanupClashGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACleanupClashGameMode.OuterSingleton, Z_Construct_UClass_ACleanupClashGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACleanupClashGameMode.OuterSingleton;
	}
	template<> CLEANUPCLASH_API UClass* StaticClass<ACleanupClashGameMode>()
	{
		return ACleanupClashGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACleanupClashGameMode);
	ACleanupClashGameMode::~ACleanupClashGameMode() {}
	struct Z_CompiledInDeferFile_FID_CleanupClash_Source_CleanupClash_CleanupClashGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_CleanupClash_Source_CleanupClash_CleanupClashGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ACleanupClashGameMode, ACleanupClashGameMode::StaticClass, TEXT("ACleanupClashGameMode"), &Z_Registration_Info_UClass_ACleanupClashGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACleanupClashGameMode), 777615356U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_CleanupClash_Source_CleanupClash_CleanupClashGameMode_h_2610592803(TEXT("/Script/CleanupClash"),
		Z_CompiledInDeferFile_FID_CleanupClash_Source_CleanupClash_CleanupClashGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_CleanupClash_Source_CleanupClash_CleanupClashGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS

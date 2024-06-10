// Copyright CyberAlien ,All Rights Reserved , 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Cy_ISM_Library.generated.h"

// Struct
USTRUCT(BlueprintType)
struct FCy_ISM_CustomDataFloat
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> CustomDataFloat;
};
USTRUCT(BlueprintType)
struct FCy_ISM_PerInstanceData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InstancesIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform WorldTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> CustomDataFloat;
};
/**
 * 
 */
UCLASS()
class CY_ISM_UTILITIES_API UCy_ISM_Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Get Transform from instance
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static TArray<FTransform> Cy_ISM_Get_InstancesTransfom( const UInstancedStaticMeshComponent* Component , const bool WorldScape = true );
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static TArray<int32> Cy_ISM_GetInstancesIndex_InSphere( const UInstancedStaticMeshComponent* Component , TArray<FTransform>& OutInstanceTransform , const FVector SphereOrigin , const double Radius );
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static TArray<FTransform> Cy_ISM_GetInstancesTranform_ByIndex( const UInstancedStaticMeshComponent* Component , const TArray<int32>& InstancesIndex , const bool WorldSpace = true );
	// Add Transform to instances
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static void Cy_ISM_AddTransform_To_Instances_Index( UInstancedStaticMeshComponent* Component , const TArray<int32>& InstancesIndex , const FTransform Transform , const bool WorldScape = true , const bool bTeleport = true );
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static void Cy_ISM_AddTransform_To_Instances_Index_Range( UInstancedStaticMeshComponent* Component , const int32 Start , const int32 End , const FTransform Transform , const bool WorldScape = true , const bool bTeleport = true );
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static void Cy_ISM_AddTransform_To_All_Instances( UInstancedStaticMeshComponent* Component , const FTransform Transform , const bool WorldScape = true , const bool bTeleport = true );
	// Get CustomData from instance
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static bool Cy_ISM_InstanceCustomDataFloat( const UInstancedStaticMeshComponent* Component , const int32 InstanceIndex , const int32 CustomDataIndex , float& ReturnData );
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static bool Cy_ISM_InstancesCustomDataFloat( const UInstancedStaticMeshComponent* Component , const TArray<int32>& InstancesIndex , const int32 CustomDataIndex , TMap<int32,float>& ReturnData );
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static bool Cy_ISM_AllInstancesCustomDataFloat( const UInstancedStaticMeshComponent* Component , const int32 CustomDataIndex , TMap<int32,float>& ReturnData );
	// Get All CustomData from instnace
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static bool Cy_ISM_InstanceGetAllCustomDataFloat( const UInstancedStaticMeshComponent* Component , const int32 InstanceIndex , FCy_ISM_CustomDataFloat& CustomDatas );
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static bool Cy_ISM_InstancesGetAllCustomDataFloat( const UInstancedStaticMeshComponent* Component , const TArray<int32>& InstancesIndex , TArray<FCy_ISM_CustomDataFloat>& CustomDatas );
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static bool Cy_ISM_AllInstancesGetAllCustomDataFloat( const UInstancedStaticMeshComponent* Component , TArray<FCy_ISM_CustomDataFloat>& CustomDatas );
	// Get All Data from instances
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static bool Cy_ISM_GetInstanceAllData( const UInstancedStaticMeshComponent* Component , const int32 InstanceIndex , FCy_ISM_PerInstanceData& InstanceData );
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static bool Cy_ISM_GetInstancesAllData( const UInstancedStaticMeshComponent* Component , const TArray<int32>& InstancesIndex , TArray<FCy_ISM_PerInstanceData>& InstancesData );
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static bool Cy_ISM_GetAllInstancesAllData( const UInstancedStaticMeshComponent* Component , TArray<FCy_ISM_PerInstanceData>& InstancesData );
	// Get instance by location
	UFUNCTION(BlueprintCallable, Category = "Cy_ISM")
	static bool Cy_ISM_GetInstanceByLocation( const UInstancedStaticMeshComponent* Component , const FVector Location , const float DistanceTolerance , int32& InstanceIndex );
};

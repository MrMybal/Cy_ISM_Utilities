// Copyright CyberAlien ,All Rights Reserved , 2024


#include "Cy_ISM_Library.h"

#include "Components/InstancedStaticMeshComponent.h"

// ---------------------------------------------------------
TArray<FTransform> UCy_ISM_Library::Cy_ISM_Get_InstancesTransfom( const UInstancedStaticMeshComponent* Component , const bool WorldScape )
{
	TArray<FTransform> Result;
	for (int32 Index = 0; Index < Component->PerInstanceSMData.Num(); Index++)
	{
		FTransform InstanceTransform;
		Component->GetInstanceTransform(Index, InstanceTransform, WorldScape);
		Result.Add(InstanceTransform);
	}
	return Result;
}
// ---------------------------------------------------------
void UCy_ISM_Library::Cy_ISM_AddTransform_To_Instances_Index( UInstancedStaticMeshComponent* Component , const TArray<int32>& InstancesIndex , const FTransform Transform , const bool WorldScape , const bool bTeleport )
{
	for ( const auto& Instance : InstancesIndex )
	{
		if ( Component->IsValidInstance(Instance) )
		{
			FTransform InstanceTransform;
			Component->GetInstanceTransform(Instance, InstanceTransform, WorldScape);
			Component->UpdateInstanceTransform(Instance, InstanceTransform + Transform , WorldScape, true, bTeleport);
		}

	}
}
// ---------------------------------------------------------
void UCy_ISM_Library::Cy_ISM_AddTransform_To_Instances_Index_Range( UInstancedStaticMeshComponent* Component , const int32 Start , const int32 End , const FTransform Transform , const bool WorldScape , const bool bTeleport )
{
	for ( int32 Instance = Start ; Instance < End ; Instance++ )
	{
		if ( Component->IsValidInstance(Instance) )
		{
			FTransform InstanceTransform;
			Component->GetInstanceTransform(Instance, InstanceTransform, WorldScape);
			Component->UpdateInstanceTransform(Instance, InstanceTransform + Transform , WorldScape, true, bTeleport);
		}
	}
}
// ---------------------------------------------------------
void UCy_ISM_Library::Cy_ISM_AddTransform_To_All_Instances( UInstancedStaticMeshComponent* Component , const FTransform Transform , const bool WorldScape , const bool bTeleport )
{
	for ( int32 Instance = 0 ; Instance < Component->PerInstanceSMData.Num() ; Instance++ )
	{
		if ( Component->IsValidInstance(Instance) )
		{
			FTransform InstanceTransform;
			Component->GetInstanceTransform(Instance, InstanceTransform, WorldScape);
			Component->UpdateInstanceTransform(Instance, InstanceTransform + Transform , WorldScape, true, bTeleport);
		}
	}
}
// ---------------------------------------------------------
TArray<int32> UCy_ISM_Library::Cy_ISM_GetInstancesIndex_InSphere( const UInstancedStaticMeshComponent* Component , TArray<FTransform>& OutInstanceTransform, const FVector SphereOrigin , const double Radius )
{
	TArray<int32> OutIndex;
	for ( int32 Index = 0 ; Index < Component->PerInstanceSMData.Num() ; Index++ )
	{
		FTransform InstanceTransform;
		Component->GetInstanceTransform(Index,InstanceTransform,true);
		if ( FVector(SphereOrigin-InstanceTransform.GetLocation()).SquaredLength() < FMath::Square(Radius) )
		{
			OutIndex.Add(Index);
			OutInstanceTransform.Add(InstanceTransform);
		}
	}
	return OutIndex;
}
// ---------------------------------------------------------
TArray<FTransform> UCy_ISM_Library::Cy_ISM_GetInstancesTranform_ByIndex( const UInstancedStaticMeshComponent* Component , const TArray<int32>& InstancesIndex , const bool WorldSpace )
{
	TArray<FTransform> Result;
	for (const auto& Index : InstancesIndex )
	{
		if ( Component->IsValidInstance(Index))
		{
			FTransform InstanceTransform;
			Component->GetInstanceTransform(Index, InstanceTransform, WorldSpace);
			Result.Add(InstanceTransform);
		}
		else
		{
			Result.Add(FTransform(FRotator(0,0,0),FVector(0,0,0),FVector(0,0,0)));
		}
	}
	return Result;
}
// ---------------------------------------------------------
bool UCy_ISM_Library::Cy_ISM_InstanceCustomDataFloat( const UInstancedStaticMeshComponent* Component , const int32 InstanceIndex , const int32 CustomDataIndex , float& ReturnData )
{
	if ( Component )
	{
		if ( Component->NumCustomDataFloats > 0 )
		{
			if ( Component->IsValidInstance(InstanceIndex))
			{
			
				if ( Component->PerInstanceSMCustomData.IsValidIndex((InstanceIndex*Component->NumCustomDataFloats)+CustomDataIndex) )
				{
					ReturnData = Component->PerInstanceSMCustomData[(InstanceIndex*Component->NumCustomDataFloats)+CustomDataIndex];
					return true;
				}
			}
		}
	}
	return false;
}
// ---------------------------------------------------------
bool UCy_ISM_Library::Cy_ISM_InstancesCustomDataFloat( const UInstancedStaticMeshComponent* Component , const TArray<int32>& InstancesIndex , const int32 CustomDataIndex , TMap<int32,float>& ReturnData )
{
	if ( Component )
	{
		if ( Component->NumCustomDataFloats > 0 )
		{
			for ( const auto& Instance : InstancesIndex )
			{
				if ( Component->IsValidInstance(Instance))
				{
					if ( Component->PerInstanceSMCustomData.IsValidIndex((Instance*Component->NumCustomDataFloats)+CustomDataIndex))
					{
						ReturnData.Add(Instance,Component->PerInstanceSMCustomData[(Instance*Component->NumCustomDataFloats)+CustomDataIndex]);
					}
				}
			}
		}
	}
	if ( ReturnData.IsEmpty() )
	{
		return false;
	}
	return true;
}
// ---------------------------------------------------------
bool UCy_ISM_Library::Cy_ISM_AllInstancesCustomDataFloat( const UInstancedStaticMeshComponent* Component , const int32 CustomDataIndex , TMap<int32,float>& ReturnData )
{
	if ( Component )
	{
		if ( Component->NumCustomDataFloats > 0 )
		{
			for ( int32 Instance = 0 ; Instance < Component->PerInstanceSMData.Num() ; Instance++ )
			{
				if ( Component->IsValidInstance(Instance))
				{
					if ( Component->PerInstanceSMCustomData.IsValidIndex((Instance*Component->NumCustomDataFloats)+CustomDataIndex))
					{
						ReturnData.Add(Instance,Component->PerInstanceSMCustomData[(Instance*Component->NumCustomDataFloats)+CustomDataIndex]);
					}
				}
			}
		}
	}
	if ( ReturnData.IsEmpty() )
	{
		return false;
	}
	return true;
}
// ---------------------------------------------------------
bool UCy_ISM_Library::Cy_ISM_InstanceGetAllCustomDataFloat( const UInstancedStaticMeshComponent* Component , const int32 InstanceIndex , FCy_ISM_CustomDataFloat& CustomDatas )
{
	if ( Component )
	{
		if ( Component->NumCustomDataFloats > 0 )
		{
			if ( Component->IsValidInstance(InstanceIndex))
			{
				for ( int32 Index = InstanceIndex*Component->NumCustomDataFloats ; Index < (InstanceIndex*Component->NumCustomDataFloats)+Component->NumCustomDataFloats ; Index++ )
				{
					if ( Component->PerInstanceSMCustomData.IsValidIndex((InstanceIndex*Component->NumCustomDataFloats)+Index) )
					{
						CustomDatas.CustomDataFloat.Add(Component->PerInstanceSMCustomData[Index]);
					}
					else
					{
						CustomDatas.CustomDataFloat.Add(0.0);
					}
				}
				if ( CustomDatas.CustomDataFloat.Num() == Component->NumCustomDataFloats )
				{
					return true;
				}
			}
		}
	}
	return false;
}
// ---------------------------------------------------------
bool UCy_ISM_Library::Cy_ISM_InstancesGetAllCustomDataFloat( const UInstancedStaticMeshComponent* Component , const TArray<int32>& InstancesIndex , TArray<FCy_ISM_CustomDataFloat>& CustomDatas )
{
	if ( Component )
	{
		if ( Component->NumCustomDataFloats > 0 )
		{
			FCy_ISM_CustomDataFloat Empty;
			for ( const auto& InstanceIndex : InstancesIndex )
			{
				CustomDatas.Add(Empty);
				if ( Component->IsValidInstance(InstanceIndex))
				{
					for ( int32 Index = InstanceIndex*Component->NumCustomDataFloats ; Index < (InstanceIndex*Component->NumCustomDataFloats)+Component->NumCustomDataFloats ; Index++ )
					{
						if ( Component->PerInstanceSMCustomData.IsValidIndex((InstanceIndex*Component->NumCustomDataFloats)+Index) )
						{
							CustomDatas[InstanceIndex].CustomDataFloat.Add(Component->PerInstanceSMCustomData[Index]);
						}
						else
						{
							CustomDatas[InstanceIndex].CustomDataFloat.Add(0.0);
						}
					}
				}
			}
			if ( CustomDatas.Num() == Component->PerInstanceSMData.Num() )
			{
				return true;
			}
		}
	}
	return false;
}
// ---------------------------------------------------------
bool UCy_ISM_Library::Cy_ISM_AllInstancesGetAllCustomDataFloat( const UInstancedStaticMeshComponent* Component , TArray<FCy_ISM_CustomDataFloat>& CustomDatas )
{
	if ( Component )
	{
		if ( Component->NumCustomDataFloats > 0 )
		{
			FCy_ISM_CustomDataFloat Empty;
			for ( int32 InstanceIndex = 0 ; InstanceIndex < Component->PerInstanceSMData.Num() ; InstanceIndex++ )
			{
				CustomDatas.Add(Empty);
				if ( Component->IsValidInstance(InstanceIndex))
				{
					for ( int32 Index = InstanceIndex*Component->NumCustomDataFloats ; Index < (InstanceIndex*Component->NumCustomDataFloats)+Component->NumCustomDataFloats ; Index++ )
					{
						if ( Component->PerInstanceSMCustomData.IsValidIndex((InstanceIndex*Component->NumCustomDataFloats)+Index) )
						{
							CustomDatas[InstanceIndex].CustomDataFloat.Add(Component->PerInstanceSMCustomData[Index]);
						}
						else
						{
							CustomDatas[InstanceIndex].CustomDataFloat.Add(0.0);
						}
					}
				}
			}
			if ( CustomDatas.Num() == Component->PerInstanceSMData.Num() )
			{
				return true;
			}
		}
	}
	return false;
}
// ---------------------------------------------------------
bool UCy_ISM_Library::Cy_ISM_GetInstanceAllData( const UInstancedStaticMeshComponent* Component , const int32 InstanceIndex , FCy_ISM_PerInstanceData& InstanceData )
{
	if ( Component )
	{
		if ( Component->IsValidInstance(InstanceIndex))
		{
			InstanceData.InstancesIndex = InstanceIndex;
			Component->GetInstanceTransform( InstanceIndex , InstanceData.WorldTransform , true );
			if ( Component->NumCustomDataFloats > 0 )
			{
				for ( int32 Index = InstanceIndex*Component->NumCustomDataFloats ; Index < (InstanceIndex*Component->NumCustomDataFloats)+Component->NumCustomDataFloats ; Index++ )
				{
					if ( Component->PerInstanceSMCustomData.IsValidIndex((InstanceIndex*Component->NumCustomDataFloats)+Index) )
					{
						InstanceData.CustomDataFloat.Add(Component->PerInstanceSMCustomData[Index]);
					}
					else
					{
						InstanceData.CustomDataFloat.Add(0.0);
					}
				}
			}
			return true;
		}
	}
	return false;
}
// ---------------------------------------------------------
bool UCy_ISM_Library::Cy_ISM_GetInstancesAllData( const UInstancedStaticMeshComponent* Component , const TArray<int32>& InstancesIndex , TArray<FCy_ISM_PerInstanceData>& InstancesData )
{
	if ( Component )
	{
		for ( const auto& InstanceIndex : InstancesIndex )
		{
			if ( Component->IsValidInstance(InstanceIndex))
			{
				FCy_ISM_PerInstanceData Data;
				Data.InstancesIndex = InstanceIndex;
				Component->GetInstanceTransform( InstanceIndex , Data.WorldTransform , true );
				if ( Component->NumCustomDataFloats > 0 )
				{
					for ( int32 Index = InstanceIndex*Component->NumCustomDataFloats ; Index < (InstanceIndex*Component->NumCustomDataFloats)+Component->NumCustomDataFloats ; Index++ )
					{
						if ( Component->PerInstanceSMCustomData.IsValidIndex((InstanceIndex*Component->NumCustomDataFloats)+Index) )
						{
							Data.CustomDataFloat.Add(Component->PerInstanceSMCustomData[Index]);
						}
						else
						{
							Data.CustomDataFloat.Add(0.0);
						}
					}
				}
				InstancesData.Add(Data);
			}
		}
		if ( !InstancesData.IsEmpty() )
		{
			return true;
		}
	}
	return false;
}
// ---------------------------------------------------------
bool UCy_ISM_Library::Cy_ISM_GetAllInstancesAllData( const UInstancedStaticMeshComponent* Component , TArray<FCy_ISM_PerInstanceData>& InstancesData )
{
	if ( Component )
	{
		for ( int32 InstanceIndex = 0 ; InstanceIndex < Component->PerInstanceSMData.Num() ; InstanceIndex++ )
		{
			if ( Component->IsValidInstance(InstanceIndex))
			{
				FCy_ISM_PerInstanceData Data;
				Data.InstancesIndex = InstanceIndex;
				Component->GetInstanceTransform( InstanceIndex , Data.WorldTransform , true );
				if ( Component->NumCustomDataFloats > 0 )
				{
					for ( int32 Index = InstanceIndex*Component->NumCustomDataFloats ; Index < (InstanceIndex*Component->NumCustomDataFloats)+Component->NumCustomDataFloats ; Index++ )
					{
						if ( Component->PerInstanceSMCustomData.IsValidIndex((InstanceIndex*Component->NumCustomDataFloats)+Index) )
						{
							Data.CustomDataFloat.Add(Component->PerInstanceSMCustomData[Index]);
						}
						else
						{
							Data.CustomDataFloat.Add(0.0);
						}
					}
				}
				InstancesData.Add(Data);
			}
		}
		if ( !InstancesData.IsEmpty() )
		{
			return true;
		}
	}
	return false;
}
// ---------------------------------------------------------
bool UCy_ISM_Library::Cy_ISM_GetInstanceByLocation( const UInstancedStaticMeshComponent* Component , const FVector Location , const float DistanceTolerance , int32& InstanceIndex )
{
	if ( Component )
	{
		for ( int32 Index = 0 ; Index < Component->PerInstanceSMData.Num() ; Index++ )
		{
			FTransform InstanceTransform;
			Component->GetInstanceTransform(Index,InstanceTransform,true);
			if ( FVector(Location-InstanceTransform.GetLocation()).SquaredLength() < FMath::Square(DistanceTolerance) )
			{
				InstanceIndex = Index;
				return true;
			}
		}
	}
	return false;
}
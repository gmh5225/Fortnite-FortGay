#pragma once

#include "Engine.h"

class UFortKismetLibrary;
class UKismetMathLibrary;
class UGameplayStatics;
SHORT(*NtGetAsyncKeyState)(DWORD);

namespace EG_S
{
	namespace Scanned
	{
		namespace FortKismetLibrary
		{
			UFortKismetLibrary* FortKismetLibrary;
			UGameplayStatics* GameplayStatics;
			uintptr_t IsDBNO;
			uintptr_t IsDead;
			uintptr_t GetFortPlayerPawns = 0;
			uintptr_t OnSameTeam = 0;
			uintptr_t GetVelocity = 0;
		}

		namespace KismetMathLibrary
		{
			UKismetMathLibrary* KismetMathLibrary;
			uintptr_t FindLookAtRotation;
		}

		namespace GameplayStatics
		{
			UGameplayStatics* GameplayStatics;
			uintptr_t GetAllActorsOfClass;
		}

		namespace Entities
		{
			UClass* Projectile;
			UClass* BuildingWeakSpot;
		}

		uintptr_t UWorld = 0;
		uintptr_t UObjects = 0;
		uintptr_t FreeFN = 0;
		uintptr_t K2_SetActorLocation = 0;
		uintptr_t K2_TeleportTo = 0;
		uintptr_t K2_AttachTo = 0;
		uintptr_t ProjectWorldLocationToScreen = 0;
		uintptr_t LineOfSightTo = 0;
		uintptr_t GetBoneMatrix = 0;
		uintptr_t GetCameraLocation = 0;
		uintptr_t K2_DrawLine = 0;
		uintptr_t IsProjectileWeapon = 0;
		uintptr_t ClientSetRotation = 0;
		uintptr_t GetCameraRotation = 0;
		uintptr_t K2_DrawText = 0;
		uintptr_t GetPlayerName = 0;
		uintptr_t GetFovAngle = 0;
		uintptr_t GameFont = 0;
		uintptr_t GetNameByIndex = 0;
		GObjects* objects = nullptr;
	}
	//These are the patterns, they change normally once a month.
	string UWorld = xorstr("48 89 05 ? ? ? ? 48 8B 4B 78");
	string UObjects = xorstr("48 8B 05 ? ? ? ? 48 8B 0C C8 48 8B 04 D1");
	string FreeFN = xorstr("E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 0F 84 ? ? ? ? E8 ? ? ? ? 90 E9 ? ? ? ? 48 8D 15 ? ? ? ? 83 CB 08 4C 8B");
	string ProjectWorldLocationToScreen = xorstr("E8 ? ? ? ? 4C 8D 5C 24 ? 41 88 06 49 8B 5B 20 49 8B 73 30 49 8B 7B 38");
	string GetBoneMatrix = xorstr("E8 ? ? ? ? 0F 10 40 68");
	string GetNameByIndex = xorstr("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 8B 01 4C 8B F2");
	string LineOfSightTo = xorstr("48 8B C4 48 89 58 20 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 8A E9");
}

namespace UnrealEngine_CoreFunctions
{
	void FreeObjName(__int64 address)
	{
		auto func = reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(EG_S::Scanned::FreeFN);

		SpoofThis(func, address);
	}

	inline void cFixName(char* Name)
	{
		for (int i = 0; Name[i] != '\0'; i++)
		{
			if (Name[i] == '_')
			{
				if (Name[i + 1] == '0' ||
					Name[i + 1] == '1' ||
					Name[i + 1] == '2' ||
					Name[i + 1] == '3' ||
					Name[i + 1] == '4' ||
					Name[i + 1] == '5' ||
					Name[i + 1] == '6' ||
					Name[i + 1] == '7' ||
					Name[i + 1] == '8' ||
					Name[i + 1] == '9')
					Name[i] = '\0';
			}
		}

		return;
	}

	string GetObjectName(uintptr_t Object, bool GetOuter = false)
	{
		if (!GetOuter)
		{
			if (Object == NULL)
				return ("");

			auto fGetObjName = reinterpret_cast<FString * (__fastcall*)(int* index, FString * res)>(EG_S::Scanned::GetNameByIndex);

			int index = *(int*)(Object + 0x18);

			FString result;
			SpoofThis(fGetObjName, &index, &result);

			if (result.c_str() == NULL)
				return ("");

			auto result_str = result.ToString();

			if (result.c_str() != NULL)
				FreeObjName((__int64)result.c_str());

			return result_str.c_str();
		}

		if (GetOuter)
		{
			if (!Object) return "";

			UObject* Object_ = (UObject*)Object;
			string name("");
			for (auto i = 0; Object_; Object_ = Object_->Outer, ++i) {

				auto fGetNameByIndex = reinterpret_cast<FString * (__fastcall*)(int* index, FString * res)>(EG_S::Scanned::GetNameByIndex);
				int index = *(int*)(reinterpret_cast<uint64_t>(Object_) + 0x18);

				FString internalName;
				fGetNameByIndex(&index, &internalName);

				if (internalName.c_str() == NULL) {
					break;
				}

				auto objectName = internalName.ToString();

				name = objectName + string(i > 0 ? xorstr(".") : xorstr("")) + name;
				FreeObjName((__int64)internalName.c_str());

			}
			return name.c_str();
		}
	}
}


string GetById(int index)
{
	auto fGetNameByIdx = reinterpret_cast<FString * (__fastcall*)(int*, FString*)>(EG_S::Scanned::GetNameByIndex);

	FString result;
	SpoofThis(fGetNameByIdx, &index, &result);

	if (result.c_str() == NULL) return (char*)"";

	auto tmp = result.ToString();

	char return_string[1024] = {};
	for (size_t i = 0; i < tmp.size(); i++)
	{
		return_string[i] += tmp[i];
	}

	UnrealEngine_CoreFunctions::FreeObjName((uintptr_t)result.c_str());
	UnrealEngine_CoreFunctions::cFixName(return_string);

	return string(return_string);
}


class APlayerState {
public:
	uintptr_t TeamIndex() {
		if (!this)
			return {};
		return *(uintptr_t*)(this + 0x1018);
	}

	char CompressedPing() {
		if (!this)
			return {};
		return *(char*)(this + 0x2A0);
	}

	FString GetPlayerName() {
		if (!this) return {};

		FString PlayerName;
		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::GetPlayerName, &PlayerName);
		if (!PlayerName.IsValid())
			return {};
		return PlayerName;
	}
};

class ARootComponent {
public:

	FVector RelativeLocation() {
		if (!this) return { 0, 0, 0 };
		return *(FVector*)((uintptr_t)this + 0x138);
	}

	FVector RelativeRotation() {
		if (!this) return { 0, 0, 0 };
		return *(FVector*)((uintptr_t)this + 0x150);
	}
};

class AFortItemDefinition {
public:
	FText* DisplayName() {
		if (!this) return 0;
		return reinterpret_cast<FText*>(*(uintptr_t*)(this + 0x90));
	}

	BYTE Tier() {
		if (!this) return 0;
		return *(BYTE*)(*(uintptr_t*)(this + 0x74));
	}
};

class AFortWeapon {
public:
	const char* ObjectName() {
		if (!this) return {};
		return UnrealEngine_CoreFunctions::GetObjectName((uintptr_t)this).c_str();
	}

	AFortItemDefinition* WeaponData() {
		if (!this) return 0;
		return (AFortItemDefinition*)(*(uintptr_t*)(this + 0x400));
	}

	BOOL IsProjectileWeapon()
	{
		struct AFortWeapon_IsProjectileWeapon_Params
		{
			bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		};
		AFortWeapon_IsProjectileWeapon_Params params;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::IsProjectileWeapon, &params);

		return params.ReturnValue;
	}
};

class AFortPawn {
public:
	uintptr_t Mesh() {
		if (!this) return 0;
		return *(uintptr_t*)((uintptr_t)this + 0x318);  //outdated
	}

	AFortWeapon* CurrentWeapon() {
		if (!this) return 0;
		return (AFortWeapon*)(*(uintptr_t*)(this + 0x7b0)); //outdated
	}

	ARootComponent* RootComponent() {
		if (!this) return 0;
		return (ARootComponent*)(*(uintptr_t*)(this + 0x190)); //outdated
	}

	APlayerState* PlayerState() {
		if (!this) return 0;
		return (APlayerState*)(*(uintptr_t*)(this + 0x2b8)); //outdated
	}

	unsigned char IsActive()
	{
		if (!this) return 0;
		return *(unsigned char*)(this + 0x2c8);
	}

	BOOL K2_TeleportTo(const FVector& DestLocation, const FVector& DestRotation)
	{
		struct AActor_K2_TeleportTo_Params
		{
			FVector										DestLocation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
			FVector										DestRotation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
			bool										ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		};

		AActor_K2_TeleportTo_Params params;
		params.DestLocation = DestLocation;
		params.DestRotation = DestRotation;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::K2_TeleportTo, &params);

		return params.ReturnValue;
	}
	BOOL K2_SetActorLocation(const FVector& NewLocation)
	{
		struct FHitResult
		{
			char memes[0x1000];
		};

		struct AActor_K2_SetActorLocation_Params
		{
			FVector                                            NewLocation;                                              // (Parm, IsPlainOldData)
			bool                                               bSweep;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
			FHitResult                                         SweepHitResult;                                           // (Parm, OutParm, IsPlainOldData)
			bool                                               bTeleport;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		};
		AActor_K2_SetActorLocation_Params params;

		params.NewLocation = NewLocation;
		params.bSweep = false;
		params.bTeleport = true;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::K2_SetActorLocation, &params);

		return params.ReturnValue;
	}


	bool IsDBNO()
	{
		struct AFortPawn_IsDBNO_Params
		{
			bool ReturnValue;
		};
		AFortPawn_IsDBNO_Params params;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::FortKismetLibrary::IsDBNO, &params);

		return params.ReturnValue;
	}

	bool IsDead()
	{
		struct AFortPawn_IsDead_Params
		{
			bool ReturnValue;
		};
		AFortPawn_IsDead_Params params;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::FortKismetLibrary::IsDead, &params);

		return params.ReturnValue;
	}

	FVector GetBone(int boneidx)
	{
		if (!this) return { 0, 0, 0 };
		FVector result;
		auto fGetBoneMatrix = ((FMatrix * (__fastcall*)(uintptr_t, FMatrix*, int))(EG_S::Scanned::GetBoneMatrix));
		SpoofThis(fGetBoneMatrix, Mesh(), myMatrix, boneidx);

		result.X = myMatrix->M[3][0];
		result.Y = myMatrix->M[3][1];
		result.Z = myMatrix->M[3][2];

		return result;
	}

	FVector GetVelocity()
	{
		if (!this) return {};

		struct
		{
			FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::FortKismetLibrary::GetVelocity, &params);

		return params.ReturnValue;
	}
};

class APlayerCameraManager {
public:

	float GetFOVAngle()
	{
		if (!this) return 0;

		struct APlayerCameraManager_GetFOVAngle_Params
		{
			float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		};
		APlayerCameraManager_GetFOVAngle_Params params;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::GetCameraLocation, &params);

		return params.ReturnValue;
	}

	FVector GetCameraLocation()
	{
		struct APlayerCameraManager_GetCameraLocation_Params
		{
			FVector ReturnValue;
		};
		APlayerCameraManager_GetCameraLocation_Params params;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::GetCameraLocation, &params);

		return params.ReturnValue;
	}

	FRotator GetCameraRotation()
	{
		struct APlayerCameraManager_GetCameraRotation_Params
		{
			FRotator ReturnValue;
		};
		APlayerCameraManager_GetCameraRotation_Params params;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::GetCameraRotation, &params);

		return params.ReturnValue;
	}
};

class APlayerController {
public:

	FVector WorldToScreen(FVector WorldLocation)
	{
		FVector out;

		if (!this) return { 0,0,0 };
		auto WorldToScreen = reinterpret_cast<bool(__fastcall*)(uintptr_t pPlayerController, FVector vWorldPos, FVector * vScreenPosOut, char)>(EG_S::Scanned::ProjectWorldLocationToScreen);
		SpoofThis(WorldToScreen, (uintptr_t)this, WorldLocation, &out, (char)0);

		return out;
	}

	void ClientSetRotation(FVector& NewRotation, bool bResetCamera = true)
	{
		struct AController_ClientSetRotation_Params
		{
			struct FVector NewRotation;
			bool bResetCamera;
		};

		AController_ClientSetRotation_Params params;
		params.NewRotation = NewRotation;
		params.bResetCamera = bResetCamera;
		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::ClientSetRotation, &params);
	}

	APlayerCameraManager* PlayerCameraManager() {
		if (!this) return 0;
		return (APlayerCameraManager*)(*(uintptr_t*)(this + 0x350));
	}

	AFortPawn* LocalPawn() {
		if (!this) return 0;
		return (AFortPawn*)(*(uintptr_t*)(this + 0x338));
	};

	BOOL LineOfSightTo(AFortPawn* pawn) {
		if (!this) return 0;

		FVector ViewPoint;
		auto LineOfSight = reinterpret_cast<bool(__fastcall*)(APlayerController * PlayerController, AFortPawn * TargetActor, FVector * ViewPoint)>(EG_S::Scanned::LineOfSightTo);
		return LineOfSight(this, pawn, &ViewPoint);
	}
};

class AViewportClient
{
public:
	int Index()
	{
		return 108;
	}
};

class ULocalPlayer {
public:
	AViewportClient* ViewportClient() {
		if (!this) return 0;
		return (AViewportClient*)(*(uintptr_t*)(this + 0x70));
	}

	APlayerController* PlayerController() {
		if (!this) return 0;
		return (APlayerController*)(*(uintptr_t*)(this + 0x30));
	}
};

class ULocalPlayers {
public:
	ULocalPlayer* LocalPlayer() {
		if (!this) return 0;
		return (ULocalPlayer*)(*(uintptr_t*)(this));
	}
};

class UGameInstance {
public:
	ULocalPlayers* LocalPlayers() {   //sdk function 
		if (!this) return 0;
		return (ULocalPlayers*)(*(uintptr_t*)(this + 0x38));
	}
};

class AActors {
public:

	AFortPawn* GetCurrentActor(int i) {
		if (!this) return 0;
		return (AFortPawn*)(*(uintptr_t*)(this + i * sizeof(uintptr_t)));
	}
};

class ULevel {
public:
	AActors* Actors() {
		if (!this) return 0;
		return (AActors*)(*(uintptr_t*)(this + 0x98));
	}

	int ActorCount() {
		if (!this) return 0;
		return (int)(*(uintptr_t*)(this + 0xA0));
	}
};

class UWorld {
public:

	UGameInstance* OwningGameInstance() {
		if (!this) return 0;
		return (UGameInstance*)(*(uintptr_t*)(this + 0x190));  //These are offsetd!
	}

	ULevel* PersistentLevel() {
		if (!this) return 0;
		return (ULevel*)(*(uintptr_t*)(this + 0x30));
	}
};

class UGameplayStatics
{
public:
	void STATIC_GetAllActorsOfClass(UWorld* WorldContextObject, UClass* ActorClass, TArray<AFortPawn*>* OutActors)
	{
		struct UGameplayStatics_GetAllActorsOfClass_Params
		{
			UWorld* WorldContextObject;
			UClass* ActorClass;
			TArray<AFortPawn*> OutActors;
		};

		UGameplayStatics_GetAllActorsOfClass_Params params;
		params.WorldContextObject = WorldContextObject;
		params.ActorClass = ActorClass;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::GameplayStatics::GetAllActorsOfClass, &params);

		if (OutActors != nullptr)
			*OutActors = params.OutActors;
	}
};

class UFortKismetLibrary
{
public:
	TArray<AFortPawn*> STATIC_GetFortPlayerPawns(UObject* WorldContextObject)
	{
		struct GetFortPlayerPawns_Params
		{
			UObject* WorldContextObject;
			TArray<AFortPawn*> ReturnValue;
		};

		GetFortPlayerPawns_Params params;
		params.WorldContextObject = WorldContextObject;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::FortKismetLibrary::GetFortPlayerPawns, &params);

		return params.ReturnValue;
	}

	bool STATIC_OnSameTeam(AFortPawn* ActorA, AFortPawn* ActorB)
	{
		struct UFortKismetLibrary_OnSameTeam_Params
		{
			class AFortPawn* ActorA;
			class AFortPawn* ActorB;
			bool ReturnValue;
		};

		UFortKismetLibrary_OnSameTeam_Params params;
		params.ActorA = ActorA;
		params.ActorB = ActorB;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::FortKismetLibrary::OnSameTeam, &params);

		return params.ReturnValue;
	}
};

class UKismetMathLibrary
{
public:
	FVector STATIC_FindLookAtRotation(const struct FVector& Start, const struct FVector& Target)
	{
		struct UKismetMathLibrary_FindLookAtRotation_Params
		{
			struct FVector Start;
			struct FVector Target;
			struct FVector ReturnValue;
		};

		UKismetMathLibrary_FindLookAtRotation_Params params;
		params.Start = Start;
		params.Target = Target;

		UObject::ProcessEvent((uintptr_t)this, (void*)EG_S::Scanned::KismetMathLibrary::FindLookAtRotation, &params);

		return params.ReturnValue;
	}
};


namespace EG_S
{
	AFortPawn* LocalPawn = nullptr;
}
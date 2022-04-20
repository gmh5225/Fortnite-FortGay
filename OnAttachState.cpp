#define _CRT_SECURE_NO_WARNINGS

#include "RenderState.h"
#include "Engine.h"
#include "UnrealClasses.h"

#include "scan.h"

void Init()
{
	MH_Initialize(); //Starts the hook

	AllocConsole();
	freopen(xorstr("CONOUT$"), xorstr("w"), stdout);

	{
		NtGetAsyncKeyState = decltype(NtGetAsyncKeyState)(SpoofThis(GetProcAddress, (HMODULE)GetModuleHandleA("win32u.dll"), (LPCSTR)"NtUserGetAsyncKeyState"));
	}

	{
		EG_S::Scanned::UWorld = Memory::PatternScan(EG_S::UWorld.c_str(), 0, 7);
		EG_S::Scanned::FreeFN = Memory::PatternScan(EG_S::FreeFN.c_str(), 0, 5);
		EG_S::Scanned::UObjects = Memory::PatternScan(EG_S::UObjects.c_str(), 0, 7);
		EG_S::Scanned::GetNameByIndex = Memory::PatternScan(EG_S::GetNameByIndex.c_str());
		EG_S::Scanned::GetBoneMatrix = Memory::PatternScan(EG_S::GetBoneMatrix.c_str(), 0, 5);
		EG_S::Scanned::ProjectWorldLocationToScreen = Memory::PatternScan(EG_S::ProjectWorldLocationToScreen.c_str(), 0, 5);
		EG_S::Scanned::LineOfSightTo = Memory::PatternScan(EG_S::LineOfSightTo.c_str());
	}

	{
		EG_S::Scanned::objects = (GObjects*)EG_S::Scanned::UObjects;
	}
	
	{
		EG_S::Scanned::KismetMathLibrary::KismetMathLibrary = (UKismetMathLibrary*)UObject::FindObject(xorstr("Class Engine.KismetMathLibrary"));
		EG_S::Scanned::FortKismetLibrary::FortKismetLibrary = (UFortKismetLibrary*)UObject::FindObject(xorstr("Class FortniteGame.FortKismetLibrary"));
		EG_S::Scanned::GameplayStatics::GameplayStatics = (UGameplayStatics*)UObject::FindObject(xorstr("Class Engine.GameplayStatics"));

		EG_S::Scanned::KismetMathLibrary::FindLookAtRotation = UObject::FindObject(xorstr("Function Engine.KismetMathLibrary.FindLookAtRotation"));
		EG_S::Scanned::FortKismetLibrary::GetFortPlayerPawns = UObject::FindObject(xorstr("Function FortniteGame.FortKismetLibrary.GetFortPlayerPawns"));
		EG_S::Scanned::GameplayStatics::GetAllActorsOfClass = UObject::FindObject(xorstr("Function Engine.GameplayStatics.GetAllActorsOfClass"));
		EG_S::Scanned::FortKismetLibrary::OnSameTeam = UObject::FindObject(xorstr("Function FortniteGame.FortKismetLibrary.OnSameTeam"));
		EG_S::Scanned::FortKismetLibrary::GetVelocity = UObject::FindObject(xorstr("Function Engine.Actor.GetVelocity"));
	}

	{
		EG_S::Scanned::Entities::Projectile = UObject::FindClass(xorstr("Class FortniteGame.FortProjectileBase"));
		EG_S::Scanned::Entities::BuildingWeakSpot = UObject::FindClass(xorstr("Class FortniteGame.BuildingWeakSpot"));
	}

	{
		EG_S::Scanned::GetPlayerName = UObject::FindObject(xorstr("Function Engine.PlayerState.GetPlayerName"));
		EG_S::Scanned::GetFovAngle = UObject::FindObject(xorstr("Function Engine.PlayerCameraManager.GetFOVAngle"));
		EG_S::Scanned::FortKismetLibrary::IsDBNO = UObject::FindObject(xorstr("Function FortniteGame.FortPawn.IsDBNO"));
		EG_S::Scanned::FortKismetLibrary::IsDead = UObject::FindObject(xorstr("Function FortniteGame.FortPawn.IsDead"));
		EG_S::Scanned::GetCameraLocation = UObject::FindObject(xorstr("Function Engine.PlayerCameraManager.GetCameraLocation"));
		EG_S::Scanned::GetCameraRotation = UObject::FindObject(xorstr("Function Engine.PlayerCameraManager.GetCameraRotation"));
		EG_S::Scanned::ClientSetRotation = UObject::FindObject(xorstr("Function Engine.Controller.ClientSetRotation"));
		EG_S::Scanned::K2_DrawText = UObject::FindObject(xorstr("Function Engine.Canvas.K2_DrawText"));
		EG_S::Scanned::K2_DrawLine = UObject::FindObject(xorstr("Function Engine.Canvas.K2_DrawLine"));
		EG_S::Scanned::K2_SetActorLocation = UObject::FindObject(xorstr("Function Engine.Actor.K2_SetActorLocation"));
		EG_S::Scanned::IsProjectileWeapon = UObject::FindObject(xorstr("Function FortniteGame.FortWeapon.IsProjectileWeapon"));
		EG_S::Scanned::K2_TeleportTo = UObject::FindObject(xorstr("Function Engine.Actor.K2_TeleportTo"));
		EG_S::Scanned::K2_AttachTo = UObject::FindObject(xorstr("Function Engine.Actor.K2_AttachTo"));
		EG_S::Scanned::GameFont = UObject::FindObject(xorstr("Font Roboto.Roboto"));
	}

	{
		auto GWorld = *(uintptr_t*)(EG_S::Scanned::UWorld);
		auto World = (UWorld*)GWorld;
		auto GameInstance = World->OwningGameInstance();
		auto LocalPlayers = GameInstance->LocalPlayers();
		auto LocalPlayer = LocalPlayers->LocalPlayer();
		auto ViewPortClient = LocalPlayer->ViewportClient();
		auto ViewPortClientTable = *(void***)(ViewPortClient);

		DWORD PEOutput;
		VirtualProtect(&ViewPortClientTable[108], 8, 0x40, &PEOutput); //Post render vtable, can be found online
		PostRendererOrig = reinterpret_cast<decltype(PostRendererOrig)>(ViewPortClientTable[108]);
		ViewPortClientTable[108] = &PostRendererHk;
		VirtualProtect(&ViewPortClientTable[108], 8, PEOutput, 0);

	}

	return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		Init();

	return TRUE;
}
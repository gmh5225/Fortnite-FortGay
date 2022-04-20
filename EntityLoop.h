#pragma once

#include "UnrealClasses.h"
#include "RenderIndex.h"
#include "option.h"

float FovAngle, Width, Height, Lenght;

void Hook() {;
}

bool Initiallize() {
	Hook();
	
	return TRUE;
}

namespace EntityLoop {
	bool main()
	{
		do
		{
			auto GWorld = (UWorld*)*(uintptr_t*)(EG_S::Scanned::UWorld);
			if (!GWorld) break;

			auto OwningGameInstance = GWorld->OwningGameInstance();
			if (!OwningGameInstance) return false;

			auto LocalPlayer = OwningGameInstance->LocalPlayers()->LocalPlayer();
			if (!LocalPlayer) return false;

			auto PlayerController = LocalPlayer->PlayerController();
			if (!PlayerController) return false;

			auto PlayerCameraManager = PlayerController->PlayerCameraManager();
			if (!PlayerCameraManager) return false;

			FovAngle = PlayerCameraManager->GetFOVAngle();

			auto CameraLocation = PlayerCameraManager->GetCameraLocation();
			if (CameraLocation.X == 0 or CameraLocation.Y == 0) return false;

			auto GetCameraRotation = PlayerCameraManager->GetCameraRotation();
			if (GetCameraRotation.Yaw == 0 or GetCameraRotation.Pitch == 0) return false;

			auto LocalPawn = PlayerController->LocalPawn();

			AFortPawn* ClosestPawn = 0;
			float	  ClosestDistance = FLT_MAX;

			//CameraRotation = GetCameraRotation;

			auto AllPlayerPawns = EG_S::Scanned::FortKismetLibrary::FortKismetLibrary->STATIC_GetFortPlayerPawns((UObject*)GWorld);
			for (int i = 0; i < AllPlayerPawns.Num(); i++)
			{
				auto CurrentActor = (AFortPawn*)AllPlayerPawns[i];
				
				bool IsVisible = true;
				
				if (LocalPawn)
				{
					if (EG_S::Scanned::FortKismetLibrary::FortKismetLibrary->STATIC_OnSameTeam(LocalPawn, CurrentActor)) 
						continue;

					if (CurrentActor->IsDead() || CurrentActor->IsDBNO()) 
						continue;
				}

				auto color = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

				if (Settings::PlayerNameESP)
				{
					auto nameloc = PlayerController->WorldToScreen(FVector{ CurrentActor->GetBone(68).X, CurrentActor->GetBone(68).Y, CurrentActor->GetBone(68).Z + 20 });
					auto Name = CurrentActor->PlayerState()->GetPlayerName();
					Engine_R::K2_DrawText(FVector2D{ nameloc.X, nameloc.Y }, Name, FLinearColor(1.f, 0, 0, 1.f), true, true);
				}

				if (Settings::EnemyWeaponESP and LocalPawn)
				{
					auto weaponloc = PlayerController->WorldToScreen(FVector{ CurrentActor->GetBone(68).X, CurrentActor->GetBone(68).Y, CurrentActor->GetBone(68).Z + 25 });
					FText* EnemyWeaponName = CurrentActor->CurrentWeapon()->WeaponData()->DisplayName();
					Engine_R::K2_DrawText(FVector2D{ weaponloc.X, weaponloc.Y }, EnemyWeaponName->GetText(), FLinearColor(1.f, 0, 0, 1.f), true, true);
				}

				if (Settings::BoxESP)
				{
					auto head = CurrentActor->GetBone(68);
					auto loc = PlayerController->WorldToScreen(FVector{ head.X, head.Y, head.Z + 15 });
					auto bottom = PlayerController->WorldToScreen(CurrentActor->GetBone(0));
					float Height1 = loc.Y - bottom.Y;
					if (Height1 < 0) Height1 = Height1 * (-1.f);
					float Width1 = Height1 * 0.65;
					loc.X = loc.X - (Width1 / 2);
					Engine_R::K2_DrawLine(GlobalCanvas, FVector2D(loc.X, loc.Y), FVector2D(loc.X + Width1, loc.Y), color, 1);
					Engine_R::K2_DrawLine(GlobalCanvas, FVector2D(loc.X, loc.Y), FVector2D(loc.X, loc.Y + Height1), color, 1);
					Engine_R::K2_DrawLine(GlobalCanvas, FVector2D(loc.X + Width1, loc.Y), FVector2D(loc.X + Width1, loc.Y + Height1), color, 1);
					Engine_R::K2_DrawLine(GlobalCanvas, FVector2D(loc.X, loc.Y + Height1), FVector2D(loc.X + Width1, loc.Y + Height1), color, 1);
				}

				if (!LocalPawn)
					continue;

				TArray<AFortPawn*> Projectile;
				EG_S::Scanned::GameplayStatics::GameplayStatics->STATIC_GetAllActorsOfClass(GWorld, EG_S::Scanned::Entities::Projectile, &Projectile);
				for (int i = 0; i < Projectile.Num(); i++)
				{
					auto pawn = Projectile[i];
					if (!pawn)
						continue;

					if (Settings::ProjectileTeleport)
					{
						bool TeleportOnce = true;

						if (TeleportOnce) {
							pawn->K2_SetActorLocation(CurrentActor->GetBone(Settings::AimBone));
							TeleportOnce = false;
						}
					}

					auto loc = PlayerController->WorldToScreen(pawn->RootComponent()->RelativeLocation());
					Engine_R::K2_DrawText(FVector2D{ loc.X, loc.Y }, xorstr(L"PROJECTILE"), FLinearColor(1.f, 0, 0, 1.f), true, false);
				}
			}

			//if (Settings::MemoryAim || Settings::StickySilentAim || Settings::SilentAim) {
			//	if (ClosestPawn) {
			//		TargetPawn = ClosestPawn;
			//	}
			//	else {
			//		TargetPawn = 0;
			//	}
			//}
			//else {
			//	TargetPawn = 0;
			//}

		} while (false);
	}
}
#pragma once

#include "CanvasGUI.h"
#include "option.h"

namespace ER
{
	bool Head = false;
	bool Neck = true;
	bool Torso = false;

	void InitMenu()
	{
		CanvasGui::SetupCanvas(GlobalCanvas);

		CanvasGui::Input::Handle();
		//Gay menu made by me in 3 seconds!
		static bool menu_opened = false;
		if (NtGetAsyncKeyState(VK_INSERT) & 1) menu_opened = !menu_opened;

		static FVector2D pos = FVector2D(700, 700);
		if (CanvasGui::Window("Engine Render Example", &pos, FVector2D{ 700.0f, 400.0f }, menu_opened))
		{
			CanvasGui::Checkbox(xorstr("Sticky Silent Aimbot"), &Settings::StickySilentAim);
			if (Settings::StickySilentAim) { Settings::SilentAim = false, Settings::MemoryAim = false; }
			CanvasGui::Checkbox(xorstr("Silent Aimbot"), &Settings::SilentAim);
			if (Settings::SilentAim) { Settings::StickySilentAim = false, Settings::MemoryAim = false; }
			CanvasGui::Checkbox(xorstr("Memory Aimbot"), &Settings::MemoryAim);
			if (Settings::MemoryAim) { Settings::SilentAim = false, Settings::StickySilentAim = false; }

			CanvasGui::Checkbox(xorstr("Head"), &Head);
			if (Head) { Neck = false, Torso = false; Settings::AimBone = 68; }
			CanvasGui::SameLine();
			CanvasGui::Checkbox(xorstr("Neck"), &Neck);
			if (Neck) { Head = false, Torso = false; Settings::AimBone = 7; }
			CanvasGui::SameLine();
			CanvasGui::Checkbox(xorstr("Torso"), &Torso);
			if (Torso) { Head = false, Neck = false; Settings::AimBone = 5; }

			CanvasGui::SliderFloat(xorstr("Aimbot Smooth Value"), &Settings::AimSmooth, 0.f, 15.f);


			CanvasGui::Checkbox(xorstr("Show Fov Circle"), &Settings::ShowFovCircle);
			CanvasGui::SliderFloat(xorstr("Fov Circle Value"), &Settings::FovCircle_Value, 0.f, 180.f);

			CanvasGui::Checkbox(xorstr("Box"), &Settings::BoxESP);
			CanvasGui::Checkbox(xorstr("Skeleton"), &Settings::SkeletonESP);
			CanvasGui::Checkbox(xorstr("Distance"), &Settings::EnemyDistanceESP);
			CanvasGui::Checkbox(xorstr("Username"), &Settings::PlayerNameESP);
			CanvasGui::Checkbox(xorstr("Weapon"), &Settings::EnemyWeaponESP);
			CanvasGui::Checkbox(xorstr("Ammo"), &Settings::EnemyAmmoESP);

			CanvasGui::Checkbox(xorstr("Projectile Teleport"), &Settings::ProjectileTeleport); //sniper tps
		}
		CanvasGui::Render();
	}
}
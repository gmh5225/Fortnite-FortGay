#pragma once

namespace Settings
{
	//Aim
	static bool StickySilentAim = 0;
	static bool SilentAim = 0;
	static bool MemoryAim = 1;

	static bool VisibilityCheck = 1;

	static float AimSmooth = 0;
	static int AimBone = 66;
	
	//Misc
	static bool ShowFovCircle = false;
	static float FovCircle_Value = 5;

	//ESP
	static bool BoxESP = 1;
	static bool SkeletonESP = 1;
	static bool PlayerNameESP = 0;
	static bool EnemyDistanceESP = 0;
	static bool EnemyWeaponESP = 0;
	static bool EnemyAmmoESP = 0;

	//Exploits
	static bool ProjectileTeleport = 0;

	static bool FovChanger = 0;
	static float FovChanger_Value = 90.f;
}
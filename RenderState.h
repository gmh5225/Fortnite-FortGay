#pragma once

#include "RenderIndex.h"
#include "EntityLoop.h"
#include "InitMenu.h"

void(*PostRendererOrig)(UObject*, UCanvas*);
void PostRendererHk(UObject* a1, UCanvas* canvas)
{
	if (!a1 || !canvas)
		return;

	GlobalCanvas = canvas;

	Width = GetSystemMetrics(0);
	Height = GetSystemMetrics(1);
	Lenght = GetSystemMetrics(2);

	if (Settings::ShowFovCircle)
		Engine_R::DrawCircle(FVector2D(Width / 2, Height / 2), Settings::FovCircle_Value, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f), 128);

	{
		ER::InitMenu();
		EntityLoop::main();
	}

	PostRendererOrig(a1, canvas);
}
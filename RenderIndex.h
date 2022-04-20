#pragma once
#include "UnrealClasses.h"

UCanvas* GlobalCanvas;

//__int64(*K2_DrawLine)(UCanvas* UCanvas, FVector2D A, FVector2D B, FLinearColor RenderColor, float Thickness);

void K2_DrawLine(UCanvas* UCanvas, FVector2D PositionToStart, FVector2D PositionToEnd, FLinearColor Color, float Thickness = 1.f)
{
	struct UCanvas_K2_DrawLine_Params
	{
		struct FVector2D                                   ScreenPositionA;                                          // (Parm, ZeroConstructor, IsPlainOldData)
		struct FVector2D                                   ScreenPositionB;                                          // (Parm, ZeroConstructor, IsPlainOldData)
		float                                              Thickness;                                                // (Parm, ZeroConstructor, IsPlainOldData)
		struct FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	};
	UCanvas_K2_DrawLine_Params params;
	params.ScreenPositionA = PositionToStart;
	params.ScreenPositionB = PositionToEnd;
	params.Thickness = Thickness;
	params.RenderColor = Color;

	UObject::ProcessEvent((uintptr_t)GlobalCanvas, (void*)EG_S::Scanned::K2_DrawLine, &params);
}

namespace Engine_R
{
	void K2_DrawLine(UCanvas* UCanvas, FVector2D PositionToStart, FVector2D PositionToEnd, FLinearColor Color, float Thickness = 1.f)
	{
		struct UCanvas_K2_DrawLine_Params
		{
			struct FVector2D                                   ScreenPositionA;                                          // (Parm, ZeroConstructor, IsPlainOldData)
			struct FVector2D                                   ScreenPositionB;                                          // (Parm, ZeroConstructor, IsPlainOldData)
			float                                              Thickness;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			struct FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
		};
		UCanvas_K2_DrawLine_Params params;
		params.ScreenPositionA = PositionToStart;
		params.ScreenPositionB = PositionToEnd;
		params.Thickness = Thickness;
		params.RenderColor = Color;

		UObject::ProcessEvent((uintptr_t)GlobalCanvas, (void*)EG_S::Scanned::K2_DrawLine, &params);
	}

	VOID RK2_DrawText(const FString& RenderText, const FVector2D& ScreenPosition, const FVector2D& Scale, const FLinearColor& RenderColor, float Kerning, const FLinearColor& ShadowColor, const FVector2D& ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, const FLinearColor& OutlineColor)
	{
		if (!GlobalCanvas) return;

		struct K2_drawText_params
		{
			class UFont* RenderFont;                                               // (Parm, ZeroConstructor, IsPlainOldData)
			struct FString                                     RenderText;                                               // (Parm, ZeroConstructor)
			struct FVector2D                                   ScreenPosition;                                           // (Parm, ZeroConstructor, IsPlainOldData)
			struct FVector2D                                   Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
			struct FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
			float                                              Kerning;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
			struct FLinearColor                                ShadowColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
			struct FVector2D                                   ShadowOffset;                                             // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bCentreX;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bCentreY;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bOutlined;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			struct FLinearColor                                OutlineColor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		};

		auto canvas = (uintptr_t)GlobalCanvas;
		K2_drawText_params params;
		params.RenderFont = (UFont*)EG_S::Scanned::GameFont;
		params.RenderText = RenderText;
		params.ScreenPosition = ScreenPosition;
		params.Scale = Scale;
		params.RenderColor = RenderColor;
		params.Kerning = Kerning;
		params.ShadowColor = ShadowColor;
		params.ShadowOffset = ShadowOffset;
		params.bCentreX = bCentreX;
		params.bCentreY = bCentreY;
		params.bOutlined = bOutlined;
		params.OutlineColor = OutlineColor;

		UObject::ProcessEvent((uintptr_t)GlobalCanvas, (void*)EG_S::Scanned::K2_DrawText, &params);
	}


	void K2_DrawText(const FVector2D& ScreenPosition, const FString& RenderText, const FLinearColor& RenderColor, bool centered, bool bOutlined)
	{
		if (!EG_S::Scanned::GameFont) return;

		struct K2_drawText_params
		{
			class UFont* RenderFont;                                               // (Parm, ZeroConstructor, IsPlainOldData)
			struct FString                                     RenderText;                                               // (Parm, ZeroConstructor)
			struct FVector2D                                   ScreenPosition;                                           // (Parm, ZeroConstructor, IsPlainOldData)
			struct FVector2D                                   Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
			struct FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
			float                                              Kerning;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
			struct FLinearColor                                ShadowColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
			struct FVector2D                                   ShadowOffset;                                             // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bCentreX;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bCentreY;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bOutlined;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			struct FLinearColor                                OutlineColor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		};

		K2_drawText_params params;
		params.RenderFont = (UFont*)EG_S::Scanned::GameFont;
		params.RenderText = RenderText;
		params.ScreenPosition = ScreenPosition;
		params.Scale = FVector2D{ 1.f, 1.f };
		params.RenderColor = RenderColor;
		params.Kerning = false;
		params.ShadowColor = FLinearColor{ 0.0f, 0.0f, 0.0f, 0.0f };
		params.ShadowOffset = ScreenPosition;
		if (centered) {
			params.bCentreX = true;
			params.bCentreY = true;
		}
		else {
			params.bCentreX = false;
			params.bCentreY = false;
		}
		params.bOutlined = bOutlined;
		params.OutlineColor = { 0.0f, 0.0f, 0.0f, 1.f };
		UObject::ProcessEvent((uintptr_t)GlobalCanvas, (void*)EG_S::Scanned::K2_DrawText, &params);
	}

	__forceinline void DrawCircle(FVector2D Location, int Radius, int Sides, FLinearColor Color, float Thickness = 1.f)
	{
#define M_PI 3.14159265358979323846264338327950288
		float Step = M_PI * 2.0 / Sides;
		int Count = 0;
		FVector2D V[128];
		for (float a = 0; a < M_PI * 2.0; a += Step) {
			float X1 = Radius * cos(a) + Location.X;
			float Y1 = Radius * sin(a) + Location.Y;
			float X2 = Radius * cos(a + Step) + Location.X;
			float Y2 = Radius * sin(a + Step) + Location.Y;
			V[Count].X = X1;
			V[Count].Y = Y1;
			V[Count + 1].X = X2;
			V[Count + 1].Y = Y2;
			Engine_R::K2_DrawLine(GlobalCanvas, FVector2D(V[Count].X, V[Count].Y), FVector2D(X2, Y2), Color, Thickness);// Circle Around
		}
	}

	void DrawCircle(FVector2D pos, int radius, FLinearColor Color, int numSides = 450)
	{
#define M_PI	3.14159265358979323846264338327950288419716939937510
		float Step = M_PI * 2.0 / numSides;
		int Count = 0;
		FVector2D V[128];
		for (float a = 0; a < M_PI * 2.0; a += Step) {
			float X1 = radius * cos(a) + pos.X;
			float Y1 = radius * sin(a) + pos.Y;
			float X2 = radius * cos(a + Step) + pos.X;
			float Y2 = radius * sin(a + Step) + pos.Y;
			V[Count].X = X1;
			V[Count].Y = Y1;
			V[Count + 1].X = X2;
			V[Count + 1].Y = Y2;
			Engine_R::K2_DrawLine(GlobalCanvas, FVector2D{ V[Count].X, V[Count].Y }, FVector2D{ X2, Y2 }, Color, 1.f);// Circle Around
		}
	}
}
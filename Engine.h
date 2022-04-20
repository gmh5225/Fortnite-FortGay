#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "others.h"

#include <string>
#include <cstdint>

using namespace std;

std::string GetById(int id);

struct FName
{
	union
	{
		struct
		{
			int32_t ComparisonIndex;
			int32_t Number;
		};

		uint64_t CompositeComparisonValue;
	};

	inline FName()
		: ComparisonIndex(0),
		Number(0)
	{
	};

	inline FName(int32_t i)
		: ComparisonIndex(i),
		Number(0)
	{
	};

	inline std::string GetName() const
	{
		return GetById(ComparisonIndex);
	};

	inline bool operator==(const FName& other) const
	{
		return ComparisonIndex == other.ComparisonIndex;
	};
};

struct FVector
{
	double                                              X;                                                        // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                              Y;                                                        // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                              Z;                                                        // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	inline FVector()
		: X(0), Y(0), Z(0)
	{ }

	inline FVector(double x, double y, double z)
		: X(x),
		Y(y),
		Z(z)
	{ }

	__forceinline FVector operator-(const FVector& V) {
		return FVector(X - V.X, Y - V.Y, Z - V.Z);
	}

	__forceinline FVector operator+(const FVector& V) {
		return FVector(X + V.X, Y + V.Y, Z + V.Z);
	}

	__forceinline FVector operator*(double Scale) const {
		return FVector(X * Scale, Y * Scale, Z * Scale);
	}

	__forceinline FVector operator/(double Scale) const {
		const double RScale = 1.f / Scale;
		return FVector(X * RScale, Y * RScale, Z * RScale);
	}

	__forceinline FVector operator+(double A) const {
		return FVector(X + A, Y + A, Z + A);
	}

	__forceinline FVector operator-(double A) const {
		return FVector(X - A, Y - A, Z - A);
	}

	__forceinline FVector operator*(const FVector& V) const {
		return FVector(X * V.X, Y * V.Y, Z * V.Z);
	}

	__forceinline FVector operator/(const FVector& V) const {
		return FVector(X / V.X, Y / V.Y, Z / V.Z);
	}

	__forceinline double operator|(const FVector& V) const {
		return X * V.X + Y * V.Y + Z * V.Z;
	}

	__forceinline double operator^(const FVector& V) const {
		return X * V.Y - Y * V.X - Z * V.Z;
	}

	__forceinline FVector& operator+=(const FVector& v) {
		(*this);
		(v);
		X += v.X;
		Y += v.Y;
		Z += v.Z;
		return *this;
	}

	__forceinline FVector& operator-=(const FVector& v) {
		(*this);
		(v);
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
		return *this;
	}

	__forceinline FVector& operator*=(const FVector& v) {
		(*this);
		(v);
		X *= v.X;
		Y *= v.Y;
		Z *= v.Z;
		return *this;
	}

	__forceinline FVector& operator/=(const FVector& v) {
		(*this);
		(v);
		X /= v.X;
		Y /= v.Y;
		Z /= v.Z;
		return *this;
	}

	__forceinline bool operator==(const FVector& src) const {
		(src);
		(*this);
		return (src.X == X) && (src.Y == Y) && (src.Z == Z);
	}

	__forceinline bool operator!=(const FVector& src) const {
		(src);
		(*this);
		return (src.X != X) || (src.Y != Y) || (src.Z != Z);
	}

	__forceinline double Size() const {
		return sqrt(X * X + Y * Y + Z * Z);
	}

	__forceinline double Size2D() const {
		return sqrt(X * X + Y * Y);
	}

	__forceinline double SizeSquared() const {
		return X * X + Y * Y + Z * Z;
	}

	__forceinline double SizeSquared2D() const {
		return X * X + Y * Y;
	}

	__forceinline double Dot(const FVector& vOther) const {
		const FVector& a = *this;

		return (a.X * vOther.X + a.Y * vOther.Y + a.Z * vOther.Z);
	}

	double Distance(FVector v)
	{
		return ((X - v.X) * (X - v.X) +
			(Y - v.Y) * (Y - v.Y) +
			(Z - v.Z) * (Z - v.Z));
	}

	inline double distance()
	{
		return sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
	}


	inline double Length() {
		return sqrt(X * X + Y * Y + Z * Z);
	}

	__forceinline double DistanceFrom(const FVector& Other) const {
		const FVector& a = *this;
		double dx = (a.X - Other.X);
		double dy = (a.Y - Other.Y);
		double dz = (a.Z - Other.Z);

		return (sqrt((dx * dx) + (dy * dy) + (dz * dz)));
	}

	__forceinline FVector Normalize() {
		FVector vector;
		double length = this->Size();

		if (length != 0) {
			vector.X = X / length;
			vector.Y = Y / length;
			vector.Z = Z / length;
		}
		else
			vector.X = vector.Y = 0.0f;
		vector.Z = 1.0f;

		return vector;
	}

};

struct FVector2D
{
	double                                             X;
	double                                             Y;

	inline FVector2D()
		: X(0), Y(0)
	{ }

	inline FVector2D(double x, double y)
		: X(x),
		Y(y)
	{ }

};

struct FRotator {
	FRotator() : Pitch(0), Yaw(0), Roll(0)
	{

	}

	FRotator(double _pitch, double _yaw, double _roll) : Pitch(_pitch), Yaw(_yaw), Roll(_roll)
	{

	}

	double Pitch;
	double Yaw;
	double Roll;

	FRotator ClampAngles() {
		if (this->Yaw > 180.f)
			this->Yaw -= 360.f;
		else if (this->Yaw < -180.f)
			this->Yaw += 360.f;

		if (this->Pitch > 180.f)
			this->Pitch -= 360.f;
		else if (this->Pitch < -180.f)
			this->Pitch += 360.f;

		if (this->Pitch < -89.f)
			this->Pitch = -89.f;
		else if (this->Pitch > 89.f)
			this->Pitch = 89.f;

		this->Roll = 0.f;

		return *this;
	}

	static FRotator CalcAngle(FVector cameraLocation, FVector boneLocation) {

		FRotator result;

		auto delta = boneLocation - cameraLocation;
		auto distance = delta.distance();

		result.Yaw = atan2f(delta.Y, delta.X) * (180.0f / 3.141592653589793f);
		result.Pitch = (-((acosf((delta.Z / distance)) * 180.0f / 3.141592653589793f) - 90.0f));
		result.Roll = NULL;

		return result;
	}


	FRotator SmoothAngles(float fSmoothing, FRotator vControlRotation)
	{
		FRotator vSmoothed = FRotator(this->Pitch, this->Yaw, this->Roll);
		if (fSmoothing > 0)
		{
			vSmoothed.Pitch = this->Pitch - vControlRotation.Pitch;
			vSmoothed.Yaw = this->Yaw - vControlRotation.Yaw;

			vSmoothed = vSmoothed.ClampAngles();

			vSmoothed.Pitch = (vSmoothed.Pitch / fSmoothing) + vControlRotation.Pitch;
			vSmoothed.Yaw = (vSmoothed.Yaw / fSmoothing) + vControlRotation.Yaw;
		}
		return vSmoothed;
	}
};

struct alignas(16) FPlane : public FVector
{
	double                                             W;                                                        // 0x0018(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
};

struct FMatrix
{
	double M[4][4];
};
static FMatrix* myMatrix = new FMatrix();

template<class T>
struct TArray
{
	friend struct FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	inline void Dump(std::string name)
	{
		std::ofstream dmp(name.c_str(), std::ios::binary);
		dmp.write(reinterpret_cast<char*>(&Data[0]), Count);
		dmp.close();
	};

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}


	T* Data;
private:
	int32_t Count;
	int32_t Max;
};

class FTextData {
public:
	char pad_0x0000[0x30];  //0x0000
	wchar_t* Name;          //0x0028 
	__int32 Length;         //0x0030 

};

struct FText {
	FTextData* Data;
	char UnknownData[0x10];

	wchar_t* GetText() const {
		if (Data) {
			return Data->Name;
		}

		return nullptr;
	}
};
struct FString : private TArray<wchar_t>
{
	inline FString()
	{
	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? wcslen(other) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const
	{
		return Data;
	}

	std::string ToString() const
	{
		auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

class UObject {
public:
	void** Vtable;                                                   // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int32_t                                            ObjectFlags;                                              // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int32_t                                            InternalIndex;                                            // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	class UClass* Class;                                                    // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	FName                                              Name;                                                     // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	class UObject* Outer;                                                    // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY

	std::string GetName();
	std::string GetFullName();
	BOOLEAN IsA(PVOID parentClass);
	static void ProcessEvent(uintptr_t address, void* fnobject, void* parms);

	static uintptr_t FindObject(const std::string& name);

	static UClass* FindClass(const std::string& name)
	{
		return (UClass*)FindObject(name);
	}
};

class UField : public UObject
{
public:
	class UField* Next;
};

class UStruct : public UField
{
public:
	char                                               pad_0030[0x10];                                           // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	class UStruct* SuperField;                                               // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	class UField* Children;                                                 // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	void* ChildProperties;                                          // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int32_t                                            PropertySize;                                             // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	int32_t                                            MinAlignment;                                             // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
	char                                               pad_0060[0x50];                                           // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
};

class UClass : public UStruct {
public:
	BYTE _padding_0[0x40];
	UClass* SuperClass;
};

class FUObjectItem
{
public:
	UObject* Object;
	int32_t Flags;
	int32_t ClusterIndex;
	int32_t SerialNumber;
	char padding[0x4];

	enum class ObjectFlags : int32_t
	{
		None = 0,
		Native = 1 << 25,
		Async = 1 << 26,
		AsyncLoading = 1 << 27,
		Unreachable = 1 << 28,
		PendingKill = 1 << 29,
		RootSet = 1 << 30,
		NoStrongReference = 1 << 31
	};

	inline bool IsUnreachable() const
	{
		return !!(Flags & static_cast<std::underlying_type_t<ObjectFlags>>(ObjectFlags::Unreachable));
	}
	inline bool IsPendingKill() const
	{
		return !!(Flags & static_cast<std::underlying_type_t<ObjectFlags>>(ObjectFlags::PendingKill));
	}
};

class PreFUObjectItem
{
public:
	FUObjectItem* FUObject[10];
};

class TUObjectArray
{
public:
	inline void NumChunks(int* start, int* end) const
	{
		int cStart = 0, cEnd = 0;

		if (!cEnd)
		{
			//find where chunks start
			while (1)
			{
				if (Objects->FUObject[cStart] == 0)
				{
					cStart++;
				}
				else
				{
					break;
				}
			}

			cEnd = cStart;
			//find where chunks end
			while (1)
			{
				if (Objects->FUObject[cEnd] == 0)
				{
					break;
				}
				else
				{
					cEnd++;
				}
			}
		}

		*start = cStart;
		*end = cEnd;
	}

	inline UObject* GetByIndex(int32_t index) const
	{
		int cStart = 0, cEnd = 0;
		int chunkIndex = 0, chunkSize = 0xFFFF, chunkPos;
		FUObjectItem* Object;

		NumChunks(&cStart, &cEnd);

		chunkIndex = index / chunkSize;
		//this is so it stays in the previous chunk when the sizes are the same
		if (chunkSize * chunkIndex != 0 &&
			chunkSize * chunkIndex == index)
		{
			chunkIndex--;
		}

		chunkPos = cStart + chunkIndex;
		if (chunkPos < cEnd)
		{
			Object = Objects->FUObject[chunkPos] + (index - chunkSize * chunkIndex);
			if (!Object) { return NULL; }

			return Object->Object;
		}

		return nullptr;
	}

	inline FUObjectItem* GetItemByIndex(int32_t index) const
	{
		int cStart = 0, cEnd = 0;
		int chunkIndex = 0, chunkSize = 0xFFFF, chunkPos;
		FUObjectItem* Object;

		NumChunks(&cStart, &cEnd);

		chunkIndex = index / chunkSize;
		//this is so it stays in the previous chunk when the sizes are the same
		if (chunkSize * chunkIndex != 0 &&
			chunkSize * chunkIndex == index)
		{
			chunkIndex--;
		}

		chunkPos = cStart + chunkIndex;
		if (chunkPos < cEnd)
		{
			Object = Objects->FUObject[chunkPos] + (index - chunkSize * chunkIndex);
			if (!Object) { return NULL; }

			return Object;
		}

		return nullptr;
	}

	inline int32_t Num() const
	{
		return NumElements;
	}

private:
	//FUObjectItem* Objects[9];
	PreFUObjectItem* Objects;
	char padding[8];
	int32_t MaxElements;
	int32_t NumElements;
};

class FUObjectArray
{
public:
	TUObjectArray ObjObjects;
};

class GObjects {
public:
	TUObjectArray* ObjectArray;
	BYTE _padding_0[0xC];
	DWORD ObjectCount;
};


struct FMinimalViewInfo
{
	FVector Location;
	FRotator Rotation;
	float FOV;
};

struct FLinearColor
{
	FLinearColor() : R(0.f), G(0.f), B(0.f), A(0.f)
	{

	}

	FLinearColor(float _R, float _G, float _B, float _A) : R(_R), G(_G), B(_B), A(_A)
	{

	}

	float R; // 0x00(0x04)
	float G; // 0x04(0x04)
	float B; // 0x08(0x04)
	float A; // 0x0c(0x04)
};

struct FColor
{
	uint8_t R; // 0x00(0x04)
	uint8_t G; // 0x04(0x04)
	uint8_t B; // 0x08(0x04)
	uint8_t A; // 0x0c(0x04)
};

class UCanvas
{
public:
	float                                              OrgX;                                                     // 0x0028(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              OrgY;                                                     // 0x002C(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              ClipX;                                                    // 0x0030(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              ClipY;                                                    // 0x0034(0x0004) (ZeroConstructor, IsPlainOldData)
	struct FColor									   DrawColor;                                                // 0x0038(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      bCenterX : 1;                                             // 0x003C(0x0001)
	unsigned char                                      bCenterY : 1;                                             // 0x003C(0x0001)
	unsigned char                                      bNoSmooth : 1;                                            // 0x003C(0x0001)
	unsigned char                                      UnknownData00[0x3];                                       // 0x003D(0x0003) MISSED OFFSET
	int                                                SizeX;                                                    // 0x0040(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                SizeY;                                                    // 0x0044(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0048(0x0008) MISSED OFFSET
	struct FPlane                                      ColorModulate;                                            // 0x0050(0x0020) (ZeroConstructor, IsPlainOldData)
	class UTexture2D* DefaultTexture;                                           // 0x0070(0x0008) (ZeroConstructor, IsPlainOldData)
	class UTexture2D* GradientTexture0;                                         // 0x0078(0x0008) (ZeroConstructor, IsPlainOldData)
	class UReporterGraph* ReporterGraph;                                            // 0x0080(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x308];                                     // 0x0088(0x0308) MISSED OFFSET
};

struct FCameraCacheEntry
{
	float                                              Timestamp;                                                // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0xC];                                       // 0x0004(0x000C) MISSED OFFSET
	struct FMinimalViewInfo                            POV;                                                      // 0x0010(0x0770)
};

namespace EG_S
{
	namespace Scanned {
		extern GObjects* objects;
	}
}
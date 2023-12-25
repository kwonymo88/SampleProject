#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

template<typename T>
class TSingleton : public FNoncopyable
{
public:
	virtual ~TSingleton()
	{
		DestroyInstance();
	}

	static bool IsNullInstance() { return (nullptr == _Instance); }

	static T& Get()
	{
		if (nullptr == _Instance)
		{
			_Instance = NewObject<T>();
			if (_Instance)
			{
				_Instance->AddToRoot();
			}
		}
		ensure(_Instance);

		return *_Instance;
	};

	static void DestroyInstance()
	{
		if (_Instance)
		{
			_Instance->RemoveFromRoot();
			_Instance = nullptr;
		}
	};
private:
	static inline T* _Instance = nullptr;
};
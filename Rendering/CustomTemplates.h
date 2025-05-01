#ifndef __CUSTOM_TEMPLATES_H__
#define __CUSTOM_TEMPLATES_H__

#include <d3d11.h> //HWND

template <typename T, typename... TArgs>
bool ConstructAndInitialize(T*& tObjPtr, TArgs&&... args)
{	
	tObjPtr = new T{};
	if (!tObjPtr)
	{
		return false;
	}
	// Initialize the T object.
	bool result = tObjPtr->Initialize(std::forward<TArgs>(args)...);
	
	return result;
}

template <typename T>
void ShutdownAndDelete(T* tObj) 
{
	if (tObj)
	{
		tObj->Shutdown();
		delete tObj;
		tObj = 0;
	}
}

template <typename T>
void ReleaseAndZero(T* what)
{
	what->Release();
	what = nullptr;
}

#endif // !__CUSTOM_TEMPLATES_H__
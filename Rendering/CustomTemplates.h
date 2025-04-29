#ifndef __CUSTOM_TEMPLATES_H__
#define __CUSTOM_TEMPLATES_H__

#include <d3d11.h> //HWND

template <typename TPtr, typename... TArgs>
bool ConstructAndInitialize(HWND hwnd, TPtr*& tObjPtr, TArgs&&... args)
{	
	tObjPtr = new TPtr;
	if (!tObjPtr)
	{
		return false;
	}
	// Initialize the TPtr object.
	bool result = tObjPtr->Initialize(std::forward<TArgs>(args)...);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the object.", L"Error", MB_OK);
		return false;
	}
	return result;
}

#endif // !__CUSTOM_TEMPLATES_H__
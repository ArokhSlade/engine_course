#ifndef __CUSTOM_TEMPLATES_H__
#define __CUSTOM_TEMPLATES_H__

template <typename TPtr, typename... TArgs>
bool ConstructAndInitialize(TPtr& tObjPtr, TArgs&&... args)
{	
	tObjPtr = new TPtr;
	if (!tObjPtr)
	{
		return false;
	}
	// Initialize the TPtr object.
	result = tObjPtr->Initialize(std::forward<TArgs>(args)...);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the object.", L"Error", MB_OK);
		return false;
	}
}

#endif // !__CUSTOM_TEMPLATES_H__
#pragma once

template <typename dataType>
inline void GlReleaseMem(dataType** pMem)
{
	if (*pMem != 0)
	{
		delete* pMem;//Type Mismatch
		*pMem = 0;
	}
}

template <typename dataTypeHOBJ>
inline void GlReleaseHOBJ(dataTypeHOBJ* hObj)
{
	if (*hObj != 0)
	{
		delete *hObj;
		*hObj = 0;
	}
}

//inline void GlReleasePEN(Pen* p) {
//	delete* p;
//}
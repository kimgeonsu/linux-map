#pragma once
<<<<<<< HEAD
=======

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
	if (*hObj != NULL)
	{
		DeleteObject(*hObj);
		*hObj = NULL;
	}
}
>>>>>>> parent of 6da7800 (왜 안될깡........)

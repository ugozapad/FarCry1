// CryInput.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#ifndef _XBOX 
_ACCESS_POOL;
#endif //_XBOX

#include <stdio.h>
#include <ILog.h>
#include <IInput.h>
#include "Input.h"

#ifdef _DEBUG
static char THIS_FILE[] = __FILE__;
#define DEBUG_CLIENTBLOCK new( _NORMAL_BLOCK, THIS_FILE, __LINE__) 
#define new DEBUG_CLIENTBLOCK
#endif

//////////////////////////////////////////////////////////////////////////
// Pointer to Global ISystem.
static ISystem* gISystem = 0;
ISystem* GetISystem()
{
	return gISystem;
}
//////////////////////////////////////////////////////////////////////////


#ifndef _XBOX
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
#endif //_XBOX

#include <SDL_syswm.h>

IInput *CreateInput( ISystem *pSystem,void* hinst, void* hwnd, bool usedinput)
{
	gISystem = pSystem;
	CInput *pInput=new CInput;

	// #TODO: properly HWND gettings, and remove 
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo((SDL_Window*)hwnd, &wmInfo);
	HWND realhwnd = wmInfo.info.win.window;

	if (!pInput->Init(pSystem,(HINSTANCE)hinst, realhwnd,usedinput))
	{
		delete pInput;
		return NULL;
	}
	return pInput;
}

#include <CrtDebugStats.h>

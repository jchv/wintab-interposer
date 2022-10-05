/* Wintab-Interposer
 *
 * Copyright © 2021, John Chadwick <john@jchw.io>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "wintab32.h"

static HMODULE hDLL = nullptr;
static FILE *fLogFile = stderr;

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, void *reserved)
{
	if (reason == DLL_PROCESS_ATTACH) {
		if (auto szLogFilename = getenv("WINTAB_LOG"); szLogFilename != nullptr) {
			fLogFile = fopen(szLogFilename, "a");
		}
	}

    fprintf(fLogFile, "[TRACE] wintab32.DllMain(%p, %lu, %p)\n", instance, reason, reserved);

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            hDLL = LoadLibraryExA("wintab32", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
			if (hDLL == nullptr || hDLL == instance) {
	            hDLL = LoadLibraryA("wintab32_real");
			}
			if (hDLL == nullptr) {
				fprintf(fLogFile, "[FATAL] wintab32.DllMain: Couldn't find real wintab32.\n");
				abort();
			}
            fprintf(fLogFile, "[TRACE] wintab32.DllMain: Forwarding DLL (wintab32) loaded (%p)\n", hDLL);
            DisableThreadLibraryCalls(instance);
            break;
        case DLL_PROCESS_DETACH:
            FreeLibrary(hDLL);
            fprintf(fLogFile, "[TRACE] wintab32.DllMain: Forwarding DLL (wintab32) freed\n");
            break;
    }

    return TRUE;
}


extern "C" UINT __stdcall WINTAB32_WTInfoA(UINT arg0, UINT arg1, LPVOID arg2)
{
	UINT (__stdcall *pFunc)(UINT, UINT, LPVOID);
	UINT retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTInfoA"));
	fprintf(fLogFile, "[TRACE] wintab32.WTInfoA((UINT)%ld,(UINT)%ld,(LPVOID)%p): forward\n",(LONG)arg0,(LONG)arg1,arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTInfoA Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" HCTX __stdcall WINTAB32_WTOpenA(HWND arg0, LPLOGCONTEXTA arg1, BOOL arg2)
{
	HCTX (__stdcall *pFunc)(HWND, LPLOGCONTEXTA, BOOL);
	HCTX retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTOpenA"));
	fprintf(fLogFile, "[TRACE] wintab32.WTOpenA((HWND)%p,(LPLOGCONTEXTA)%p,(BOOL)%ld): forward\n",arg0,arg1,(LONG)arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTOpenA Returned (%p)\n",retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTClose(HCTX arg0)
{
	BOOL (__stdcall *pFunc)(HCTX);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTClose"));
	fprintf(fLogFile, "[TRACE] wintab32.WTClose((HCTX)%p): forward\n",arg0);
	retVal = pFunc(arg0);
	fprintf(fLogFile, "[TRACE] wintab32.WTClose Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" int __stdcall WINTAB32_WTPacketsGet(HCTX arg0, int arg1, LPVOID arg2)
{
	int (__stdcall *pFunc)(HCTX, int, LPVOID);
	int retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTPacketsGet"));
	fprintf(fLogFile, "[TRACE] wintab32.WTPacketsGet((HCTX)%p,(int)%ld,(LPVOID)%p): forward\n",arg0,(LONG)arg1,arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTPacketsGet Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTPacket(HCTX arg0, UINT arg1, LPVOID arg2)
{
	BOOL (__stdcall *pFunc)(HCTX, UINT, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTPacket"));
	fprintf(fLogFile, "[TRACE] wintab32.WTPacket((HCTX)%p,(UINT)%ld,(LPVOID)%p): forward\n",arg0,(LONG)arg1,arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTPacket Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTEnable(HCTX arg0, BOOL arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, BOOL);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTEnable"));
	fprintf(fLogFile, "[TRACE] wintab32.WTEnable((HCTX)%p,(BOOL)%ld): forward\n",arg0,(LONG)arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTEnable Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTOverlap(HCTX arg0, BOOL arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, BOOL);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTOverlap"));
	fprintf(fLogFile, "[TRACE] wintab32.WTOverlap((HCTX)%p,(BOOL)%ld): forward\n",arg0,(LONG)arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTOverlap Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTConfig(HCTX arg0, HWND arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, HWND);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTConfig"));
	fprintf(fLogFile, "[TRACE] wintab32.WTConfig((HCTX)%p,(HWND)%p): forward\n",arg0,arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTConfig Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTGetA(HCTX arg0, LPLOGCONTEXTA arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, LPLOGCONTEXTA);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTGetA"));
	fprintf(fLogFile, "[TRACE] wintab32.WTGetA((HCTX)%p,(LPLOGCONTEXTA)%p): forward\n",arg0,arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTGetA Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTSetA(HCTX arg0, LPLOGCONTEXTA arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, LPLOGCONTEXTA);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTSetA"));
	fprintf(fLogFile, "[TRACE] wintab32.WTSetA((HCTX)%p,(LPLOGCONTEXTA)%p): forward\n",arg0,arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTSetA Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTExtGet(HCTX arg0, UINT arg1, LPVOID arg2)
{
	BOOL (__stdcall *pFunc)(HCTX, UINT, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTExtGet"));
	fprintf(fLogFile, "[TRACE] wintab32.WTExtGet((HCTX)%p,(UINT)%ld,(LPVOID)%p): forward\n",arg0,(LONG)arg1,arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTExtGet Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTExtSet(HCTX arg0, UINT arg1, LPVOID arg2)
{
	BOOL (__stdcall *pFunc)(HCTX, UINT, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTExtSet"));
	fprintf(fLogFile, "[TRACE] wintab32.WTExtSet((HCTX)%p,(UINT)%ld,(LPVOID)%p): forward\n",arg0,(LONG)arg1,arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTExtSet Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTSave(HCTX arg0, LPVOID arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTSave"));
	fprintf(fLogFile, "[TRACE] wintab32.WTSave((HCTX)%p,(LPVOID)%p): forward\n",arg0,arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTSave Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" HCTX __stdcall WINTAB32_WTRestore(HWND arg0, LPVOID arg1, BOOL arg2)
{
	HCTX (__stdcall *pFunc)(HWND, LPVOID, BOOL);
	HCTX retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTRestore"));
	fprintf(fLogFile, "[TRACE] wintab32.WTRestore((HWND)%p,(LPVOID)%p,(BOOL)%ld): forward\n",arg0,arg1,(LONG)arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTRestore Returned (%p)\n",retVal);
	return retVal;
}


extern "C" int __stdcall WINTAB32_WTPacketsPeek(HCTX arg0, int arg1, LPVOID arg2)
{
	int (__stdcall *pFunc)(HCTX, int, LPVOID);
	int retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTPacketsPeek"));
	fprintf(fLogFile, "[TRACE] wintab32.WTPacketsPeek((HCTX)%p,(int)%ld,(LPVOID)%p): forward\n",arg0,(LONG)arg1,arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTPacketsPeek Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" int __stdcall WINTAB32_WTDataGet(HCTX arg0, UINT arg1, UINT arg2, int arg3, LPVOID arg4, LPINT arg5)
{
	int (__stdcall *pFunc)(HCTX, UINT, UINT, int, LPVOID, LPINT);
	int retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTDataGet"));
	fprintf(fLogFile, "[TRACE] wintab32.WTDataGet((HCTX)%p,(UINT)%ld,(UINT)%ld,(int)%ld,(LPVOID)%p,(LPINT)%p): forward\n",arg0,(LONG)arg1,(LONG)arg2,(LONG)arg3,arg4,arg5);
	retVal = pFunc(arg0,arg1,arg2,arg3,arg4,arg5);
	fprintf(fLogFile, "[TRACE] wintab32.WTDataGet Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" int __stdcall WINTAB32_WTDataPeek(HCTX arg0, UINT arg1, UINT arg2, int arg3, LPVOID arg4, LPINT arg5)
{
	int (__stdcall *pFunc)(HCTX, UINT, UINT, int, LPVOID, LPINT);
	int retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTDataPeek"));
	fprintf(fLogFile, "[TRACE] wintab32.WTDataPeek((HCTX)%p,(UINT)%ld,(UINT)%ld,(int)%ld,(LPVOID)%p,(LPINT)%p): forward\n",arg0,(LONG)arg1,(LONG)arg2,(LONG)arg3,arg4,arg5);
	retVal = pFunc(arg0,arg1,arg2,arg3,arg4,arg5);
	fprintf(fLogFile, "[TRACE] wintab32.WTDataPeek Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" int __stdcall WINTAB32_WTQueueSizeGet(HCTX arg0)
{
	int (__stdcall *pFunc)(HCTX);
	int retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTQueueSizeGet"));
	fprintf(fLogFile, "[TRACE] wintab32.WTQueueSizeGet((HCTX)%p): forward\n",arg0);
	retVal = pFunc(arg0);
	fprintf(fLogFile, "[TRACE] wintab32.WTQueueSizeGet Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTQueueSizeSet(HCTX arg0, int arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, int);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTQueueSizeSet"));
	fprintf(fLogFile, "[TRACE] wintab32.WTQueueSizeSet((HCTX)%p,(int)%ld): forward\n",arg0,(LONG)arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTQueueSizeSet Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" HMGR __stdcall WINTAB32_WTMgrOpen(HWND arg0, UINT arg1)
{
	HMGR (__stdcall *pFunc)(HWND, UINT);
	HMGR retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrOpen"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrOpen((HWND)%p,(UINT)%ld): forward\n",arg0,(LONG)arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrOpen Returned (%p)\n",retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrClose(HMGR arg0)
{
	BOOL (__stdcall *pFunc)(HMGR);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrClose"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrClose((HMGR)%p): forward\n",arg0);
	retVal = pFunc(arg0);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrClose Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrContextEnum(HMGR arg0, WTENUMPROC arg1, LPARAM arg2)
{
	BOOL (__stdcall *pFunc)(HMGR, WTENUMPROC, LPARAM);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrContextEnum"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrContextEnum((HMGR)%p,(WTENUMPROC)%p,(LPARAM)%lld): forward\n",arg0,arg1,(long long int)arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrContextEnum Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" HWND __stdcall WINTAB32_WTMgrContextOwner(HMGR arg0, HCTX arg1)
{
	HWND (__stdcall *pFunc)(HMGR, HCTX);
	HWND retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrContextOwner"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrContextOwner((HMGR)%p,(HCTX)%p): forward\n",arg0,arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrContextOwner Returned (%p)\n",retVal);
	return retVal;
}


extern "C" HCTX __stdcall WINTAB32_WTMgrDefContext(HMGR arg0, BOOL arg1)
{
	HCTX (__stdcall *pFunc)(HMGR, BOOL);
	HCTX retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrDefContext"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrDefContext((HMGR)%p,(BOOL)%ld): forward\n",arg0,(LONG)arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrDefContext Returned (%p)\n",retVal);
	return retVal;
}


extern "C" UINT __stdcall WINTAB32_WTMgrDeviceConfig(HMGR arg0, UINT arg1, HWND arg2)
{
	UINT (__stdcall *pFunc)(HMGR, UINT, HWND);
	UINT retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrDeviceConfig"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrDeviceConfig((HMGR)%p,(UINT)%ld,(HWND)%p): forward\n",arg0,(LONG)arg1,arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrDeviceConfig Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrExt(HMGR arg0, UINT arg1, LPVOID arg2)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrExt"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrExt((HMGR)%p,(UINT)%ld,(LPVOID)%p): forward\n",arg0,(LONG)arg1,arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrExt Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrEnable(HMGR arg0, UINT arg1, BOOL arg2)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, BOOL);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrEnable"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrEnable((HMGR)%p,(UINT)%ld,(BOOL)%ld): forward\n",arg0,(LONG)arg1,(LONG)arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrEnable Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrButtonMap(HMGR arg0, UINT arg1, LPBYTE arg2, LPBYTE arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, LPBYTE, LPBYTE);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrButtonMap"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrButtonMap((HMGR)%p,(UINT)%ld,(LPBYTE)%p,(LPBYTE)%p): forward\n",arg0,(LONG)arg1,arg2,arg3);
	retVal = pFunc(arg0,arg1,arg2,arg3);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrButtonMap Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrPressureBtnMarks(HMGR arg0, UINT arg1, DWORD arg2, DWORD arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, DWORD, DWORD);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrPressureBtnMarks"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrPressureBtnMarks((HMGR)%p,(UINT)%ld,(DWORD)%ld,(DWORD)%ld): forward\n",arg0,(LONG)arg1,(LONG)arg2,(LONG)arg3);
	retVal = pFunc(arg0,arg1,arg2,arg3);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrPressureBtnMarks Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrPressureResponse(HMGR arg0, UINT arg1, UINT * arg2, UINT * arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, UINT *, UINT *);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrPressureResponse"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrPressureResponse((HMGR)%p,(UINT)%ld,(UINT *)%p,(UINT *)%p): forward\n",arg0,(LONG)arg1,arg2,arg3);
	retVal = pFunc(arg0,arg1,arg2,arg3);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrPressureResponse Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrExt(HMGR arg0, UINT arg1, UINT arg2, LPVOID arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, UINT, LPVOID);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrExt"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrExt((HMGR)%p,(UINT)%ld,(UINT)%ld,(LPVOID)%p): forward\n",arg0,(LONG)arg1,(LONG)arg2,arg3);
	retVal = pFunc(arg0,arg1,arg2,arg3);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrExt Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTQueuePacketsEx(HCTX arg0, UINT * arg1, UINT * arg2)
{
	BOOL (__stdcall *pFunc)(HCTX, UINT *, UINT *);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTQueuePacketsEx"));
	fprintf(fLogFile, "[TRACE] wintab32.WTQueuePacketsEx((HCTX)%p,(UINT *)%p,(UINT *)%p): forward\n",arg0,arg1,arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTQueuePacketsEx Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrCsrPressureBtnMarksEx(HMGR arg0, UINT arg1, UINT * arg2, UINT * arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, UINT, UINT *, UINT *);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrCsrPressureBtnMarksEx"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrPressureBtnMarksEx((HMGR)%p,(UINT)%ld,(UINT *)%p,(UINT *)%p): forward\n",arg0,(LONG)arg1,arg2,arg3);
	retVal = pFunc(arg0,arg1,arg2,arg3);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrCsrPressureBtnMarksEx Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrConfigReplaceExA(HMGR arg0, BOOL arg1, LPSTR arg2, LPSTR arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, BOOL, LPSTR, LPSTR);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrConfigReplaceExA"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrConfigReplaceExA((HMGR)%p,(BOOL)%ld,(LPSTR)%s,(LPSTR)%s): forward\n",arg0,(LONG)arg1,arg2,arg3);
	retVal = pFunc(arg0,arg1,arg2,arg3);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrConfigReplaceExA Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" HWTHOOK __stdcall WINTAB32_WTMgrPacketHookExA(HMGR arg0, int arg1, LPSTR arg2, LPSTR arg3)
{
	HWTHOOK (__stdcall *pFunc)(HMGR, int, LPSTR, LPSTR);
	HWTHOOK retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrPacketHookExA"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrPacketHookExA((HMGR)%p,(int)%ld,(LPSTR)%s,(LPSTR)%s): forward\n",arg0,(LONG)arg1,arg2,arg3);
	retVal = pFunc(arg0,arg1,arg2,arg3);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrPacketHookExA Returned (%p)\n",retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrPacketUnhook(HWTHOOK arg0)
{
	BOOL (__stdcall *pFunc)(HWTHOOK);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrPacketUnhook"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrPacketUnhook((HWTHOOK)%p): forward\n",arg0);
	retVal = pFunc(arg0);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrPacketUnhook Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" LRESULT __stdcall WINTAB32_WTMgrPacketHookNext(HWTHOOK arg0, int arg1, WPARAM arg2, LPARAM arg3)
{
	LRESULT (__stdcall *pFunc)(HWTHOOK, int, WPARAM, LPARAM);
	LRESULT retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrPacketHookNext"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrPacketHookNext((HWTHOOK)%p,(int)%ld,(WPARAM)%ld,(LPARAM)%lld): forward\n",arg0,(LONG)arg1,(LONG)arg2,(long long int)arg3);
	retVal = pFunc(arg0,arg1,arg2,arg3);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrPacketHookNext Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" HCTX __stdcall WINTAB32_WTMgrDefContextEx(HMGR arg0, UINT arg1, BOOL arg2)
{
	HCTX (__stdcall *pFunc)(HMGR, UINT, BOOL);
	HCTX retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrDefContextEx"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrDefContextEx((HMGR)%p,(UINT)%ld,(BOOL)%ld): forward\n",arg0,(LONG)arg1,(LONG)arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrDefContextEx Returned (%p)\n",retVal);
	return retVal;
}


extern "C" UINT __stdcall WINTAB32_WTInfoW(UINT arg0, UINT arg1, LPVOID arg2)
{
	UINT (__stdcall *pFunc)(UINT, UINT, LPVOID);
	UINT retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTInfoW"));
	fprintf(fLogFile, "[TRACE] wintab32.WTInfoW((UINT)%ld,(UINT)%ld,(LPVOID)%p): forward\n",(LONG)arg0,(LONG)arg1,arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTInfoW Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" HCTX __stdcall WINTAB32_WTOpenW(HWND arg0, LPLOGCONTEXTW arg1, BOOL arg2)
{
	HCTX (__stdcall *pFunc)(HWND, LPLOGCONTEXTW, BOOL);
	HCTX retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTOpenW"));
	fprintf(fLogFile, "[TRACE] wintab32.WTOpenW((HWND)%p,(LPLOGCONTEXTW)%p,(BOOL)%ld): forward\n",arg0,arg1,(LONG)arg2);
	retVal = pFunc(arg0,arg1,arg2);
	fprintf(fLogFile, "[TRACE] wintab32.WTOpenW Returned (%p)\n",retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTGetW(HCTX arg0, LPLOGCONTEXTW arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, LPLOGCONTEXTW);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTGetW"));
	fprintf(fLogFile, "[TRACE] wintab32.WTGetW((HCTX)%p,(LPLOGCONTEXTW)%p): forward\n",arg0,arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTGetW Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTSetW(HCTX arg0, LPLOGCONTEXTW arg1)
{
	BOOL (__stdcall *pFunc)(HCTX, LPLOGCONTEXTW);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTSetW"));
	fprintf(fLogFile, "[TRACE] wintab32.WTSetW((HCTX)%p,(LPLOGCONTEXTW)%p): forward\n",arg0,arg1);
	retVal = pFunc(arg0,arg1);
	fprintf(fLogFile, "[TRACE] wintab32.WTSetW Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" BOOL __stdcall WINTAB32_WTMgrConfigReplaceExW(HMGR arg0, BOOL arg1, LPWSTR arg2, LPSTR arg3)
{
	BOOL (__stdcall *pFunc)(HMGR, BOOL, LPWSTR, LPSTR);
	BOOL retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrConfigReplaceExW"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrConfigReplaceExW((HMGR)%p,(BOOL)%ld,(LPWSTR)%ls,(LPSTR)%s): forward\n",arg0,(LONG)arg1,arg2,arg3);
	retVal = pFunc(arg0,arg1,arg2,arg3);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrConfigReplaceExW Returned (%ld)\n",(LONG)retVal);
	return retVal;
}


extern "C" HWTHOOK __stdcall WINTAB32_WTMgrPacketHookExW(HMGR arg0, int arg1, LPWSTR arg2, LPSTR arg3)
{
	HWTHOOK (__stdcall *pFunc)(HMGR, int, LPWSTR, LPSTR);
	HWTHOOK retVal;
	pFunc=reinterpret_cast<decltype(pFunc)>(GetProcAddress(hDLL,"WTMgrPacketHookExW"));
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrPacketHookExW((HMGR)%p,(int)%ld,(LPWSTR)%ls,(LPSTR)%s): forward\n",arg0,(LONG)arg1,arg2,arg3);
	retVal = pFunc(arg0,arg1,arg2,arg3);
	fprintf(fLogFile, "[TRACE] wintab32.WTMgrPacketHookExW Returned (%p)\n",retVal);
	return retVal;
}

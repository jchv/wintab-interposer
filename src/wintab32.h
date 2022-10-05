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

#pragma once
#include <windows.h>

enum class WTInfoCategory {
    INTERFACE  = 1,
    STATUS     = 2,
    DEFCONTEXT = 3,
    DEFSYSCTX  = 4,
    DEVICES    = 100,
    CURSORS    = 200,
    EXTENSIONS = 300,
    DDCTXS     = 400,
    DSCTXS     = 500,
};

enum class WTInfoIntf {
    WINTABID      = 1,
    SPECVERSION   = 2,
    IMPLVERSION   = 3,
    NUMDEVICES    = 4,
    NUMCURSORS    = 5,
    NUMCONTEXTS   = 6,
    CTXOPTIONS    = 7,
    CTXSAVESIZE   = 8,
    NUMEXTENSIONS = 9,
    NUMMANAGERS   = 10,
};

enum class WTInfoState {
    CONTEXTS  = 1,
    SYSCTXS   = 2,
    PKTRATE   = 3,
    PKTDATA   = 4,
    MANAGERS  = 5,
    SYSTEM    = 6,
    BUTTONUSE = 7,
    SYSBTNUSE = 8,
};

enum class WTInfoCtx {
    NAME      =  1,
    OPTIONS   =  2,
    STATUS    =  3,
    LOCKS     =  4,
    MSGBASE   =  5,
    DEVICE    =  6,
    PKTRATE   =  7,
    PKTDATA   =  8,
    PKTMODE   =  9,
    MOVEMASK  = 10,
    BTNDNMASK = 11,
    BTNUPMASK = 12,
    INORGX    = 13,
    INORGY    = 14,
    INORGZ    = 15,
    INEXTX    = 16,
    INEXTY    = 17,
    INEXTZ    = 18,
    OUTORGX   = 19,
    OUTORGY   = 20,
    OUTORGZ   = 21,
    OUTEXTX   = 22,
    OUTEXTY   = 23,
    OUTEXTZ   = 24,
    SENSX     = 25,
    SENSY     = 26,
    SENSZ     = 27,
    SYSMODE   = 28,
    SYSORGX   = 29,
    SYSORGY   = 30,
    SYSEXTX   = 31,
    SYSEXTY   = 32,
    SYSSENSX  = 33,
    SYSSENSY  = 34,
};

enum class WTInfoDVC {
    NAME        = 1,
    HARDWARE    = 2,
    NCSRTYPES   = 3,
    FIRSTCSR    = 4,
    PKTRATE     = 5,
    PKTDATA     = 6,
    PKTMODE     = 7,
    CSRDATA     = 8,
    XMARGIN     = 9,
    YMARGIN     = 10,
    ZMARGIN     = 11,
    X           = 12,
    Y           = 13,
    Z           = 14,
    NPRESSURE   = 15,
    TPRESSURE   = 16,
    ORIENTATION = 17,
    ROTATION    = 18,
};

enum class WTInfoCSR {
    NAME         = 1,
    ACTIVE       = 2,
    PKTDATA      = 3,
    BUTTONS      = 4,
    BUTTONBITS   = 5,
    BTNNAMES     = 6,
    BUTTONMAP    = 7,
    SYSBTNMAP    = 8,
    NPBUTTON     = 9,
    NPBTNMARKS   = 10,
    NPRESPONSE   = 11,
    TPBUTTON     = 12,
    TPBTNMARKS   = 13,
    TPRESPONSE   = 14,
    PHYSID       = 15,
    MODE         = 16,
    MINPKTDATA   = 17,
    MINBUTTONS   = 18,
    CAPABILITIES = 19,
    TYPE         = 20,
};

enum class WTInfoExt {
    NAME       = 1,
    TAG        = 2,
    MASK       = 3,
    SIZE       = 4,
    AXES       = 5,
    DEFAULT    = 6,
    DEFCONTEXT = 7,
    DEFSYSCTX  = 8,
    CURSORS    = 9,
};

typedef HANDLE HMGR;
typedef HANDLE HCTX;
typedef HANDLE HWTHOOK;
typedef LPVOID LPLOGCONTEXTA;
typedef LPVOID LPLOGCONTEXTW;
typedef LPVOID WTENUMPROC;

extern "C" UINT __stdcall WINTAB32_WTInfoA(UINT arg0, UINT arg1, LPVOID arg2);
extern "C" HCTX __stdcall WINTAB32_WTOpenA(HWND arg0, LPLOGCONTEXTA arg1, BOOL arg2);
extern "C" BOOL __stdcall WINTAB32_WTClose(HCTX arg0);
extern "C" int __stdcall WINTAB32_WTPacketsGet(HCTX arg0, int arg1, LPVOID arg2);
extern "C" BOOL __stdcall WINTAB32_WTPacket(HCTX arg0, UINT arg1, LPVOID arg2);
extern "C" BOOL __stdcall WINTAB32_WTEnable(HCTX arg0, BOOL arg1);
extern "C" BOOL __stdcall WINTAB32_WTOverlap(HCTX arg0, BOOL arg1);
extern "C" BOOL __stdcall WINTAB32_WTConfig(HCTX arg0, HWND arg1);
extern "C" BOOL __stdcall WINTAB32_WTGetA(HCTX arg0, LPLOGCONTEXTA arg1);
extern "C" BOOL __stdcall WINTAB32_WTSetA(HCTX arg0, LPLOGCONTEXTA arg1);
extern "C" BOOL __stdcall WINTAB32_WTExtGet(HCTX arg0, UINT arg1, LPVOID arg2);
extern "C" BOOL __stdcall WINTAB32_WTExtSet(HCTX arg0, UINT arg1, LPVOID arg2);
extern "C" BOOL __stdcall WINTAB32_WTSave(HCTX arg0, LPVOID arg1);
extern "C" HCTX __stdcall WINTAB32_WTRestore(HWND arg0, LPVOID arg1, BOOL arg2);
extern "C" int __stdcall WINTAB32_WTPacketsPeek(HCTX arg0, int arg1, LPVOID arg2);
extern "C" int __stdcall WINTAB32_WTDataGet(HCTX arg0, UINT arg1, UINT arg2, int arg3, LPVOID arg4, LPINT arg5);
extern "C" int __stdcall WINTAB32_WTDataPeek(HCTX arg0, UINT arg1, UINT arg2, int arg3, LPVOID arg4, LPINT arg5);
extern "C" int __stdcall WINTAB32_WTQueueSizeGet(HCTX arg0);
extern "C" BOOL __stdcall WINTAB32_WTQueueSizeSet(HCTX arg0, int arg1);
extern "C" HMGR __stdcall WINTAB32_WTMgrOpen(HWND arg0, UINT arg1);
extern "C" BOOL __stdcall WINTAB32_WTMgrClose(HMGR arg0);
extern "C" BOOL __stdcall WINTAB32_WTMgrContextEnum(HMGR arg0, WTENUMPROC arg1, LPARAM arg2);
extern "C" HWND __stdcall WINTAB32_WTMgrContextOwner(HMGR arg0, HCTX arg1);
extern "C" HCTX __stdcall WINTAB32_WTMgrDefContext(HMGR arg0, BOOL arg1);
extern "C" UINT __stdcall WINTAB32_WTMgrDeviceConfig(HMGR arg0, UINT arg1, HWND arg2);
extern "C" BOOL __stdcall WINTAB32_WTMgrExt(HMGR arg0, UINT arg1, LPVOID arg2);
extern "C" BOOL __stdcall WINTAB32_WTMgrCsrEnable(HMGR arg0, UINT arg1, BOOL arg2);
extern "C" BOOL __stdcall WINTAB32_WTMgrCsrButtonMap(HMGR arg0, UINT arg1, LPBYTE arg2, LPBYTE arg3);
extern "C" BOOL __stdcall WINTAB32_WTMgrCsrPressureBtnMarks(HMGR arg0, UINT arg1, DWORD arg2, DWORD arg3);
extern "C" BOOL __stdcall WINTAB32_WTMgrCsrPressureResponse(HMGR arg0, UINT arg1, UINT * arg2, UINT * arg3);
extern "C" BOOL __stdcall WINTAB32_WTMgrCsrExt(HMGR arg0, UINT arg1, UINT arg2, LPVOID arg3);
extern "C" BOOL __stdcall WINTAB32_WTQueuePacketsEx(HCTX arg0, UINT * arg1, UINT * arg2);
extern "C" BOOL __stdcall WINTAB32_WTMgrCsrPressureBtnMarksEx(HMGR arg0, UINT arg1, UINT * arg2, UINT * arg3);
extern "C" BOOL __stdcall WINTAB32_WTMgrConfigReplaceExA(HMGR arg0, BOOL arg1, LPSTR arg2, LPSTR arg3);
extern "C" HWTHOOK __stdcall WINTAB32_WTMgrPacketHookExA(HMGR arg0, int arg1, LPSTR arg2, LPSTR arg3);
extern "C" BOOL __stdcall WINTAB32_WTMgrPacketUnhook(HWTHOOK arg0);
extern "C" LRESULT __stdcall WINTAB32_WTMgrPacketHookNext(HWTHOOK arg0, int arg1, WPARAM arg2, LPARAM arg3);
extern "C" HCTX __stdcall WINTAB32_WTMgrDefContextEx(HMGR arg0, UINT arg1, BOOL arg2);
extern "C" UINT __stdcall WINTAB32_WTInfoW(UINT arg0, UINT arg1, LPVOID arg2);
extern "C" HCTX __stdcall WINTAB32_WTOpenW(HWND arg0, LPLOGCONTEXTW arg1, BOOL arg2);
extern "C" BOOL __stdcall WINTAB32_WTGetW(HCTX arg0, LPLOGCONTEXTW arg1);
extern "C" BOOL __stdcall WINTAB32_WTSetW(HCTX arg0, LPLOGCONTEXTW arg1);
extern "C" BOOL __stdcall WINTAB32_WTMgrConfigReplaceExW(HMGR arg0, BOOL arg1, LPWSTR arg2, LPSTR arg3);
extern "C" HWTHOOK __stdcall WINTAB32_WTMgrPacketHookExW(HMGR arg0, int arg1, LPWSTR arg2, LPSTR arg3);

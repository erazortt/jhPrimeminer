#ifndef __JHSYSTEMLIB
#define __JHSYSTEMLIB

#ifdef _WIN32
#define NOMINMAX
#include<Windows.h>
#else
#include <signal.h>
#include <stdint.h>
#endif
#include <cstring> // for memcpy/memset
#include<math.h>
#include <algorithm>

#ifdef _WIN32
typedef __int64           sint64;
typedef unsigned __int64  uint64;
typedef __int32           sint32;
typedef unsigned __int32  uint32;
typedef __int16           sint16;
typedef unsigned __int16  uint16;
typedef __int8            sint8;
typedef unsigned __int8   uint8;
#else
using std::min;
using std::max;

typedef int64_t sint64;
typedef uint64_t uint64;
typedef int32_t sint32;
typedef uint32_t uint32;
typedef int16_t sint16;
typedef uint16_t uint16;
typedef int8_t sint8;
typedef uint8_t uint8;

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stdint.h>

inline unsigned long long GetTickCount64()
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
  return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}
inline unsigned int GetTickCount()
{
  return (unsigned int)GetTickCount64();
}

#ifndef _fastcall
#define _fastcall __attribute__((fastcall))
#endif
#ifndef __fastcall
#define __fastcall __attribute__((fastcall))
#endif
#ifndef _stdcall
#define _stdcall __attribute__((stdcall))
#endif
#ifndef __stdcall
#define __stdcall __attribute__((stdcall))
#endif
#ifndef _cdecl
#define _cdecl __attribute__((cdecl))
#endif
#ifndef __cdecl
#define __cdecl __attribute__((cdecl))
#endif
#ifndef __declspec
#define __declspec(e) __attribute__((e))
#endif
#ifndef _declspec
#define _declspec(e) __attribute__((e))
#endif
#ifndef __debugbreak
#define __debugbreak(x) raise(SIGTRAP)
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif
#ifndef ADDR_ANY
#define ADDR_ANY INADDR_ANY
#endif

#define Sleep(ms) usleep(1000*ms)
#define closesocket(x) close(x)
#define __debugbreak(x) raise(SIGTRAP)
#define RtlCopyMemory memcpy
#define RtlZeroMemory(o, s) memset(o,0,s)
#define EnterCriticalSection pthread_mutex_lock
#define LeaveCriticalSection pthread_mutex_unlock
#define _ADDRESSOF(v) (&reinterpret_cast<const char &>(v))
#define OutputDebugString(x) printf("%s", (x))
#define _strdup strdup
#define ExitProcess exit
#define _getch getchar
#define __try try
#define __except(x) catch(...)
#define SetThreadPriority(h, p) (void)0
#define SetPriorityClass(h, p) (void)0

typedef uint8_t BYTE;
typedef uint32_t DWORD;
typedef bool BOOL;
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef fd_set FD_SET;
typedef pthread_mutex_t CRITICAL_SECTION;

#define HANDLE pthread_t
#define LPVOID void*
#define TerminateThread(h, x) pthread_cancel(x)
#define CloseHandle(x) {}
typedef void* (*LPTHREAD_START_ROUTINE)(void* lpThreadParameter);
inline HANDLE CreateThread(LPVOID, size_t stackSize, LPTHREAD_START_ROUTINE a3, LPVOID params, DWORD dwFlags, DWORD* pdwThreadID)
{
  HANDLE threadId;
  pthread_create(&threadId, nullptr, a3, params);
  pthread_attr_t threadAttr;
  pthread_attr_init(&threadAttr);
  // Set the stack size of the thread
  pthread_attr_setstacksize(&threadAttr, 120*1024);
  // free resources of thread upon return
  pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
  return threadId;
}

#endif


#define JHCALLBACK	__fastcall

void* _ex1_malloc(int size);
void* _ex1_realloc(void* old, int size);
void _ex1_free(void* p);

void _ex2_initialize();

void* _ex2_malloc(int size, char* file, sint32 line);
void* _ex2_realloc(void* old, int size, char* file, sint32 line);
void _ex2_free(void* p, char* file, sint32 line);
void _ex2_analyzeMemoryLog();

// memory validator
//#define malloc(x) _ex1_malloc(x)
//#define realloc(x,y) _ex1_realloc(x,y)
//#define free(x) _ex1_free(x)

// memory logger
//#define MEMORY_LOGGER_ACTIVE			1
//#define MEMORY_LOGGER_ANALYZE_ACTIVE	1

#ifdef MEMORY_LOGGER_ACTIVE
#define malloc(x) _ex2_malloc(x,__FILE__,__LINE__)
#define realloc(x,y) _ex2_realloc(x,y,__FILE__,__LINE__)
#define free(x) _ex2_free(x,__FILE__,__LINE__)
#endif

#include"streamWrapper.h"
#include"fastString.h"
#include"hashTable.h"
#include"fastSorter.h"
#include"fileMgr.h"
#include"bmp.h"
#include"tgaLib.h"
#include"packetBuffer.h"
#include"msgQueue.h"
#include"simpleList.h"
#include"customBuffer.h"
#include"fMath.h"
#include"sData.h"


/* error */
#define assertFatal(condition, message, errorCode) if( condition ) { OutputDebugString(message);  ExitProcess(errorCode); } 


#endif

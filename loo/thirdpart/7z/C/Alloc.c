/* Alloc.c -- Memory allocation functions
2008-09-24
Igor Pavlov
Public domain */

#ifdef _WIN32
#include <windows.h>
#endif
#include <stdlib.h>

#include "Alloc.h"

/* #define _SZ_ALLOC_DEBUG */

/* use _SZ_ALLOC_DEBUG to debug alloc/free operations */
#ifdef _SZ_ALLOC_DEBUG
#include <stdio.h>
int g_allocCount = 0;
int g_allocCountMid = 0;
int g_allocCountBig = 0;
#endif

void *MyAlloc(size_t size)
{
  if (size == 0)
    return 0;
  #ifdef _SZ_ALLOC_DEBUG
  {
    void *p = malloc(size);
    fprintf(stderr, "\nAlloc %10d bytes, count = %10d,  addr = %8X", size, g_allocCount++, (unsigned)p);
    return p;
  }
  #else
  return malloc(size);
  #endif
}

void MyFree(void *address)
{
  #ifdef _SZ_ALLOC_DEBUG
  if (address != 0)
    fprintf(stderr, "\nFree; count = %10d,  addr = %8X", --g_allocCount, (unsigned)address);
  #endif
  free(address);
}

#ifdef _WIN32

void *MidAlloc(size_t size)
{
  if (size == 0)
    return 0;
  #ifdef _SZ_ALLOC_DEBUG
  fprintf(stderr, "\nAlloc_Mid %10d bytes;  count = %10d", size, g_allocCountMid++);
  #endif
#if defined(WINAPI_FAMILY) && ((WINAPI_FAMILY == WINAPI_FAMILY_APP) || (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP))
  return malloc(size);
#else
  return VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
#endif
}

void MidFree(void *address)
{
  #ifdef _SZ_ALLOC_DEBUG
  if (address != 0)
    fprintf(stderr, "\nFree_Mid; count = %10d", --g_allocCountMid);
  #endif
  if (address == 0)
    return;
#if defined(WINAPI_FAMILY) && ((WINAPI_FAMILY == WINAPI_FAMILY_APP) || (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP))
  free(address);
#else
  VirtualFree(address, 0, MEM_RELEASE);
#endif
}

#ifndef MEM_LARGE_PAGES
#undef _7ZIP_LARGE_PAGES
#endif

#ifdef _7ZIP_LARGE_PAGES
SIZE_T g_LargePageSize = 0;
typedef SIZE_T (WINAPI *GetLargePageMinimumP)();
#endif

void SetLargePageSize()
{
#if defined(WINAPI_FAMILY) && ((WINAPI_FAMILY == WINAPI_FAMILY_APP) || (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP))
#else
  #ifdef _7ZIP_LARGE_PAGES
  SIZE_T size = 0;
  GetLargePageMinimumP largePageMinimum = (GetLargePageMinimumP)
        GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetLargePageMinimum");
  if (largePageMinimum == 0)
    return;
  size = largePageMinimum();
  if (size == 0 || (size & (size - 1)) != 0)
    return;
  g_LargePageSize = size;
  #endif
#endif
}


void *BigAlloc(size_t size)
{
  if (size == 0)
    return 0;
  #ifdef _SZ_ALLOC_DEBUG
  fprintf(stderr, "\nAlloc_Big %10d bytes;  count = %10d", size, g_allocCountBig++);
  #endif
  
  #ifdef _7ZIP_LARGE_PAGES
  if (g_LargePageSize != 0 && g_LargePageSize <= (1 << 30) && size >= (1 << 18))
  {
#if defined(WINAPI_FAMILY) && ((WINAPI_FAMILY == WINAPI_FAMILY_APP) || (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP))
    void *res = malloc((size + g_LargePageSize - 1) & (~(g_LargePageSize - 1)));
#else
    void *res = VirtualAlloc(0, (size + g_LargePageSize - 1) & (~(g_LargePageSize - 1)),
        MEM_COMMIT | MEM_LARGE_PAGES, PAGE_READWRITE);
#endif
    if (res != 0)
      return res;
  }
  #endif
#if defined(WINAPI_FAMILY) && ((WINAPI_FAMILY == WINAPI_FAMILY_APP) || (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP))
  return malloc(size);
#else
  return VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
#endif
}

void BigFree(void *address)
{
  #ifdef _SZ_ALLOC_DEBUG
  if (address != 0)
    fprintf(stderr, "\nFree_Big; count = %10d", --g_allocCountBig);
  #endif
  
  if (address == 0)
    return;
#if defined(WINAPI_FAMILY) && ((WINAPI_FAMILY == WINAPI_FAMILY_APP) || (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP))
  free(address);
#else
  VirtualFree(address, 0, MEM_RELEASE);
#endif
}

#endif

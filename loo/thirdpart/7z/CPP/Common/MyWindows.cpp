// MyWindows.cpp

#include "StdAfx.h"

#include "MyWindows.h"

#ifndef IS_WINDOWS_DESKTOP
#include "Types.h"
#include <stdlib.h>

static inline void *AllocateForBSTR(size_t cb) { return ::malloc(cb); }
static inline void FreeForBSTR(void *pv) { ::free(pv);}

static UINT MyStringLen(const wchar_t *s)
{
  UINT i;
  for (i = 0; s[i] != '\0'; i++);
  return i;
}

STDAPI_(BSTR) SysAllocStringByteLen(LPCSTR psz, UINT len)
{
  int realLen = len + sizeof(UINT) + sizeof(OLECHAR) + sizeof(OLECHAR);
  void *p = AllocateForBSTR(realLen);
  if (p == 0)
    return 0;
  *(UINT *)p = len;
  BSTR bstr = (BSTR)((UINT *)p + 1);
  memmove(bstr, psz, len);
  Byte *pb = ((Byte *)bstr) + len;
  for (int i = 0; i < sizeof(OLECHAR) * 2; i++)
    pb[i] = 0;
  return bstr;
}

STDAPI_(BSTR) SysAllocString(const OLECHAR *sz)
{
  if (sz == 0)
    return 0;
  UINT strLen = MyStringLen(sz);
  UINT len = (strLen + 1) * sizeof(OLECHAR);
  void *p = AllocateForBSTR(len + sizeof(UINT));
  if (p == 0)
    return 0;
  *(UINT *)p = strLen;
  BSTR bstr = (BSTR)((UINT *)p + 1);
  memmove(bstr, sz, len);
  return bstr;
}

STDAPI_(void) SysFreeString(BSTR bstr)
{
  if (bstr != 0)
    FreeForBSTR((UINT *)bstr - 1);
}

STDAPI_(UINT) SysStringByteLen(BSTR bstr)
{
  if (bstr == 0)
    return 0;
  return *((UINT *)bstr - 1);
}

STDAPI_(UINT) SysStringLen(BSTR bstr)
{
  return SysStringByteLen(bstr) / sizeof(OLECHAR);
}

STDAPI_(HRESULT) VariantClear(VARIANTARG *prop)
{
  if (prop->vt == VT_BSTR)
    SysFreeString(prop->bstrVal);
  prop->vt = VT_EMPTY;
  return S_OK;
}

STDAPI_(HRESULT) VariantCopy(VARIANTARG *dest, const VARIANTARG *src)
{
  HRESULT res = ::VariantClear(dest);
  if (res != S_OK)
    return res;
  if (src->vt == VT_BSTR)
  {
    dest->bstrVal = SysAllocStringByteLen((LPCSTR)src->bstrVal,
        SysStringByteLen(src->bstrVal));
    if (dest->bstrVal == 0)
      return E_OUTOFMEMORY;
    dest->vt = VT_BSTR;
  }
  else
    *dest = *src;
  return S_OK;
}

STDAPI_(LONG) CompareFileTime(const FILETIME* ft1, const FILETIME* ft2)
{
  if (ft1->dwHighDateTime < ft2->dwHighDateTime) return -1;
  if (ft1->dwHighDateTime > ft2->dwHighDateTime) return 1;
  if (ft1->dwLowDateTime < ft2->dwLowDateTime) return -1;
  if (ft1->dwLowDateTime > ft2->dwLowDateTime) return 1;
  return 0;
}

#ifndef _WIN32
STDAPI_(DWORD) GetLastError()
{
  return 0;
}
#endif

#endif

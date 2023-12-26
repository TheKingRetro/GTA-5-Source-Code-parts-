#pragma once

#ifndef IMEM_H
#define IMEM_H

#include "stdafx.h"

typedef unsigned short ushort;
typedef unsigned int uint;
typedef uintptr_t QWORD;

#ifdef _WIN64
	#define PTRMAXVAL ((PVOID)0x000F000000000000)
#else
	#define PTRMAXVAL ((PVOID)0xFFF00000)
#endif

class Mem
{
public:

	template <class vType>
	static vType Read(DWORD64 Add)
	{
		__try
		{
			return *(vType*)(Add);
		}
		__except (InternalErrorHandler(GetExceptionCode(), GetExceptionInformation()))
		{
			return vType();
		}
	}

	static std::string ReadString(DWORD64 Add, size_t strLength)
	{
		char szString[512] = { 0 };
		for (size_t i = 0; i < strLength; i++)
		{
			char tChar;
			tChar = *(char*)(Add + (i * 0x1));
			szString[i] = tChar;
		}
		return szString;
	}

	template <class vType>
	static vType ReadPtr(DWORD64 Add, DWORD64 o1, DWORD64 o2, DWORD64 o3, DWORD64 o4, DWORD64 o5, DWORD64 o6)
	{
		__try
		{
			DWORD64* ptr1 = (DWORD64*)(Add + o1);
			if (IsValid(ptr1))
			{
				DWORD64* ptr2 = (DWORD64*)(*ptr1 + o2);
				if (IsValid(ptr2))
				{
					DWORD64* ptr3 = (DWORD64*)(*ptr2 + o3);
					if (IsValid(ptr3))
					{
						DWORD64* ptr4 = (DWORD64*)(*ptr3 + o4);
						if (IsValid(ptr4))
						{
							DWORD64* ptr5 = (DWORD64*)(*ptr4 + o5);
							if (IsValid(ptr5))
							{
								return *(vType*)(*ptr5 + o6);
							}
						}
					}
				}
			}
		}
		__except (InternalErrorHandler(GetExceptionCode(), GetExceptionInformation()))
		{
			return vType();
		}
	}

	template <class vType>
	static vType ReadPtr(DWORD64 Add, DWORD64 o1, DWORD64 o2, DWORD64 o3, DWORD64 o4, DWORD64 o5)
	{
		__try
		{
			DWORD64* ptr1 = (DWORD64*)(Add + o1);
			if (IsValid(ptr1))
			{
				DWORD64* ptr2 = (DWORD64*)(*ptr1 + o2);
				if (IsValid(ptr2))
				{
					DWORD64* ptr3 = (DWORD64*)(*ptr2 + o3);
					if (IsValid(ptr3))
					{
						DWORD64* ptr4 = (DWORD64*)(*ptr3 + o4);
						if (IsValid(ptr4))
						{
							return *(vType*)(*ptr4 + o5);
						}
					}
				}
			}
		}
		__except (InternalErrorHandler(GetExceptionCode(), GetExceptionInformation()))
		{
			return vType();
		}
	}

	template <class vType>
	static vType ReadPtr(DWORD64 Add, DWORD64 o1, DWORD64 o2, DWORD64 o3, DWORD64 o4)
	{
		__try
		{
			DWORD64* ptr1 = (DWORD64*)(Add + o1);
			if (IsValid(ptr1))
			{
				DWORD64* ptr2 = (DWORD64*)(*ptr1 + o2);
				if (IsValid(ptr2))
				{
					DWORD64* ptr3 = (DWORD64*)(*ptr2 + o3);
					if (IsValid(ptr3))
					{
						return *(vType*)(*ptr3 + o4);
					}
				}
			}
		}
		__except (InternalErrorHandler(GetExceptionCode(), GetExceptionInformation()))
		{
			return vType();
		}
	}

	template <class vType>
	static vType ReadPtr(DWORD64 Add, DWORD64 o1, DWORD64 o2, DWORD64 o3)
	{
		__try
		{
			DWORD64* ptr1 = (DWORD64*)(Add + o1);
			if (IsValid(ptr1))
			{
				DWORD64* ptr2 = (DWORD64*)(*ptr1 + o2);
				if (IsValid(ptr2))
				{
					return *(vType*)(*ptr2 + o3);
				}
			}
		}
		__except (InternalErrorHandler(GetExceptionCode(), GetExceptionInformation()))
		{
			return vType();
		}
	}

	template <class vType>
	static vType ReadPtr(DWORD64 Add, DWORD64 o1, DWORD64 o2)
	{
		__try
		{
			DWORD64* ptr1 = (DWORD64*)(Add + o1);
			if (IsValid(ptr1))
			{
				return *(vType*)(*ptr1 + o2);
			}
		}
		__except (InternalErrorHandler(GetExceptionCode(), GetExceptionInformation()))
		{
			return vType();
		}
	}

	template <class vType>
	static vType ReadPtr(DWORD64 Add, DWORD64 o1)
	{
		__try
		{
			DWORD64* ptr1 = (DWORD64*)(Add);
			if (IsValid(ptr1))
			{
				return *(vType*)(*ptr1 + o1);
			}
		}
		__except (InternalErrorHandler(GetExceptionCode(), GetExceptionInformation()))
		{
			return vType();
		}
	}

	template <class vType>
	static BOOLEAN Write(DWORD64 address, vType value)
	{
		__try
		{
			*(vType*)address = value;
		}
		__except (InternalErrorHandler(GetExceptionCode(), GetExceptionInformation()))
		{
			return FALSE;
		}
		return TRUE;
	}

	static int InternalErrorHandler(unsigned int Code, struct _EXCEPTION_POINTERS* EP)
	{
		return (Code == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH;
	}

	static __forceinline BOOLEAN IsValid(PVOID ptr)
	{ 
		return (ptr >= (PVOID)0x10000) && (ptr < PTRMAXVAL) && ptr != nullptr;
	}

	static DWORD64 GetBase()
	{
		return (DWORD64)GetModuleHandle(NULL);
	}

};


#endif
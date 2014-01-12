/**
* commontype.h
* this file define the Rainbow2 project 's type
*
* @version 1.0 (8 12, 2009)
* @author ken
*
*/
#pragma once

#include <utility>

typedef signed __int64 int64;
typedef signed int int32;
typedef signed short int16;
typedef signed char int8;

typedef unsigned __int64 uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef unsigned char byte;
typedef unsigned long       ulong;

typedef std::pair<std::size_t,byte*> ByteBuf;

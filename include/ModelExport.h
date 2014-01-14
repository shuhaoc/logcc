#pragma once

// 静态链接取消此宏定义
#define MODEL_DYNAMIC_LINK

#ifdef MODEL_DYNAMIC_LINK

#ifdef MODEL_EXPORTS

#define MODEL_EXPORT __declspec(dllexport)

#else

#define MODEL_EXPORT __declspec(dllimport)

#endif

#else

#define MODEL_EXPORT

#endif

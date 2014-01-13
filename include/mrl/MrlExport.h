#pragma once

// 静态链接取消此宏定义
#define MRL_DYNAMIC_LINK

#ifdef MRL_DYNAMIC_LINK

#ifdef MRL_EXPORTS

#define MRL_EXPORT __declspec(dllexport)

#else

#define MRL_EXPORT __declspec(dllimport)

#endif

#else

#define MRL_EXPORT

#endif
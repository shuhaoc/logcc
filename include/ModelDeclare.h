#pragma once

// ��̬����ȡ���˺궨��
#define MODEL_DYNAMIC_LINK

#ifdef MODEL_DYNAMIC_LINK

#ifdef MODEL_EXPORTS

#define MODEL_INTERFACE __declspec(dllexport)

#else

#define MODEL_INTERFACE __declspec(dllimport)

#endif

#else

#define MODEL_INTERFACE

#endif
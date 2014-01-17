#pragma once

#ifndef MRL_STATIC_LINK

#ifdef MRL_EXPORTS

#define MRL_EXPORT __declspec(dllexport)

#else

#define MRL_EXPORT __declspec(dllimport)

#endif

#else

#define MRL_EXPORT

#endif
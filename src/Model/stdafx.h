﻿// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>



// TODO: 在此处引用程序需要的其他头文件

#include <tchar.h>

#include <vector>
#include <fstream>
#include <functional>
#include <algorithm>
#include <hash_map>
#include <exception>
#include <sstream>
#include <cassert>

using namespace std;

#include <boost/utility.hpp>
#include <boost/thread.hpp>

#include <common/tstring.h>
#include <common/singleton_support.h>
#include <common/observer_list.h>
#include <common/utility/debug_info.h>
#include <common/utility/code_conv.h>
#include <common/utility/wm_task_handler.h>

using common::tstring;

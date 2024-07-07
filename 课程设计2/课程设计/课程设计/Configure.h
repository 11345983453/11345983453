

#pragma once//这是一种防止头文件被多次包含的方式，确保头文件只会被编译一次。这可以避免重复定义和多次包含同一个头文件的问题。

#ifdef UNICODE//检查是否定义了 UNICODE 宏
#undef UNICODE//如果定义了 UNICODE，则通过 #undef UNICODE 取消定义它。确保不使用 Unicode 字符集，可能是为了避免与非 Unicode 函数或库发生冲突。
#endif // UNICODE



#include<easyx.h>
#include<string>

#include <conio.h>//用于处理键盘输入。 
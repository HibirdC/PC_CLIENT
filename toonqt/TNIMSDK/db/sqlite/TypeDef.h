//
//  TypeDef.h
//  sqlite3
//
//  Created by 王旭影 on 17/8/22.
//  Copyright © 2017年 思源. All rights reserved.
//

#ifndef TypeDef_h
#define TypeDef_h

#ifdef __WIN32
#define __WIN_TYPES 1
#else

#ifdef __WIN64
#define __WIN_TYPES 1
#else

#define __POSIX_TYPES 1

#endif
#endif

#ifdef __POSIX_TYPES
#include <sys/types.h>
typedef long long INT64;
#else
typedef __int64 INT64;
#endif

#endif /* TypeDef_h */

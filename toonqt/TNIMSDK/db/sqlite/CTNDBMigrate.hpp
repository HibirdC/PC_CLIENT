//
//  CTNDBMigrate.hpp
//  tnimsdk
//
//  Created by 王旭影 on 2017/12/29.
//  Copyright © 2017年 syswin. All rights reserved.
//

#ifndef CTNDBMigrate_hpp
#define CTNDBMigrate_hpp

#include <stdio.h>
#include "sqlite3.h"

#ifdef __APPLE__
namespace toonim {
    void getAtMeMsgId(sqlite3_context *context, int argc, sqlite3_value **argv);
    void calcUnReadCount(sqlite3_context *context, int argc, sqlite3_value **argv);
    void extractContent(sqlite3_context *context, int argc, sqlite3_value **argv);
    void supplyContent(sqlite3_context *context, int argc, sqlite3_value **argv);
    void chatFileSize(sqlite3_context *context, int argc, sqlite3_value **argv);
    void lastMsgToJson(sqlite3_context *context, int argc, sqlite3_value **argv);
    void getLocalMaxSeq(sqlite3_context *context, int argc, sqlite3_value **argv);
    void generatSessionId(sqlite3_context *context, int argc, sqlite3_value **argv);
}
#endif

#endif /* CSqliteDBMigrate_hpp */

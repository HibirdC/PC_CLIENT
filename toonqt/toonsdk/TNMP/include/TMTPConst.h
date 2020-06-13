//
//  TNMPConst.h
//  TNMP
//
//  Created by 兰怀玉 on 16/4/15.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#ifndef TMTPConst_h
#define TMTPConst_h

//网络协议
//TNMPNetConnected此状态可以自动重连
//TNMPNetLogout此状态不能自动重连,自己退出或者被踢掉
typedef enum  _TNMPNetStatus{
    TNMPNetNone = 0,
    TNMPNetConnecting = 1,
    TNMPNetConnected = 2,
    TNMPNetLogout =  3,
    TNMPNetRecving = 4
} TNMPNetStatus;


#define DEVICE_TYPE_IOS      1
#define DEVICE_TYPE_ANDROID  2
#define DEVICE_TYPE_WINDOWS  3
#define DEVICE_TYPE_MAC      4


#ifdef WIN32
#include <stdint.h>
//#include <windows.h>

#define tn_msleep(t)   Sleep(t)

#else
#include <unistd.h>

#define tn_msleep(t)   usleep(t*1000)

#endif






#endif /* TNMPConst_h */

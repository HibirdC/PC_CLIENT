#include "mac_getwindowrects.h"
#include <Cocoa/Cocoa.h>
#include <QDebug>
#include <string>
Mac_getWindowRects::Mac_getWindowRects()
{

}

Mac_getWindowRects::~Mac_getWindowRects()
{

}

QList<QRect> Mac_getWindowRects::getWindowList()
{
    QList<QRect> all_open_windows;
    CFArrayRef all_window = CGWindowListCopyWindowInfo(
                            kCGWindowListOptionOnScreenOnly | kCGWindowListExcludeDesktopElements,
                            kCGNullWindowID);
    for (CFIndex i=0;i<CFArrayGetCount(all_window);i++){
            CFDictionaryRef temp = (CFDictionaryRef)CFArrayGetValueAtIndex(all_window, i);
            CGRect rect;
            int int_window_id,int_window_layer;
            CFNumberRef window_layer = (CFNumberRef)CFDictionaryGetValue(temp,kCGWindowLayer);
            CFNumberGetValue(window_layer,kCGWindowIDCFNumberType,&int_window_layer);
            CFStringRef cf_name = (CFStringRef)CFDictionaryGetValue(temp,kCGWindowName);
            std::string std_name;
            if(cf_name != NULL){
                std_name = [(NSString*)cf_name UTF8String];
            }
            QRect q_rect;
            if(CGRectMakeWithDictionaryRepresentation((CFDictionaryRef)CFDictionaryGetValue(temp,kCGWindowBounds),&rect)
                   ){
                    q_rect.setX(rect.origin.x);
                    q_rect.setY(rect.origin.y);
                    q_rect.setWidth(rect.size.width);
                    q_rect.setHeight(rect.size.height);
            }
            if(int_window_layer >= 0 && int_window_layer <= 25 && std_name != "Dock"){
                all_open_windows.push_back(q_rect);
            }
            CFNumberRef window_id = (CFNumberRef)CFDictionaryGetValue(temp,kCGWindowNumber);
            CFNumberGetValue(window_id,kCGWindowIDCFNumberType,&int_window_id);
            qDebug() << "window_id" << int_window_id << "window_layer:" << int_window_layer << "window size:"
                     << q_rect << "wind_name:" << std_name.c_str();
            CFRelease(window_id);
            CFRelease(window_layer);
            CFRelease(temp);
    }
    /*
    NSMutableArray *windows = (__bridge NSMutableArray *)CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly | kCGWindowListExcludeDesktopElements, kCGNullWindowID);
    for (NSDictionary *window in windows) {
        //NSString *name = [window objectForKey:@"kCGWindowName" ];
        CGRect bounds;
        CGRectMakeWithDictionaryRepresentation((CFDictionaryRef)[window objectForKey:@"kCGWindowBounds"], &bounds);
        //NSLog(@"%@: %@",name,NSStringFromRect(bounds));
        QRect q_rect;
        q_rect.setX(bounds.origin.x);
        q_rect.setY(bounds.origin.y);
        q_rect.setWidth(bounds.size.width);
        q_rect.setHeight(bounds.size.height);
        all_open_windows.append(q_rect);
    }
    */
    return all_open_windows;
}

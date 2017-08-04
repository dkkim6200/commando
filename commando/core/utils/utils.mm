#include "main.h"

#import <Foundation/Foundation.h>

string randString(int length) {
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

string getPathToFile(string fileName, string fileExt) {
//    CFBundleRef mainBundle = CFBundleGetMainBundle();
//    CFURLRef    urlToReturn;
//    
//    // Look for a resource in the main bundle by name and type.
//    urlToReturn = CFBundleCopyResourceURL( mainBundle, CFStringCreateWithCString(NULL, fileName.c_str(), kCFStringEncodingUTF8), CFStringCreateWithCString(NULL, fileExt.c_str(), kCFStringEncodingUTF8), NULL );
//    
//    string strToReturn = CFStringGetCStringPtr(CFURLGetString(urlToReturn),kCFStringEncodingUTF8);
//    strToReturn = strToReturn.substr(7, strToReturn.size());
//    
//    return strToReturn;
    
    return [[[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:fileName.c_str()] ofType:[NSString stringWithUTF8String:fileExt.c_str()]] UTF8String];
}
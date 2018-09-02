#import <Foundation/Foundation.h>
#import <Flutter/Flutter.h>

@interface FLTCppPlugin : NSObject

+ (void)initPlugin:(NSObject<FlutterBinaryMessenger>*) messenger;

@end

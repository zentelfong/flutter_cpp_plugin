#import <Foundation/Foundation.h>
#import <Flutter/Flutter.h>

@interface FLTCppPlugin : NSObject

+ (FLTCppPlugin *) getInstance;

- (void)initPlugin:(FlutterBinaryMessenger*) messenger;

@end

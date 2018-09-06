#import <Foundation/Foundation.h>
#import <Flutter/Flutter.h>

@interface FLTCppPlugin : NSObject
//注册插件
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar> *)registrar;
@end

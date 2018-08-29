// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import "DeviceInfoPlugin.h"
#import <sys/utsname.h>

@implementation FLTCppPlugin
{
  FlutterBinaryMessenger* messenger;
}

static FLTCppPlugin* instance = nil;

+(FLTCppPlugin *) getInstance{
  if (instance == nil) {
      instance = [[FLTCppPlugin alloc] init];//调用自己改写的”私有构造函数“
  }
  return instance;
}

- (void)initPlugin:(FlutterBinaryMessenger*) messenger{



}

@end

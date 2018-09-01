#import "CppPlugin.h"
#include "plugin_manager.h"
#include <stdio.h>

@implementation FLTCppPlugin
{
  FlutterBinaryMessenger* messenger;
}

static FLTCppPlugin* instance = nil;

+(FLTCppPlugin *) getInstance{
  if (instance == nil) {
      instance = [[FLTCppPlugin alloc] init];
  }
  return instance;
}

- (void)initPlugin:(FlutterBinaryMessenger*) messenger{
  _messenger=messenger;
  plugin_main();
}

- (FlutterBinaryMessenger*)getMessenger{
  return _messenger;
}
@end



namespace cpp_plugin
{

class MethodResultIos:public MethodResult
{
public:
  MethodResultIos(Plugin* plugin,FlutterBinaryReply reply)
    :m_plugin(plugin),m_reply(reply)
  {
  }

  virtual void SuccessInternal(const void *result)
  {
      std::unique_ptr<std::vector<uint8_t>> data = m_plugin->GetCodec().EncodeSuccessEnvelope(result);
      Reply(data->data(),data->size());
  }

  virtual void ErrorInternal(const std::string &error_code,
                          const std::string &error_message,
                          const void *error_details)
  {
      std::unique_ptr<std::vector<uint8_t>> data = m_plugin->GetCodec().EncodeErrorEnvelope(
                                  error_code,error_message,error_details);
      Reply(data->data(),data->size());
  }

  virtual void NotImplementedInternal()
  {
      Reply(NULL,0);
  }

  void Reply(const uint8_t* data,size_t len)
  {
    NSData* nsdata=null;
    if(data)
    {
      nsdata = [NSData dataWithBytes:data length:len];
    }
    m_reply(nsdata);
  }

private:
  Plugin* m_plugin;
  FlutterBinaryReply m_reply
};



PluginManagerIos* s_manager=NULL;

class PluginManagerIos:public PluginManager
{
public:
  PluginManagerIos()
  {

  }

  virtual void RegisterPlugin(Plugin* plugin)
  {
    PluginManager::RegisterPlugin(plugin);

    FlutterBinaryMessenger* messenger = [[FLTCppPlugin getInstance] getMessenger];
    if(!messenger)
    {
      printf("FLTCppPlugin not inited");
      return;
    }
    std::string channel = plugin->channel();
    NSString *nschannel= [NSString stringWithCString:channel.c_str() encoding:NSUTF8StringEncoding];


    FlutterBinaryMessageHandler handler=^(NSData* _Nullable message, FlutterBinaryReply reply){

      std::unique_ptr<MethodResult> method_result = std::make_unique<MethodResultIos>(plugin,reply);
      PluginManager::Instance()->HandleMethodCall(channel,[message bytes],message->length,std::move(method_result));
    };
    [messenger setMessageHandlerOnChannel:nschannel binaryMessageHandler:handler];
  }

  virtual void UnRegisterPlugin(Plugin* plugin)
  {
    PluginManager::UnRegisterPlugin(plugin);
    FlutterBinaryMessenger* messenger = [[FLTCppPlugin getInstance] getMessenger];
    if(!messenger)
    {
      printf("FLTCppPlugin not inited");
      return;
    }
    std::string channel = plugin->channel();
    NSString *nschannel= [NSString stringWithCString:channel.c_str() encoding:NSUTF8StringEncoding];   
    [messenger setMessageHandlerOnChannel:nschannel binaryMessageHandler:null];
  }

  virtual void InvokeMethodCall(const std::string &channel,const uint8_t* data,size_t len)
  {
    FlutterBinaryMessenger* messenger = [[FLTCppPlugin getInstance] getMessenger];
    if(!messenger)
    {
      printf("FLTCppPlugin not inited");
      return;
    }
    NSString *nschannel= [NSString stringWithCString:channel.c_str() encoding:NSUTF8StringEncoding];
    NSData *nsdata = null;
    if(data)
      nsdata = [NSData dataWithBytes:data length:len];
    [messenger sendOnChannel:nschannel message:nsdata];
  }

};

PluginManager* Instance()
{
  if(!s_manager)
  {
    s_manager=new PluginManagerIos();
  }
  return s_manager;
}


}//namespace


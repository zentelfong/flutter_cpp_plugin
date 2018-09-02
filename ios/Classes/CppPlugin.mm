#import "CppPlugin.h"
#include <plugin_manager.h>
#include <stdio.h>

@implementation FLTCppPlugin

static NSObject<FlutterBinaryMessenger> * sMessenger=nil;
static FLTCppPlugin* sInstance = nil;

+ (void)initPlugin:(NSObject<FlutterBinaryMessenger>*) messenger{
  sMessenger=messenger;
  plugin_main();
}

+ (NSObject<FlutterBinaryMessenger>*)getMessenger{
  return sMessenger;
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
    NSData* nsdata=NULL;
    if(data)
    {
      nsdata = [NSData dataWithBytes:data length:len];
    }
    m_reply(nsdata);
  }

private:
  Plugin* m_plugin;
  FlutterBinaryReply m_reply;
};



class PluginManagerIos* s_manager=NULL;

class PluginManagerIos:public PluginManager
{
public:
  PluginManagerIos()
  {

  }

  virtual void RegisterPlugin(Plugin* plugin)
  {
    PluginManager::RegisterPlugin(plugin);

    NSObject<FlutterBinaryMessenger>* messenger = [FLTCppPlugin getMessenger];
      
    if(!messenger)
    {
      printf("FLTCppPlugin not inited");
      return;
    }
    std::string channel = plugin->channel();
    NSString *nschannel= [NSString stringWithCString:channel.c_str() encoding:NSUTF8StringEncoding];


    FlutterBinaryMessageHandler handler=^(NSData* _Nullable message, FlutterBinaryReply reply){

      std::unique_ptr<MethodResult> method_result = std::make_unique<MethodResultIos>(plugin,reply);
      PluginManager::Instance()->HandleMethodCall(channel,(const uint8_t*)message.bytes,message.length,std::move(method_result));
    };
    [messenger setMessageHandlerOnChannel:nschannel binaryMessageHandler:handler];
  }

  virtual void UnRegisterPlugin(Plugin* plugin)
  {
    PluginManager::UnRegisterPlugin(plugin);
    NSObject<FlutterBinaryMessenger>* messenger = [FLTCppPlugin getMessenger];
    if(!messenger)
    {
      printf("FLTCppPlugin not inited");
      return;
    }
    std::string channel = plugin->channel();
    NSString *nschannel= [NSString stringWithCString:channel.c_str() encoding:NSUTF8StringEncoding];   
    [messenger setMessageHandlerOnChannel:nschannel binaryMessageHandler:NULL];
  }

  virtual void InvokeMethodCall(const std::string &channel,const uint8_t* data,size_t len)
  {
    NSObject<FlutterBinaryMessenger>* messenger = [FLTCppPlugin getMessenger];
    if(!messenger)
    {
      printf("FLTCppPlugin not inited");
      return;
    }
    NSString *nschannel= [NSString stringWithCString:channel.c_str() encoding:NSUTF8StringEncoding];
    NSData *nsdata = NULL;
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


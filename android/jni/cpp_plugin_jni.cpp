#include "plugin.h"
#include "plugin_manager.h"
#include "jni_unity.h"

namespace cpp_plugin
{

class MethodResultJni:public MethodResult
{
private:
    JNIEnv *m_env;
    jobject m_object;
    Plugin* m_plugin;
public:
    MethodResultJni(const std::string& channel,JNIEnv* env,jobject obj)
        :m_env(env),m_object(obj)
    {
        m_plugin=PluginManager::Instance()->GetPlugin(channel);
    }

    void Reply(const uint8_t* data,size_t len)
    {
        jclass cls = m_env->GetObjectClass(m_object);   
        jmethodID callback = m_env->GetMethodID(cls,"reply","(Ljava/nio/ByteBuffer)V");  

        if(data)
        {
            jobject jmessage = m_env->NewDirectByteBuffer((void*)data,len);
            m_env->CallVoidMethod(m_object,callback,jmessage);
            m_env->DeleteLocalRef(jmessage);
        }
        else
        {
            m_env->CallVoidMethod(m_object,callback);
        }
    }

    virtual void SuccessInternal(const void *result)
    {
        //调用java中BinaryReply的reply函数
        std::unique_ptr<std::vector<uint8_t>> data = m_plugin->GetCodec().EncodeSuccessEnvelope(result);
        Reply(data->data(),data->size());
    }

    virtual void ErrorInternal(const std::string &error_code,
                            const std::string &error_message,
                            const void *error_details)
    {
        //调用java中BinaryReply的reply函数
        std::unique_ptr<std::vector<uint8_t>> data = m_plugin->GetCodec().EncodeErrorEnvelope(
                                    error_code,error_message,error_details);
        Reply(data->data(),data->size());
    }

    virtual void NotImplementedInternal()
    {
        Reply(NULL,0);
    }
};

void JNICALL Java_io_flutter_cpp_plugin_CppBinaryMessageHandler_onMessageJni  
  (JNIEnv *env, jobject jobj,jobject jmsg,jobject jreply)  
{
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, "mChannel","Ljava/lang/String;");
	jstring jchannel = (jstring)env->GetObjectField(jobj, fid);
    std::string channel = jstring2string(env,jchannel);

    std::unique_ptr<MethodResult> method_result = std::make_unique<MethodResultJni>(channel,env,jreply);

    size_t len = env->GetDirectBufferCapacity(jmsg);
	const uint8_t* data = (uint8_t*)env->GetDirectBufferAddress(jmsg);
    PluginManager::Instance()->HandleMethodCall(channel,data,len,std::move(method_result));
}  


class PluginManagerJni:public PluginManager
{
private:
    JavaVM* m_vm;
    JNIEnv *m_env;
    jclass m_class;
public:
    PluginManagerJni(JavaVM* vm,JNIEnv* env)
        :m_vm(vm),m_env(env)
    {
        m_class = m_env->FindClass("io.flutter.cpp_plugin/CppPlugin");
    }

    virtual void RegisterPlugin(Plugin* plugin)
    {
        PluginManager::RegisterPlugin(plugin);

        int status = m_vm->AttachCurrentThread(&m_env, NULL);
        if(status<0)
        {
            LOGE("callback_handler: failed to attach current thread");
            return;
        }
        
        jmethodID register_method = m_env->GetStaticMethodID(m_class,"registerPlugin","(Ljava/lang/String)V");
        if (register_method == NULL) {
            m_vm->DetachCurrentThread();
            return;
        }

        // 3、调用clazz类的callStaticMethod静态方法
        jstring jchannel = m_env->NewStringUTF(plugin->channel().c_str());
        m_env->CallStaticVoidMethod(m_class,register_method, jchannel);
        
        // 删除局部引用
        m_env->DeleteLocalRef(jchannel); 

        m_vm->DetachCurrentThread();
    }

    virtual void UnRegisterPlugin(Plugin* plugin)
    {
        PluginManager::UnRegisterPlugin(plugin);
        int status = m_vm->AttachCurrentThread(&m_env, NULL);
        if(status<0)
        {
            LOGE("callback_handler: failed to attach current thread");
            return;
        }
        
        jmethodID register_method = m_env->GetStaticMethodID(m_class,"unregisterPlugin","(Ljava/lang/String)V");
        if (register_method == NULL) {
            m_vm->DetachCurrentThread();
            return;
        }

        // 3、调用clazz类的callStaticMethod静态方法
        jstring jchannel = m_env->NewStringUTF(plugin->channel().c_str());
        m_env->CallStaticVoidMethod(m_class,register_method, jchannel);
        
        // 删除局部引用
        m_env->DeleteLocalRef(jchannel);
        m_vm->DetachCurrentThread();
    }

    virtual void InvokeMethodCall(const std::string &channel,const uint8_t* data,size_t len)
    {
        int status = m_vm->AttachCurrentThread(&m_env, NULL);
        if(status<0)
        {
            LOGE("callback_handler: failed to attach current thread");
            return;
        }

        // 2、从clazz类中查找send方法
        jmethodID send_method = m_env->GetStaticMethodID(m_class,"invokeMethodCall","(Ljava/lang/String;Ljava.nio.ByteBuffer)V");
        if (send_method == NULL) {
            m_vm->DetachCurrentThread();
            return;
        }

        // 3、调用clazz类的callStaticMethod静态方法
        jstring jchannel = m_env->NewStringUTF(channel.c_str());
        jobject jmessage = m_env->NewDirectByteBuffer((void*)data,len);
        m_env->CallStaticVoidMethod(m_class,send_method, jchannel, jmessage);
        
        // 删除局部引用
        m_env->DeleteLocalRef(jchannel);
        m_env->DeleteLocalRef(jmessage);
        m_vm->DetachCurrentThread();
    }

};



PluginManagerJni* s_manager=NULL;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv* env = NULL;
    jint result = -1;
    if(vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
      return -1;

    s_manager = new PluginManagerJni(vm,env);
    return JNI_VERSION_1_4;
}


PluginManager* PluginManager::Instance()
{
    return s_manager;
}


}//namespace



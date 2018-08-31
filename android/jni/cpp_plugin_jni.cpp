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
    jobject m_reply;
    Plugin* m_plugin;
public:
    MethodResultJni(const std::string& channel,JNIEnv* env,jobject obj,jobject reply)
        :m_env(env),m_object(obj),m_reply(reply)
    {
        m_plugin=PluginManager::Instance()->GetPlugin(channel);
    }

    void Reply(const uint8_t* data,size_t len)
    {
        jclass replycls = m_env->GetObjectClass(m_reply);   
        jmethodID callback = m_env->GetMethodID(replycls,"reply","(Ljava/nio/ByteBuffer;)V");  

        if(data)
        {
            jclass cls = m_env->GetObjectClass(m_object);  
            jmethodID convertDataMethod = m_env->GetMethodID(cls,"convertData","([B)Ljava/nio/ByteBuffer;");

            jbyteArray arrayData =m_env->NewByteArray(len);
            m_env->SetByteArrayRegion(arrayData, 0, len, (jbyte*)data);

            jobject jmessage = m_env->CallObjectMethod(m_object,convertDataMethod,arrayData);

            //jobject jmessage = m_env->NewDirectByteBuffer((void*)data,(jlong)len);

            m_env->CallVoidMethod(m_reply,callback,jmessage);
            m_env->DeleteLocalRef(jmessage);
            m_env->DeleteLocalRef(arrayData);

            m_env->DeleteLocalRef(cls);
        }
        else
        {
            m_env->CallVoidMethod(m_object,callback);
        }
        m_env->DeleteLocalRef(replycls); 
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


class PluginManagerJni:public PluginManager
{
private:
    JavaVM* m_vm;
public:
    PluginManagerJni(JavaVM* vm,JNIEnv* env)
        :m_vm(vm)
    {
        
    }

    JNIEnv* GetEnv(bool &isAttacked){
        JNIEnv* env=NULL;
        int status = m_vm->GetEnv((void **) &env, JNI_VERSION_1_4);
        if(status < 0) {
            LOGI("callback_handler:failed to get JNI environment assuming native thread"); 
            status = m_vm->AttachCurrentThread(&env, NULL);
            if(status < 0) {
                LOGE("callback_handler: failed to attach current thread");
                return NULL;
            }
            isAttacked = true;
        }
        return env;
    }



    virtual void RegisterPlugin(Plugin* plugin)
    {
        PluginManager::RegisterPlugin(plugin);

        LOGI("RegisterPlugin %s",plugin->channel().c_str());
        bool  isAttacked = false;
        JNIEnv* env = GetEnv(isAttacked);
        if(!env)
            return;

        jclass jclass = env->FindClass("io/flutter/cppplugin/CppPlugin");
        if(!jclass)
            LOGE("cant find class CppPlugin");

        jmethodID register_method = env->GetStaticMethodID(jclass,"registerPlugin","(Ljava/lang/String;)V");
        if (register_method == NULL) {
            LOGE("cant find registerPlugin");
            if(isAttacked)
                m_vm->DetachCurrentThread();
            return;
        }

        // 3、调用clazz类的callStaticMethod静态方法
        jstring jchannel = env->NewStringUTF(plugin->channel().c_str());
        env->CallStaticVoidMethod(jclass,register_method, jchannel);
        LOGI("call CppPlugin.registerPlugin");

        // 删除局部引用
        env->DeleteLocalRef(jchannel); 
        env->DeleteLocalRef(jclass);

        LOGI("RegisterPlugin finish");

        if(isAttacked)
            m_vm->DetachCurrentThread();
    }

    virtual void UnRegisterPlugin(Plugin* plugin)
    {
        PluginManager::UnRegisterPlugin(plugin);

        LOGI("UnRegisterPlugin %s",plugin->channel().c_str());

        bool isAttacked = false;
        JNIEnv* env = GetEnv(isAttacked);
        if(!env)
            return;

        jclass jclass = env->FindClass("io/flutter/cppplugin/CppPlugin");
        if(!jclass)
            LOGE("cant find class CppPlugin");

        jmethodID register_method = env->GetStaticMethodID(jclass,"unregisterPlugin","(Ljava/lang/String;)V");
        if (register_method == NULL) {
            LOGE("cant find unregisterPlugin");
            if(isAttacked)
                m_vm->DetachCurrentThread();
            return;
        }

        // 3、调用clazz类的callStaticMethod静态方法
        jstring jchannel = env->NewStringUTF(plugin->channel().c_str());
        env->CallStaticVoidMethod(jclass,register_method, jchannel);
        
        // 删除局部引用
        env->DeleteLocalRef(jchannel);
        env->DeleteLocalRef(jclass);

        if(isAttacked)
            m_vm->DetachCurrentThread();
    }

    virtual void InvokeMethodCall(const std::string &channel,const uint8_t* data,size_t len)
    {
        LOGI("InvokeMethodCall %s",channel.c_str());
        
        bool isAttacked = false;
        JNIEnv* env = GetEnv(isAttacked);
        if(!env)
            return;

        jclass jclass = env->FindClass("io/flutter/cppplugin/CppPlugin");
        if(!jclass)
            LOGE("cant find class CppPlugin");

        // 2、从clazz类中查找send方法
        jmethodID send_method = env->GetStaticMethodID(jclass,"invokeMethodCall","(Ljava/lang/String;Ljava.nio.ByteBuffer;)V");
        if (send_method == NULL) {
            if(isAttacked)
                m_vm->DetachCurrentThread();
            return;
        }

        // 3、调用clazz类的callStaticMethod静态方法
        jstring jchannel = env->NewStringUTF(channel.c_str());
        jobject jmessage = env->NewDirectByteBuffer((void*)data,len);
        env->CallStaticVoidMethod(jclass,send_method, jchannel, jmessage);
        
        // 删除局部引用
        env->DeleteLocalRef(jchannel);
        env->DeleteLocalRef(jmessage);
        env->DeleteLocalRef(jclass);

        if(isAttacked)
            m_vm->DetachCurrentThread();
    }

};



PluginManagerJni* s_manager=NULL;

PluginManager* PluginManager::Instance()
{
    return s_manager;
}


}//namespace

using namespace cpp_plugin;

extern "C"
{


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv* env = NULL;
    jint result = -1;
    if(vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
      return -1;

    s_manager = new PluginManagerJni(vm,env);
    return JNI_VERSION_1_4;
}


void JNICALL Java_io_flutter_cppplugin_CppBinaryMessageHandler_onMessageJni  
  (JNIEnv *env, jobject jobj,jbyteArray jmsg,jobject jreply)  
{
	jclass cls = env->GetObjectClass(jobj);
	jfieldID fid = env->GetFieldID(cls, "mChannel","Ljava/lang/String;");
	jstring jchannel = (jstring)env->GetObjectField(jobj, fid);
    std::string channel = jstring2string(env,jchannel);

    std::unique_ptr<MethodResult> method_result = std::make_unique<MethodResultJni>(channel,env,jobj,jreply);

    jbyte* data = env->GetByteArrayElements(jmsg, 0);
    jsize len  = env->GetArrayLength(jmsg);

    LOGI("RecvMsg %s",data);
    PluginManager::Instance()->HandleMethodCall(channel,(uint8_t*)data,len,std::move(method_result));

    env->ReleaseByteArrayElements(jmsg,data,0);
}  

void JNICALL Java_io_flutter_cppplugin_CppPlugin_mainJni(JNIEnv *,jclass)
{
    plugin_main();
}

}//extern "C"


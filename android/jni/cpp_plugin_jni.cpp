#include "binary_messenger.h"
#include "jni_unity.h"

namespace cpp_plugin
{

class BinaryMessengerAndroid: public BinaryMessenger
{
private:
    JNIEnv *m_env;
    jclass m_class;
public:
    BinaryMessengerAndroid(JNIEnv* env)
        :m_env(env)
    {
        m_class = m_env->FindClass("io.flutter.cpp_plugin/CppPlugin");
    }

    void send(const std::string& channel,const std::vector<uint8_t>& message)
    {
        // 2、从clazz类中查找send方法
        jmethodID send_method = m_env->GetStaticMethodID(m_class,"send","(Ljava/lang/String;Ljava.nio.ByteBuffer)V");
        if (send_method == NULL) {
            return;
        }

        // 3、调用clazz类的callStaticMethod静态方法
        jstring jchannel = m_env->NewStringUTF(channel.c_str());
        jobject jmessage = m_env->NewDirectByteBuffer((void*)message.data(),message.size());
        m_env->CallStaticVoidMethod(m_class,send_method, jchannel, jmessage);
        
        // 删除局部引用
        m_env->DeleteLocalRef(jchannel);
        m_env->DeleteLocalRef(jmessage);
    }


    void send(const std::string& channel, const std::vector<uint8_t>& message, BinaryReply* callback)
    {
        // 2、从clazz类中查找send方法
        jmethodID send_method = m_env->GetStaticMethodID(m_class,"send2","(Ljava/lang/String;Ljava.nio.ByteBuffer;J)V");
        if (send_method == NULL) {
            return;
        }

        // 3、调用clazz类的callStaticMethod静态方法
        jstring jchannel = m_env->NewStringUTF(channel.c_str());
        jobject jmessage = m_env->NewDirectByteBuffer((void*)message.data(),message.size());
        m_env->CallStaticVoidMethod(m_class,send_method, jchannel, jmessage,jlongFromPointer(callback));
        
        // 删除局部引用
        m_env->DeleteLocalRef(jchannel);
        m_env->DeleteLocalRef(jmessage);
    }

    void setMessageHandler(const std::string& channel, BinaryMessageHandler* handler)
    {
        // 2、从clazz类中查找send方法
        jmethodID send_method = m_env->GetStaticMethodID(m_class,"setMessageHandler","(Ljava/lang/String;J)V");
        if (send_method == NULL) {
            return;
        }

        // 3、调用clazz类的callStaticMethod静态方法
        jstring jchannel = m_env->NewStringUTF(channel.c_str());
        m_env->CallStaticVoidMethod(m_class,send_method, jchannel,jlongFromPointer(handler));
        
        // 删除局部引用
        m_env->DeleteLocalRef(jchannel);
    }
};



BinaryMessengerAndroid* s_messenger=NULL;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv* env = NULL; //注册时在JNIEnv中实现的，所以必须首先获取它
    jint result = -1;
    if(vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) //从JavaVM获取JNIEnv，一般使用1.4的版本
      return -1;

    s_messenger = new BinaryMessengerAndroid(env);
    return JNI_VERSION_1_4; //这里很重要，必须返回版本，否则加载会失败。
}


BinaryMessenger* BinaryMessenger::Instance()
{
    return s_messenger;
}


}//namespace



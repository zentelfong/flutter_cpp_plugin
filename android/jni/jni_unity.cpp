#include "jni_unity.h"
 
std::string jstring2string(JNIEnv* env, jstring jstr)
{
	std::string rtn;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
 
	if (alen > 0)
	{
		rtn.append((char*)ba,alen);
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}
 
jstring char2Jstring(JNIEnv* env, const char* pat)
{
	jclass strClass = env->FindClass("Ljava/lang/String;");
	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = env->NewByteArray(strlen(pat));
	env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
	jstring encoding = env->NewStringUTF("utf-8");
	return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}


//C++ 和 ByteBuffer 交互
//jobject NewDirectByteBuffer(void* address, jlong capacity);


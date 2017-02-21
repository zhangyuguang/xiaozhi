#include <jni.h>
#include <string.h>
#include <stdio.h>

#include "utils/log/log.h"

#include "collab_filter.h"
 
#define PATH_SEPARATOR ':'

static char output[OUTPUT_LEN] = {0};
 
char* collab_filter(const char* input)
{
   JavaVMOption options[1];
   JNIEnv *env;
   JavaVM *jvm;
   JavaVMInitArgs vm_args;
  
   long status;
   jclass cls;
   jmethodID mid;
   jfieldID fid;
   jobject obj;

   char* ret = 0;
  
   options[0].optionString = "-Djava.class.path=.:/home/openair/xiao-zhi-app-service/collab_filter/java_obj:/usr/lib/jvm/jdk1.8.0_102/lib:/usr/lib/jvm/jdk1.8.0_102/jre/lib:/usr/lib/mahout/apache-mahout-distribution-0.12.2/lib:/usr/lib/mahout/apache-mahout-distribution-0.12.2/conf:/usr/lib/jvm/jdk1.8.0_102/lib/tools.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-flink_2.10-0.12.2.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-h2o_2.10-0.12.2-dependency-reduced.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-h2o_2.10-0.12.2.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-hdfs-0.12.2.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-integration-0.12.2.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-math-0.12.2.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-math-scala_2.10-0.12.2.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-mr-0.12.2.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-mr-0.12.2-job.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-spark_2.10-0.12.2-dependency-reduced.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-spark_2.10-0.12.2.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/mahout-spark-shell_2.10-0.12.2.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/examples/target/mahout-examples-*-job.jar:/usr/lib/mahout/apache-mahout-distribution-0.12.2/math-scala/target/mahout-math-scala_*.jar";

   memset(&vm_args, 0, sizeof(vm_args));
   vm_args.version = JNI_VERSION_1_8;
   vm_args.nOptions = 1;
   vm_args.options = options;
  
   status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
  
   if(status != JNI_ERR)
   {
       cls = (*env)->FindClass(env, "XiaozhiWithAnonymousRecommender");
       if(cls != 0)
       {
          mid = (*env)->GetStaticMethodID(env, cls, "XiaozhiRecomend",  "(Ljava/lang/String;)Ljava/lang/String;");
          if(mid != 0)
          {
              //const char* input = "20590 3.0 98925 5.0 8587 2.0";
              jstring arg = (*env)->NewStringUTF(env, input);
              jstring result = (jstring)(*env)->CallStaticObjectMethod(env, cls, mid, arg);
              const char* str = (*env)->GetStringUTFChars(env, result, 0);
              
              strncpy(output, str, OUTPUT_LEN);
              PRT_LOG_T(LOG_ERR, COLLAB_FILTER, "Result of recommend: %s\n", str);

              if (strlen(str) < OUTPUT_LEN)
                  ret = output;
              else
                  PRT_LOG_T(LOG_ERR, COLLAB_FILTER, "The length of recommendation is too long!\n");
              
              (*env)->ReleaseStringUTFChars(env, result, 0);
          }
          else
              PRT_LOG_T(LOG_ERR, COLLAB_FILTER, "Cannot get the method!\n");
       }
       else
           PRT_LOG_T(LOG_ERR, COLLAB_FILTER, "Cannot find class!\n");
      
       (*jvm)->DestroyJavaVM(jvm);
       return ret;
   }
   else
   {
       PRT_LOG_T(LOG_ERR, COLLAB_FILTER, "JVMCreated failed!\n");
       return ret;
   }
}

/*
void main(void)
{
    char* input = "20590 3.0 98925 5.0 8587 2.0";
    char* output = 0;
    
    output = collab_filter(input);
    printf("Result of collab_filter: %s\n", output);
}
*/

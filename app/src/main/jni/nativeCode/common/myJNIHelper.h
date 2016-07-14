/*
 *    Copyright 2016 Anand Muralidhar
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef MY_JNI_HELPER_H
#define MY_JNI_HELPER_H

#include "myLogger.h"
#include <android_native_app_glue.h>
#include <pthread.h>
#include <string>
#include <jni.h>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

class MyJNIHelper {

private:
    mutable pthread_mutex_t threadMutex;
    std::string apkInternalPath;
    AAssetManager *apkAssetManager;

public:
    MyJNIHelper(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir);

    ~MyJNIHelper();

    void Init(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir);

    bool ExtractAssetReturnFilename(std::string assetName, std::string &filename,
                                    bool checkIfFileIsAvailable = false);

    bool ReadFileFromAssetsToBuffer(const char *filename, std::vector<uint8_t> *bufferRef);
};

extern MyJNIHelper *gHelperObject;

#ifdef __cplusplus
}
#endif

#endif // #define MY_JNI_HELPER_H

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

#include "myJNIHelper.h"
#include "misc.h"
#include <android/asset_manager_jni.h>

MyJNIHelper::MyJNIHelper(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir) {

    // get a native instance of the asset manager
    // assetManager is passed from Java and should not be garbage collected!
    apkAssetManager = AAssetManager_fromJava(env, assetManager);

    //Save app internal data storage path -- we will extract assets and save here
    const char *cPathToInternalDir;
    cPathToInternalDir = env->GetStringUTFChars(pathToInternalDir, NULL ) ;
    apkInternalPath = std::string(cPathToInternalDir);
    env->ReleaseStringUTFChars(pathToInternalDir, cPathToInternalDir);

    //mutex for thread safety
    pthread_mutex_init(&threadMutex, NULL );
}

MyJNIHelper::~MyJNIHelper()
{
    pthread_mutex_destroy( &threadMutex);
}

/**
 * Search for a file in assets, extract it, save it in internal storage, and return the new path
 */
bool MyJNIHelper::ExtractAssetReturnFilename(std::string assetName, std::string & filename,
                                             bool checkIfFileIsAvailable) {

    // construct the filename in internal storage by concatenating with path to internal storage
    filename = apkInternalPath + "/" + GetFileName(assetName);

    // check if the file was previously extracted and is available in app's internal dir
    FILE* file = fopen(filename.c_str(), "rb");
    if (file && checkIfFileIsAvailable) {

        MyLOGI("Found extracted file in assets: %s", filename.c_str());
        fclose(file);
        pthread_mutex_unlock( &threadMutex);
        return true;

    }

    // let us look for the file in assets
    bool result = false;

    // AAsset objects are not thread safe and need to be protected with mutex
    pthread_mutex_lock( &threadMutex);

    // Open file
    AAsset* asset = AAssetManager_open(apkAssetManager, assetName.c_str(), AASSET_MODE_STREAMING);

    char buf[BUFSIZ];
    int nb_read = 0;
    if (asset != NULL)
    {
        FILE* out = fopen(filename.c_str(), "w");
        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
        {
            fwrite(buf, nb_read, 1, out);
        }
        fclose(out);
        AAsset_close(asset);
        result = true;

        MyLOGI("Asset extracted: %s", filename.c_str());
    }
    else
    {
        MyLOGE("Asset not found: %s", assetName.c_str());
    }

    pthread_mutex_unlock( &threadMutex);
    return result;

}

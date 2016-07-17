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

#include <jni.h>
#include "modelAssimp.h"


#ifdef __cplusplus
extern "C" {
#endif

extern ModelAssimp *gAssimpObject;

JNIEXPORT void JNICALL
Java_com_anandmuralidhar_assimpandroid_MyGLRenderer_DrawFrameNative(JNIEnv *env,
                                                                      jobject instance) {

    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->Render();

}

JNIEXPORT void JNICALL
Java_com_anandmuralidhar_assimpandroid_MyGLRenderer_SurfaceCreatedNative(JNIEnv *env,
                                                                           jobject instance) {

    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->PerformGLInits();

}

JNIEXPORT void JNICALL
Java_com_anandmuralidhar_assimpandroid_MyGLRenderer_SurfaceChangedNative(JNIEnv *env,
                                                                           jobject instance,
                                                                           jint width,
                                                                           jint height) {

    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->SetViewport(width, height);

}

#ifdef __cplusplus
}
#endif


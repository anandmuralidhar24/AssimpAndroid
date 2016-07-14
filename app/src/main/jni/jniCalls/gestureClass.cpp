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
#include "myJNIHelper.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ModelAssimp *gCubeObject;

JNIEXPORT void JNICALL
Java_com_anandmuralidhar_assimpandroid_GestureClass_DoubleTapNative(JNIEnv *env, jobject instance) {

    if (gCubeObject == NULL) {
        return;
    }
    gCubeObject->DoubleTapAction();

}

/**
 * one finger drag - compute normalized current position and normalized displacement
 * from previous position
 */
JNIEXPORT void JNICALL
Java_com_anandmuralidhar_assimpandroid_GestureClass_ScrollNative(JNIEnv *env, jobject instance,
                                                               jfloat distanceX, jfloat distanceY,
                                                               jfloat positionX, jfloat positionY) {

    if (gCubeObject == NULL) {
        return;
    }
    // normalize movements on the screen wrt GL surface dimensions
    // invert dY to be consistent with GLES conventions
    float dX = (float) distanceX / gCubeObject->GetScreenWidth();
    float dY = -(float) distanceY / gCubeObject->GetScreenHeight();
    float posX = 2*positionX/ gCubeObject->GetScreenWidth() - 1.;
    float posY = -2*positionY / gCubeObject->GetScreenHeight() + 1.;
    posX = fmax(-1., fmin(1., posX));
    posY = fmax(-1., fmin(1., posY));
    gCubeObject->ScrollAction(dX, dY, posX, posY);

}

/**
 * Pinch-and-zoom gesture: pass the change in scale to class' method
 */
JNIEXPORT void JNICALL
Java_com_anandmuralidhar_assimpandroid_GestureClass_ScaleNative(JNIEnv *env, jobject instance,
                                                              jfloat scaleFactor) {

    if (gCubeObject == NULL) {
        return;
    }
    gCubeObject->ScaleAction((float) scaleFactor);

}


/**
 * Two-finger drag - normalize the distance moved wrt GLES surface size
 */
JNIEXPORT void JNICALL
Java_com_anandmuralidhar_assimpandroid_GestureClass_MoveNative(JNIEnv *env, jobject instance,
                                                               jfloat distanceX, jfloat distanceY) {

    if (gCubeObject == NULL) {
        return;
    }

    // normalize movements on the screen wrt GL surface dimensions
    // invert dY to be consistent with GLES conventions
    float dX = distanceX / gCubeObject->GetScreenWidth();
    float dY = -distanceY / gCubeObject->GetScreenHeight();
    gCubeObject->MoveAction(dX, dY);

}

#ifdef __cplusplus
}
#endif

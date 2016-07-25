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

#include "myShader.h"
#include "modelAssimp.h"


#include "assimp/Importer.hpp"
#include <opencv2/opencv.hpp>
#include <myJNIHelper.h>

/**
 * Class constructor
 */
ModelAssimp::ModelAssimp() {

    MyLOGD("ModelAssimp::ModelAssimp");
    initsDone = false;

    // create MyGLCamera object and set default position for the object
    myGLCamera = new MyGLCamera();
    float pos[]={0.,0.,0.,0.2,0.5,0.};
    std::copy(&pos[0], &pos[5], std::back_inserter(modelDefaultPosition));
    myGLCamera->SetModelPosition(modelDefaultPosition);

    modelObject = NULL;
}

ModelAssimp::~ModelAssimp() {

    MyLOGD("ModelAssimp::ModelAssimpssimp");
    if (myGLCamera) {
        delete myGLCamera;
    }
    if (modelObject) {
        delete modelObject;
    }
}

/**
 * Perform inits and load the triangle's vertices/colors to GLES
 */
void ModelAssimp::PerformGLInits() {

    MyLOGD("ModelAssimp::PerformGLInits");

    MyGLInits();

    modelObject = new AssimpLoader();

    // extract the OBJ and companion files from assets
    std::string objFilename, mtlFilename, texFilename;
    bool isFilesPresent  =
            gHelperObject->ExtractAssetReturnFilename("amenemhat/amenemhat.obj", objFilename) &&
            gHelperObject->ExtractAssetReturnFilename("amenemhat/amenemhat.mtl", mtlFilename) &&
            gHelperObject->ExtractAssetReturnFilename("amenemhat/amenemhat.jpg", texFilename);
    if( !isFilesPresent ) {
        MyLOGE("Model %s does not exist!", objFilename.c_str());
        return;
    }

    modelObject->Load3DModel(objFilename);

    CheckGLError("ModelAssimp::PerformGLInits");
    initsDone = true;
}


/**
 * Render to the display
 */
void ModelAssimp::Render() {

    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 mvpMat = myGLCamera->GetMVP();
    modelObject->Render3DModel(&mvpMat);

    CheckGLError("ModelAssimp::Render");

}

/**
 * set the viewport, function is also called when user changes device orientation
 */
void ModelAssimp::SetViewport(int width, int height) {

    screenHeight = height;
    screenWidth = width;
    glViewport(0, 0, width, height);
    CheckGLError("Cube::SetViewport");

    myGLCamera->SetAspectRatio((float) width / height);
}


/**
 * reset model's position in double-tap
 */
void ModelAssimp::DoubleTapAction() {

    myGLCamera->SetModelPosition(modelDefaultPosition);
}

/**
 * rotate the model if user scrolls with one finger
 */
void ModelAssimp::ScrollAction(float distanceX, float distanceY, float positionX, float positionY) {

    myGLCamera->RotateModel(distanceX, distanceY, positionX, positionY);
}

/**
 * pinch-zoom: move the model closer or farther away
 */
void ModelAssimp::ScaleAction(float scaleFactor) {

    myGLCamera->ScaleModel(scaleFactor);
}

/**
 * two-finger drag: displace the model by changing its x-y coordinates
 */
void ModelAssimp::MoveAction(float distanceX, float distanceY) {

    myGLCamera->TranslateModel(distanceX, distanceY);
}
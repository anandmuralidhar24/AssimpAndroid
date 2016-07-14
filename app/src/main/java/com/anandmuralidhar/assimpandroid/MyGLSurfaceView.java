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

package com.anandmuralidhar.assimpandroid;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;

class MyGLSurfaceView extends GLSurfaceView {

    private MyGLRenderer mRenderer;

    public MyGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);

        try {
            // Create GLES context. Even though we are specifying OpenGL ES 2, it will try to
            // create the highest possible context on a phone
            setEGLContextClientVersion(2);

            // set our custom Renderer for drawing on the created SurfaceView
            mRenderer = new MyGLRenderer();
            setRenderer(mRenderer);

            // calls onDrawFrame(...) continuously
            setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);

        } catch (Exception e) {

            // Trouble, something's wrong!
            Log.e("MyGLSurfaceView", "Unable to create GLES context!", e);

        }

    }

}

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

import android.app.Activity;
import android.support.v4.view.GestureDetectorCompat;
import android.support.v4.view.MotionEventCompat;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.View;

public class GestureClass {

   private GestureDetectorCompat mTapScrollDetector;
    private ScaleGestureDetector mScaleDetector;
    private native void DoubleTapNative();
    private native void ScrollNative(float distanceX, float distanceY, float positionX, float positionY);
    private native void ScaleNative(float scaleFactor);
    private native void MoveNative(float distanceX, float distanceY);

    public GestureClass(Activity activity) {

        // instantiate two listeners for detecting double-tap/drag and pinch-zoom
        mTapScrollDetector = new GestureDetectorCompat(activity, new MyTapScrollListener());
        mScaleDetector = new ScaleGestureDetector(activity.getApplicationContext(),
                new ScaleListener());

    }

    static int INVALID_POINTER_ID = -100;
    private int mTwoFingerPointerId = INVALID_POINTER_ID;

    // this listener detects gesture of dragging with two fingers
    public View.OnTouchListener TwoFingerGestureListener = new View.OnTouchListener() {
        private float mLastTouchX, mLastTouchY;

        @Override
        public boolean onTouch(View v, MotionEvent event) {

            // let the other detectors also consume the event
            mTapScrollDetector.onTouchEvent(event);
            mScaleDetector.onTouchEvent(event);

            final int action = MotionEventCompat.getActionMasked(event);

            switch (action) {
                case MotionEvent.ACTION_DOWN: {
                    break;
                }

                case MotionEvent.ACTION_MOVE: {
                    // track the drag only if two fingers are placed on screen
                    if(mTwoFingerPointerId != INVALID_POINTER_ID) {

                        final float x = MotionEventCompat.getX(event, mTwoFingerPointerId);
                        final float y = MotionEventCompat.getY(event, mTwoFingerPointerId);

                        // Calculate the distance moved
                        final float dx = x - mLastTouchX;
                        final float dy = y - mLastTouchY;

                        // Remember this touch position for the next move event
                        mLastTouchX = x;
                        mLastTouchY = y;
                        MoveNative(dx, dy);
                    }
                    break;
                }

                case MotionEvent.ACTION_UP: {
                    mTwoFingerPointerId = INVALID_POINTER_ID;
                    break;
                }

                case MotionEvent.ACTION_CANCEL: {
                    mTwoFingerPointerId = INVALID_POINTER_ID;
                    break;
                }

                case MotionEvent.ACTION_POINTER_DOWN: {
                    // detected two fingers, start the drag
                    mTwoFingerPointerId = MotionEventCompat.getActionIndex(event);
                    final float x = MotionEventCompat.getX(event, mTwoFingerPointerId);
                    final float y = MotionEventCompat.getY(event, mTwoFingerPointerId);

                    // Remember where we started (for dragging)
                    mLastTouchX = x;
                    mLastTouchY = y;
                    break;
                }

                case MotionEvent.ACTION_POINTER_UP: {
                    // two fingers are not placed on screen anymore
                    mTwoFingerPointerId = INVALID_POINTER_ID;
                    break;
                }
            }
            return true;
        }
    };

    // this class detects double-tap gesture and tracks the drag gesture by single finger
    class MyTapScrollListener extends GestureDetector.SimpleOnGestureListener {

        public boolean onDoubleTap (MotionEvent event) {
            DoubleTapNative();
            return true;
        }

        // function is called if user scrolls with one/two fingers
        // we ignore the call if two fingers are placed on screen
        public boolean onScroll (MotionEvent e1, MotionEvent e2,
                                 float distanceX, float distanceY) {

            if(mTwoFingerPointerId == INVALID_POINTER_ID) {
                ScrollNative(distanceX, distanceY, e2.getX(), e2.getY());
            }
            return true;
        }
    }

    // this class detects pinch and zoom gestures
    private class ScaleListener extends ScaleGestureDetector.SimpleOnScaleGestureListener {

        @Override
        public boolean onScale(ScaleGestureDetector detector) {
            ScaleNative(detector.getScaleFactor());
            return true;
        }
    }

}

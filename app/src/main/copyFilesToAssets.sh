#!/usr/bin/env bash
# Create assets directory if it does not exist
if [ ! -d "./assets" ]; then
	mkdir assets
fi

# Delete all existing shaders in assets
rm -rf ./assets/*.?sh;

# Copy all shaders to assets
# We assume that vertex shaders are named as **.vsh and fragment shaders as **.fsh
find ./jni -name "*.?sh" -exec cp "{}" ./assets/ \;

# Copy all 3D models to assets
find ./3Dmodels -name "*.obj" -exec cp "{}" ./assets/ \;
find ./3Dmodels -name "*.mtl" -exec cp "{}" ./assets/ \;
find ./3Dmodels -name "*.jpg" -exec cp "{}" ./assets/ \;

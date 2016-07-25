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

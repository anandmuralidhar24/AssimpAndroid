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

#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <string>
#include "myLogger.h"
#include "myGLM.h"

std::string GetFileName(std::string fileName);

std::string GetDirectoryName(std::string fullFileName);

void PrintGLMMat4(glm::mat4 testMat);

#endif //MISC_H

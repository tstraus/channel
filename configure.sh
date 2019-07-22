#!/bin/bash

mkdir build
cd build

cmake -Wno-dev -DCMAKE_BUILD_TYPE=Debug ..

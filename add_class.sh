#!/bin/sh
classname=$1
touch sources/bounce/src/$classname.cc
git add sources/bounce/src/$classname.cc
touch sources/bounce/include/$classname.h
git add sources/bounce/include/$classname.h

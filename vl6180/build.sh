#!/bin/bash

set -xe

gcc src/*.c  -o output -I inc

if [ $? == 0 ]
then
  ./output
fi

#!/bin/bash

set -xe

gcc src/*.c -Wall -Wextra -o output -I inc

if [ $? == 0]
then
  ./output
fi

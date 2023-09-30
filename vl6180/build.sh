#!/bin/bash

set -xe

gcc src/*.c  -o output -I inc

./output

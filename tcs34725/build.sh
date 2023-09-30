#!/bin/bash

set -xe

gcc *.c ./src/*.c -Wall -Wextra -o output -I ./src

./output

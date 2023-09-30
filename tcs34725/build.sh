#!/bin/bash

set -xe

gcc src/*.c -Wall -Wextra -o output -I inc

./output

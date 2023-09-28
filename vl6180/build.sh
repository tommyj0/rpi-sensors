#!/bin/bash

set -xe

gcc src/*.c main.c -o output
./bin/output

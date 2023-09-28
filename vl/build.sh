#!/bin/bash

set -xe

gcc src/*.c -I include -o bin/output
./bin/output

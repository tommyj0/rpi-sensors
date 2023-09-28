#!/bin/bash

set +xe

gcc *.c -Wall -Wextra -o output 

./bin/output

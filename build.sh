#!/bin/sh

set -xe
exec_name="main"

clang -Wall -Wextra -ggdb -o $exec_name main.c -lm
./$exec_name

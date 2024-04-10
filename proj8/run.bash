#!/bin/bash
set -e
g++ -Wall -Werror -g main.cpp config.cpp charmatrix.cpp linked_list.cpp dataset.cpp -o lex
./lex $*

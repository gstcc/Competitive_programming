#!/bin/bash

python3 generate.py
g++ -o exc partial.cc
./exc < data.in > output.out
python3 correct.py < data.in > answer.out
python3 tmp.py
#!/bin/bash
./main text.txt | iconv -f cp1251 -t utf8

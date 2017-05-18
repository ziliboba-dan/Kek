#!/bin/bash
 iconv -f utf8 -t cp1251 text1.txt -o text.txt
./main text.txt | iconv -f cp1251 -t utf8
echo -n > text.txt


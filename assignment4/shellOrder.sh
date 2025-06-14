#!/bin/bash
g++ -std=c++20 main.cpp spellcheck.cpp -o main 
main "hello world"

main --stdin < "examples/(marquez).txt"
#!/bin/bash

echo $CLASSPATH

javac *.java
java Main -v -s 4 -E 1 -b 6 -t test_trace.txt

#!/bin/bash

echo "building myLed.cpp"
g++ myLed.cpp -o myLed.cgi -lcgicc -pthread
echo "building myLed.cpp finished"

#!/bin/bash

echo "cp_and_chmod running"

echo "sending a copy to the following directory /usr/lib/cgi-bin/"

sudo cp myLed.cgi /usr/lib/cgi-bin/

echo "copied"

echo "changing persmissions"
sudo chmod +s /usr/lib/cgi-bin/myLed.cgi
echo "permissions changed."
echo "Run script by going to 192.168.7.2:80/cgi-bin/myLed.cgi"

#!/bin/sh

# this script will automatically call 'make' command when a cpp or h file has changed

while true; do

inotifywait -e modify,create,delete -r ./Onodrim/Onodrim/ && \
make

done
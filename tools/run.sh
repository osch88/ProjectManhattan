#!/usr/bin/env bash

cd ..
gnome-terminal --title=REO          --geometry 50x5+500+1000    -- ./build/reo.out
gnome-terminal --title=Dashboard    --geometry 50x5             -- ./build/avic.out -c vcan0
gnome-terminal --title=Input        --geometry 40x25+50+1000    -- ./build/inputhandler.out
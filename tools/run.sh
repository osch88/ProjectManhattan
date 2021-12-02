#!/usr/bin/env bash

cd ..
gnome-terminal --title=Input        --geometry 20x25+50+1000    -- ./build/inputhandler.out
gnome-terminal --title=REO          --geometry 50x5+750+1000    -- ./build/reo.out
gnome-terminal --title=Dashboard    --geometry 50x5+1400+1000   -- ./build/avic.out -c vcan0
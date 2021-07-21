#! /usr/bin/bash

echo "*****paint.sh*****"
cd /home/dean/weather-eink/fetcher
node index.js
cp downloads/dark.bmp ../eink-example/pic/037-1yb1.bmp

cd ../eink-example/
echo "*****eink-example/epd*****"
./epd

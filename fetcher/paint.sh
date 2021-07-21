#! /usr/bin/bash

echo "*****git pull*****"
cd /home/dean/weather-eink
git pull
echo "*****paint.sh*****"
cd fetcher
node index.js
cp downloads/dark.bmp ../eink-example/pic/037-1yb1.bmp

cd ../eink-example/
echo "*****eink-example/epd*****"
./epd

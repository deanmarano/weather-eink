#! /usr/bin/bash

echo "*****git pull*****"
cd /home/dean/weather-eink
git pull

cd fetcher
echo "*****current downloads*****"
ls downloads
echo "*****fetching latest bmp*****"
node index.js
echo "*****new downloads*****"
ls downloads
cp downloads/dark.bmp ../eink-example/pic/037-1yb1.bmp

cd ../eink-example/
echo "*****eink-example/epd*****"
./epd

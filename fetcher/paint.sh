#!/usr/bin/env bash
set -o errexit
set -o nounset
set -o pipefail

echo "***** git pull *****"
cd /home/dean/weather-eink
git pull

cd fetcher
echo "***** current downloads *****"
ls downloads
echo "***** starting Node.js *****"
node index.js
echo "***** new downloads *****"
ls downloads
cp downloads/dark.bmp ../eink-example/pic/037-1yb1.bmp
cp downloads/yellow.bmp ../eink-example/pic/037-1yy1.bmp

cd ../eink-example/
echo "***** eink-example/epd *****"
./epd

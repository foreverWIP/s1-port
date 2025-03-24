#!/bin/sh

ffmpeg -r 60 -i 'movie/movie%d.qoi' -i movie/movie.wav -c:v libx264 -crf 19 -maxrate 4M -bufsize 50M -pix_fmt yuv420p -c:a aac -y movie/movie.mp4

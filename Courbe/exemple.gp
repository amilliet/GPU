#!/usr/bin/gnuplot

set term pdf #enhanced monochrome dashed
set output "test.pdf"

set key right bottom

set xlabel "Nombres de thread"
set ylabel "Speed up (#items/s)"

plot "test.data" with linespoints title "test 1"

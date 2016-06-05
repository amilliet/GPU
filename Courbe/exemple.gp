#!/usr/bin/gnuplot

set term pdf #enhanced monochrome dashed
set output "Eboulement_128x128.pdf"

set key right bottom

set xlabel "Nombres de threads"
set ylabel "Speed up (#items/s)"

plot "Eboulement_init_central.data" with linespoints title "Config Central",\
"Eboulement_init_homogene.data" with linespoints title "Config Homogène"

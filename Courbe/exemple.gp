#!/usr/bin/gnuplot

set term pdf #enhanced monochrome dashed
set output "Vision_voisin_128x128.pdf"

set key right bottom

set xlabel "Nombres de threads"
set ylabel "Speed up"

plot "Vision_voisin_init_central.data" with linespoints title "Config Central",\
"Vision_voisin_init_homogene.data" with linespoints title "Config Homogène"

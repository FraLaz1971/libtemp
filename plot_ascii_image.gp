set size ratio -1
set term png
set output 'mercury.png'
set palette gray;
unset xtics
unset ytics
unset label
unset border
unset colorbox
plot 'mariner_mercury.asc' matrix with image


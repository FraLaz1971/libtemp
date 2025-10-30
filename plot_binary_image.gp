set size ratio -1
set term png
set output 'mercury.png'
set palette gray;
unset xtics
unset ytics
unset label
unset border
unset colorbox
unset title
plot 'mercury1_500x320.raw' binary array=(500,320) format="%int" with image


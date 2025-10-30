set palette gray; 
set size ratio -1
set palette gray;
unset xtics
unset ytics
unset label
unset border
unset colorbox
plot 'mercury1_500x320.raw' binary array=(500,320) format="%int" with image


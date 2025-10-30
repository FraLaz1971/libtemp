# libtemp
template example c project with a library and many targets
###
To compile on linux
###
`make`
###
To run on linux
`./mfile1 tmdb.txt`
###
To compile on MS Windows with MSVC, open cmd terminal and enter the folder libtemp
###
`nmake /f makefile.vc`
###
To run on windows
###
`mfile1 tmdb.txt`
###
check the file pipeline.log
The library gives the possibility to read, write and plot 2D arrays and images in different formats,
included plain ascii (e. g. csv or ssv) raw binary, fits, pds4, png.
###
to know wich macro are defined by the compiler:
###
`$(CC) -std=c99 -E -dM empty.c`
###

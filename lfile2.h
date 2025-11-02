#ifndef LFILE2_H
#define LFILE2_H
#define MAXSIZE  10000
#define MAXWIDTH  10000
#define MAXHEIGHT 10000 
#define MAXCHARS  60000 
#include "lfile1.h"

enum file_format{ASCII,BINARY,ASCII_TABLE,BINARY_TABLE,FLOAT_BINARY,DOUBLE_BINARY,ASCIIERR,GPTABLE,
	FITS_IMAGE,FITS_ASCII_TABLE,FITS_BINARY_TABLE,PDS4,NETCDF,PS,PNG,GIF};

enum plot_type{PLOTUTILS,GNUPLOT};

/* plotutils settings */
struct PLOTTER{
	int engine; /* plot_type (e.g. gnuplot or plotutils graph, ...)*/
	char *driver; /* plot driver */
	char pcmd[256]; /* plot command */
	char ifile[256]; /* data input file name (e.g. "data.asc" or "data.bin")*/
	char *bfile; /* batch commands file name (e.g. "myplot.gp" or myplot.bat or myplot.sh)*/
	char ofile[256]; /* plot output file name (e.g. "myplot.png")*/
	char *xlabel; /* name of the x-axis */
	char *ylabel; /* name of the y-axis */
	char *title; /* title of the plot */
	int xmin; /* minimum of the x range */
	int xmax; /* maximum of the x range*/
	int ymin; /* minimum of the ypsilon range */
	int ymax; /* maximum of the ypsilon range */
	int ftype; /* type of the input file (ascii or binary)*/
	struct curve2D *curve; /* pointer to the curve to plot */
	struct array2D *image; /* pointer to the image to plot */
	int iftype; /* input file format */
	int oftype; /* output file format */
	unsigned char data_present;
};

struct curve2D{
	int *x; /* abscissa (x-axis)*/
	int *y; /* ordinata (y-axis)*/
	double *xd; /* abscissa (x-axis)*/
	double *yd; /* ordinata (y-axis)*/
	char **ttype;
	char **tform;
	char **tunit;
	unsigned long size;
	FILE *ifp; /* pointer to the input file */
	FILE *ofp; /* pointer to the output file */
	char ifile[256]; /* data input file name (e.g. "data.asc" or "data.bin")*/
	char ofile[256]; /* plot output file name (e.g. "myplot.png")*/
	int iftype; /* input file format */
	int oftype; /* output file format */
	struct LOG *logger;
	struct PLOTTER *plotter;
};

struct array2D{
	int **arr;
	unsigned long height; /* rows (NAXIS1) (line)*/
	unsigned long width; /* columns (NAXIS2) (sample)*/
	FILE *ifp; /* pointer to the input file */
	FILE *ofp; /* pointer to the output file */
	char ifile[256]; /* data input file name (e.g. "data.asc" or "data.bin")*/
	char ofile[256]; /* plot output file name (e.g. "myplot.png")*/
	int iftype; /* input file format */
	int oftype; /* output file format */
	struct LOG *logger;
	struct PLOTTER *plotter;
};

int init_curve_2D(struct curve2D *curve, struct LOG *logger, FILE *lfp);

int plot_curve_2D(struct curve2D *curve, int ptype, struct LOG *logger, FILE *lfp);

int read_curve_2D(const char *ifname, struct curve2D *curve, int ftype, struct LOG * logger, FILE *lfp);

int save_curve_2D(const char *ofname, struct curve2D *curve, int ftype, struct LOG *logger, FILE *lfp);

int set_curve2D_log(struct curve2D *curve, struct LOG *log, FILE * lfp);

int destroy_curve_2D(struct curve2D *curve, struct LOG *logger, FILE * lfp);

int init_array_2D(struct array2D *matrix, struct LOG *logger, FILE * lfp);

int plot_array_2D(struct array2D *matrix, int ptype, struct LOG *logger, FILE * lfp);

int read_array_2D(const char *ifname, struct array2D *matrix, int ftype, struct LOG *logger, FILE * lfp);

int save_array_2D(const char *ofname, struct array2D *matrix, int ftype, struct LOG *logger, FILE * lfp);

int set_array2D_log(struct array2D *matrix, struct LOG *log, FILE * lfp);

int destroy_array_2D(struct array2D *matrix, struct LOG *logger, FILE * lfp);
#endif /* LFILE2_H */

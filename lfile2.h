#ifndef LFILE2_H
#define LFILE2_H
#define MAXSIZE  1000
#define MAXWIDTH  1000
#define MAXHEIGHT 1000 
#include "lfile1.h"

enum file_type{ASCII,BINARY};

enum plot_type{PLOTUTILS,GNUPLOT};

/* plotutils settings */
struct PLOTTER{
	int engine; /* plot_type (e.g. gnuplot or plotutils graph, ...)*/
	char *driver; /* plot driver */
	char *pcmd; /* plot command */
	char *ifile; /* data input file name (e.g. "data.asc")*/
	char *bfile; /* batch commands file name (e.g. "myplot.gp" or myplot.bat or myplot.sh)*/
	char *ofile; /* plot output file name (e.g. "myplot.png")*/
	char *xlabel; /* name of the x-axis */
	char *ylabel; /* name of the y-axis */
	char *title; /* title of the plot */
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	int ftype; /* type of the input file (ascii or binary)*/
	struct curve2D *curve; /* pointer to the curve to plot */
	struct array2D *image; /* pointer to the image to plot */
};

struct curve2D{
	int *x; /* abscissa (x-axis)*/
	int *y; /* ordinata (y-axis)*/
	unsigned long size;
	FILE *ifp; /* pointer to the input file */
	FILE *ofp; /* pointer to the output file */
	struct LOG *logger;
};

struct array2D{
	unsigned short **arr;
	unsigned long height; /* rows (NAXIS1) (line)*/
	unsigned long width; /* columns (NAXIS2) (sample)*/
	FILE *ifp; /* pointer to the input file */
	FILE *ofp; /* pointer to the output file */
	struct LOG *logger;
};

int init_curve_2D(struct curve2D *curve, struct LOG *logger, FILE *lfp);

int plot_curve_2D(struct curve2D *curve, int ptype, struct LOG *logger, FILE *lfp);

int read_curve_2D(const char *ifname, struct curve2D *curve, int ftype, struct LOG * logger, FILE *lfp);

int save_curve_2D(const char *ofname, struct curve2D *curve, int ftype, struct LOG *logger, FILE *lfp);

int set_curve2D_log(struct curve2D *curve, struct LOG *log);

int destroy_curve_2D(struct curve2D *curve, struct LOG *logger, FILE * lfp);

int init_array_2D(struct array2D *matrix);

int plot_array_2D(struct array2D *matrix, int ptype);

int read_array_2D(const char *ifname, struct array2D *matrix, int ftype);

int save_array_2D(const char *ifname, struct array2D *matrix, int ftype);

int set_array2D_log(struct array2D *matrix, struct LOG *log);

int destroy_array_2D(struct array2D *matrix);
#endif /* LFILE2_H */

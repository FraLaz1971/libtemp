#ifndef FIMAGE_H
#define FIMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fitsio.h"
#include "lfile1.h"
#include "lfile2.h"
#include "lfile3.h"
struct table{
  char extname[32];
  char *planet[128];
  long diameter[128];
  float density[128];
  int hdutype;
  int hdunum;
  long firstrow;
  long firstelem;
  int tfields;/* n. of columns*/
  long nrows;/* n. of rows */
  char *ttype[3];
  char *tform[3];
  char *tunit[3];
};
struct image{
  int *arr; /* the 32 bits array */
  short int *arr16; /* the 16 bits array */
  char *arr8;
  float *farr; /* 32 bits float array */
  long nrows;
  long ncols;
  long count;
  long fpixel; /* first pixel in the array */
  long nelements; /* n. of elements of the array */
  int nullval;
  int anynull;
  int status;
  fitsfile *ifp;
  fitsfile *ofp;
  int bitpix; /* n. of bits for each pixel */
  long naxis; /*n. of axis(dimensions) */
  long naxes[2]; /*dimension of each axis */
  char fname[80]; /* name of the output file */
  char ifname[80]; /* name of the input file */
  char cmt[80];
  int chdu;
  struct table btable;
  struct SIM_STC_HK stable;
};
int allocate_array(int nbits,struct image *img);
int fill_array(struct image *img);
int print_array(struct image *img);
int free_array(struct image *img);
int save_fits(struct image *img); /* save image array on a fits file */
int save_bin(struct image *img); /* save image array on a binary file */
int init_table(struct image *img); /* init the fits file to then adda a table */
int load_fits(struct image *img);
void set_element(long rownum,long colnum,int val,struct image *img);
int get_element(long rownum,long colnum,struct image *img);
int set_chdu(int hdunum,struct image *img);
int add_stchk_table(struct image *img,struct PDS *pds);
void printerror( int status);
#endif //FIMAGE_H

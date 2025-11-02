#include <stdio.h>
#include <string.h>
#include "fimage.h"
#include "fitsio.h"
void printerror(int status);
int main(int argc, char ** argv){
    fitsfile *fptr;       /* pointer to the FITS file, */
    int status, ii, jj;
    long  fpixel, nelements;
    unsigned short *array[200];                                                            /* initialize FITS image parameters */
    char filename[128];
            /* name of the file */
    int bitpix   =  USHORT_IMG; /* 16-bit unsigned short */
    long naxis    =   2;  /* 2-dimensional image */
    long naxes[2] = { 300, 200 };   /* image is 300 pixel x 300 */
/* 300=n.columns=width 200=n.rows=height */
/* allocate memory for the whole image */
    if ( argc < 2){
      fprintf(stderr,"usage:%s <filename.fits>\n",argv[0]);
      return 1;
    }
    strcpy(filename,argv[1]);
    array[0] = (unsigned short *)malloc( naxes[0] * naxes[1]
* sizeof( unsigned short int));                                                            /* allocate memory for the whole image */
for( ii=1; ii<naxes[1]; ii++ )
      array[ii] = array[ii-1] + naxes[0];

    remove(filename);               /* Delete old file */

    status = 0;         /* initialize status before call create_file */

    if (fits_create_file(&fptr, filename, &status)) /* create the file */
         printerror( status );           /* call printerror() */
 /* initialize the values in the image with a linear> pattern */
    for (jj = 0; jj < naxes[1]; jj++)
    {   for (ii = 0; ii < naxes[0]; ii++)
        {
            array[jj][ii] = ii + jj;
        }
    }

    fpixel = 1;  /* first pixel */
    nelements = naxes[0] * naxes[1];  /* total number of elements */


    if ( fits_create_img(fptr, bitpix, naxis, naxes, &status))
         printerror( status );

    /* write the array of unsigned integers to the FITS */
    if ( fits_write_img(fptr, TUSHORT, fpixel, nelements, array[0], &status) )
        printerror( status );

    if ( fits_close_file(fptr, &status) )
         printerror( status );
  free(array[0]);
  return 0;
}



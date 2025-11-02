#include <stdio.h>
#include <string.h>
#include "fimage.h"
#include "fitsio.h"
void printerror(int status);
int main(int argc, char ** argv){
    fitsfile *fptr;       /* pointer to the FITS file, */
    int status;
    char filename[128];
            /* name of the file */
/* 300=n.columns=width 200=n.rows=height */
/* allocate memory for the whole image */

    long firstrow, firstelem;

    int tfields = 3;       /* table will have 3 columns> */
    long nrows  = 6;       /* table will have 6 rows   */

    char extname[] = "PLANETS_ASCII";             /* ex>*/

    /* define the name, datatype, and physical units fo>*/
    char *ttype[] = { "Planet", "Diameter", "Density" };
    char *tform[] = { "a8",     "I6",       "F4.2"    };
    char *tunit[] = { "\0",      "km",       "g/cm^2" };

    /* define the name diameter, and density of each pl>*/
    char *planet[] = {"Mercury", "Venus", "Earth", "Mars","Jupiter","Saturn"};
    long  diameter[] = {4880,    12112,    12742,   6800,  143000,   121000};
    float density[]  = { 5.1f,     5.3f,      5.52f,  3.94f,  1.33f,  0.69f};

    if ( argc < 2){
      fprintf(stderr,"usage:%s <filename.fits>\n",argv[0]);
      return 1;
    }
    strcpy(filename,argv[1]);

    remove(filename);               /* Delete old file */

    status = 0;         /* initialize status before call create_file */

    if (fits_create_file(&fptr, filename, &status)) /* create the file */
         printerror( status );           /* call printerror() */


/* append a new empty ASCII table onto the FITS fil>*/
    if ( fits_create_tbl( fptr, ASCII_TBL, nrows, tfields, ttype, tform,
                tunit, extname, &status) )
                printerror( status );
    firstrow  = 1;  /* first row in table to write   */     firstelem = 1;  /* first element in row  (ignored i */
    /* write names to the first column (character strin> */
    /* write diameters to the second column (longs) */      /* write density to the third column (floats) */
   fits_write_col(fptr, TSTRING, 1, firstrow, firstelem, nrows, planet, 
		   &status);
    /* write the array of unsigned integers to the FITS */
   fits_write_col(fptr, TLONG, 2, firstrow, firstelem, nrows, diameter,
                   &status);
   fits_write_col(fptr, TFLOAT, 3, firstrow, firstelem, nrows, density,
                   &status);
    if ( fits_close_file(fptr, &status) )
         printerror( status );
  return 0;
}


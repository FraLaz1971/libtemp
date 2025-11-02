#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fimage.h"
#include "fitsio.h"
#define STRLEN 128
int main(int argc, char ** argv){
    fitsfile *fptr;       /* pointer to the FITS file, */
    int status,i;
    char filename[128];
            /* name of the file */

    long firstrow, firstelem;

    int tfields;       /* table will have 3 columns> */
    long nrows;       /* table will have 6 rows   */

    char extname[] = "PLANETS_BINARY";             /* ex>*/

    /* define the name, datatype, and physical units fo>*/
    char **ttype;
    char **tform;
    char **tunit;

    /* define the name diameter, and density of each pl>*/
    char **planet;
    long  *diameter;
    float *density;
    if (argc < 4) {
      fprintf(stderr,"usage:%s <filename.fits> <ncols> <nrows>\n",argv[0]);
      return 1;
    } 
    strcpy(filename,argv[1]);
    tfields = atoi(argv[2]); /* table will have tfields columns> */
    nrows  = atoi(argv[3]);  /* table will have nrows rows   */
    /* define the name, datatype, and physical units fo>*/
    ttype=(char **)malloc(tfields*sizeof(char *));
    for(i=0;i<tfields;i++)
      ttype[i]=(char *)malloc(STRLEN);
    tform=(char **)malloc(tfields*sizeof(char *));
    for(i=0;i<tfields;i++)
      tform[i]=(char *)malloc(STRLEN);
    tunit=(char **)malloc(tfields*sizeof(char *));
    for(i=0;i<tfields;i++)
      tunit[i]=(char *)malloc(STRLEN);
    strcpy(ttype[0],"Planet");
    strcpy(ttype[1],"Diameter");
    strcpy(ttype[2],"Density");
    fprintf(stderr,"ttype set\n");
    strcpy(tform[0],"8A");
    strcpy(tform[1],"J");
    strcpy(tform[2],"E");
    fprintf(stderr,"tform set\n");

    strcpy(tunit[0],"\0");
    strcpy(tunit[1],"km");
    strcpy(tunit[2],"g/cm^2");
    fprintf(stderr,"tunit set\n");

    /* define the name diameter, and density of each pl>*/
    planet=(char **)malloc(nrows*sizeof(char *));
    for(i=0;i<nrows;i++)
      planet[i]=(char *)malloc(STRLEN);
    diameter=(long *)malloc(nrows*sizeof(long));
    density=(float *)malloc(nrows*sizeof(float));

    strcpy(planet[0],"Mercury");
    strcpy(planet[1],"Venus");
    strcpy(planet[2],"Earth"); 
    strcpy(planet[3],"Mars");
    strcpy(planet[4],"Jupiter");
    strcpy(planet[5],"Saturn");

    diameter[0] =  4880;
    diameter[1] =  12112;
    diameter[2] =  12742;
    diameter[3] =  6800;
    diameter[4] =  143000;
    diameter[5] =  121000;


    density[0] =  5.1f;
    density[1] =  5.3f;
    density[2] =  5.52f;
    density[3] =  3.94f;
    density[4] =  1.33f;
    density[5] =  0.69f;


    remove(filename);               /* Delete old file */

    status = 0;         /* initialize status before call create_file */

    if (fits_create_file(&fptr, filename, &status)) /* create the file */
         printerror( status );           /* call printerror() */


/* append a new empty ASCII table onto the FITS fil>*/
    if ( fits_create_tbl( fptr, BINARY_TBL, nrows, tfields, ttype, tform,
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
    free(ttype);
    free(tform);
    free(tunit);
    for(i=0;i<nrows;i++)
      free(planet[i]);
    free(planet);
    free(diameter);
    free(density);
    if ( fits_close_file(fptr, &status) )
         printerror( status );
  return 0;
}


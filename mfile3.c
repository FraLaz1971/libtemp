#include <stdlib.h>
#include "lfile1.h"
#include "lfile2.h"
int main(int argc, char **argv){
	FILE *lfp;
	struct curve2D mycurve;
	struct TM tm2;
	struct LOG mylog;
        if(argc<3){
	  fprintf(stderr,"usage:%s <infile.asc> <outfile.bin>\n",argv[0]);
	  return 1;
	}
	init_db(&tm2,&mylog);
	lfp=fopen("pipeline.log", "a");
	/* allocate memory for the data structure */
	mycurve.x=(int *)malloc(MAXSIZE*sizeof(int));
	mycurve.y=(int *)malloc(MAXSIZE*sizeof(int));
	read_curve_2D(argv[1],&mycurve,ASCII,&mylog,lfp);
	mycurve.x=(int *)realloc(mycurve.x,mycurve.size*sizeof(int));
	mycurve.y=(int *)realloc(mycurve.y,mycurve.size*sizeof(int));	
	save_curve_2D(argv[2],&mycurve, BINARY,&mylog,lfp);
	free(mycurve.x);
	free(mycurve.y);
	fclose(lfp);
	return 0;
}

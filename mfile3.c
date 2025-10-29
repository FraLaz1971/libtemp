#include <stdlib.h>
#include "lfile1.h"
#include "lfile2.h"
int main(){
	FILE *lfp;
	struct curve2D mycurve;
	struct TM tm2;
	struct LOG mylog;
	init_db(&tm2,&mylog);
	lfp=fopen("pipeline.log", "a");
	/* allocate memory for the data structure */
	mycurve.x=(int *)malloc(MAXSIZE*sizeof(int));
	mycurve.y=(int *)malloc(MAXSIZE*sizeof(int));
	read_curve_2D("parabola001.asc",&mycurve,ASCII,&mylog,lfp);
	save_curve_2D("curve001.bin",&mycurve, BINARY,&mylog,lfp);
	free(mycurve.x);	
	free(mycurve.y);
	fclose(lfp);
	return 0;
}

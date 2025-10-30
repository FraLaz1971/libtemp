#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lfile1.h"
#include "lfile2.h"
int main(int argc, char **argv){
	FILE *lfp; int i,res; char msg[512];
	struct array2D myimage;
	struct TM tm2;
	struct LOG mylog;
     if(argc<3){
	  fprintf(stderr,"usage:%s <image.asc> <image.bin>\n",argv[0]);
	  return 1;
	}
   myimage.plotter=(struct PLOTTER *)malloc(sizeof(struct PLOTTER));
/* open log file for writing */
	lfp=fopen("pipeline.log", "a");
	/* initialize resources */
	init_db(&tm2,&mylog);
	strcpy(mylog.caller,__func__);
    print_log("opened log file for writing",&mylog,lfp);
    print_log("initializing resources",&mylog,lfp);
	myimage.height=MAXSIZE;
	myimage.width=MAXSIZE;
	/* allocate memory for the data structure */
	strcpy(mylog.caller,__func__);
    print_log("allocating memory for the data structure",&mylog,lfp);
	myimage.arr=(int **)malloc(myimage.height*sizeof(int *));
	for(i=0;i<myimage.height;i++)
		myimage.arr[i]=(int *)malloc(myimage.width*sizeof(int));
	/* read image file into RAM and find actual width and height */
	strcpy(mylog.caller,__func__);
	snprintf(msg, 511,"reading image file %s into RAM and find actual width and height", argv[1]);
    print_log(msg,&mylog,lfp);	
    read_array_2D(argv[1],&myimage,ASCII,&mylog,lfp);
	/* reallocate for the correct dimensions */
	strcpy(mylog.caller,__func__);
    print_log("reallocate 2D array for the correct dimensions",&mylog,lfp);	
	myimage.arr=(int **)realloc(myimage.arr,myimage.height*sizeof(int *));
	for(i=0;i<myimage.height;i++)
		myimage.arr[i]=(int *)realloc(myimage.arr[i],myimage.width*sizeof(int));	
	/* save the image in raw binary format */
    print_log("saving the image in raw binary format",&mylog,lfp);	
	save_array_2D(argv[2],&myimage, BINARY,&mylog,lfp);
	/* plotting the just saved binary file with gnuplot in png format*/
	myimage.plotter->data_present=1;
	strcpy(myimage.plotter->ifile,argv[2]); 
	myimage.plotter->iftype = BINARY;
	myimage.plotter->oftype = PNG;
	res=plot_array_2D(&myimage,GNUPLOT,&mylog,lfp); 

	/* free the resources and close log file*/
	strcpy(mylog.caller,__func__);
	print_log("freeing resources and close log file",&mylog,lfp);
	free(myimage.plotter);
	for(i=0;i<myimage.height;i++)
		free(myimage.arr[i]);
	free(myimage.arr);
	fclose(lfp);
	return 0;
}

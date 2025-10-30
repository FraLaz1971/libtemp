#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lfile2.h"
int main(int argc, char **argv){
	struct TM tm2;
	struct LOG log2; char buf[64], mes[1024];
	struct curve2D curve;
	FILE *lfp2; int res;
    char *ofname="curve001.bin";
	curve.plotter=(struct PLOTTER *)malloc(sizeof(struct PLOTTER));
	if(argc<2){
		fprintf(stderr,"usage:%s <filename>\n",argv[0]);
		return 1;
	}
	init_db(&tm2,&log2);
	snprintf(buf,63,"mfile2::main()");
	strcpy(log2.caller,buf);
	snprintf(mes,1023,"starting program mfile2");
	strcpy(log2.msg,mes);
	lfp2 = fopen("pipeline.log","a");
	if(!lfp2){
		fprintf(stderr,"ERROR: cannot open log file pipeline.log for writing\n");
		return 1;
	}
	fprintf(lfp2,"test text\n");
	fflush(lfp2);
        //curve.logger->lfp = lfp2;
	print_log("executing",&log2,lfp2);
	snprintf(buf,63,"input file is %s",argv[1]);
	print_log(buf,&log2,lfp2);
	/* computing after here */
	//res = set_curve2D_log(&curve,&log2);
	res = init_curve_2D(&curve,&log2,lfp2);
	curve.x=(int *)malloc(MAXSIZE*sizeof(int));
	curve.y=(int *)malloc(MAXSIZE*sizeof(int));
	res = read_curve_2D("parabola001.asc",&curve,ASCII,&log2,lfp2);
    res = save_curve_2D(ofname, &curve, BINARY, &log2,lfp2);
    strcpy(curve.plotter->ifile,"mycurve.dat");
    curve.oftype=PNG;
    curve.plotter->data_present=0;
    res=plot_curve_2D(&curve,GNUPLOT,&log2,lfp2); 
    /* plot the saved binary file with plotutils graph */
    strcpy(curve.plotter->ifile,ofname);
	strcpy(log2.caller,"mfile2::main()");
	print_log("after strcpy(curve.plotter->ofile,ofname)",&log2,lfp2); 
    curve.oftype=GIF;
	strcpy(log2.caller,"mfile2::main()");
	print_log("going to plot a binary data file with plotutils graph",&log2,lfp2);
    curve.plotter->data_present=1;
    res=plot_curve_2D(&curve,PLOTUTILS,&log2,lfp2);
	strcpy(log2.caller,"mfile2::main()");
	print_log("going to free the resources",&log2,lfp2);
    res=destroy_curve_2D(&curve,&log2,lfp2);
	free(curve.x);
	free(curve.y);
	free(curve.plotter);
	strcpy(log2.caller,"mfile2::main()");
	print_log("program ended",&log2,lfp2);
	fclose(lfp2);
	return 0;
}

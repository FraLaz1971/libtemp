#include <string.h>
#include <stdlib.h>
#include "lfile1.h"
#include "lfile2.h"
extern int debug;
int init_curve_2D(struct curve2D *curve, struct LOG *logger,FILE *lfp){
        strcpy(logger->caller,"init_curve_2D()");
        print_log("starting curve",logger,lfp);
	return 0; 
}

int plot_curve_2D(struct curve2D *curve, int ptype, struct LOG *logger, FILE *lfp){
		unsigned long int i;
		/* data file pointer */
		FILE *df;
		/* batch file pointer */
		FILE *bf;
		/* total plot command string */
		char tpcmd[256], tlm[1024];
		/* plotter structure */
		struct PLOTTER myplot;
		/* data file name */
        strcpy(logger->caller,__func__);
        print_log("start plotting curve",logger,lfp);
        myplot.ifile=(char *)malloc(255);
		strcpy(myplot.ifile,"mycurve.dat");
        print_log("set plot input file name mycurve.dat",logger,lfp);
        /* set output driver */
        myplot.driver="png";
        /* set output plot file name */
        myplot.ofile=(char *)malloc(255);
        strcpy(myplot.ofile,"mycurve.png");
        /* switch between plot type */
        if (ptype==GNUPLOT){
			myplot.engine=GNUPLOT;
			myplot.pcmd=(char *)malloc(16);
			strcpy(myplot.pcmd,"gnuplot ");
			print_log("selected gnuplot plotting engine",logger,lfp);
        /* write plotter batch script */
        myplot.bfile=(char *)malloc(16);
		strcpy(myplot.bfile,"myplot.gp");
		myplot.xlabel=(char *)malloc(16); strcpy(myplot.xlabel,"x-axis");
		myplot.ylabel=(char *)malloc(16); strcpy(myplot.ylabel,"y-axis");
		myplot.title=(char *)malloc(32); strcpy(myplot.title, "Interesting Curve");
        bf=fopen(myplot.bfile, "w");
        fprintf(bf,"reset\n");
        fprintf(bf,"set term '%s'\n",myplot.driver);
        fprintf(bf,"set output '%s'\n",myplot.ofile);
        fprintf(bf,"set xlabel '%s'\n",myplot.xlabel);
        fprintf(bf,"set ylabel '%s'\n",myplot.ylabel);
        fprintf(bf,"set title '%s'\n",myplot.title);
        fprintf(bf, "plot '%s' using 1:2 with linespoints\n",myplot.ifile);
        fclose(bf);
		} else if (ptype==PLOTUTILS){
			myplot.engine=PLOTUTILS;
			print_log("selected plotutils graph plotting engine",logger,lfp);
		} else {
			strcpy(logger->level,"WARN");
			print_log("unknown plotting engine selected",logger,lfp);
			strcpy(logger->level,"INFO");
		}
        /* open data output file */
        df=fopen(myplot.ifile, "w");
        if(df==NULL) {
			strcpy(logger->level,"ERR");
			print_log("unknown plotting engine selected",logger,lfp);
			strcpy(logger->level,"INFO");
		}
        /* write data file */
        for(i=0;i<curve->size;i++){
			fprintf(df,"%d %d\n", curve->x[i],curve->y[i]);
		}        
        /* close data output file */
        fclose(df);
		print_log("data file written",logger,lfp);
        /* compose total batch command */
        snprintf(tpcmd,1023,"%s%s",myplot.pcmd, myplot.bfile);
        /* run batch command */
        snprintf(tlm,1023,"going to run on the system command %s", tpcmd);
        print_log(tlm,logger,lfp);
        system(tpcmd);
        /* free all resources */
		free(myplot.ifile);
		free(myplot.ofile);
		free(myplot.pcmd);
		free(myplot.xlabel);
		free(myplot.ylabel);
		free(myplot.title);
        print_log("curve plotted",logger,lfp);
	return 0; 
}

int read_curve_2D(const char *ifname,struct curve2D *curve, int ftype, struct LOG *logger, FILE *lfp){
	FILE *ifp; int cnt; char line[128];
	debug=1;
        strcpy(logger->caller,"read_curve_2D()");
        print_log("reading curve data",logger,lfp);
	if(ftype==ASCII){
        print_log("data format is ASCII",logger,lfp);
		cnt=0;
		ifp = fopen(ifname, "r");
		if (ifp == NULL) {
	        fprintf(stderr,"ERROR: no such file %s", ifname);
	        return 0;
		}
		while (fscanf(ifp, "%d %d\n", &curve->x[cnt],&curve->y[cnt]) == 2){
	        if (debug) fprintf(stderr,"read_curve_2D() x[%d]:%d y[%d]:%d\n",cnt,curve->x[cnt],cnt,curve->y[cnt]);
	        cnt++;
		}
		curve->size = cnt;
		fclose(ifp);
	}
        print_log("ended reading data",logger,lfp);
	return 0;
}

int save_curve_2D(const char *ofname, struct curve2D *curve, int ftype, struct LOG *logger, FILE *lfp){ 
        strcpy(logger->caller,__func__);
        print_log("saving curve on file",logger,lfp);
	return 0;
}
int set_curve2D_log(struct curve2D *curve, struct LOG *log){
        curve->logger = log;
	return 0;
}
int destroy_curve_2D(struct curve2D *curve, struct LOG * logger,FILE * lfp){ 
        strcpy(logger->caller,__func__);
        print_log("destroying curve",logger,lfp);
	return 0;
}

int init_array_2D(struct array2D *matrix){ 
	return 0;
}

int plot_array_2D(struct array2D *matrix, int ptype){ 
	return 0;
}

int read_array_2D(const char *ifname, struct array2D *matrix, int ftype){ 
	return 0;
}

int save_array_2D(const char *ifname, struct array2D *matrix, int ftype){ 
	return 0;
}
int set_array2D_log(struct array2D *matrix, struct LOG *log){
        matrix->logger = log;
	return 0;
}
int destroy_array_2D(struct array2D *matrix){
	return 0;
}

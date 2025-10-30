#include <string.h>
#include <stdlib.h>
#include "lfile1.h"
#include "lfile2.h"

extern int debug;
int init_curve_2D(struct curve2D *curve, struct LOG *logger,FILE *lfp){
        strcpy(logger->caller,__func__);
        print_log("starting curve",logger,lfp);
	return 0; 
}

int plot_curve_2D(struct curve2D *curve, int ptype, struct LOG *logger, FILE *lfp){
		int res=0;
		unsigned long int i;
		/* data file pointer */
		FILE *df;
		/* batch file pointer */
		FILE *bf;
		/* total plot command string */
		char tpcmd[256], tlm[1024], lmsg[256];
		/* plotter structure */
		struct PLOTTER myplot;
        strcpy(logger->caller,__func__);
        print_log("starting plot",logger,lfp);
		myplot.oftype = curve->plotter->oftype;
		myplot.data_present = curve->plotter->data_present;
		/* data file name */
        strcpy(logger->caller,__func__);
        print_log("start plotting curve",logger,lfp);
		strcpy(myplot.ifile,"mycurve.dat");
		if(myplot.data_present) {
			strcpy(myplot.ifile,"curve001.bin");
			fprintf(stderr,"the data to plot is yet present, file: %s\n",myplot.ifile);
			print_log("set plot input file name mycurve.dat",logger,lfp);
		} else{
        print_log("set plot input file name curve001.bin",logger,lfp);
		}
        /* set output driver */
        if (curve->oftype==PNG) {
			myplot.driver="png";
			/* set output plot file name */
			strcpy(myplot.ofile,"mycurve.png");
        print_log("plot output file set to mycurve.png",logger,lfp);
		} else if (curve->oftype==PS) {
			myplot.driver="ps";
			/* set output plot file name */
			strcpy(myplot.ofile,"mycurve.ps");
			print_log("plot output file set to mycurve.ps",logger,lfp);
		} else if (curve->oftype==GIF) {
			myplot.driver="gif";
			/* set output plot file name */
			strcpy(myplot.ofile,"mycurve.gif");
			print_log("plot output file set to mycurve.gif",logger,lfp);
		} else {
			strcpy(logger->level,"WARN");
			snprintf(lmsg,255,"unknown output file format: %d",curve->oftype);
			print_log(lmsg,logger,lfp);
			strcpy(logger->level,"INFO");
			/* default is png*/
			myplot.driver="png";
			/* set output plot file name */
			strcpy(myplot.ofile,"mycurve.png");
		}
        /* switch between plot type */
        if (ptype==GNUPLOT){
			myplot.engine=GNUPLOT;
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
			strcpy(myplot.pcmd,"sh ");
        /* write plotter batch script */
        myplot.bfile=(char *)malloc(16);
	if(__unix__)
		strcpy(myplot.bfile,"myplot.sh");
	else
		strcpy(myplot.bfile,"myplot.bat");
	myplot.xlabel=(char *)malloc(16); strcpy(myplot.xlabel,"x-axis");
	myplot.ylabel=(char *)malloc(16); strcpy(myplot.ylabel,"y-axis");
	myplot.title=(char *)malloc(32); strcpy(myplot.title, "Interesting Curve");
        bf=fopen(myplot.bfile, "w");
	if(__unix__)
	        fprintf(bf,"#!/bin/bash\n");
        fprintf(bf,"graph -T '%s' \\\n",myplot.driver);
        fprintf(bf, "-I i \\\n");
        fprintf(bf, "-m 3 -C \\\n");
        fprintf(bf,"-X '%s' \\\n",myplot.xlabel);
        fprintf(bf,"-Y '%s' \\\n",myplot.ylabel);
        fprintf(bf,"-L '%s' \\\n",myplot.title);
        fprintf(bf, "'%s' > \\\n",myplot.ifile);
        fprintf(bf,"'%s'\n",myplot.ofile);
        fclose(bf);
		} else {
			strcpy(logger->level,"WARN");
			print_log("unknown plotting engine selected",logger,lfp);
			strcpy(logger->level,"INFO");
		}
		if(!myplot.data_present){
        /* open data output file */
        snprintf(lmsg,255, "going to open file %s for writing", myplot.ifile);
		print_log(lmsg,logger,lfp);
        df=fopen(myplot.ifile, "w");
        if(df==NULL) {
			strcpy(logger->level,"ERR");
			print_log("error in opening data file for writing",logger,lfp);
			strcpy(logger->level,"INFO");
		}
        /* write data file */
	        for(i=0;i<curve->size;i++){
				fprintf(df,"%d %d\n", curve->x[i],curve->y[i]);
			}        
	        /* close data output file */
	        fclose(df);
			print_log("data file written",logger,lfp);
		}
        /* compose total batch command */
        snprintf(tpcmd,255,"%s%s",myplot.pcmd, myplot.bfile);
        /* run batch command */
        snprintf(tlm,1023,"going to run on the system command %s", tpcmd);
        print_log(tlm,logger,lfp);
        res = system(tpcmd);
        fprintf(stderr, "system res = %d", res);
        /* free all resources */
		free(myplot.xlabel);
		free(myplot.ylabel);
		free(myplot.title);
        print_log("curve plotted",logger,lfp);
	return 0; 
}

int read_curve_2D(const char *ifname,struct curve2D *curve, int ftype, struct LOG *logger, FILE *lfp){
	FILE *ifp; int cnt; char line[128];
    strcpy(logger->caller,__func__);
    print_log("starting reading",logger,lfp);
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
		char lmsg[256]; FILE *ofp; int i;
        strcpy(logger->caller,__func__);
        snprintf(lmsg,255, "saving curve on file %s", ofname);
        print_log(lmsg,logger,lfp);
        if(ftype==BINARY){
        ofp=fopen(ofname, "wb");
		snprintf(lmsg,255,"ofp = %p",ofp);
		print_log(lmsg,logger,lfp);
        if(ofp==NULL) {
			strcpy(logger->level,"ERR");
			print_log("error in opening binary data file for writing",logger,lfp);
			strcpy(logger->level,"INFO");
		}
		/* write data rows */
		snprintf(lmsg,255,"curve->size is %lu",curve->size);
		print_log(lmsg,logger,lfp);
		debug=1;
        for(i=0;i<curve->size;i++){
			fwrite(&curve->x[i],4,1,ofp);fwrite(&curve->y[i],4,1,ofp);
	        if (debug) fprintf(stderr,"save_curve_2D() x[%d]:%d y[%d]:%d\n",i,curve->x[i],i,curve->y[i]);
		}        
		debug=0;
        /* close ascii output file */
        fflush(ofp);
        fclose(ofp);
		} else if (ftype==ASCII){
			/* open ascii file for writing */
        /* write data file */
        ofp=fopen(ofname, "w");
        if(ofp==NULL) {
			strcpy(logger->level,"ERR");
			print_log("error in opening ascii data file for writing",logger,lfp);
			strcpy(logger->level,"INFO");
		}
		/* write data rows */
        for(i=0;i<curve->size;i++){
			fprintf(ofp,"%d %d\n", curve->x[i],curve->y[i]);
		}        
        /* close ascii output file */
        fclose(ofp);
		} else {
			strcpy(logger->level,"WARN");
			print_log("unhandled file type",logger,lfp);			
			strcpy(logger->level,"INFO");
		}
	return 0;
}
int set_curve2D_log(struct curve2D *curve, struct LOG *log, FILE * lfp){
        curve->logger = log;
	return 0;
}
int destroy_curve_2D(struct curve2D *curve, struct LOG * logger,FILE * lfp){ 
        strcpy(logger->caller,__func__);
        print_log("destroying curve",logger,lfp);
	return 0;
}

int init_array_2D(struct array2D *matrix, struct LOG *logger, FILE * lfp){ 
		strcpy(logger->caller,__func__);
		print_log("initing array 2D",logger,lfp);
	return 0;
}

int plot_array_2D(struct array2D *matrix, int ptype, struct LOG *logger, FILE * lfp){ 
		int res=0;
		unsigned long int i,j;
		/* data file pointer */
		FILE *df;
		/* batch file pointer */
		FILE *bf;
		/* total plot command string */
		char tpcmd[256], tlm[1024], lmsg[256];
		/* plotter structure */
		struct PLOTTER myplot;
		strcpy(logger->caller,__func__);
		print_log("starting plot array 2D (image)",logger,lfp);
		myplot.iftype = matrix->plotter->iftype;
		myplot.oftype = matrix->plotter->oftype;
		myplot.data_present = matrix->plotter->data_present;
		snprintf(lmsg,255,"iftype:%d oftype:%d data_present:%d",myplot.iftype,myplot.oftype,myplot.data_present);
		print_log(lmsg,logger,lfp);
		strcpy(myplot.ifile,matrix->plotter->ifile);
		/* data file name */
        strcpy(logger->caller,__func__);
        print_log("start plotting image",logger,lfp);
		strcpy(myplot.ifile,matrix->plotter->ifile);
		if(myplot.data_present) {
			snprintf(lmsg,255,"the data to plot is yet present, file: %s\n",myplot.ifile);
			print_log(lmsg,logger,lfp);
		} else{
			strcpy(myplot.ifile,"image.asc");
			print_log("set plot input file name curve001.bin",logger,lfp);
		}
        /* set output driver */
        if (myplot.oftype==PNG) {
			myplot.driver="png";
			/* set output plot file name */
			strcpy(myplot.ofile,"myimage.png");
			print_log("plot output file set to mycurve.png",logger,lfp);
		} else if (myplot.oftype==PS) {
			myplot.driver="eps";
			/* set output plot file name */
			strcpy(myplot.ofile,"myimage.eps");
			print_log("plot output file set to mycurve.ps",logger,lfp);
		} else if (myplot.oftype==GIF) {
			myplot.driver="gif";
			/* set output plot file name */
			strcpy(myplot.ofile,"myimage.gif");
			print_log("plot output file set to mycurve.gif",logger,lfp);
		} else {
			strcpy(logger->level,"WARN");
			snprintf(lmsg,255,"unknown output file format: %d",matrix->oftype);
			print_log(lmsg,logger,lfp);
			strcpy(logger->level,"INFO");
			/* default is png*/
			myplot.driver="png";
			/* set output plot file name */
			strcpy(myplot.ofile,"myimage.png");
		}
        /* switch between plot type */
        if (ptype==GNUPLOT){
			myplot.engine=GNUPLOT;
			strcpy(myplot.pcmd,"gnuplot ");
			print_log("selected gnuplot plotting engine",logger,lfp);
        /* write plotter batch script */
        myplot.bfile=(char *)malloc(16);
		strcpy(myplot.bfile,"image.gp");
        bf=fopen(myplot.bfile, "w");
        fprintf(bf,"reset\n");
        fprintf(bf,"set term '%s'\n",myplot.driver);
        fprintf(bf,"set output '%s'\n",myplot.ofile);
        fprintf(bf,"set size ratio -1\n");
        fprintf(bf,"set palette gray;\n");
        fprintf(bf,"unset xtics\n");
        fprintf(bf,"unset ytics\n");
        fprintf(bf,"unset label\n");
        fprintf(bf,"unset border\n");
        fprintf(bf,"unset colorbox\n");
        if(myplot.iftype==ASCII)
			fprintf(bf, "plot '%s' matrix with image\n",myplot.ifile);
		else if (myplot.iftype==BINARY)
			fprintf(bf, "plot '%s' binary array=(%lu,%lu) format='%%int' with image\n",myplot.ifile,
			matrix->width,matrix->height);
        fclose(bf);
		} else {
			strcpy(logger->level,"WARN");
			print_log("unknown plotting engine selected",logger,lfp);
			strcpy(logger->level,"INFO");
		}
		if(!myplot.data_present){
        /* open data output file */
        snprintf(lmsg,255, "going to open file %s for writing", myplot.ifile);
		print_log(lmsg,logger,lfp);
        df=fopen(myplot.ifile, "w");
        if(df==NULL) {
			strcpy(logger->level,"ERR");
			print_log("error in opening image data file for writing",logger,lfp);
			strcpy(logger->level,"INFO");
		}
        /* write image file */
	        for(i=0;i<matrix->height;i++){
				for(j=0;j<matrix->width;j++){
					fprintf(df,"%d ", matrix->arr[i][i]);
				}
				fprintf(df,"/n");
			}        
	        /* close data output file */
	        fclose(df);
			print_log("image data file written",logger,lfp);
		}
        /* compose total batch command */
        snprintf(tpcmd,255,"%s%s",myplot.pcmd, myplot.bfile);
        /* run batch command */
        snprintf(tlm,1023,"going to run on the system command %s", tpcmd);
        print_log(tlm,logger,lfp);
        res = system(tpcmd);
        fprintf(stderr, "system res = %d", res);
        /* free all resources */
        print_log("image plotted",logger,lfp);		
	return 0;
}

int read_array_2D(const char *ifname, struct array2D *matrix, int ftype, struct LOG *logger, FILE * lfp){ 
	FILE *ifp; int i,j; char line[MAXCHARS]; char *sep=" ";/* field separator */
	char *val; char msg[1024];
    strcpy(logger->caller,__func__);
    snprintf(msg,1023,"opening image file %s for reading", ifname);
    print_log(msg,logger,lfp);
	if(ftype==ASCII){
        print_log("data format is ASCII",logger,lfp);
		ifp = fopen(ifname, "r");
		if (ifp == NULL) {
	        fprintf(stderr,"ERROR: no such file %s", ifname);
	        return 0;
		}
		i=0;j=0;
		while (fgets(line,MAXCHARS,ifp)){ /* loop*/
			val = strtok(line," ");
			while(val&&(val[0]!='\n')){
				if(debug)fprintf(stderr, "val: %d len: %ld\n" , val[0], strlen(val));
				matrix->arr[i][j]=atoi(val);
				if (debug) fprintf(stderr,"%d ",matrix->arr[i][j]);
				val = strtok(NULL, " ");
				j++;
				if(i==0) matrix->width = j;
			}
			if (debug) fprintf(stderr,"\n");
			j=0;
			i++;
		}
        print_log("ended reading image data",logger,lfp);
		matrix->height = i;	
		snprintf(msg,512,"image width: %lu height: %lu \n", matrix->width,matrix->height);
		fclose(ifp);
        print_log("image input file closed ",logger,lfp);
	} /* process ASCII input case */
	return 0;
}

int save_array_2D(const char *ofname, struct array2D *matrix, int ftype, struct LOG *logger, FILE * lfp){ 
		char lmsg[256]; FILE *ofp; int i,j;
		strcpy(logger->caller,__func__);
		print_log("starting saving image 2D",logger,lfp);
        strcpy(logger->caller,__func__);
        snprintf(lmsg,255, "saving image on file %s", ofname);
        print_log(lmsg,logger,lfp);
        if(ftype==BINARY){
        ofp=fopen(ofname, "wb");
		snprintf(lmsg,255,"opened file %s for writing",ofname);
		print_log(lmsg,logger,lfp);
        if(ofp==NULL) {
			strcpy(logger->level,"ERR");
			print_log("error in opening binary data file for writing",logger,lfp);
			strcpy(logger->level,"INFO");
		}
		
		/* write image data  */

		snprintf(lmsg,255,"image width: %lu height: %lu",matrix->width,matrix->height);
		print_log(lmsg,logger,lfp);
        for(i=0;i<matrix->height;i++){
			for(j=0;j<matrix->width; j++){
				fwrite(&matrix->arr[i][j],4,1,ofp);;
				if (debug) fprintf(stderr,"%d ",matrix->arr[i][j]);
			}
		}
        /* close ascii output file */
        fclose(ofp);
		} else if (ftype==ASCII){
			/* open ascii file for writing */
        /* write data file */
        ofp=fopen(ofname, "w");
        if(ofp==NULL) {
			strcpy(logger->level,"ERR");
			print_log("error in opening ascii data file for writing",logger,lfp);
			strcpy(logger->level,"INFO");
		}
		/* write data rows */
        for(i=0;i<matrix->height;i++){
			for(j=0;j<matrix->width; j++){
				fprintf(ofp,"%d ", matrix->arr[i][j]);
			}
			puts("");
		}        
        /* close ascii output file */
        fclose(ofp);
		} else {
			strcpy(logger->level,"WARN");
			print_log("unhandled file type",logger,lfp);			
			strcpy(logger->level,"INFO");
		}

	return 0;
}
int set_array2D_log(struct array2D *matrix, struct LOG *log, FILE * lfp){
		strcpy(log->caller,__func__);
		print_log("starting setting log on array 2D",log,lfp);
        matrix->logger = log;
	return 0;
}
int destroy_array_2D(struct array2D *matrix, struct LOG *logger, FILE * lfp){
		strcpy(logger->caller,__func__);
		print_log("starting destroying array 2D",logger,lfp);
	return 0;
}

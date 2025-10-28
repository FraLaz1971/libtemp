#include "lfile1.h"
#include "lfile2.h"
extern int debug;
int init_curve_2D(struct curve2D *curve, struct LOG *logger,FILE *lfp){
        strcpy(logger->caller,"init_curve_2D()");
        print_log("starting curve",logger,lfp);
	return 0; 
}

int plot_curve_2D(struct curve2D *curve, int ptype, struct LOG *logger, FILE *lfp){ 
        strcpy(logger->caller,__func__);
        print_log("plotting curve",logger,lfp);
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

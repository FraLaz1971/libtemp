#include <stdio.h>
#include <string.h>
#include "lfile2.h"
int main(int argc, char **argv){
	struct TM tm2;
	struct LOG log2; char buf[1024];
	struct curve2D curve;
	FILE *lfp2; int res;
	if(argc<2){
		fprintf(stderr,"usage: <filename>\n",argv[0]);
		return 1;
	}
	init_db(&tm2,&log2);
	snprintf(buf,1023,"%s::main()",argv[0]);
	strcpy(log2.caller,buf);
	snprintf(buf,1023,"starting program %s",argv[0]);
	strcpy(log2.msg,buf);
	lfp2 = fopen("pipeline.log","a");
	if(!lfp2){
		fprintf(stderr,"ERROR: cannot open log file for writing\n",argv[0]);
		return 1;
	}
	print_log("executing",&log2,lfp2);
	snprintf(buf,1023,"input file is %s",argv[1]);
	print_log(buf,&log2,lfp2);
	/* computing after here */
	curve.x=(unsigned short *)malloc(MAXSIZE*sizeof(unsigned short));
	curve.y=(unsigned short *)malloc(MAXSIZE*sizeof(unsigned short));
	res = init_curve_2D(&curve);
	res = read_curve_2D("parabola001.asc",&curve,ASCII);
	/* computing stops here */
	free(curve.x);
	free(curve.y);
	print_log("program ended",&log2,lfp2);
	fclose(lfp2);
	return 0;
}

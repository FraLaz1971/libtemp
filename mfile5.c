#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lfile3.h"
#include "fimage.h"
int main(int argc, char **argv){
	struct PDS pds4;
	struct LOG log4;
	char msg[256];
	char ofname[256];
	FILE *lfp;
	int i, res;
	if(argc<3){
		fprintf(stderr, "usage:%s <infile> <datatype>\n",argv[0]);
		return 1;
	}
	/* initialize data table structure */
	init_log(&log4);
	init_pds(&pds4);
	lfp=fopen("pipeline.log","a");
	strcpy(log4.caller, "mfile5::main()");
	print_log("opened for writing log file pipeline.log",&log4,lfp);
	print_log("initializing data structures",&log4,lfp);
	pds4.version=4;
	pds4.stchk=(struct SIM_STC_HK*)malloc(sizeof(struct SIM_STC_HK));
	pds4.stchk->ACQUISITION_TIME_UTC=(char **)malloc(MAXSIZE*sizeof(char *));
	for(i=0;i<MAXSIZE;i++)
		pds4.stchk->ACQUISITION_TIME_UTC[i]=(char *)malloc(MAXSIZE*28); 
	pds4.stchk->ACQUISITION_TIME_SCET=(float *)malloc(MAXSIZE*sizeof(float));
	pds4.stchk->LAST_EVENT=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->COMMANDED_TEST_MODE=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->COMMANDED_TEC_STATUS=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->COMMANDED_DETECTOR_STATUS=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->COMMANDED_TEC_TREF=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->COMMANDED_TEC_N_P=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->COMMANDED_TEC_N_I=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->COMMANDED_TEC_N_E=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->ANTI_WIND_UP_STATUS=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->ANTI_WIND_UP_METHOD=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->COMMANDED_TEC_N_SS=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->PE_ADDRESS=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->PE_ADDRESS_CONTENT=(int *)malloc(MAXSIZE*sizeof(int)); 
	pds4.stchk->TEMPERATURE_FPA_1=(float *)malloc(MAXSIZE*sizeof(float)); 
	pds4.stchk->TEMPERATURE_FPA_2=(float *)malloc(MAXSIZE*sizeof(float)); 
	pds4.stchk->TEMPERATURE_PE=(float *)malloc(MAXSIZE*sizeof(float)); 
	pds4.stchk->TEMPERATURE_FPA_PACKAGE=(float *)malloc(MAXSIZE*sizeof(float)); /* channel 1 */
	pds4.stchk->TEMPERATURE_STC_OPTICAL_BENCH=(float *)malloc(MAXSIZE*sizeof(float)); /* channel 2 */ 
	pds4.stchk->VOLTAGE_AT_3_3V=(float *)malloc(MAXSIZE*sizeof(float)); 
	pds4.stchk->TEC_CURRENT=(float *)malloc(MAXSIZE*sizeof(float));
	print_log("memory allocation end",&log4,lfp);
	
	/* test assignment*/
	strcpy(pds4.stchk->ACQUISITION_TIME_UTC[0],"2020-12-14T21:43:04.178912Z");
	/* test reading */
	snprintf(msg,255,"ACQUISITION_TIME_UTC[0] is %s",pds4.stchk->ACQUISITION_TIME_UTC[0]);
	print_log(msg,&log4,lfp);
	/* read PDS4 file(s) in RAM */
	snprintf(msg,255,"going to read pds version %d file(s) %s",pds4.version,argv[1]);
	print_log(msg,&log4,lfp);
	res = read_pds_file(pds4.version, argv[1],&pds4, ASCII_TABLE, &log4, lfp);
	fprintf(stderr,"res: %d\n",res);
	/* do something */
	strcpy(ofname,"output.fits");
	strcpy(log4.caller, "mfile5::main()");
	snprintf(msg,255,"going to write pds version %d file(s) %s",pds4.version,ofname);
	print_log(msg,&log4,lfp);
	/* write PDS4 file(s) on file */
	res = write_pds_file(pds4.version, ofname,&pds4, FITS_BINARY_TABLE, &log4, lfp);
	fprintf(stderr,"res: %d\n",res);
	
	/* free resources */
	strcpy(log4.caller, "mfile5::main()");
	print_log("starting freeing resources",&log4,lfp);
	for(i=0;i<MAXSIZE;i++)
		free(pds4.stchk->ACQUISITION_TIME_UTC[i]); 
	free(pds4.stchk->ACQUISITION_TIME_UTC); 
	free(pds4.stchk->ACQUISITION_TIME_SCET);
	free(pds4.stchk->LAST_EVENT); 
	free(pds4.stchk->COMMANDED_TEST_MODE); 
	free(pds4.stchk->COMMANDED_TEC_STATUS); 
	free(pds4.stchk->COMMANDED_DETECTOR_STATUS); 
	free(pds4.stchk->COMMANDED_TEC_TREF); 
	free(pds4.stchk->COMMANDED_TEC_N_P); 
	free(pds4.stchk->COMMANDED_TEC_N_I); 
	free(pds4.stchk->COMMANDED_TEC_N_E); 
	free(pds4.stchk->ANTI_WIND_UP_STATUS); 
	free(pds4.stchk->ANTI_WIND_UP_METHOD); 
	free(pds4.stchk->COMMANDED_TEC_N_SS); 
	free(pds4.stchk->PE_ADDRESS); 
	free(pds4.stchk->PE_ADDRESS_CONTENT); 
	free(pds4.stchk->TEMPERATURE_FPA_1); 
	free(pds4.stchk->TEMPERATURE_FPA_2); 
	free(pds4.stchk->TEMPERATURE_PE); 
	free(pds4.stchk->TEMPERATURE_FPA_PACKAGE); /* channel 1 */
	free(pds4.stchk->TEMPERATURE_STC_OPTICAL_BENCH); /* channel 2 */ 
	free(pds4.stchk->VOLTAGE_AT_3_3V); 
	free(pds4.stchk->TEC_CURRENT);
	free(pds4.stchk);
	/* close log file */
	print_log("closing log file pipeline.log",&log4,lfp);
	fclose(lfp);

	return 0;
}

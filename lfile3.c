#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lfile3.h"
#include "fimage.h"
#include "fitsio.h"
extern int debug;
int init_pds(struct PDS *pds){
	pds->image=NULL;
	//pds->image->height=0;
	//pds->image->width=0;
	pds->curve=NULL;
	//pds->curve->size=0;
	pds->stchk=NULL;
	//pds->stchk->size=0;
	//pds->stchk->ncols=0;
	return 0;
}
int write_pds_file(int pdsver, char *fname,struct PDS *pds, int oftype,struct LOG *log, FILE *lfp){
	char msg[256];
	struct image img;
	strcpy(log->caller, __func__);
	snprintf(msg,255,"starting writing pds version %d file(s) %s ",pdsver,fname);
	print_log(msg,log,lfp);
	if( (pds->stchk!=NULL)||(pds->stchk->size>0)){ /* if stc hk data file has been read branch*/
		print_log("STC HK data table present in memory ",log,lfp);
		if(oftype==FITS_BINARY_TABLE){
			strcpy(img.fname,fname);
			img.status=0;
	fprintf(stderr,"write_pds_file() going to initialize the fits file\n");
	print_log("going to initialize the fits file",log,lfp);
	if(init_table(&img))fprintf(stderr,"error in initializing fits file\n");
	fprintf(stderr,"write_pds_file() image saved on file\n");
	print_log("image saved on file",log,lfp);
	if(set_chdu(1,&img))  fprintf(stderr,"error in setting the hdu\n");
	fprintf(stderr,"write_pds_file() hdu set\n");
	print_log("hdu set",log,lfp);
	if(add_stchk_table(&img, pds))  fprintf(stderr,"error in adding a table\n");
	fprintf(stderr,"write_pds_file() binary table addedd\n");
	print_log("FITS binary table added to file",log,lfp);
	} else {
			snprintf(msg,255,"unhandled output file format: %d",oftype);
			print_log(msg,log,lfp);
		}
	} /* if stc hk data file has been read branch end */ 
	else {
			print_log("no stc hk data table is in memory: not saving.",log,lfp);
	}
	return 0;
}
int read_pds_file(int pdsver, char *fname,struct PDS *pds, int iftype,struct LOG *log, FILE *lfp){
	FILE *ifp; int i,j,res; char line[4096]; char *sep=",";/* field separator */
	char *val; char msg[1024];
    strcpy(log->caller,__func__);
	snprintf(msg,255,"starting reading pds version %d file(s) %s",pdsver,fname);
	print_log(msg,log,lfp);
	val=(char *)malloc(4096); 
	pds->stchk->size=0;pds->stchk->ncols=0;
	if(iftype==ASCII_TABLE){
        print_log("data type is ASCII_TABLE",log,lfp);
		snprintf(msg,1023,"opening data table file %s for reading", fname);
		print_log(msg,log,lfp);
		ifp = fopen(fname, "r");
		snprintf(msg,1023,"input file pointer ifp = %p", ifp);
		print_log(msg,log,lfp);
		if (ifp == 0) {
	        fprintf(stderr,"ERROR: no such file %s", fname);
	        exit(1);
		}
		print_log("skipping the first row",log,lfp);
		/* read/skip intestation row */
		strcpy(val,fgets(line,4096,ifp));
		i=0;j=0;
		while (fgets(line,4096,ifp)){ /* loop on the lines (rows) */
			val = strtok(line,sep);
			while(val&&(val[0]!='\n')){ /* loop on the fields (columns) */
				if(debug)fprintf(stderr, "%s " , val);
				if(debug)fprintf(stderr, "reading row %d column %d \n",i ,j);
				switch(j){
					case 0:
						strcpy(pds->stchk->ACQUISITION_TIME_UTC[i],val);
						break;
					case 1:
						pds->stchk->ACQUISITION_TIME_SCET[i]=atof(val);
						break;
					case 2:
						pds->stchk->LAST_EVENT[i]=atoi(val);
						break;
					case 3:
						pds->stchk->COMMANDED_TEST_MODE[i]=atoi(val);
						break;
					case 4:
						pds->stchk->COMMANDED_TEC_STATUS[i]=atoi(val);
						break;
					case 5:
						pds->stchk->COMMANDED_DETECTOR_STATUS[i]=atoi(val);
						break;
					case 6:
						pds->stchk->COMMANDED_TEC_TREF[i]=atoi(val);
						break;
					case 7:
						pds->stchk->COMMANDED_TEC_N_P[i]=atoi(val);
						break;
					case 8:
						pds->stchk->COMMANDED_TEC_N_I[i]=atoi(val);
						break;
					case 9:
						pds->stchk->COMMANDED_TEC_N_E[i]=atoi(val);
						break;
					case 10:
						pds->stchk->ANTI_WIND_UP_STATUS[i]=atoi(val);
						break;
					case 11:
						pds->stchk->ANTI_WIND_UP_METHOD[i]=atoi(val);
						break;
					case 12:
						pds->stchk->COMMANDED_TEC_N_SS[i]=atoi(val);
						break;
					case 13:
						pds->stchk->PE_ADDRESS[i]=atoi(val);
						break;
					case 14:
						pds->stchk->PE_ADDRESS_CONTENT[i]=atoi(val);
						break;
					case 15:
						pds->stchk->TEMPERATURE_FPA_1[i]=atof(val);
						break;
					case 16:
						pds->stchk->TEMPERATURE_FPA_2[i]=atof(val);
						break;
					case 17:
						pds->stchk->TEMPERATURE_PE[i]=atof(val);
						break;
					case 18:
						pds->stchk->TEMPERATURE_FPA_PACKAGE[i]=atof(val);
						break;
					case 19:
						pds->stchk->TEMPERATURE_STC_OPTICAL_BENCH[i]=atof(val);
						break;
					case 20:
						pds->stchk->VOLTAGE_AT_3_3V[i]=atof(val);
						break;
					case 21:
						pds->stchk->TEC_CURRENT[i]=atof(val);
						break;
					default:
					fprintf(stderr,"extra column found: %d\n",j);
					snprintf(msg,255,"extra column found: %d\n",j);
					print_log(msg,log,lfp);
				}
				if (debug) fprintf(stderr,"%s ",val);
				val = strtok(NULL, sep);
				j++;
				if(i==0) pds->stchk->ncols = j;
			}
			if (debug) fprintf(stderr,"\n");
			j=0;
			i++;
		}
        print_log("ended reading image data",log,lfp);
		pds->stchk->size = i;
		snprintf(msg,512,"table rows: %lu, columns:%lu", pds->stchk->size,pds->stchk->ncols);
        print_log(msg,log,lfp);
		fclose(ifp);
	}
		free(val);
        print_log("ended reading data",log,lfp);
	return 0;
}

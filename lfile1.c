#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "lfile1.h"
int debug=0;
#if defined(_MSC_VER) && _MSC_VER < 1900
double round(double number)
{
    return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
}
#endif

 int init_db(struct TM *tm, struct LOG *log){
	char temp[2];
    fprintf(stderr,"init_db() init operations\n");
	ic=0;
	strcpy(log->utc, "2025-06-09T12:00:00");
	if (debug) printf("init_db() utc: %s\n",log->utc);
	strcpy(log->host, "localhost");
	if (debug) printf("init_db() host: %s\n",log->host);
	strcpy(log->caller, "lfile1::init_db()");
	if (debug) printf("init_db() caller: %s\n",log->caller);
	strcpy(log->level, "INFO");
	if (debug) printf("init_db() level: %s\n",log->level);
	strcpy(log->msg, "keep going");
	if (debug) printf("init_db() msg: %s\n",log->msg);
	strcpy(temp,"|");
	log->FS=temp[0];
	if (debug) printf("init_db() FS: %c\n",log->FS);
	strcpy(log->RS,"\r\n");
	if (debug) printf("init_db() RS: %s\n",log->RS);
  return 0;
}
int populate_db(struct TM *tm, FILE *ifp){
    int i;
    fprintf(stderr,"populate_db() going to read in memory data from the ascii file\n");
    for(i=0;i<DBSIZE;i++){
    tm[i].ID=ic++;
    fscanf(ifp,"%hu\n",&tm[i].APID);
    fscanf(ifp,"%hhu\n",&tm[i].PID);
    fscanf(ifp,"%hhu\n",&tm[i].CAT);
    fscanf(ifp,"%63s\n",tm[i].fname);
    fscanf(ifp,"%lu\n",&tm[i].size);
    fscanf(ifp,"%63s\n",tm[i].tstart);
    fscanf(ifp,"%63s\n",tm[i].tstop);
  }
  return 0;
}
int dump_db(struct TM *tm, FILE *ofp){
  int i;
  fprintf(stderr,"dump_db() dumping the structure array content on a file or stdout\n");
  for(i=0;i<DBSIZE;i++){
      fprintf(ofp,"ID: %lu\n",tm[i].ID);
      fprintf(ofp,"APID: %hu\n",tm[i].APID);
      fprintf(ofp,"PID: %hhu\n",tm[i].PID);
      fprintf(ofp,"CAT: %hhu\n",tm[i].CAT);
      fprintf(ofp,"fname: %s\n",tm[i].fname);
      fprintf(ofp,"size: %lu\n",tm[i].size);
      fprintf(ofp,"tstart: %s\n",tm[i].tstart);
      fprintf(ofp,"tstop: %s\n",tm[i].tstop);
  }
  return 0;
}

void leftpad(char *s,char c){
  int i,slen;
  slen=strlen(s);
  for(i=0;(i<slen)&&(s[i]==' ');++s){
    s[i]=c;
  }
  return ;
}

// yyyy-MM-ddThh:mm:ss
void getUTC(char *bcstrt, double ts){
	int year,mon,day,hour,min,sec;
    char smon[3],sday[3],shour[3],smin[3],ssec[3];
	char *dt;
	double mytime=ts;
	// Structure to store local time
    struct tm* ptr;
    // Variable to store current time
    time_t t;
	time_t mytimet=(time_t)mytime; /* input time seconds */
    double bcoffset = TIMEOFFS;
	double bctime=mytime+bcoffset;
	time_t bctimet=(time_t)bctime;
	time_t bt;
	double mytimeud; /* input time microseconds */
	unsigned int mytimeu;
	mytimeud = (mytime-(double)mytimet)*1000000.0;
	mytimeu = (unsigned int)round(mytimeud);
	if (debug) printf("read input time: %f\n",mytime);
	if (debug) printf("input time seconds: %ld\n",mytimet);
	if (debug) printf("input time microseconds (double): %f\n",mytimeud);
	if (debug) printf("input time microseconds (uint): %u\n",mytimeu);
    ptr = gmtime(&bctimet); 
    if (debug) printf("UTC: %s\n", asctime(ptr));    
  year=ptr->tm_year+1900;
  mon=ptr->tm_mon+1;
  snprintf(smon,3,"%2d",mon);
  snprintf(sday,3,"%2d",ptr->tm_mday);
  snprintf(shour,3,"%2d",ptr->tm_hour);
  snprintf(smin,3,"%2d",ptr->tm_min);
  snprintf(ssec,3,"%2d",ptr->tm_sec);
 
  leftpad(smon,'0'); 
  leftpad(sday,'0');
  leftpad(shour,'0');
  leftpad(smin,'0');
  leftpad(ssec,'0');
  
  snprintf(bcstrt,32,"%d-%2s-%2s:%2s:%2s:%2s",year,smon,\
  sday,shour,smin,ssec);
  if (debug) printf("getBC_UTC():BC Tm str: %s\n",bcstrt);
	return;
}
int getSecs(double *ts, char *bcstrt){
  return 0;
}
int print_log(char *msg, struct LOG *log, FILE *lfp){
	time_t s; /* seconds since 1970-01-01T00:00:00 */
	int year,mon,day,hour,min,sec;
    char smon[3],sday[3],shour[3],smin[3],ssec[3];
	char *dt; char msgbuf[2048]; int res;
	strcpy(log->msg,msg);
	    // Get current time
    s = time(NULL);
	getUTC(log->utc,s);
	if (debug) printf("print_log() utc: %s\n",log->utc);
	if (debug) printf("print_log() host: %s\n",log->host);
	if (debug) printf("print_log() caller: %s\n",log->caller);
	if (debug) printf("print_log() level: %s\n",log->level);
	if (debug) printf("print_log() msg: %s\n",log->msg);
	if (debug) printf("print_log() FS: %c\n",log->FS);
	if (debug) printf("print_log() RS: %s\n",log->RS);
	res = sprintf(msgbuf,"%s%c%s%c%s%c%s%c%s%s",(char *)log->utc,log->FS,(char *)log->host, log->FS,
	(char *)log->caller,log->FS,(char *)log->level,log->FS,(char *)log->msg,(char *)log->RS);
	fprintf(lfp,"%s",msgbuf);
  return res;
}
int destroy_db(struct TM *tm){
  fprintf(stderr,"destroy_db() going to free memory of the structure array\n");
/*  free(tm); */
  return 0;
}


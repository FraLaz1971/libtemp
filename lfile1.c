#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "lfile1.h"
#ifdef _MSC_VER
#include <windows.h>
#endif
#define WITHMS 1
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
	int year,mon,day,hour,min,sec,msec,usec;
    char smon[3],sday[3],shour[3],smin[3],ssec[3],smsec[4];
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
	if (debug) printf("lfile1::getUTC() bctime: %lf \n",bctime);
	if (debug) printf("lfile1::getUTC() bctimet: %ld \n",bctimet);
	usec = (bctime - bctimet)*1000000.0;
	if (debug) printf("lfile1::getUTC() usec: %d \n",usec);
	msec = usec/1000.0;
	if (debug) printf("lfile1::getUTC() msec: %d \n",msec);
    ptr = gmtime(&bctimet); 
    if (debug) printf("UTC: %s\n", asctime(ptr));    
  year=ptr->tm_year+1900;
  mon=ptr->tm_mon+1;
  snprintf(smon,3,"%2d",mon);
  snprintf(sday,3,"%2d",ptr->tm_mday);
  snprintf(shour,3,"%2d",ptr->tm_hour);
  snprintf(smin,3,"%2d",ptr->tm_min);
  snprintf(ssec,3,"%2d",ptr->tm_sec);
  snprintf(smsec,4,"%3d",msec);
 
  leftpad(smon,'0'); 
  leftpad(sday,'0');
  leftpad(shour,'0');
  leftpad(smin,'0');
  leftpad(ssec,'0');
  leftpad(smsec,'0');
#if defined(WITHMS) && WITHMS
  snprintf(bcstrt,32,"%d-%2s-%2sT%2s:%2s:%2s.%3s",year,smon,\
  sday,shour,smin,ssec,smsec);
#else
  snprintf(bcstrt,32,"%d-%2s-%2sT%2s:%2s:%2s",year,smon,\
  sday,shour,smin,ssec);
#endif
 
  if (debug) printf("getUTC():BC Tm str: %s\n",bcstrt);
	return;
}
/* return unix time seconds given UTC datetime string*/
int getSecs(double *ts, char *bcstrt){
  int year,month,day,hour,min,sec,i,res;
  char smon[3],sday[3],shour[3],smin[3],ssec[3];
  struct tm tmp; time_t t,s;
  res=sscanf(bcstrt,"%4d-%2d-%2dT%2d:%2d:%2d",
  &year,&month,&day,&hour,&min,&sec);
  //year=2025;month=10;day=27;hour=18;min=23;sec=34;
  tmp.tm_year=year-1900;
  tmp.tm_mon=month-1;
  tmp.tm_mday=day;
  tmp.tm_hour=hour;
  tmp.tm_min=min;
  tmp.tm_sec=sec;
  t = mktime(&tmp);
  if (debug) printf("lfile1::getSecs() t: %ld\n",t);
  tmp.tm_yday;
  if (debug) printf("lfile1::getSecs() tmp.hour: %d\n",tmp.tm_hour);
  if (debug) printf("lfile1::getSecs() tmp.yday: %d\n",tmp.tm_yday);
  /*
  *ts = (tmp.tm_year-70)*86400*365.25+tmp.tm_yday
  *86400+tmp.tm_hour*3600+tmp.tm_min*60+tmp.tm_sec; */
  *ts=(double)t;
  if (debug) printf("lfile1::getSecs() ts: %lf\n",*ts);
  return 0;
}
int print_log(char *msg, struct LOG *log, FILE *lfp){
	time_t t; /* seconds since 1970-01-01T00:00:00 */
	double s;
	int year,mon,day,hour,min,sec,msec;
    char smon[3],sday[3],shour[3],smin[3],ssec[3],smsec[4];
	char *dt; char msgbuf[2048]; int res;
    unsigned long nano;
#ifndef _MSC_VER
    struct timespec tres;
#else
    SYSTEMTIME st, lt;
#endif
	strcpy(log->msg,msg);
	    // Get current time
    t = time(NULL);
	if (debug) printf("print_log() t: %ld\n",t);
#ifndef _MSC_VER
    clock_gettime(CLOCK_REALTIME,&tres);
    nano = tres.tv_nsec;
#else
    GetSystemTime(&st);
    GetLocalTime(&lt);
    if (debug) printf("print_log() (MSVC) The system time is: %02d:%02d\n", st.wHour, st.wMinute);
    if (debug) printf("print_log() (MSVC) The local time is: %02d:%02d\n", lt.wHour, lt.wMinute);
    if (debug) printf("print_log() (MSVC) The system time ms are: %03d\n", st.wMilliseconds);
    if (debug) printf("print_log() (MSVC) The local time ms are: %03d\n", lt.wMilliseconds);
    nano = lt.wMilliseconds*1000000;
#endif
	if (debug) printf("print_log() nano: %lu\n",nano);
    s = (double)t+nano*0.000000001;
	if (debug) printf("print_log() s: %lf\n",s);

    /* read consecutive nanosecond values */
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
	perror(msgbuf); 
	fflush(lfp);
  return res;
}
int destroy_db(struct TM *tm){
  fprintf(stderr,"destroy_db() going to free memory of the structure array\n");
/*  free(tm); */
  return 0;
}
time_t datetime_to_epoch(const char* datetime_str){
    int res;
    struct tm timeinfo = {0};
// Parse the datetime string (yyyy-MM-ddThh:mm:ss f>
    res = sscanf(datetime_str, "%4d-%2d-%2dT%2d:%2d:%2d",
               &timeinfo.tm_year, &timeinfo.tm_mon, &timeinfo.tm_mday,
               &timeinfo.tm_hour, &timeinfo.tm_min, &timeinfo.tm_sec);
    printf("datetime_to_epoch() res from scanf() : %d\n",res);

    // Adjust struct tm values (tm_year is years since >
    timeinfo.tm_year -= 1900;
    timeinfo.tm_mon -= 1;

    // Convert to time_t (seconds since epoch)
    return mktime(&timeinfo);
}
void epoch_to_datetime(time_t epoch_seconds, char* buffer, size_t buffer_size){
    struct tm* timeinfo;
    // Convert epoch seconds to struct t
   timeinfo = localtime(&epoch_seconds);

    // Format as yyyy-MM-ddThh:mm:ss
    strftime(buffer, buffer_size, "%Y-%m-%dT%H:%M:%S", timeinfo);
}

/*

struct tm {
    // seconds,  range 0 to 59
    int tm_sec;

    // minutes, range 0 to 59
    int tm_min;

    // hours, range 0 to 23
    int tm_hour;

    // day of the month, range 1 to 31
    int tm_mday;

    // month, range 0 to 11
    int tm_mon;

    // The number of years since 1900
    int tm_year;

    // day of the week, range 0 to 6
    int tm_wday;

    // day in the year, range 0 to 365
    int tm_yday;

    // daylight saving time
    int tm_isdst;
}

*/

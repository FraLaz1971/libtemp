#ifndef LFILE1_H
#define LFILE1_H
#define DBSIZE 2
#define TIMEOFFS 0
#if defined(_MSC_VER) && _MSC_VER < 1900
#define __func__ __FUNCTION__
#endif
#if defined(_MSC_VER) && _MSC_VER < 1900
#define snprintf _snprintf
#endif
#include <stdio.h>
#include <stddef.h>
#include <time.h>
static size_t ic;
struct LOG{
	char utc[32];
	char host[24];
	char caller[24];
	char level[8];
	char msg[1024];
    char FS;
    char RS[3];
    FILE *lfp;
};

struct TM{
    unsigned long ID;
    unsigned short APID;
    unsigned char PID;
    unsigned char CAT;
    char fname[64];
    unsigned long size;
    char tstart[64];
    char tstop[64];
};
#if defined(_MSC_VER) && _MSC_VER < 1900
double round(double number);
#endif

int init_db(struct TM *tm, struct LOG *log);
int populate_db(struct TM *tm, FILE *ifp);
int dump_db(struct TM *tm, FILE *ofp);
void leftpad(char *s,char c);
void getUTC(char *bcstrt, double ts);
int getSecs(double *ts, char *bcstrt);
int get_log_date();
int get_log_host();
int get_log_caller();
int print_log(char *msg, struct LOG *log, FILE *lfp);
int destroy_db(struct TM *tm);
time_t datetime_to_epoch(const char* datetime_str);
void epoch_to_datetime(time_t epoch_seconds, char* buffer, size_t buffer_size);

#endif /* LFILE1_H */

#ifndef LFILE1_H
#define LFILE1_H
#define DBSIZE 2
#define TIMEOFFS 0
#if defined(_MSC_VER) && _MSC_VER < 1900
#define snprintf _snprintf
#endif
#include <stdio.h>
#include <stddef.h>
static size_t ic;
struct LOG{
	char utc[24];
	char host[24];
	char caller[24];
	char level[8];
	char msg[1024];
    char FS;
    char RS[2];
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

#endif /* LFILE1_H */

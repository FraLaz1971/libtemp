#ifndef LFILE1_H
#define LFILE1_H
#define DBSIZE 2

struct TM{
    unsigned short APID;
    unsigned char PID;
    unsigned char CAT;
    char fname[64];
    size_t size;
    char tstart[64];
    char tstop[64];
};

int init_db(struct TM *tm);
int populate_db(struct TM *tm, FILE *ifp);
int dump_db(struct TM *tm, FILE *ofp);
int destroy_db(struct TM *tm);

#endif /* LFILE1_H */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lfile1.h"
int main(int argc, char **argv){
  int res;
  char *fname, message[1024]="alive";
  char dtbuf[24]="2025-10-27T18:27:33";
  FILE *ifp=NULL;
  FILE *lfp=NULL;
  struct TM *tm=NULL;
  struct LOG *log=NULL;
  char *logfile="pipeline.log";
  char test1[32];
  double tv,sec;
  if(argc<2){
    fprintf(stderr,"usage:%s <inputfile.txt>\n",argv[0]);
    return 1;
  }
  tm=(struct TM*)malloc(DBSIZE*sizeof(struct TM));
  log=(struct LOG*)malloc(sizeof(struct LOG));
    res = init_db(tm, log);
    if(res){perror("main() error in initing the structures");exit(1);}
    fname=argv[1];
    ifp = fopen(fname, "r");
    lfp = fopen(logfile, "a");
    if (!ifp) {perror("main() cannot open file!");exit(1);}
    res = populate_db(tm, ifp);
    if(res){perror("main() error in populating the database");exit(1);}
    res = dump_db(tm, stdout);
    if(res){perror("main() error in dumping the database");exit(1);}
    tv=1761585814.0;
    printf("main::dt2e() tv: %lf\n",tv);
    getUTC(test1,tv);
    printf("main() UTC: %s\n",test1);
    epoch_to_datetime((long int)tv, dtbuf, 24);
    printf("main::e2dt() dt: %s\n",dtbuf);
    sec=(double)datetime_to_epoch(dtbuf);
    printf("main::dt2e() sec: %lf\n",sec);
    if (argc>2) strcpy(message, argv[2]);
    strcpy(log->caller,"mfile1::main()");
    res=print_log(message, log, stdout);
    printf("res: %d\n",res);
    if(!res){perror("main() error in printing log message");exit(1);}
    res=print_log(message, log, lfp);
    printf("res: %d\n",res);
    if(!res){perror("main() error in printing on file log message");exit(1);}
    res=getSecs(&sec,(char *)dtbuf);
    /* get back to seconds for CET time */
    sec+=3600;
    printf("main() sec: %lf\n",sec);
    getUTC(test1,sec);
    printf("main()2 UTC: %s\n",test1);
  fclose(ifp);
  fclose(lfp);
  free(log);
  free(tm);
  /*res = destroy_db(tm);*/
  return 0;
}

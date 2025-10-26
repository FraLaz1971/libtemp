#include <stdio.h>
#include "lfile1.h"

int main(){
    int i;
    char fname[]="tmdb.txt";
    FILE *ifp;
    struct TM tm[10];
    ifp=fopen(fname, "r");
    for(i=0;i<DBSIZE;i++){
        fscanf(ifp,"%hd",&tm[i].APID);
        fscanf(ifp,"%hhd",&tm[i].PID);
        fscanf(ifp,"%hhd",&tm[i].CAT);
        fscanf(ifp,"%s",tm[i].fname);
        fscanf(ifp,"%ld",&tm[i].size);
        fscanf(ifp,"%s",tm[i].tstart);
        fscanf(ifp,"%s",tm[i].tstop);
    }
  for(i=0;i<DBSIZE;i++){
      fprintf(stdout,"%hd\n",tm[i].APID);
      fprintf(stdout,"%hhd\n",tm[i].PID);
      fprintf(stdout,"%hhd\n",tm[i].CAT);
      fprintf(stdout,"%s\n",tm[i].fname);
      fprintf(stdout,"%ld\n",tm[i].size);
      fprintf(stdout,"%s\n",tm[i].tstart);
      fprintf(stdout,"%s\n",tm[i].tstop);
  }

    fclose(ifp);
}

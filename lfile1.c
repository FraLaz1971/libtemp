#include <stdlib.h>
#include <stdio.h>
#include "lfile1.h"
int init_db(struct TM *tm){
  fprintf(stderr,"init_db() going to allocate memory for the structure array\n");
  tm=(struct TM*)malloc(DBSIZE*sizeof(struct TM));
  return 0;
}
int populate_db(struct TM *tm, FILE *ifp){
    int i;
    fprintf(stderr,"populate_db() going to read in memory data from the ascii file\n");
    for(i=0;i<DBSIZE;i++){
    fscanf(ifp,"%hd\n",&tm[i].APID);
    fscanf(ifp,"%hhd\n",&tm[i].PID);
    fscanf(ifp,"%hhd\n",&tm[i].CAT);
    fscanf(ifp,"%s\n",tm[i].fname);
    fscanf(ifp,"%ld\n",&tm[i].size);
    fscanf(ifp,"%s\n",tm[i].tstart);
    fscanf(ifp,"%s\n",tm[i].tstop);
  }
  return 0;
}
int dump_db(struct TM *tm, FILE *ofp){
  int i;
  fprintf(stderr,"dump_db() dumping the structure array content on a file or stdout\n");
  for(i=0;i<DBSIZE;i++){
      fprintf(ofp,"%hd\n",tm[i].APID);
      fprintf(ofp,"%hhd\n",tm[i].PID);
      fprintf(ofp,"%hhd\n",tm[i].CAT);
      fprintf(ofp,"%s\n",tm[i].fname);
      fprintf(ofp,"%ld\n",tm[i].size);
      fprintf(ofp,"%s\n",tm[i].tstart);
      fprintf(ofp,"%s\n",tm[i].tstop);
  }
  return 0;
}
int destroy_db(struct TM *tm){
  fprintf(stderr,"destroy_db() going to free memory of the structure array\n");
  free(tm);
  return 0;
}

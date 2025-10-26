#include <stdio.h>
#include <stdlib.h>
#include "lfile1.h"
int main(int argc, char **argv){
  int res, i;
  char *fname;
  FILE *ifp=NULL, *ofp=NULL;
  struct TM *tm=NULL;
  tm=(struct TM*)malloc(DBSIZE*sizeof(struct TM));

  /*res = init_db(tm);*/
  if(argc<2){
    fprintf(stderr,"usage:%s <inputfile.txt>\n",argv[0]);
    return 1;
  }
    fname=argv[1];
    ifp = fopen(fname, "r");
    if (!ifp) {perror("cannot open file!");return 1;}
    res = populate_db(tm, ifp);
    res = dump_db(tm, stdout);
  fclose(ifp);
  free(tm);
  /*res = destroy_db(tm);*/
  return 0;
}

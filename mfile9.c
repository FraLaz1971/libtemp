#include <stdio.h>
#include <stdlib.h>
#include "lfile3.h"
int main(int argc,char **argv){
  int i,res;
  char *fname;
  FILE *ifp;
  struct curve2D curve;
  if(argc<2){
	fprintf(stderr,"usage:%s <infile.csv>\n",argv[0]);
    return 1;
  }
  curve.xd=(double *)malloc(MAXSIZE*sizeof(double));
  curve.yd=(double *)malloc(MAXSIZE*sizeof(double));
  curve.ttype=(char**)malloc(2*sizeof(char*));
  curve.ttype[0]=(char*)malloc(32);
  curve.ttype[1]=(char*)malloc(32);
  curve.tform=(char**)malloc(2*sizeof(char*));
  curve.tform[0]=(char*)malloc(32);
  curve.tform[1]=(char*)malloc(32);
  curve.tunit=(char**)malloc(2*sizeof(char*));
  curve.tunit[0]=(char*)malloc(32);
  curve.tunit[1]=(char*)malloc(32);
  fname=argv[1];
  ifp=fopen(fname,"r");
  /* read header */
  
  /* read column name (ttype) */
  res=fscanf(ifp,"%s %s\n",curve.ttype[0],curve.ttype[1]);
  fprintf(stderr,"res:%d\n",res);
  fprintf(stderr,"column names:%s %s\n",curve.ttype[0],curve.ttype[1]);
  /* read column format (tform) */
  res=fscanf(ifp,"%s %s\n",curve.tform[0],curve.tform[1]);
  fprintf(stderr,"res:%d\n",res);
  fprintf(stderr,"column names:%s %s\n",curve.tform[0],curve.tform[1]);
  /* read column phys. unit (tunit) */
  res=fscanf(ifp,"%s %s\n",curve.tunit[0],curve.tunit[1]);
  fprintf(stderr,"res:%d\n",res);
  fprintf(stderr,"column names:%s %s\n",curve.tunit[0],curve.tunit[1]);
  
  i=0;
  while(fscanf(ifp,"%lf %lf\n",&curve.xd[i],&curve.yd[i])==2){
	fprintf(stderr,"%lf %lf\n",curve.xd[i],curve.yd[i]);
	i++;
  } 
  curve.size=i;
  fprintf(stderr,"size:%lu\n",curve.size);
  free(curve.ttype[0]);
  free(curve.ttype[1]);
  free(curve.ttype);
  free(curve.tform[0]);
  free(curve.tform[1]);
  free(curve.tform);
  free(curve.tunit[0]);
  free(curve.tunit[1]);
  free(curve.tunit);
  free(curve.xd);
  free(curve.yd);
  fclose(ifp);
  return 0;
}

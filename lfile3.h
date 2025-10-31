#ifndef LFILE3_H
#define LFILE3_H
#include "lfile2.h"
struct PDS {
	int version;
	FILE *datafile;
	FILE *label;
	char idfile[256]; /* data input file name (e.g. "data.asc" or "data.bin")*/
	char odfile[256]; /* plot output file name (e.g. "myplot.png")*/
	char ilabel[256]; /* data input file name (e.g. "data.asc" or "data.bin")*/
	char olabel[256]; /* plot output file name (e.g. "myplot.png")*/
	int iftype; /* input data file format */
	int oftype; /* output data file format */
	int iltype; /* input label file format */
	int oltype; /* output label file format */
	struct curve2D *curve; /* pointer to the curve to archive */
	struct array2D *image; /* pointer to the image to archive */
	struct LOG *logger;
	struct SIM_STC_HK *stchk;
};
struct SIM_STC_HK {
	unsigned long size;
	unsigned long ncols;
	char extname[32];
	int hdutype;
	int hdunum;
	long firstrow;
	long firstelem;
	int tfields;/* n. of columns*/
	long nrows;/* n. of rows */
	char *ttype[255];
	char *tform[255];
	char *tunit[255];
	/* SIMBIO-SYS STC HouseKeeping data table */
	char **ACQUISITION_TIME_UTC; /* 0 */
	float *ACQUISITION_TIME_SCET;/* 1 */
	int *LAST_EVENT; /* 2 */
	int *COMMANDED_TEST_MODE;/* 3 */
	int *COMMANDED_TEC_STATUS; /* 4 */
	int *COMMANDED_DETECTOR_STATUS; /* 5 */
	int *COMMANDED_TEC_TREF; /* 6 */
	int *COMMANDED_TEC_N_P; /* 7 */
	int *COMMANDED_TEC_N_I; /* 8 */
	int *COMMANDED_TEC_N_E; /* 9 */
	int *ANTI_WIND_UP_STATUS; /* 10 */
	int *ANTI_WIND_UP_METHOD; /* 11 */
	int *COMMANDED_TEC_N_SS; /* 12 */
	int *PE_ADDRESS; /* 13 */
	int *PE_ADDRESS_CONTENT; /* 14 */
	float *TEMPERATURE_FPA_1; /* 15 */
	float *TEMPERATURE_FPA_2; /* 16 */
	float *TEMPERATURE_PE; /* 17 */
	float *TEMPERATURE_FPA_PACKAGE; /* channel 1 */ /* 18 */
	float *TEMPERATURE_STC_OPTICAL_BENCH; /* channel 2 */  /* 19  */
	float *VOLTAGE_AT_3_3V; /* 20 */
	float *TEC_CURRENT; /* 21 */
};
int init_pds(struct PDS *pds);
int write_pds_file(int pdsver, char *fname,struct PDS *pds, int oftype,struct LOG *log, FILE *lfp);
int read_pds_file(int pdsver, char *fname,struct PDS *pds, int iftype,struct LOG *log, FILE *lfp);
#endif /* LFILE3_H */

#include "fimage.h"
int allocate_array(int nbits,struct image *img){
  long int i;
  if(nbits==32)
	img->arr=(int *)malloc(img->nrows*img->ncols*sizeof(int));
  else if (nbits==16)
	img->arr16=(short int *)malloc(img->nrows*img->ncols*sizeof(short int));
  else if (nbits==8)
	img->arr8=(char *)malloc(img->nrows*img->ncols*sizeof(char));
  return img->status;
}
int fill_array(struct image *img){
long int i,j;
  for(i=0;i<img->nrows;i++)
    for(j=0;j<img->ncols;j++)
       set_element(i,j,++img->count,img);
  return img->status;
}
int print_array(struct image *img){
long int i,j;
  for(i=0;i<img->nrows;i++){
    for(j=0;j<img->ncols;j++)
       printf("%d ",get_element(i,j,img));
    puts("");
  }
  return img->status;
}
int free_array(struct image *img){
  long int i;
  if(img->bitpix==32)
    free(img->arr);
  if(img->bitpix==16)
    free(img->arr16);
  if(img->bitpix==8)
    free(img->arr8);
  fprintf(stderr,"free_array() freed the %d bit array\n",img->bitpix);
  return img->status;
}
int save_bin(struct image *img){
  /* remove the file if exists */
  fprintf(stderr,"save_bin() going to remove the file if yet existent\n");
  remove(img->fname);
  fprintf(stderr,"save_bin() file %s removed\n",img->fname);
  /* open fits file for writing */
//  if (fits_create_file(&img->ofp, img->fname, &img->status)) /* create new FITS file */
//         printerror( img->status );           /* call printerror if error occurs */
  img->ofp=(fitsfile *)fopen(img->fname,"wb");
//  fprintf(stderr,"save_bin() raw file created\n");
  /* create the image */
//  if ( fits_create_img(img->ofp, img->bitpix, img->naxis, img->naxes, &img->status) )
//         printerror( img->status );
//  fprintf(stderr,"save_bin() image created\n");
  /* initialize the array*/
	img->status=0;
/*  if(allocate_array(img->bitpix,img)) fprintf(stderr,"error in allocating array memory\n"); 
  fprintf(stderr,"save_fits() array allocated\n");
*/
  /* write the image */
  fprintf(stderr,"save_bin() raw file %s opened\n",img->fname);
  fprintf(stderr,"save_bin() size of the array %ld\n",img->nelements);
  if(img->bitpix==32){
        fprintf(stderr,"save_bin() going to write a 32 bits int image \n");
        fwrite(img->arr,img->nelements*4,1,(FILE *)img->ofp);
//  if ( fits_write_img(img->ofp, TINT, img->fpixel, img->nelements, img->arr, &img->status) )
//        printerror( img->status );
  } else if (img->bitpix==16) {
  fprintf(stderr,"save_bin() going to write a 16 bits int image \n");
        fwrite(img->arr16,img->nelements*2,1,(FILE *)img->ofp);
//  if ( fits_write_img(img->ofp, TSHORT, img->fpixel, img->nelements, img->arr16, &img->status) )
//        printerror( img->status );
  } else if (img->bitpix==8){
  fprintf(stderr,"save_bin() going to write a 8 bits int image \n");
//  if ( fits_write_img(img->ofp, TBYTE, img->fpixel, img->nelements, img->arr8, &img->status) )
//        printerror( img->status );
        fwrite(img->arr8,img->nelements,1,(FILE *)img->ofp);
  } else if (img->bitpix==-32){
  fprintf(stderr,"save_bin() going to write a 32 bits float image \n");
//  if ( fits_write_img(img->ofp, TFLOAT, img->fpixel, img->nelements, img->arr8, &img->status) )
//        printerror( img->status );
        fwrite(img->arr,img->nelements,1,(FILE *)img->ofp);
  }
  fprintf(stderr,"save_bin() raw file written\n");
  /* close fits file */
  //if ( fits_close_file(img->ofp, &img->status) ) /* close the file */
         //printerror( img->status );           
         fclose((FILE *)img->ofp);
  fprintf(stderr,"save_bin() raw file closed\n");
  return img->status;
}

int save_fits(struct image *img){
  /* remove the file if exists */
  fprintf(stderr,"save_fits() going to remove the file if yet existent\n");
  remove(img->fname);
  fprintf(stderr,"save_fits() file %s removed\n",img->fname);
  /* open fits file for writing */
  if (fits_create_file(&img->ofp, img->fname, &img->status)) /* create new FITS file */
         printerror( img->status );           /* call printerror if error occurs */
  fprintf(stderr,"save_fits() fits file created\n");
  /* create the image */
  if ( fits_create_img(img->ofp, img->bitpix, img->naxis, img->naxes, &img->status) )
         printerror( img->status );
  fprintf(stderr,"save_fits() image created\n");
  /* initialize the array*/
	img->status=0;
/*  if(allocate_array(img->bitpix,img)) fprintf(stderr,"error in allocating array memory\n"); 
  fprintf(stderr,"save_fits() array allocated\n");
*/
  /* write the image */
  fprintf(stderr,"save_fits() fits file opened\n");
  if(img->bitpix==32){
        fprintf(stderr,"save_fits() going to write a 32 bits image \n");
  if ( fits_write_img(img->ofp, TINT, img->fpixel, img->nelements, img->arr, &img->status) )
        printerror( img->status );
  } else if (img->bitpix==16) {
  fprintf(stderr,"save_fits() going to write a 16 bits image \n");
  if ( fits_write_img(img->ofp, TSHORT, img->fpixel, img->nelements, img->arr16, &img->status) )
        printerror( img->status );
  } else if (img->bitpix==8){
  fprintf(stderr,"save_fits() going to write a 8 bits image \n");
  if ( fits_write_img(img->ofp, TBYTE, img->fpixel, img->nelements, img->arr8, &img->status) )
        printerror( img->status );
  }
  fprintf(stderr,"save_fits() fits file written\n");
  /* close fits file */
  if ( fits_close_file(img->ofp, &img->status) ) /* close the file */
         printerror( img->status );           
  fprintf(stderr,"save_fits() fits file closed\n");
  return img->status;
}
int init_table(struct image *img){
  fprintf(stderr,"init_table() going to remove the file if yet existent\n");
  remove(img->fname);
  fprintf(stderr,"init_table() file %s removed\n",img->fname);
  /* open fits file for writing */
  fprintf(stderr,"init_table() going to open file for writing\n");
  
  img->status=0;
  if (fits_create_file(&img->ofp, img->fname, &img->status)) /* create new FITS file */
         printerror( img->status );           /* call printerror if error occurs */

  fprintf(stderr,"init_table() fits file created\n");
  return img->status;
}
void set_element(long rownum,long colnum,int val,struct image *img){
	if(img->bitpix==32){
		img->arr[rownum*img->ncols+colnum]=val;
	} else if(img->bitpix==16){
		img->arr16[rownum*img->ncols+colnum]=val;
	} else if (img->bitpix==8){
		img->arr8[rownum*img->ncols+colnum]=val;
    }
}
int get_element(long rownum,long colnum,struct image *img){
	if(img->bitpix==32){
		return img->arr[rownum*img->ncols+colnum];
    } else if(img->bitpix==16){
		return img->arr16[rownum*img->ncols+colnum];
    } else if(img->bitpix==8){
		return img->arr8[rownum*img->ncols+colnum];
	} else
	  return 0;
}
int load_fits(struct image *img){
long int i,j;
  /* open fits file for reading */
  img->status=0;
  fprintf(stderr,"load_fits() going to open file %s\n",img->ifname);
  if ( fits_open_file(&img->ifp, img->ifname, READONLY, &img->status) )
     printerror( img->status );
  fprintf(stderr,"load_fits() input fits file opened\n");
  /* load image in memory */
  if(fits_read_key(img->ifp, TLONG, (char*)"NAXIS", &img->naxis,
       (char*)img->cmt, &img->status)) printerror(img->status);
  fprintf(stderr,"naxis:%ld comment:%s\n",img->naxis,img->cmt);
  if(fits_read_key(img->ifp, TLONG, (char*)"NAXIS1", &img->naxes[0],
       (char*)img->cmt, &img->status)) printerror(img->status);
  fprintf(stderr,"naxes[0]:%ld comment:%s\n",img->naxes[0],img->cmt);
  if(fits_read_key(img->ifp, TLONG, (char*)"NAXIS2", &img->naxes[1],
       (char*)img->cmt, &img->status)) printerror(img->status);
  fprintf(stderr,"naxes[1]:%ld comment:%s\n",img->naxes[1],img->cmt);
  if(fits_read_key(img->ifp, TLONG, (char*)"BITPIX", &img->bitpix,
       (char*)img->cmt, &img->status)) printerror(img->status);
  fprintf(stderr,"bitpix:%d comment:%s\n",img->bitpix,img->cmt);
  img->ncols=img->naxes[0];
  img->nrows=img->naxes[1];
  img->nelements=img->naxes[0]*img->naxes[1];
  /* initialize the array*/
  img->status=0;
  if(allocate_array(img->bitpix,img)) fprintf(stderr,"error in allocating array memory\n");
  fprintf(stderr,"load_fits() array allocated\n");

  if(img->bitpix==32){
                  fprintf(stderr,"load_fits() reading a 32 bit per pixel image\n");
  if ( fits_read_img(img->ifp, TINT, img->fpixel, img->nelements, &img->nullval,
                  img->arr, &img->anynull, &img->status) ) printerror( img->status );
  } else if (img->bitpix==16){
                  fprintf(stderr,"load_fits() reading a 16 bit per pixel image\n");
  if ( fits_read_img(img->ifp, TSHORT, img->fpixel, img->nelements, &img->nullval,
                  img->arr16, &img->anynull, &img->status) ) printerror( img->status );
  } else if (img->bitpix==8){
                  fprintf(stderr,"load_fits() reading a 8 bit per pixel image\n");
  if ( fits_read_img(img->ifp, TBYTE, img->fpixel, img->nelements, &img->nullval,
                  img->arr8, &img->anynull, &img->status) ) printerror( img->status );
  }
  fprintf(stderr,"load_fits() image loaded in memory\n");
  /* close fits file */
  if ( fits_close_file(img->ifp, &img->status) ) printerror( img->status );
  fprintf(stderr,"load_fits() input fits file closed\n");
return img->status;
}

int set_chdu(int hdunum,struct image *img){
  img->chdu=hdunum;
  fprintf(stderr,"set_chdu() current hdu set to %d\n",img->chdu);
  fprintf(stderr,"set_chdu() going to open fits file %s\n",img->fname);
if (fits_open_file(&img->ofp, img->fname, READWRITE, &img->status) )
   printerror(img->status);
  fprintf(stderr,"set_chdu() opened fits file %s\n",img->fname);
if ( fits_movabs_hdu(img->ofp, img->chdu, &img->stable.hdutype, &img->status) )
  printerror(img->status);
  fprintf(stderr,"set_chdu() moved to hdu %d type %d\n",img->chdu,img->stable.hdutype);
  return img->status;
}
int add_stchk_table(struct image *img, struct PDS *pds){
	struct LOG log; FILE* lfp; char msg[256];
	init_log(&log);
	/* open log file for writing (append)*/
	lfp=fopen("pipeline.log","a");
	strcpy(log.caller, __func__);
	print_log("starting FITS BINARY TABLE",&log,lfp);

    img->stable.tfields = pds->stchk->ncols;/* table will have 22 columns */
    img->stable.nrows = pds->stchk->size;/* table will have 2120 rows    */
	snprintf(msg,255,"n.columns:%d n.rows:%ld ",img->stable.tfields,img->stable.nrows);
	print_log(msg,&log,lfp);

    img->stable.firstrow = 1;/* first row in table to write */
    img->stable.firstelem = 1;/* first elwment in row*/
    strcpy(img->stable.extname,"BC_SIM_STC_HK");           /* extension name */
	snprintf(msg,255,"extension name: %s ",img->stable.extname);
	print_log(msg,&log,lfp);

    /* define the name, datatype, and physical units for the 22 columns */
    img->stable.ttype[0]  = "ACQUISITION_TIME_UTC";
    img->stable.ttype[1]  = "ACQUISITION_TIME_SCET";
    img->stable.ttype[2]  = "LAST_EVENT";
    img->stable.ttype[3]  = "COMMANDED_TEST_MODE";
    img->stable.ttype[4]  = "COMMANDED_TEC_STATUS";
    img->stable.ttype[5]  = "COMMANDED_DETECTOR_STATUS";
    img->stable.ttype[6]  = "COMMANDED_TEC_TREF";
    img->stable.ttype[7]  = "COMMANDED_TEC_N_P";
    img->stable.ttype[8]  = "COMMANDED_TEC_N_I";
    img->stable.ttype[9]  = "COMMANDED_TEC_N_E";
    img->stable.ttype[10] = "ANTI_WIND_UP_STATUS";
    img->stable.ttype[11] = "ANTI_WIND_UP_METHOD";
    img->stable.ttype[12] = "COMMANDED_TEC_N_SS";
    img->stable.ttype[13] = "PE_ADDRESS";
    img->stable.ttype[14] = "PE_ADDRESS_CONTENT";
    img->stable.ttype[15] = "TEMPERATURE_FPA_1";
    img->stable.ttype[16] = "TEMPERATURE_FPA_2";
    img->stable.ttype[17] = "TEMPERATURE_PE";
    img->stable.ttype[18] = "TEMPERATURE_FPA_PACKAGE";
    img->stable.ttype[19] = "TEMPERATURE_STC_OPTICAL_BENCH";
    img->stable.ttype[20] = "VOLTAGE_AT_3_3V";
    img->stable.ttype[21] = "TEC_CURRENT";
	print_log("defined name of the columns (ttype)",&log,lfp);
    
    img->stable.tform[0] = "28a";
    img->stable.tform[1] = "1E";
    img->stable.tform[2] = "1J";
    img->stable.tform[3] = "1J";
    img->stable.tform[4] = "1J";
    img->stable.tform[5] = "1J";
    img->stable.tform[6] = "1J";
    img->stable.tform[7] = "1J";
    img->stable.tform[8] = "1J";
    img->stable.tform[9] = "1J";
    img->stable.tform[10] = "1J";
    img->stable.tform[11] = "1J";
    img->stable.tform[12] = "1J";
    img->stable.tform[13] = "1J";
    img->stable.tform[14] = "1J";
    img->stable.tform[15] = "1E";
    img->stable.tform[16] = "1E";
    img->stable.tform[17] = "1E";
    img->stable.tform[18] = "1E";
    img->stable.tform[19] = "1E";
    img->stable.tform[20] = "1E";
    img->stable.tform[21] = "1E";
	print_log("defined data type of the columns (tform)",&log,lfp);
    
    img->stable.tunit[0] = "time";
    img->stable.tunit[1] = "s";
    img->stable.tunit[2] = "";
    img->stable.tunit[3] = "";
    img->stable.tunit[4] = "";
    img->stable.tunit[5] = "";
    img->stable.tunit[6] = "";
    img->stable.tunit[7] = "";
    img->stable.tunit[8] = "";
    img->stable.tunit[9] = "";
    img->stable.tunit[10] = "";
    img->stable.tunit[11] = "";
    img->stable.tunit[12] = "";
    img->stable.tunit[13] = "";
    img->stable.tunit[14] = "";
    img->stable.tunit[15] = "ch";
    img->stable.tunit[16] = "ch";
    img->stable.tunit[17] = "ch";
    img->stable.tunit[18] = "ch";
    img->stable.tunit[19] = "ch";
    img->stable.tunit[20] = "ch";
    img->stable.tunit[21] = "V?";
    img->stable.tunit[22] = "A?";
	print_log("defined measurememnt unit of the columns (tunit)",&log,lfp);

  fprintf(stderr,"add_stchk_table() defined columns metadata\n");
  print_log("defined columns metadata",&log,lfp);
    /* write the data of each column */

  fprintf(stderr,"add_stchk_table() defined columns content\n");
if ( fits_create_tbl( img->ofp, BINARY_TBL,
img->stable.nrows, img->stable.tfields,
img->stable.ttype, img->stable.tform,
img->stable.tunit, img->stable.extname, &img->status) )
         printerror( img->status );
  fprintf(stderr,"add_stchk_table() created table\n");

    if(fits_write_col(img->ofp, TSTRING, 1, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->ACQUISITION_TIME_UTC,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 1\n");
    if(fits_write_col(img->ofp, TFLOAT, 2, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->ACQUISITION_TIME_SCET,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 2\n");
    if(fits_write_col(img->ofp, TINT, 3, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->LAST_EVENT,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 3\n");
    if(fits_write_col(img->ofp, TINT, 4, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->COMMANDED_TEST_MODE,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 4\n");
    if(fits_write_col(img->ofp, TINT, 5, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->COMMANDED_TEC_STATUS,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 5\n");
    if(fits_write_col(img->ofp, TINT, 6, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->COMMANDED_DETECTOR_STATUS,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 5\n");
    if(fits_write_col(img->ofp, TINT, 7, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->COMMANDED_TEC_TREF,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 7\n");
    if(fits_write_col(img->ofp, TINT, 8, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->COMMANDED_TEC_N_P,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 8\n");
    if(fits_write_col(img->ofp, TINT, 9, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->COMMANDED_TEC_N_I,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 9\n");
    if(fits_write_col(img->ofp, TINT, 10, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->COMMANDED_TEC_N_E,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 10\n");
    if(fits_write_col(img->ofp, TINT, 11, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->ANTI_WIND_UP_STATUS,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 11\n");
    if(fits_write_col(img->ofp, TINT, 12, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->ANTI_WIND_UP_METHOD,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 12\n");
    if(fits_write_col(img->ofp, TINT, 13, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->COMMANDED_TEC_N_SS,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 13\n");
    if(fits_write_col(img->ofp, TINT, 14, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->PE_ADDRESS,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 14\n");
    if(fits_write_col(img->ofp, TINT, 15, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->PE_ADDRESS_CONTENT,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 15\n");
    if(fits_write_col(img->ofp, TFLOAT, 16, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->TEMPERATURE_FPA_1,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 16\n");
    if(fits_write_col(img->ofp, TFLOAT, 17, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->TEMPERATURE_FPA_2,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 17\n");
    if(fits_write_col(img->ofp, TFLOAT, 18, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->TEMPERATURE_PE,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 18\n");
    if(fits_write_col(img->ofp, TFLOAT, 19, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->TEMPERATURE_FPA_PACKAGE,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 19\n");
    if(fits_write_col(img->ofp, TFLOAT, 20, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->TEMPERATURE_STC_OPTICAL_BENCH,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 20\n");
    if(fits_write_col(img->ofp, TFLOAT, 21, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->VOLTAGE_AT_3_3V,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 21\n");
    if(fits_write_col(img->ofp, TFLOAT, 22, img->stable.firstrow, img->stable.firstelem, img->stable.nrows, pds->stchk->TEC_CURRENT,
                   &img->status)) printerror(img->status);
    fprintf(stderr,"add_stchk_table() written column 22\n");
    if ( fits_close_file(img->ofp, &img->status) )
         printerror( img->status );
    fprintf(stderr,"add_table() closed fits file\n");
	fclose(lfp);
  return img->status;
}

void printerror( int status)
{
    /*****************************************************/
    /* Print out cfitsio error messages and exit program */
    /*****************************************************/
    if (status)
    {
       fits_report_error(stderr, status); /* print error report */
       exit( status );    /* terminate the program, returning error status */
    }
    return;
}

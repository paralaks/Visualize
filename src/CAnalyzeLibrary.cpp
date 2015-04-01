#include "CAnalyzeLibrary.h"

void swap_short(unsigned char *pntr)
{
  unsigned char b0, b1;
  b0 = *pntr;
  b1 = *(pntr+1);
  *pntr = b1;
  *(pntr+1) = b0;
}

void swap_long(unsigned char *pntr)
{
  unsigned char b0, b1, b2, b3;
  b0 = *pntr;
  b1 = *(pntr+1);
  b2 = *(pntr+2);
  b3 = *(pntr+3);
  *pntr = b3;
  *(pntr+1) = b2;
  *(pntr+2) = b1;
  *(pntr+3) = b0;
}

void swap_hdr(dsr* pntr)
{
  swap_long((unsigned char *) &pntr->hk.sizeof_hdr) ;
  swap_long((unsigned char *) &pntr->hk.extents) ;
  swap_short((unsigned char *) &pntr->hk.session_error) ;
  swap_short((unsigned char *) &pntr->dime.dim[0]) ;
  swap_short((unsigned char *) &pntr->dime.dim[1]) ;
  swap_short((unsigned char *) &pntr->dime.dim[2]) ;
  swap_short((unsigned char *) &pntr->dime.dim[3]) ;
  swap_short((unsigned char *) &pntr->dime.dim[4]) ;
  swap_short((unsigned char *) &pntr->dime.dim[5]) ;
  swap_short((unsigned char *) &pntr->dime.dim[6]) ;
  swap_short((unsigned char *) &pntr->dime.dim[7]) ;
  swap_short((unsigned char *) &pntr->dime.unused1) ;
  swap_short((unsigned char *) &pntr->dime.datatype) ;
  swap_short((unsigned char *) &pntr->dime.bitpix) ;
  swap_long((unsigned char *) &pntr->dime.pixdim[0]) ;
  swap_long((unsigned char *) &pntr->dime.pixdim[1]) ;
  swap_long((unsigned char *) &pntr->dime.pixdim[2]) ;
  swap_long((unsigned char *) &pntr->dime.pixdim[3]) ;
  swap_long((unsigned char *) &pntr->dime.pixdim[4]) ;
  swap_long((unsigned char *) &pntr->dime.pixdim[5]) ;
  swap_long((unsigned char *) &pntr->dime.pixdim[6]) ;
  swap_long((unsigned char *) &pntr->dime.pixdim[7]) ;
  swap_long((unsigned char *) &pntr->dime.vox_offset) ;
  swap_long((unsigned char *) &pntr->dime.funused1) ;
  swap_long((unsigned char *) &pntr->dime.funused2) ;
  swap_long((unsigned char *) &pntr->dime.cal_max) ;
  swap_long((unsigned char *) &pntr->dime.cal_min) ;
  swap_long((unsigned char *) &pntr->dime.compressed) ;
  swap_long((unsigned char *) &pntr->dime.verified) ;
  swap_short((unsigned char *) &pntr->dime.dim_un0) ;
  swap_long((unsigned char *) &pntr->dime.glmax) ;
  swap_long((unsigned char *) &pntr->dime.glmin) ;
}



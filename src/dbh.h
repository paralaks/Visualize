/*
 *
 * (c) Copyright, 1986-1995
 * Biomedical Imaging Resource
 * Mayo Foundation
 *
 * dbh.h
 *
 *
 * database sub-definitions
 */

#ifndef __DBH_H
#define __DBH_H

#include "CVoxel.h"

struct header_key          		        //      header_key
    {                                  		// off + size
        int sizeof_hdr;                		// 0 + 4
        char data_type[10];            		// 4 + 10
        char db_name[18];              		// 14 + 18
        int extents;                   		// 32 + 4
        short int session_error;       		// 36 + 2
        char regular;                  		// 38 + 1
        char hkey_un0;                 		// 39 + 1
    };           				// total=40

struct image_dimension      		        //      image_dimension
    {                               		// off + size
        short int dim[8];           		// 0 + 16
        char vox_units[4];			// 16 + 4
        char cal_units[8];			// 20 + 4
        short int unused1;			// 24 + 2
        short int datatype;			// 30 + 2
        short int bitpix;                   	// 32 + 2
        short int dim_un0;                      // 34 + 2
        float pixdim[8];                        // 36 + 32
        float vox_offset;                    	// 68 + 4
        float roi_scale;                        // 72 + 4
        float funused1;                      	// 76 + 4
        float funused2;                      	// 80 + 4
        float cal_max;                    	// 84 + 4
        float cal_min;                     	// 88 + 4
        int compressed;                     	// 92 + 4
        int verified;                     	// 96 + 4
        int glmax, glmin;                 	// 100 + 8
    };          				// total=108

struct data_history          		        //      data_history
    {                                    	// off + size
        char descrip[80];                	// 0 + 80
        char aux_file[24];               	// 80 + 24
        char orient;                     	// 104 + 1
        short int originator[5];       	        // 105 + 10
        char generated[10];              	// 115 + 10
        char scannum[10];                	// 125 + 10
        char patient_id[10];             	// 135 + 10
        char exp_date[10];               	// 145 + 10
        char exp_time[10];               	// 155 + 10
        char hist_un0[3];                	// 165 + 3
        int views;                       	// 168 + 4
        int vols_added;                  	// 172 + 4
        int start_field;                 	// 176 + 4
        int field_skip;                  	// 180 + 4
        int omax,omin;                   	// 184 + 8
        int smax,smin;                   	// 192 + 8
    };                     			// total=200

struct dsr                 		        //      dsr
    {                                  		// off + size
        struct header_key hk;          		// 0 + 40
        struct image_dimension dime;   		// 40 + 108
        struct data_history hist;      		// 148 + 200
    };                     			// total=348

/*
Acceptable values for hdr.dime.datatype
---------------------------------------
DT_NONE, DT_UNKNOWN, DT_BINARY, DT_UNSIGNED_CHAR, DT_SIGNED_SHORT
DT_SIGNED_INT, DT_FLOAT, DT_COMPLEX, DT_DOUBLE, DT_RGB, DT_ALL
*/

#define HEADER_SIZE                     348

#define IO_TRANSVERSE_UNFLIPPED         0
#define IO_CORONAL_UNFLIPPED            1
#define IO_SAGITTAL_UNFLIPPED           2
#define IO_TRANSVERSE_FLIPPED           3
#define IO_CORONAL_FLIPPED              4
#define IO_SAGITTAL_FLIPPED             5

#endif


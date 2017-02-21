/**********************************************************************
 *
 *  Copyright(c) 2016 Alcatel-Lucent.
 *  All rights reserved.
 *
 *  ALL RIGHTS ARE RESERVED BY ALCATEL-LUCENT.  ACCESS TO THIS
 *  SOURCE CODE IS STRICTLY RESTRICTED UNDER CONTRACT. THIS CODE IS TO
 *  BE KEPT STRICTLY CONFIDENTIAL.
 *
 *  UNAUTHORIZED MODIFICATIONS OF THIS FILE WILL VOID YOUR SUPPORT
 *  CONTRACT WITH ALCATEL-LUCENT.  IF SUCH MODIFICATIONS ARE FOR
 *  THE PURPOSE OF CIRCUMVENTING LICENSING LIMITATIONS, LEGAL ACTION
 *  MAY RESULT.
 *
 ***********************************************************************/

/*! \file log.c
* \brief log implementation
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup utils
*/


#define LOG_C

#include "log.h"

#define MAX_DUMP_SIZE 1500
FILE *log_file_g = NULL;
int log_level_g  = LOG_WARNING;

/***
 * Function get_comp_name()
 * Get each component's name
 *
 */
char * get_comp_name(comp_name_t type)
{
	switch (type)
	{
	case OUTER_INTERFACE:
		return "OUTER_INTERFACE";
		break;
	case INNER_INTERFACE:
		return "INNER_INTERFACE";
		break;
	case VENDOR_MANAGEMENT:
		return "VENDOR_MANAGEMENT";
		break;
	case ENVENT_PUSH:
		return "ENVENT_PUSH";
		break;
	case COLLAB_FILTER:
		return "COLLAB_FILTER";
		break;
	case OAI_IOTA_INTERFACE:
		return "OAI_IOTA_INTERFACE";
		break;
	default:
		return "";
		break;
	}
}

/***
 * Function str_to_num()
 * covert string to num
 *
 */
void str_to_num(char* source, char* dest, int len)
{
	int i = 0;
	char high_byte = 0;
	char low_byte = 0;
	
	for (i = 0; i < len; i+= 2)
	{
		high_byte = toupper(source[i]);
		low_byte  = toupper(source[i + 1]);
		if (high_byte > 0x39)
				high_byte -= 0x37;
		else
			high_byte -= 0x30;
		
		if (low_byte > 0x39)
			low_byte -= 0x37;
		else
			low_byte -= 0x30;
			
		dest[i / 2] = (high_byte << 4) | low_byte;
    }
}

/***
 * Function dump_msg_in_hex()
 * Dump the contains of a buffer in HEX to log file
 *
 */
void dump_msg_in_hex(char *buffer, int size)
{
	int i = 0;
	char output[MAX_DUMP_SIZE*4];
	char *p = output;

	for(i=0; i<size; i++)
	{
		if (i%16 == 0)
		{
			p += sprintf(p, "\n");
		}
		p += sprintf(p, "%02x ", (unsigned char)*buffer);
		buffer++;
	}
	
	PRT_LOG(LOG_INFO, "Raw data dump:%s\n", output);
}

/***
 * Function init_log()
 * Initialize the log utility
 * If no configuration file is specified, all log will be direct to standard error output
 *
 */
void init_log(char *log_file_name)
{
	if (log_file_name != NULL)
	{
		log_file_g = fopen(log_file_name, "a");

		if (log_file_g == NULL)
		{
			log_file_g = stderr;
			fprintf(stderr, "Failed to open log file %s errno %d: %s\n", log_file_name, errno, strerror(errno));
		}
	}
}


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

/*! \file common.h
* \brief back-end service common structure definition
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup main
*/

#ifndef __COMMON_H__
#define __COMMON_H__

/*
 * Configuration structure to store the IP/Port information for the LAMP and the local.
 */
typedef struct lamp_config_s {
	unsigned short lamp_port;
	char lamp_ip[16];
	unsigned short local_port;
	char local_ip[16];
	int socket_fd;
} lamp_config_t;
/*
 * App request information type
 */
typedef enum event_type_e {
	LOCATION,
	SMS,
	CALL,
	SEARCH,
	INVALID_EVENT
} EVENT_TYPE_T;

// max lamp info length
#define MAX_LEN 256
/*
 * lamp data update info.
 */
typedef struct lamp_data_s {
	EVENT_TYPE_T lamp_type;
	int lamp_uid;
	time_t lamp_date_time;
	char lamp_info[MAX_LEN];
	char add_info[MAX_LEN]
} lamp_data_t;
/*
 * Supported pattern recognition type
 */
typedef enum pr_type_e {
	LU_KUANG,
	RECOMMEND,
	EMPTY
} PR_TYPE_T;
/*
 * pattern recognition deal result
 */
typedef struct pr_result_s {
	PR_TYPE_T pr_type;
	char pr_prompt[MAX_LEN];
	char pr_special[MAX_LEN];
} pr_result_t;

// max data buffer size
#define MAX_MSG_SIZE 8*1024
// used for mysql DB access
#define MAX_MYSQL_BUF_SIZE 1024

#endif /* __COMMON_H__ */

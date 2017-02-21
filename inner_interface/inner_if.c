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

/*! \file inner_if.c
* \brief app --- back-end service inner interface deal
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup inner_if
*/


#define INNER_IF_C

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "../common.h"
#include "utils/log/log.h"
#include "app_api/app_api.h"
#include "outer_interface/jpush_api/jpush_api.h"
#include "outer_interface/baidu_api/baidu_api.h"
#include "pattern_recognition/pattern_recognition.h"

#include "inner_if.h"

/***
 * Function init_inner_interface()
 * Initialize the inner interface layer
 *
 */
void init_inner_interface()
{
	PRT_LOG_T(LOG_INFO, INNER_INTERFACE, "Start to init inner interface layer...\n");
	init_location_interface();
}

/***
 * handle message info coming from LAMP;
 * return: void
 */
 void handle_incoming_lamp_data(char *rcv_buf, int len, struct sockaddr_in remote_addr)
{
	int ret = 0;
	char *tmp_str = NULL;
	char tmp[64];
	//char *delim = "-";
	lamp_data_t lamp_data;
	//lamp_data_t test_lamp_data = {LOCATION, 500, 123406389, "劲松路", ""};
	pr_result_t pr_result;
	
	memset(&lamp_data, '\0', sizeof(lamp_data));
	
	PRT_LOG_T(LOG_INFO, INNER_INTERFACE, "Receive message from lamp\n");
	
	/*printf("%s \n", strtok(rcv_buf, delim));
	while (tmp_str = strtok(NULL, delim))
	{
		printf("%s \n", tmp_str);
	}*/
	
	dump_msg_in_hex(rcv_buf, len);
	
	unsigned char tmp_type = 0;
	memcpy(&tmp_type, rcv_buf, 1);
	lamp_data.lamp_type = atoi(&tmp_type);
	printf("lamp_data.lamp_type %d tmp_type %d\n", lamp_data.lamp_type, tmp_type);
	
	unsigned int tmp_uid = 0;
	memcpy(&tmp_uid, rcv_buf+1, 3);
	lamp_data.lamp_uid = atoi(&tmp_uid);
	printf("lamp_data.lamp_uid %d\n", lamp_data.lamp_uid);

	unsigned long int tmp_dt;
	memcpy(&tmp_dt, rcv_buf+4, 10);
	lamp_data.lamp_date_time = atoi(&tmp_dt);
	printf("lamp_data.lamp_date_time %d\n", lamp_data.lamp_date_time);
	
	if (!memcmp(rcv_buf+14, "ZSDL", 4))
	{
		memcpy(&lamp_data.lamp_info, "劲松路", 12);
		printf("lamp_data.lamp_info %s\n", lamp_data.lamp_info);
	}
	
	init_users();
	ret = pattern_recognition(&lamp_data, &pr_result);
	if (!ret)
	{
		PRT_LOG_T(LOG_ERR, INNER_INTERFACE, "Pattern recognition failure!!!");
		return;
	}
	
	//PRT_LOG_T(LOG_INFO, INNER_INTERFACE, "Pattern recognition deal is %s, msg is %s\n", pr_result.pr_prompt, pr_result.pr_special);
	printf("Pattern recognition deal is %s, msg is %s\n", pr_result.pr_prompt, pr_result.pr_special);
	memcpy(pr_result.pr_prompt, "离电影开场还有60分钟，现向您推荐李沧万达广场—味千拉面(独享50抵100)", 256);
	send_msg_to_jpush(pr_result.pr_prompt);
	
	//send_msg_to_baidu("baidu_place", pr_result.pr_special);
}


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

/*! \file xiao_zhi_main.c
* \brief back-end service entry implementation
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup main
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <mysql/mysql.h>

#include "common.h"

#include "utils/log/log.h"
#include "utils/db/db_mysql.h"
#include "inner_interface/inner_if.h"
#include "outer_interface/outer_if.h"
#include "pattern_recognition/pattern_recognition.h"

#include "xiao_zhi_main.h"

lamp_config_t    lamp_config;
// used for mysql DB access
MYSQL *g_mysql_conn = NULL;

/*
 * The entry of the xiao-zhi-app service program.
 * Options include:
 *  -l to specify the log level
 *  -f to specify the path of log file
 * */
int
main( int argc, char **argv)
{
	int ret;
	char log_file_name[128];
	char opt;
	pid_t pid;
	
	memset(log_file_name, 0, sizeof(log_file_name));
	
	while ((opt = getopt(argc, argv, "f:l:")) != -1)
	{
		switch (opt)
		{
		case 'f':
			strncpy(log_file_name, optarg, 127);
			break;
		case 'l':
            log_level_g = 0;
			log_level_g = atoi(optarg);
			if( (log_level_g < LOG_EMERG) || (log_level_g >= NUM_LOG_LEVEL) )
			{
				fprintf(stderr, "Invalid log level, use default %d\n", LOG_ERR);
				log_level_g = LOG_ERR;
			}
			fprintf(stdout, "Set log level to %d\n", log_level_g);
			break;
		default:
			fprintf(stderr, "Invalid option %c\n", opt);
			fprintf(stderr, "Usage: %s <-l log_level_g> <-f log file>\n", argv[0]);
			exit(1);
			break;
		}
	}
	
	if (log_file_name[0] == '\0')
	{
		//sprintf(log_file_name, "/tmp/%s_%d.log", argv[0], getpid());
		sprintf(log_file_name, "/tmp/xiao_zhi_app_service_%d.log", getpid());
	}

	printf("Log print to file %s\n", log_file_name);

	// put the process to back ground
	umask(0);
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Failed to fork new process, errno %d: %s\n", errno, strerror(errno));
		exit(1);
	}
	else if (pid != 0)
	{
		exit(0);
	}
	setsid();
	
	// init log utils
	(void)init_log(log_file_name);
	
	PRT_LOG(LOG_ERR, "############################################\n");
	PRT_LOG(LOG_ERR, "xiao-zhi-app service started\n");
	PRT_LOG(LOG_ERR, "############################################\n");
	
	// test db module
	/*char sql_info[MAX_MYSQL_BUF_SIZE];
	memset((void*)sql_info, 0, MAX_MYSQL_BUF_SIZE);
	sprintf(sql_info, "INSERT INTO `test`(`name`, `location`) VALUES('test', 'QD')");
	update_db_mysql(sql_info);
	memset((void*)sql_info, 0, MAX_MYSQL_BUF_SIZE);
	sprintf(sql_info, "SELECT * FROM `test`");
	query_db_mysql(sql_info);
	PRT_LOG(LOG_INFO, "Finish test DB module\n");*/
	
	// test collab module
	/*
	char* input = "20590 3.0 98925 5.0 8587 2.0";
	char* output = 0;
	
	output = collab_filter(input);
	PRT_LOG(LOG_INFO, "Result of collab_filter: %s\n", output);
	*/
	// test pattern_recognition module
	/*lamp_data_t lamp_data = {LOCATION, 500, 123406389, "劲松路"};
	pr_result_t pr_result;
	
	init_users();
	pattern_recognition(&lamp_data, &pr_result);
	*/
	// here deal module init
	(void)init_outer_interface();
	PRT_LOG(LOG_ERR, "Finish to init outer interface\n");
	(void)init_inner_interface();
	PRT_LOG(LOG_ERR, "Finish to init inner interface\n");
	
	
	// init sockets tmp give a dummy test value need to change later
	strncpy(lamp_config.lamp_ip, "192.168.168.128", sizeof(lamp_config.lamp_ip)-1);
	lamp_config.lamp_port = 8080;
	PRT_LOG(LOG_INFO, "LAMP ip=%s port=%d\n", lamp_config.lamp_ip, lamp_config.lamp_port);
	lamp_config.socket_fd = init_sockets(lamp_config.lamp_ip, lamp_config.lamp_port);
	
	// here maybe need start a thread to deal message from lamp
	(void)receive_from_lamp_by_port(lamp_config.socket_fd);
	
	return 0;
}


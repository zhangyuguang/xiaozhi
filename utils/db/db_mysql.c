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

/*! \file db_mysql.c
* \brief mysql DB interface implementation
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup utils
*/


#define DB_MYSQL_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#include "utils/log/log.h"
#include "../common.h"

#include "db_mysql.h"

/***
 * print latest error info
 * return: -
 */
void print_mysql_err(const char *msg)
{
	if (msg)
	{
		PRT_LOG(LOG_ERR, "%s: %s\n", msg, mysql_error(g_mysql_conn));
	}
	else
	{
		puts(mysql_error(g_mysql_conn));
	}
}

/***
 * initialization mysql db;
 * return: OK 0; NOK -1
 */
int init_db_mysql()
{
	const char *host_name = "localhost";
	const char *user_name = "root";
	const char *password = "openair";
	const char *db_name = "xiao_zhi";
	const unsigned int db_port = 3306;
	
	// init the database connection
	g_mysql_conn = mysql_init(NULL);

	// connect the database
	if(!mysql_real_connect(g_mysql_conn, host_name, user_name, password, db_name, db_port, NULL, 0))
	{
		PRT_LOG(LOG_ERR, "Mysql connecting failure!!!\n");
		print_mysql_err(NULL);
		return -1;
	}
	
	return 0;
}

/***
 * close mysql db;
 * return: OK 0; NOK -1
 */
int close_db_mysql()
{
	// close the database connection
	if (!g_mysql_conn)
	{
		PRT_LOG(LOG_ERR, "Mysql close failure due to g_mysql_conn=0x%x\n", g_mysql_conn);
		return -1;
	}
	
	mysql_close(g_mysql_conn);
	
	return 0;
}

/***
 * query mysql db;
 * return: OK 0; NOK -1
 */
int query_db_mysql(const char *sql)
{
	MYSQL_RES *mysql_res = NULL;
	MYSQL_ROW mysql_row;
	int rows = 0;
	int fields = 0;
	
	init_db_mysql();
	if (mysql_real_query(g_mysql_conn, sql, strlen(sql)))
	{
		PRT_LOG(LOG_ERR, "Mysql query failure!!!\n");
		print_mysql_err(NULL);
		return -1;
	}
	
	mysql_res = mysql_store_result(g_mysql_conn);
	if (NULL == mysql_res)
	{
		PRT_LOG(LOG_ERR, "Mysql store result failure!!!\n");
		print_mysql_err(NULL);
		return -1;
	}
	rows = mysql_num_rows(mysql_res);
	fields = mysql_num_fields(mysql_res);

	PRT_LOG(LOG_INFO, "Total recording=%d and each record has fileds=%d\n", rows, fields);
	puts("id\tname\n");
	while ((mysql_row=mysql_fetch_row(mysql_res)))
	{
		printf("%s\t%s\n", mysql_row[0], mysql_row[1]);
	}
	
	mysql_free_result(mysql_res);
	
	close_db_mysql();

	return 0;
}

/***
 * update mysql db;
 * return: OK 0; NOK -1
 */
int update_db_mysql(const char *sql)
{
	int rows = 0;
	int fields = 0;
	
	init_db_mysql();
	
	if (mysql_real_query(g_mysql_conn, sql, strlen(sql)))
	{
		PRT_LOG(LOG_ERR, "Mysql query failure!!!\n");
		print_mysql_err(NULL);
		return -1;
	}
	
	mysql_close(g_mysql_conn);

	return 0;
}

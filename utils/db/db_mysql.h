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

 /*! \file db_mysql.h
* \brief xiao-zhi-app service mysql DB interface
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup utils
*/

#ifndef __DB_MYSQL_H__
#define __DB_MYSQL_H__


#ifdef __cplusplus
extern "C" {
#endif

// used for mysql DB access
extern MYSQL *g_mysql_conn;

/*--- INTERFACES ---------------------------------------------------------------*/
#ifdef SOCKET_C
#	define private_db_mysql(x) x
#	define public_db_mysql(x) x
#else
#	define private_db_mysql(x)
#	define public_db_mysql(x) extern x
#endif

/** @defgroup mysql DB Interfaces
 * @{*/
public_db_mysql(int query_db_mysql(const char *sql);)
public_db_mysql(int update_db_mysql(const char *sql);)
/* @}*/
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif


#endif /* __DB_MYSQL_H__ */


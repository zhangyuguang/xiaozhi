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

/*! \file jpush_api.h
* \brief xiao-zhi-app service provide data deal with 3rd party API
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup outer_interface

*/

#ifndef __JPUSH_API_H__
#define __JPUSH_API_H__

/*--- INCLUDES ---------------------------------------------------------------*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*--- INCLUDES ---------------------------------------------------------------*/
#ifdef JPUSH_API_C
#	define private_outer_interface(x) x
#	define public_outer_interface(x) x
#else
#	define private_outer_interface(x)
#	define friend_outer_interface(x) extern x
#	define public_outer_interface(x) extern x
#	endif
/** @defgroup outer_interface
 * @{*/
public_outer_interface(void init_jpush_interface();)
public_outer_interface(int send_msg_to_jpush(char *push_info);)
/* @}*/
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif


#endif /* __JPUSH_API_H__ */



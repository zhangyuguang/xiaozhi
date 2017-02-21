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

/*! \file app_api.h
* \brief xiao-zhi-app service provide application layer used API
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup inner_interface

*/

#ifndef __INNER_INTERFACE_H__
#define __INNER_INTERFACE_H__

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
#ifdef INNER_INTERFACE_C
#	define private_inner_interface(x) x
#	define public_inner_interface(x) x
#else
#	define private_inner_interface(x)
#	define friend_inner_interface(x) extern x
#	define public_inner_interface(x) extern x
#	endif
/** @defgroup inner_interface
 * @{*/
public_inner_interface(void init_location_interface();)
/* @}*/
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif


#endif /* __INNER_INTERFACE_H__ */



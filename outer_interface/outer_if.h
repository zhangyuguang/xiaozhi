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

/*! \file outer_if.h
* \brief back-end service --- 3rd party outer interface deal
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup outer_if
*/

#ifndef __OUTER_IF_H__
#define __OUTER_IF_H__


#ifdef __cplusplus
extern "C" {
#endif

/*--- INTERFACES ---------------------------------------------------------------*/
#ifdef OUTER_IF_C
#	define private_outer_if(x) x
#	define public_outer_if(x) x
#else
#	define private_outer_if(x)
#	define public_outer_if(x) extern x
#endif

/** @defgroup OUTER Interfaces
 * @{*/
public_outer_if(void init_outer_interface();)
public_outer_if(void handle_to_outer_data(char *rcv_buf, int len, struct sockaddr_in remote_addr);)
/* @}*/
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif


#endif /* __OUTER_IF_H__ */


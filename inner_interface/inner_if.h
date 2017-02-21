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

/*! \file inner_if.h
* \brief app --- back-end service inner interface deal
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup inner_if
*/

#ifndef __INNER_IF_H__
#define __INNER_IF_H__


#ifdef __cplusplus
extern "C" {
#endif

/*--- INTERFACES ---------------------------------------------------------------*/
#ifdef INNER_IF_C
#	define private_inner_if(x) x
#	define public_inner_if(x) x
#else
#	define private_inner_if(x)
#	define public_inner_if(x) extern x
#endif

/** @defgroup INNER Interfaces
 * @{*/
public_inner_if(void init_inner_interface();)
public_inner_if(void handle_incoming_lamp_data(char *rcv_buf, int len, struct sockaddr_in remote_addr);)
/* @}*/
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif


#endif /* __INNER_IF_H__ */


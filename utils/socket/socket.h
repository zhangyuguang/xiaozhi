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

 /*! \file socket.h
* \brief xiao-zhi-app service socket communication
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup utils
*/

#ifndef __SOCKET_H__
#define __SOCKET_H__


#ifdef __cplusplus
extern "C" {
#endif

extern lamp_config_t    lamp_config;

/*--- INTERFACES ---------------------------------------------------------------*/
#ifdef SOCKET_C
#	define private_socket(x) x
#	define public_socket(x) x
#else
#	define private_socket(x)
#	define public_socket(x) extern x
#endif

/** @defgroup SOCKET Interfaces
 * @{*/
public_socket(int init_sockets(char ip[16], unsigned short port);)
public_socket(int send_to_lamp_by_port(int soket_fd, char *buffer, int length);)
public_socket(void receive_from_lamp_by_port(int soket_fd);)
/* @}*/
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif


#endif /* __SOCKET_H__ */


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

/*! \file outer_if.c
* \brief back-end service --- 3rd party outer interface deal
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup outer_if
*/


#define OUTER_IF_C

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "utils/log/log.h"
#include "../common.h"
#include "baidu_api/baidu_api.h"
#include "jpush_api/jpush_api.h"

#include "outer_if.h"

/***
 * Function init_outer_interface()
 * Initialize the outer interface layer
 *
 */
void init_outer_interface()
{
	PRT_LOG_T(LOG_ERR, OUTER_INTERFACE, "Start to init outer interface layer...\n");
	init_baidu_interface();
	init_jpush_interface();
}
 
/***
 * handle data info to outer layer;
 * return: void
 */
 void handle_to_outer_data(char *rcv_buf, int len, struct sockaddr_in remote_addr)
{

}


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

/*! \file socket.c
* \brief socket communication implementation
* \author Sean Wang
* \date 2016
* \version 1.0
* @ingroup utils
*/


#define SOCKET_C

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "utils/log/log.h"
#include "../common.h"

#include "socket.h"

/***
 * initialization the socket base on IP and port;
 * return: OK socket_fd; NOK -1
 */
int init_sockets(char ip[16], unsigned short port)
{
	int rc = -1;
	int socket_fd = -1;
	struct sockaddr_in  local_addr;
	struct in_addr      tmp_addr;

	//1. open socket
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socket_fd < 0)
	{
		PRT_LOG(LOG_ERR, "Open UDP socket failed, errno=%d: %s\n", errno, strerror(errno));
		return -1;
	}
	
	//2. bind socket
	memset((void*)&local_addr, 0, sizeof(local_addr));
	
	inet_aton(ip, &tmp_addr);
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);
	local_addr.sin_addr.s_addr = tmp_addr.s_addr;
	
	rc = bind(socket_fd, (struct sockaddr *)&local_addr, sizeof(local_addr));
	if (rc != 0)
	{
		PRT_LOG(LOG_ERR, "Bind to socket address failed: errno=%d: %s\n", errno, strerror(errno));
		return -1;
	}
	PRT_LOG(LOG_INFO, "Bind to socket address successful!!!\n");
	
	return socket_fd;
}

/***
 * send data to LAMP;
 * return: OK 1, NOK -1
 */
int send_to_lamp_by_port(int soket_fd, char *buffer, int length)
{
	int rc = -1;
	int result = 0;
	struct sockaddr_in remote_addr;
	
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(lamp_config.lamp_port);
	inet_aton((char*)&lamp_config.lamp_ip, &(remote_addr.sin_addr));
	
	PRT_LOG(LOG_INFO, "Parameters socket=%d, port=%d ,len=%d\n", soket_fd, lamp_config.lamp_port, length);
	
	result = sendto(soket_fd, buffer, length, 0, (struct sockaddr*)&(remote_addr), sizeof(struct sockaddr_in));
	if (result != length)
	{
		PRT_LOG(LOG_ERR, "Function sendto() failed result=%d, errno=%d: %s\n", result, errno, strerror(errno));
		rc = -1;
	}
	else
	{
		PRT_LOG(LOG_INFO, "Function sendto() OK\n");
		rc = 1;
	}
	return rc;
}

/***
 * receive data from LAMP;
 * return: void
 */
void receive_from_lamp_by_port(int soket_fd)
{
	char rcv_buf[MAX_MSG_SIZE];
	struct sockaddr_in remote_addr;
	int addr_len = 0;
	int len;
	struct timeval tv;
	fd_set read_fds;
	
	addr_len = sizeof(remote_addr);
	memset((void*)&remote_addr, 0, addr_len);
	
	PRT_LOG(LOG_INFO, "Begin to wait for incoming messages\n");
	for (;;)
	{
		FD_ZERO(&read_fds);
		FD_SET(soket_fd,&read_fds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		
		select(soket_fd, &read_fds, NULL, NULL, &tv);
		// read data from soket_fd, using FD_ISSET can deal the specified soket_fd;
		len = recvfrom(soket_fd, rcv_buf, sizeof(rcv_buf), 0, (struct sockaddr *)&remote_addr, &addr_len);
		if (len > 0)
		{
			if (len < 3)  // here we need to replace with the actually message length
			{
				PRT_LOG(LOG_ERR, "Invalid message received from ip:port=0x%x:%d with len=%d\n", ntohl(remote_addr.sin_addr.s_addr), ntohs(remote_addr.sin_port), len);
				continue;
			}
			PRT_LOG(LOG_INFO, "Message received from ip:port=0x%x:%d with len=%d\n", ntohl(remote_addr.sin_addr.s_addr), ntohs(remote_addr.sin_port), len);
			
			(void)handle_incoming_lamp_data(rcv_buf, len, remote_addr);
		}
	}
}


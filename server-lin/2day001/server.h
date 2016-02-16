#ifndef __SERVER_H__
#define __SERVER_H__
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <netdb.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/time.h>          
#include <sys/select.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stddef.h>
#include </usr/local/include/json/json.h>

#define LISTEN_NUM 5 
#define SERVER_PORT "8888"

#define handle_error(msg) \
		do { perror(msg); exit(EXIT_FAILURE); } while (0)

/*kenel list*/
struct kool_list
{
	struct list_head list;
	int from;
	int to;
};

#endif

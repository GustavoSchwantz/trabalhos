#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>

int call_socket (char *hostname, unsigned short portnum);

int main ()
{
	int s;

	s = call_socket ("gustavo-Inspiron-5566", 50000);

        write (s, "UM MONTE DE BOSTA!", 20);

	close (s);

	return 0;
}

int call_socket (char *hostname, unsigned short portnum) 
{ 
	struct sockaddr_in sa; 
	struct hostent *hp; 
	int a, s; 
	
	if ((hp= gethostbyname (hostname)) == NULL) {             /* do we know the host's */ 
		errno = ECONNREFUSED;                             /* address? */ 
		return (-1);                                      /* no */ 
	} 
	
	memset (&sa, 0, sizeof(sa)); 
	memcpy ((char *) &sa.sin_addr, hp->h_addr, hp->h_length); /* set address */ 
	
	sa.sin_family = hp->h_addrtype; 
	sa.sin_port = htons((u_short)portnum); 

	if ((s= socket(hp->h_addrtype,SOCK_STREAM,0)) < 0)        /* get socket */ 
		return(-1); 
	
	if (connect(s,&sa,sizeof sa) < 0) {                       /* connect */ 
		close(s); 
		return(-1); 
	} 
	
	return(s); 
}


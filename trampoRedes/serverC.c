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

int establish (unsigned short portnum);
int get_connection (int s);
int read_data (int s, char *buf, int n);

int main ()
{
	int s, t;

	if ((s = establish (50000)) < 0) { 
	       	perror ("establish"); 
		exit (1); 
	}

        printf ("Esperando por conexão...\n");

	if ((t = get_connection (s)) < 0) {   /* get a connection */ 
		perror("accept");             /* bad */ 
		exit(1); 
	}

        printf ("Conexão estabelecida!\n");

        char buffer [20];

        read_data (t, buffer, 20);

        printf ("Mensagem do cliente: ");
        puts (buffer);

        close (t);
        close (s);	

	return 0;
}

int establish (unsigned short portnum) 
{ 
	char myname[50+1]; 
	int s; 
	struct sockaddr_in sa; 
	struct hostent *hp; 
	
	memset (&sa, 0, sizeof (struct sockaddr_in));          /* clear our address */

	if ( gethostname (myname, 50) < 0 )  	               /* who are we? */
	        return (-1);

	hp = gethostbyname (myname);                           /* get our address info */ 
	
	if (hp == NULL)                                        /* we don't exist !? */ 
		return (-1); 
	
	sa.sin_family = hp->h_addrtype;                        /* this is our host address type */ 
	sa.sin_port = htons(portnum);                          /* this is our port number */ 
	
	if ((s = socket (AF_INET, SOCK_STREAM, 0)) < 0)        /* create socket */ 
		return (-1); 
	
	if (bind (s, &sa, sizeof (struct sockaddr_in)) < 0) { 
		close(s); 
		return(-1);                                    /* bind address to socket */ 
	} 
	
	listen (s, 3);                                          /* max # of queued connects */ 
	
	return (s); 
}

/* wait for a connection to occur on a socket created with establish() */ 
int get_connection (int s) 
{ 
	int t;                                  /* socket of connection */ 

	if ( (t = accept (s, NULL, NULL) ) < 0) /* accept connection if there is one */ 
		return (-1); 
	return (t); 
}

int read_data (int s, char *buf, int n) 
{ 
	int bcount;                                   /* counts bytes read */ 
	int br;                                       /* bytes read this pass */ 
	bcount= 0; 
	br= 0; 
	
	while (bcount < n) {                           /* loop until full buffer */ 
		if ((br= read(s,buf,n-bcount)) > 0) { 
			bcount += br;                  /* increment byte counter */ 
			buf += br;                     /* move buffer ptr for next read */ 
		} 
		else if (br < 0)                       /* signal an error to the caller */ 
			return(-1); 
	} 
	
	return(bcount); 
}

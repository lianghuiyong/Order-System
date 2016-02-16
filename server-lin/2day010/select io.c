#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STDIN 0

void display_pu();
void display_xx();
void display_time(int day,int hour,int mins,int sec);
int main()
{
	struct timeval tv;
	char buf[BUFSIZ];
	fd_set readfd;
	int re,i;
	int itime = 0;
	int d,h,m,s;
	d = h = m = s =0;
	while(1){
				display_pu();
				display_time(d,h,m,s);
		for(i = 0 ;i < 60; i++){
			s = i+1;
			d += h/24;
			if(h == 24)
				h = 0;
			h += m/60;
			if(m == 60)
				m = 0;
			m += s/60;
			if(s == 60)
				s = 0;
			tv.tv_sec = 1;
			tv.tv_usec = 0;
			FD_ZERO(&readfd);
			FD_SET(STDIN, &readfd); 
			if((re = select(STDIN+ 1,&readfd,NULL,NULL,&tv)) == -1){
				printf("select error\n");
			}
			else if(re == 0&&itime ==0){
				display_pu();
				display_time(d,h,m,s);
			}
			else if(FD_ISSET(STDIN,&readfd)){
				fgets(buf,BUFSIZ,stdin);
				if(!strcmp(buf,"\n"))
					display_xx();
				itime = 10;
			}
			if(itime!=0){
				display_xx();
				display_time(d,h,m,s);
				itime--;
			}
		}
	}
	return 0;
}

void display_pu()
{
				system("clear");

				printf("-----------pu tong shu ju--------------\n");
}
void display_xx()
{
				system("clear");
					printf("------------xiang xi shu ju------------\n");
}
void display_time(int day,int hour,int mins,int sec)
{
	printf("system runing time:\n-----day:%d hour:%d mins:%d sec:%d\n",day,hour,mins,sec);
}

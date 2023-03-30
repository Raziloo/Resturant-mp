#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<dirent.h>

int main(int argc,char* argv[])
{
	char *addstr, buf[256]={0};
	int fd1,filec=0;
	DIR *dirp;
	struct dirent *entry;

	if(argc!=2)
	{
		perror("Wrong number of parameters\n");
		exit(0);
	}

	if (!(addstr=(char*)malloc((strlen(argv[1])+8)*sizeof(char)))){
	printf("dir"); exit(0);
	}

//set directory address
	strcpy(addstr,"./");
	strcat(addstr,argv[1]);
	strcat(addstr,"_Order");

//check if restaurant listed
	if((fd1=open(addstr,O_RDONLY,0))==-1)
	{
		printf("Resturant Not Found!\n");
		exit(0);
	}
//open restaurant orders directory
	if ((dirp = opendir(addstr))==NULL)
	{
		printf("failed to open dir");
		exit(0);
	}
//count txt files in directory
	while((entry=readdir(dirp))!=NULL)
	{
		if((strstr(entry->d_name,".txt"))!=NULL) 
		{
			filec++;
		}
	}
	if(filec!=0) 	
	printf("%d Orders\n",filec);
	else printf("No orders Yet\n");

	closedir(dirp);
	return 1;
}

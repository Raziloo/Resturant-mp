#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(int argc,char* argv[])
{
	char buff[1024]={0};
	int fd,f1;

	if(argc!=2)
	{
		perror("Wrong number of parameters.");
		exit(1);
	}

//get restaurant name
	strcpy(buff,argv[1]);

//open restaurant menu file to read
	if((fd=open(argv[1],O_RDONLY,0))==-1)
	{
		perror("Read");
		exit(1);
	}
//read file and print menu to screen
do
	{
		if((f1=read(fd,buff,1024))==-1)
		{
			perror("read");
			exit(1);
		}
		printf("%s",buff);
		strcpy(buff,"");
	}
	while(f1!=0);
	close(fd);
	return 1;
}
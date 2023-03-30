#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(int argc,char* argv[])
{
	int fd1,f1,count7,i;
	char buff[1024],price[256],*temp,strdish[256];

	if(argc<3)
	{
		perror("Wrong number of parameters");
		exit(1);
	}

//open restaurant menu file 
	if((fd1=open(argv[1],O_RDONLY,0))==-1)
	{
		printf("Resturant Not Found!\n");
		exit(0);
	}

//read file & seek for dish to get its price
if((f1=read(fd1,buff,1024)==-1))
	{
		perror("Write");
		close(fd1);
		exit(1);
	}
	strcpy(strdish,"   ");
	for(i=2;i<argc;i++)
	{
		strcat(strdish,argv[i]);
		strcat(strdish," ");
	}
	strcat(strdish,".");
	strcpy(price,"");
	temp=strstr(buff,strdish);

	if(temp!=NULL)
	{
	temp=temp+21;
		count7=0;
		while(temp[count7]>='0' && temp[count7]<='9')
		{
			strncat(price,&temp[count7],1);
			count7++;
		}
	printf("%s NIS\n",price);
	}

//report if dish not found
	else printf("Dish not found\n");
	return 1;
}


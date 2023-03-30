#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<time.h>

int main(int argc,char* argv[])
{
	time_t tm;
   	 time(&tm);
	int fd1,f1,fd2,f2,sum,k,w,q,len=0,numtemp,count7;
	char str[256],buff[1024],price[10]={0},addstr[256],totstr[256],ordstr[256],numarr[256],chararr[256],app[256],sumstr[256];
	char* temp;

	if(argc!=3)
	{
		printf("Please enter the right parameters\n");
		exit(0);
	}

//open restaurant menu file
if((fd1=open(argv[1],O_RDONLY,0))==-1)
	{
		printf("Resturant not found.\n");
		exit(0);
	}

//set order file address...
	strcpy(addstr,"");
	strcat(addstr,argv[1]);
	strcat(addstr,"_Order/");
	strcat(addstr,argv[2]);
	strcat(addstr,".txt");

//create order file
	if((fd2=open(addstr,O_WRONLY | O_CREAT,0777))==-1)
	{
		perror("Write");
		exit(1);
	}

	strcpy(ordstr,argv[1]);
	strcat(ordstr," Order\n\n");

	if((f2=write(fd2,ordstr,strlen(ordstr)))==-1)
	{
		perror("Write2");
		close(fd2);
		exit(1);
	}

//get input from user until "finish"
	sum=0;
	printf("Insert your order (Finish to finish):\n");
	fgets(str,sizeof(str),stdin);
	str[strlen(str)-1]='\0';

	do{
	q=0;
	w=0;
	for(k=0;k<strlen(str);k++)
		{
				if(str[k]>='0'&&str[k]<='9')
				{
					numarr[q++]=str[k];
				}
				else chararr[w++]=str[k];
		}
	numarr[q]='\0';
	chararr[w]='\0';
	strcat(str,"\n");

//print order to file
		if((f2=write(fd2,str,strlen(str)))==-1)
		{
			perror("Write3");
			close(fd2);
			exit(1);
		}

//find dish in the menu
			if((f1=read(fd1,buff,1024))==-1)
			{
				perror("read");
				exit(1);
			}
			temp=strstr(buff,chararr);
			if(temp==NULL)
			{
				printf("Dish not Found");
				exit(0);
			}
			temp=temp+18;
			count7=0;
//get price
			while(temp[count7]>='0' && temp[count7]<='9')
			{
				strncat(price,&temp[count7],1);
				count7++;
			}
			sum=sum+(atoi(price)*atoi(numarr));
			strcpy(price,"");
			fgets(str,sizeof(str),stdin);
			str[strlen(str)-1]='\0';
	}while(strcmp(str,"Finish")!=0 && strcmp(str,"finish")!=0);

//calculate total price
	strcpy(totstr,"Total Price: ");
	numtemp=sum;
	while(numtemp)
	{
		len++;
		numtemp/=10;
	}
sumstr[len--]=0;
	while(sum)
	{
		sumstr[len--]=(sum%10)+'0';
		sum/=10;
	}
	strcat(totstr,sumstr);
	strcat(totstr,"NIS\n\n");
	printf("%s",totstr);
	strcat(totstr,ctime(&tm));

//get approval
	printf("(Confirm to approve/else cancel)\n");
	fgets(app,sizeof(app),stdin);
	app[strlen(app)-1]='\0';
	if(strcmp(app,"Confirm")!=0)
{
		close(fd2);
		remove(addstr);
		exit(1);
	}

//report order creation success
	else
	{
		printf("Order created!\t // %s.txt Created in %s_Order Dir with Read Mode\n",argv[2],argv[1]);
		if((f2=write(fd2,totstr,strlen(totstr)))==-1)
	{
		perror("Write4");
		close(fd2);
		exit(1);
	}
		chmod(addstr,S_IRUSR | S_IRGRP | S_IROTH);
		close(fd2);
	close(fd1);
	}
	return 1;
}


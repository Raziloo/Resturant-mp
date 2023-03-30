#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(int argc,char* argv[])
{
	int i, son;
	char *op,str[256],add[256];

//run advanced shell until exit
	while(1)
	{
		printf("AdvShell>");
		fgets(str,sizeof(str),stdin);

//if no input start again... else continue...
if (strlen(str)>1){

		str[strlen(str)-1]='\0';
		argv[0]=strtok(str," ");
		for(i=1;i<4;i++) argv[i]=strtok(NULL," ");
//if exit finish...
		if((strcmp(argv[0],"exit"))==0)
		{
			printf("GoodBye...\n");
			exit(0);
		}
//else run separately (fork) the new func entered
		switch (son=fork())
		{
			case -1:
				perror("fork\n");
				exit(1);
			case 0:

//check if one of the new declared functions and set rellevant address
				if((strcmp(argv[0],"CreateMenu")==0)||(strcmp(argv[0],"getMenu")==0)
||(strcmp(argv[0],"MakeOrder")==0)||(strcmp(argv[0],"getPrice")==0)||
(strcmp(argv[0],"getOrderNum")==0)) 
				strcpy(add,"/home/braude/");

//set address for regular shell function
				else strcpy(add,"/bin/");

				strcat(add,argv[0]);

//run the function
				execl(add,argv[0],argv[1],argv[2],argv[3],NULL);
//report "not supported" for unvalid func name
				printf("Not Supported\n");
				exit(1);
//wait for sons...
	default:
			wait(NULL);
			break;
}
			}
			}
			return 0;
			}
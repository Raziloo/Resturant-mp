#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(int argc,char* argv[])
{
	
	int i,j,typeDishNum,fd_file,fd_dir,fd_buff,k,q,w,z,l;
	char temp[256],buff[256],chcnt,str[256],str1[256]={0},strtemp[256],chararr[100],numarr[100],strfinal[256];

	if(argc!=3)
	{
		printf("Please enter the right parameters\n");
		exit(1);
	}

//create restaurant orders directory
	strcat(str1,argv[1]);
	strcat(str1,"_Order");
	if((fd_dir=mkdir(str1,0777))==-1)
{
		perror("Open directory");
		exit(1);
	}

//create restaurant menu file
	if((fd_file=open(argv[1],O_RDWR|O_CREAT,0777))==-1)
	{
		perror("Open file");
		exit(1);
	}
	strcpy(buff,argv[1]);
	strcat(buff," Menu\n\n");
	if((fd_buff=write(fd_file,buff,strlen(buff)))==-1)
	{
		perror("Write");
		close(fd_file);
		exit(1);
	}
//get menu from user:
	typeDishNum=atoi(argv[2]);
	for(i=0;i<typeDishNum;i++)
	{
chcnt='a'+i;
		printf("Insert Type Dish %c:\n",chcnt);
		fgets(temp,sizeof(temp),stdin);
		temp[strlen(temp)-1]='\0';
		j=1;
		strcpy(strtemp,"");
		strncat(strtemp,&chcnt,1);
		strcat(strtemp,". ");
		strcat(strtemp,temp);
		strcat(strtemp,"\n");
//& write to the file
		if((fd_buff=write(fd_file,strtemp,strlen(strtemp)))==-1)
 {
               	 perror("Write");
               	 close(fd_file);
               	 exit(1);
       		 }
		printf("Insert dish name %d:\n",j);
		memset(str, 0 , sizeof(str));
		fgets(str,sizeof(str),stdin);
		str[strlen(str)-1]='\0';
		//gets(str);
		while(strcmp("stop",str)!=0 && strcmp("Stop",str)!=0)
		{
			q=0;
			w=0;
			z=0;

for(k=0;k<strlen(str);k++)
			{
				if(str[k]>='0'&&str[k]<='9')
				{
					numarr[q++]=str[k];
				}
				else chararr[w++]=str[k];
			}
			for(l=0;l<w;l++)
			{
				str[l]=chararr[l];
			}
			for(l=w;l<17;l++)
			{
				str[l]='.';
			}
str[17]=' ';
			for(l=18;l<18+q;l++)
			{
				str[l]=numarr[z++];
			}
			str[l]='N';
			str[l+1]='I';
			str[l+2]='S';
			str[l+3]='\0';
			strcat(str,"\n");
			//printf("%s",str);
			strcpy(strfinal,"   ");
			strcat(strfinal,str);
			if((fd_buff=write(fd_file,strfinal,strlen(strfinal)))==-1)
			        {
               				 perror("Write");
               				 close(fd_file);
               				 exit(1);
        			}
	strcpy(numarr,"");
			strcpy(chararr,"");
			q=0;
			w=0;

			printf("Insert dish name %d:\n",++j);
			//gets(str);
			fgets(str,sizeof(str),stdin);
			str[strlen(str)-1]='\0';

		}
		if((fd_buff=write(fd_file,"\n",1))==-1)
		{
			perror("write");
			close(fd_file);
			exit(1);
		}
	}
	if((fd_buff=write(fd_file,"\n\tBon Appetit\n",strlen("\n\tBon Appetit\n")))==-1)
	        {
			perror("Write");
			close(fd_file);
			exit(1);
       		 }
//report if succeed to create menu
		printf("Seccessfully created // %s.txt created , %s_Order dir created.\n",argv[1],argv[1]);
		close(fd_file);
		return 1;
	
}




#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct CODE
{
	char name[20];
	char password[20];
	struct CODE *pNext; 
}Code; //ע����Ϣ�ڵ�����
Code* P_Head=NULL;   //����ע����Ϣͷ
Code* addCode(Code* pHead); //����һ��ע����Ϣ 
void saveCode(Code* pHead); //����ע����Ϣ 
Code* loadCode(Code* pHead);//��ȡע����Ϣ 
int lookup(Code* pHead,char* name); //�ж��Ƿ�����û�  
int lookupPassword(Code* pHead,char* name,char * password); //��ѯָ���˻������Ƿ���ȷ 
void print(Code* pHead);//��ӡ�˺����� 
int loginIn(Code* pHead);//��¼����
int main(void)
{   
    P_Head=loadCode(P_Head);
    loginIn(P_Head);
    saveCode(P_Head);
	return 0;
} 
Code* addCode(Code* pHead)
{
	Code* pNew=(Code*)malloc(sizeof(Code));
	Code* pTemp=NULL; //��סβ�ڵ� 
	char ch;
	char psw[20]; //���������������; 
	int p=0,flog1=1,flog2=1;
	if(pNew==NULL)
	{
		printf("�ڴ�����ʧ��\n");
		return NULL;
	} 
	pTemp=pHead;
	while(pHead!=NULL&&pTemp->pNext!=NULL)
	{
		pTemp=pTemp->pNext;   //������β ͷ��Ϊ�� 
	}
	while(flog1) //�ж��Ƿ�ע���  
   {
			printf("������ע����Ϣ:\n");
			printf("�˺�:");
			scanf("%s",pNew->name);
			if(lookup(pHead,pNew->name)==0) //�ж��Ƿ�����û� 
			{
				flog1=0;
				printf("���˺ſ���ʹ��!\n"); 
			}
			else
			{
				printf("���˺��Ѿ�ע���,����������\n");
				continue;
			}            
			while(flog2)
		    {	
		       printf("����:");
			   while((ch=getch())!='\r')//�ж��Ƿ�Ϊ�س�
					{
						if(ch==8)
						{
							putchar('\b');
							putchar(' ');
							putchar('\b');
							if(p>0)
							p--;
						} 
						if(!isdigit(ch)&&!isalpha(ch))//�ж��Ƿ������ֻ��ַ���
						  continue;
						putchar('*');
						pNew->password[p++]=ch;//�������� 
					} 
					pNew->password[p]='\0';//�ַ�����β
					p=0;
					printf("\n���ٴ���������:");
						while((ch=getch())!='\r')//�ж��Ƿ�Ϊ�س�
					{
						if(ch==8)
						{
							putchar('\b');
							putchar(' ');
							putchar('\b');
							if(p>0)
							p--;
						} 
						if(!isdigit(ch)&&!isalpha(ch))//�ж��Ƿ������ֻ��ַ���
						  continue;
						putchar('*');
						psw[p++]=ch;//�������� 
					} 
					psw[p]='\0';//�ַ�����β
					p=0;
					if(strcmp(pNew->password,psw)==0)
					{
						flog2=0;
					}
					else
						printf("\n���������������,����������\n");
			} 
	}
	pNew->pNext=NULL;
	if(pHead==NULL)   //ͷ��Ϊ�� �½ڵ��Ϊͷ 
	{
		pHead=pNew;
	printf("\nע��ɹ���\n");
		return pHead;
	}	
	pTemp->pNext=pNew; //ͷ��Ϊ�� ����β֮�� 
	printf("\nע��ɹ���\n");
	return pHead;
} 
void saveCode(Code* pHead) //����ע����Ϣ���ļ���
{
	Code* pTemp=NULL;
	FILE *p=NULL;
	char buf[30];
	if(pHead==NULL)
	{
		printf("ע����ϢΪ��\n");
		return ;
	} 
	p=fopen("register.dat","wb+");
	if(p==NULL)
	{
		printf("�ļ���ʧ��\n");
		return ;
	}
	pTemp=pHead;
    while(pTemp!=NULL)
    {
    	strcpy(buf,pTemp->name);
		strcat(buf," ");
		strcat(buf,pTemp->password);
		fwrite(buf,1,strlen(buf),p);
		fwrite("\r\n",1,strlen("\r\n"),p);
    	pTemp=pTemp->pNext;
	}
	fclose(p);
	p=NULL;
} 
Code* loadCode(Code* pHead)  //��ȡע����Ϣ
{
	FILE * p=NULL;
	Code *pTemp=NULL;
	char buf[30];
	int i,j,flog=1; 
	Code* pNew=NULL; 
	p=fopen("register.dat","rb+");
	if(p==NULL)
	{
		printf("�ļ���ʧ��\n");
		return NULL;
	}
	while(fgets(buf,30,p)!=NULL)
	{
			pNew=(Code*)malloc(sizeof(Code));
	      if(pNew==NULL)
				{
					printf("�ڴ�����ʧ��\n");
					return NULL; 
				}
		 for(i=0,j=0;i<30;i++)
	     {
	       if(flog==1)
		 	 {
		 		pNew->name[i]=buf[i];
		 		if(buf[i]==' ')
	     	   {
                pNew->name[i]='\0';
                flog=0;
                continue;
			   }
		      }
			if(flog==0)
			   {
				pNew->password[j]=buf[i];
				if(buf[i]=='\r')
				{
					pNew->password[j]='\0';
					flog=1;
				    break;
				}
				j++;
			   }
		}
		   pNew->pNext=NULL;
		     if(pHead==NULL)
			   {
			   	  pHead=pNew;
			   	  pTemp=pHead;
			   }
			else
			   {
			   	pTemp->pNext=pNew; 
			   	pTemp=pTemp->pNext;
			   }
	}
	fclose(p);
	return pHead;
}
int lookup(Code* pHead,char* name) //�ж��Ƿ�����û�
{
	Code *pTemp=NULL;
	if(pHead==NULL)
	{
		return 0;
	} 
	pTemp=pHead;
	while(pTemp!=NULL)
	{
		if(strcmp(name,pTemp->name)==0)
		{
			return 1;
		}
		pTemp=pTemp->pNext;
	}
	return 0;
} 
void print(Code*pHead)
{
	Code* pTemp=NULL;
	if(pHead==NULL)
	{
		return ;
	}
	pTemp=pHead;
	while(pTemp!=NULL)
	{
		printf("�˺�:%s,����:%s\n",pTemp->name,pTemp->password);
		pTemp=pTemp->pNext;
	}
	return ;
} 

int lookupPassword(Code* pHead,char* name,char * password) //��ѯָ���˻������Ƿ���ȷ
{
	Code* pTemp;
	if(pHead==NULL)
	{
		return 0; 
	} 
	if(lookup(pHead,name)==1)
	{
		pTemp=pHead;
		while(pTemp!=NULL)
		{
			if(strcmp(pTemp->password,password)==0)
			{
			   return 1;
			}
			pTemp=pTemp->pNext;
		}
		return 0;
	}
	
} 
int loginIn(Code* pHead) //��¼����
{
    Code* pTemp=NULL;
    char name[20];
	char password[20]; 
	char ch;
	int p,flog=1,n;
	if(pHead==NULL)
	{
		printf("��ϢΪ��,��ע��\n");
		return 0; 
	}
   while(1)
 {	printf("�������˺���Ϣ:\n");
	printf("�˺�:");
	scanf("%s",name);
	printf("����:");
	 while((ch=getch())!='\r')//�ж��Ƿ�Ϊ�س�
	  {
			if(ch==8)
			{
			   putchar('\b');
			   putchar(' ');
			   putchar('\b');
			   if(p>0)
				p--;
			} 
			if(!isdigit(ch)&&!isalpha(ch))//�ж��Ƿ������ֻ��ַ���
				continue;
			putchar('*');
			password[p++]=ch;//�������� 
     } 
		password[p]='\0';//�ַ�����β 
		p=0;
	 if(lookupPassword(pHead,name,password)==1)
	 {
	 	printf("\n��¼�ɹ�!\n");
	 	return 1; //�����˺� �ж�Ȩ��  ����... 
	 }
	 printf("\n�˺Ż��������,�����ԣ����˳���¼\n");
	 printf("1.���� 2.�˳���¼\n");
	 while(flog) 
	 {
	 scanf("%d",&n);
	  switch(n)
	  {case 1 :
	  	flog=0;
	 	break;
	  case 2 :
	  	flog=0;
	 	return 0;
	 	break;
	  default :
	 	printf("��������ȷָ��\n"); 
	  } 
	 }
 }
} 

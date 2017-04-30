#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct Data
{
    char strStuName[20];
    char strStuNum[20];
    int strStuSorce;
}Data; //����Data���ݽṹ��
typedef struct NODE
{
	Data data;
    struct NODE* pFont;
	struct NODE* pNext;
}Node;   //�������ݽڵ�
Node* p_Head=NULL;//������������ͷ
Node* create(Node* pHead);//����n���ڵ��˫������
void print(Node* pHead);  //��ӡȫ������
int strNum(char* str); //�ж�ѧ���Ƿ���ȷ
Node *findNode(Node* pHead); //����ָ��ѧ��
Node* insertNode(Node* pHead); //ָ��λ�ò���һ��ѧ������Ϣ
Node* delNode(Node*pHead);  //ɾ��ָ��ѧ��
void rewrite(Node* pHead);  //�޸�ָ��ѧ����Ϣ
Node* sort(Node* pHead);//��ѧ���ɼ�����
Node* reverse(Node* pHead);//����ѧ����Ϣ
Node* freeLink(Node* pHead);//���ѧ����Ϣ
void saveData(Node* pHead);//����ѧ����Ϣ�����ļ�
Node* loadData(Node* pHead);//���ļ��ж�ȡѧ������Ϣ
void showOrder(void);//��ʾ�˵�
int main(void)
{   
    int flog=1,n;
	p_Head=loadData(p_Head);
	showOrder();
	while(flog)
	{
		printf("������ָ��:");
		scanf("%d",&n);
		switch(n)
		{
		  case 1: 
		  p_Head=create(p_Head);
		  break;
		  case 2:
		  print(p_Head); 
		  break;
		  case 3:
          p_Head=delNode(p_Head);
		  break;
		  case 4:
          p_Head=findNode(p_Head);
		  break;
		  case 5:
          p_Head=insertNode(p_Head);
		  break;
		  case 6:
          rewrite(p_Head); 
		  break;
		  case 7:
          p_Head=reverse(p_Head);
		  break;
		  case 8:
		  p_Head=sort(p_Head);
		  break;
		  case 9:
          showOrder();
		  break;
		  case 0:
          saveData(p_Head);
		  flog=0;
		  break;
		  default :
			printf("��������ȷָ��!\n");
		}
	}
    p_Head=freeLink(p_Head);
    return 0;
}

Node* create(Node* pHead)//����n���ڵ��˫������
{
  int n,i,flog=0,j,flogs=0;  //�ڵ㳤�� ѭ������ ���
  Node* pFoot=NULL;
  Node* pNew=NULL;
  if(pHead!=NULL)
  {
	  printf("�ѽ�������,�벻Ҫ�ظ�����\n");
	  return pHead;
  }
  pHead=(Node*)malloc(sizeof(Node));
  pHead->data.strStuSorce=0;
  strcpy(pHead->data.strStuName,"\0");
  strcpy(pHead->data.strStuNum,"\0");
  pHead->pFont=NULL;  //ͷ�ڵ�ǰ��ָ���
  pHead->pNext=NULL;  //ͷ������ָ���
  pFoot=pHead; //β�ڵ� ָ���׽ڵ�
  printf("Ҫ��������ѧ����:");
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
	  pNew=(Node*)malloc(sizeof(Node));
	  if(pNew==NULL)
	  {
		  printf("�ڴ�����ʧ�ܣ�\n");
		  return NULL;
	  }
      while(1)
	  {  
		  printf("�������%d��ֵ\n",i);
		  printf("ѧ������:");
		  scanf("%s",pNew->data.strStuName);
		  printf("ѧ��ѧ��:");
		  scanf("%s",pNew->data.strStuNum);            //�������ݺϷ���
		  printf("ѧ���ɼ�:");
		  scanf("%d",&pNew->data.strStuSorce);
		  if(pNew->data.strStuName!=NULL&&pNew->data.strStuNum!=NULL&&pNew->data.strStuSorce>=0)
		  {
			  flog++;
		  }
		  for(j=0;j<strlen(pNew->data.strStuNum);j++)
		  {
			   if(pNew->data.strStuNum[j]>='0'&&pNew->data.strStuNum[j]<='9')
			   {
				   flogs+=1;
			   }
		  }
		  if(flogs==strlen(pNew->data.strStuNum)&&flog==1)
		  {
			  flog=0;
			  flogs=0;
              break;
		  }
		  printf("���������Ϣ���� ����������!\n");
		  flog=0;
		  flogs=0;
	  }
	  printf("¼�����!\n");
	  pNew->pNext=NULL;  //�½ڵ�ĺ���ָ��
      pNew->pFont=pFoot;//�½ڵ��ǰ��ָ��β
	  pFoot->pNext=pNew; //β�ڵ�ĺ���ָ���½ڵ�
	  pFoot=pNew; //β�ڵ����
  }
  return pHead; //����ͷ�ڵ�
}
void print(Node* pHead)  //��ӡȫ������
{
	Node *pTemp=pHead->pNext;
	if(pTemp==NULL||pHead==NULL)
	{
		printf("������������\n");
		return;
	}
	while(pTemp!=NULL)
	{
		printf("ѧ������:%s ѧ��ѧ��:%s ѧ���ɼ�:%d\n",pTemp->data.strStuName,pTemp->data.strStuNum,pTemp->data.strStuSorce);
		pTemp=pTemp->pNext;
	}
	return ;
}
Node *findNode(Node* pHead) //����ָ��ѧ��
{
	Node* pTemp=NULL;
	char str[20]="\0";
	if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("������������\n");
		return NULL;
	}
	while(1)
	{
		printf("������Ҫ���ҵ�ѧ����ѧ��:");
	    scanf("%s",str);
		if(strNum(str))
		{
			break;
		}
		else
		{
			printf("ѧ���������,����������\n");
		}
    }	
	pTemp=pHead->pNext;
	while(pTemp!=NULL&&strcmp(pTemp->data.strStuNum,str))
	{
		pTemp=pTemp->pNext;
	}
	if(pTemp==NULL)
	{
		return NULL;
	}
	printf("�Ѳ��ҵ����ѧ��:\n");
	printf("ѧ������:%s ѧ��ѧ��:%s ѧ���ɼ�:%d\n",pTemp->data.strStuName,pTemp->data.strStuNum,pTemp->data.strStuSorce);
	return pTemp;
} 
int strNum(char* str) //�ж�ѧ���Ƿ���ȷ
{
    int i,flog=0;
	for(i=0;i<strlen(str);i++)
	{
          if(str[i]>='0'&&str[i]<='9')
		  {
			  flog++;
		  }
	}
	if(flog==strlen(str))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
Node* insertNode(Node* pHead) //ָ��λ�ò���һ��ѧ������Ϣ
{
	 Node* pNode=NULL;
	 Node* pNew=NULL;
	 Node* pTemp=findNode(pHead);
	 int flog=1,i,data,flogs=1;
	 if(pHead==NULL)
	 {
		 printf("����Ϊ��\n");
		 return NULL;
	 }
	 while(pTemp==NULL)
	 {
		 printf("δ�ҵ�����λ�� �����²���\n");
		 pTemp=findNode(p_Head);
	 }
	 pNew=(Node*)malloc(sizeof(Node));
	 if(pNew==NULL)
	 {
		 printf("�����ڵ�ʧ��\n");
		 return NULL;
	 }
	 printf("������Ҫ����ѧ������Ϣ:\n");
	 while(flogs)
	 {
          printf("ѧ������:");
		  scanf("%s",pNew->data.strStuName);
		  printf("ѧ��ѧ��:");
		  scanf("%s",pNew->data.strStuNum);
		  printf("ѧ���ɼ�:");
		  scanf("%d",&pNew->data.strStuSorce);
		  if(pNew->data.strStuName!=NULL&&strNum(pNew->data.strStuNum)&&pNew->data.strStuSorce>=0)
		  {
			  flogs=0;
		  }
		  else
		  {
			  printf("���������Ϣ����,����������\n");
		  }
	 }
	 while(flog)
	 {
		 printf("�ڴ�ѧ��ǰ�����룿\n 0.ǰ 1.��:");
	     scanf("%d",&i);
		 switch(i)
		 {
	     case 1:
		    if(pTemp->pNext==NULL)
			 {
                //��β�ڵ��������һ���½ڵ�
				 pNew->pNext=NULL;  //new����ָ��NULL
				 pNew->pFont=pTemp; //new��ǰ��ָ��tem
				 pTemp->pNext=pNew;  //tem�ĺ���ָ��new
			 }
			 else
			 {
                  //������λ�ú�������һ���½ڵ�
				 pNew->pNext=pTemp->pNext;   //new�ĺ���ָ�� tem�ĺ���
				 pNew->pFont=pTemp;  //new��ǰ�� ָ��tem
				 (pTemp->pNext)->pFont=pNew; //tem�ĺ�����ǰ�� ָ��new
		 	     pTemp->pNext=pNew;  //tem�ĺ���ָ�� new	 
			 }
			 flog=0;
			 break;
		 case 0:
			 pNew->pNext=pTemp; //new�ĺ���ָ��tem
			 pNew->pFont=(pTemp->pFont);  //new��ǰ��ָ�� temp��ǰ��
			 (pTemp->pFont)->pNext=pNew;  //tem��ǰ���ĺ���ָ��new
			 pTemp->pFont=pNew;   //tem��ǰ��ָ��new
			 flog=0;
			 break;
		 default :
			 printf("��������ȷ��ָ��\n");
		 }
	 }
	 printf("����ɹ�\n");
	 print(pHead);
	 return pHead;
}

Node* delNode(Node* pHead)                          //ɾ��ָ��ѧ��
{
	Node* pTemp=findNode(pHead); 
	if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("����Ϊ��\n");
		return NULL;
	}
	while(pTemp==NULL)
	{
		printf("δ�ҵ�ָ��ѧ�������²���\n");
		pTemp=findNode(pHead);
	}
    if(pTemp->pNext==NULL) //��Ҫɾβ�ڵ�
	{   
		(pTemp->pFont)->pNext=NULL;  //β�ڵ��ǰ���ĺ���ָ��
		 pTemp->pFont=NULL;  //β�ڵ��ǰ��ָ��
         free(pTemp);
		  pTemp=NULL;
		  printf("ɾ���ɹ�\n");
		  print(pHead);
		  return pHead;
	}
	else
	{
		(pTemp->pFont)->pNext=pTemp->pNext; //�˽ڵ��ǰ���ĺ���ָ�� �˽ڵ�ĺ���
		(pTemp->pNext)->pFont=pTemp->pFont; //�˽ڵ�ĺ�����ǰ��ָ�� �˽ڵ��ǰ��
		pTemp->pFont=NULL; //�˽ڵ��ǰ����ָ��
		pTemp->pNext=NULL;
		printf("ɾ���ɹ���\n");
		print(pHead);
		return pHead;
	}
}
void rewrite(Node* pHead) //�޸�ָ��ѧ������Ϣ
{
	Node* pTemp=NULL;
	int i,flog=1,n,flogs=1;
	if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("ѧ����ϢΪ��\n");
		return ;
	}
	pTemp=findNode(pHead);
	while(pTemp==NULL)
	{
		printf("δ�ҵ���ѧ���������²���\n");
		pTemp=findNode(pHead);
	}
	while(flog)
	{
		while(flogs)
		{ 
			printf("Ҫ�޸ĵ�ѧ����Ϣ:\n 1.���� 2.ѧ�� 3.�ɼ� 0.�˳�\n");
		    scanf("%d",&n);
			switch(n)
			{
			  case 1:printf("�������޸ĺ�ѧ����������");
		             scanf("%s",pTemp->data.strStuName);
					 break;
			  case 2:printf("�������޸ĺ�ѧ����ѧ�ţ�");
		             scanf("%s",pTemp->data.strStuNum);
					 break;
			  case 3:printf("�������޸ĺ�ѧ���ĳɼ���");
		             scanf("%d",&pTemp->data.strStuSorce);
					 break;
			  case 0:
				     flogs=0;
					 break;
			  default:
				  printf("��������ȷָ��:\n");
			}
        
		}
		if(pTemp->data.strStuName!=NULL&&strNum(pTemp->data.strStuNum)&&pTemp->data.strStuSorce>=0)
		{
			flog=0;
		}
		else
		{
			printf("�������ѧ����Ϣ��������������\n");
		}
	}
	return ;
}
Node* sort(Node* pHead) //���ɼ��ߵ�����
{
	Node* pTemp=NULL;
	Node* pFoot=NULL;
	int i=0;
	int j=0;
	int n=0;
    if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("ѧ����ϢΪ��\n");
		return NULL;
	}
	pTemp=pHead->pNext;
	while(pTemp!=NULL)
	{
        pFoot=pTemp; //�ҳ�β�ڵ�
		pTemp=pTemp->pNext;//temp����
		n++;
	}
	for(i=1;i<n;i++)
    {
		for(pTemp=pHead->pNext,j=1;j<n;j++)
        {
			if(pTemp->data.strStuSorce>pTemp->pNext->data.strStuSorce)  //ð������
			{
                if(pTemp->pNext->pNext==NULL)  //��С��Ϊ��
				{
					pTemp->pFont->pNext=pTemp->pNext; //���ǰ���ĺ���ָ��С��
					pTemp->pNext->pNext=pTemp; //С�ĺ���ָ����
					pTemp->pNext->pFont=pTemp->pFont; //С��ǰ��ָ����ǰ��
					pTemp->pFont=pTemp->pNext; //���ǰ��ָ��С��
					pTemp->pNext=NULL;  //��ĺ���ָ��NULL
				}
				else
				{
                     (pTemp->pFont)->pNext=pTemp->pNext;               //���ǰ���ĺ���ָ��С��
					 ((pTemp->pNext)->pNext)->pFont=pTemp;             //С�ĺ�����ǰ��ָ����
                      pTemp->pNext=((pTemp->pFont)->pNext)->pNext;     //��ĺ���ָ��С�ĺ���					 
				      ((pTemp->pFont)->pNext)->pNext=pTemp;            //С�ĺ���ָ����
                       ((pTemp->pFont)->pNext)->pFont=pTemp->pFont;    //С��ǰ��ָ���ǰ
				       pTemp->pFont=((pTemp->pFont)->pNext);            //���ǰ��ָ��С��
				}
			}
			else
			{
				pTemp=pTemp->pNext;
			}

		}
	}
	print(pHead);
	return pHead;
}
Node* reverse(Node* pHead)   //������Ϣ
{
	Node* pNewHead=(Node*)malloc(sizeof(Node));//������ͷ
	 Node* pTemp=pHead->pNext;//��ʱ�ڵ�pָ���һ���ڵ�
	 Node* pCurrent=NULL;//��ס��ʱ�ڵ����һ��
	 Node* pEnd=pNewHead;//��ס�������β
	 if(pHead==NULL||pHead->pNext==NULL)
	 {
		 printf("����Ϊ��\n");
		 return NULL;
	 }
	 if(pNewHead==NULL)
	 {
		 printf("�����ڴ�ʧ��\n");
		 return NULL;
	 }
	 pNewHead->pFont=NULL;
	 pNewHead->pNext=NULL; //��ʼ����ͷ
	 while(pTemp->pNext!=NULL)
	 {
		 pTemp=pTemp->pNext;  //��Tempָ��β
	 }
	 while(pTemp!=pHead)  //�������׽ڵ����
	 {  
		 pCurrent=pTemp->pFont;  //��ס��ʱ�ڵ��ǰһ��
		 if(pNewHead->pNext==NULL) //��������Ϊ��
		 {
              pTemp->pFont=pNewHead;
			  pTemp->pNext=NULL;
			  pNewHead->pNext=pTemp;   //������������;
              pEnd=pEnd->pNext;  //β����
		 }
		 else
		 {
			 pTemp->pFont=pEnd;
			 pTemp->pNext=NULL;
			 pEnd->pNext=pTemp;  //�����±��
			 pEnd=pEnd->pNext;
		 }
		 pTemp=pCurrent; //Temp��ǰ��
	 }
	 print(pNewHead);
	 free(pHead);
	 pHead=NULL; //�����ͷ
	 return pNewHead;
}
Node* freeLink(Node* pHead) //���ѧ����Ϣ
{
	Node* pTemp=NULL;
	Node* pCurrent=NULL;
	if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("����Ϊ��\n");
		return NULL;
	}
	pTemp=pHead;
    while(pTemp!=NULL)
	{   
		pCurrent=pTemp;
		pTemp=pTemp->pNext;
		free(pCurrent);
		pCurrent=NULL;

	}
	pHead->pNext=NULL;
	printf("������\n");
	print(pHead);
	return pHead;
}
void saveData(Node* pHead)//����ѧ����Ϣ���ļ���
{
	FILE *p=NULL;
	Node *pTemp=NULL;
	if(pHead==NULL||pHead->pNext==NULL)
	{
		printf("ѧ����ϢΪ��\n");
		return ;
	}
	p=fopen("dat.txt","w+");
	   if(p!=NULL)
	   {    
		  pTemp=pHead->pNext;
		  while(pTemp!=NULL)
		  {
			  fprintf(p,"����:%s ѧ��:%s �ɼ�:%d\n",pTemp->data.strStuName,pTemp->data.strStuNum,pTemp->data.strStuSorce);
			  pTemp=pTemp->pNext;
		  }
		  if(fclose(p)==0)
		  {  
			   p=NULL;
			   return ;
		  }
		  else
		  {
			  printf("�ļ��ر�ʧ��\n");
			  return ;
		  }
		}
       else
		{
			printf("�ļ���ʧ��\n");
			return;
		}
}
Node* loadData(Node* pHead)
{
      FILE *p=fopen("dat.txt","r+");
	  Node *pTemp=NULL;
	  Node *pNew=NULL;
      char strname[20];
	  char strnum[20];
	  int sorce;
	  pHead=(Node*)malloc(sizeof(Node));
      pHead->data.strStuSorce=0;
      strcpy(pHead->data.strStuName,"\0");
      strcpy(pHead->data.strStuNum,"\0");
	  pHead->pFont=NULL;
	  pHead->pNext=NULL;
	  pTemp=pHead;
	  while(fscanf(p,"����:%s ѧ��:%s �ɼ�:%d\n",strname,strnum,&sorce)==3)
	  { 
		  pNew=(Node*)malloc(sizeof(Node));
		  if(pNew==NULL)
		  {
			  printf("�ڴ�����ʧ��\n");
			  return NULL;
		  }
		  strcpy(pNew->data.strStuName,strname);
		  strcpy(pNew->data.strStuNum,strnum);
		  pNew->data.strStuSorce=sorce;
		  pNew->pNext=NULL;
		  pNew->pFont=pTemp;
		  pTemp->pNext=pNew;
		  pTemp=pTemp->pNext;
	  }
	  fclose(p);
	  p=NULL;
	  return pHead;
}
void showOrder(void)
{
    printf("*********�˵�*******\n");
	printf("*****1.��������*****\n");
	printf("*****2.��ӡ����*****\n");
	printf("*****3.ɾ���ڵ�*****\n");
    printf("*****4.���ҽڵ�*****\n");
	printf("*****5.����ڵ�*****\n");
	printf("*****6.�޸Ľڵ�*****\n");
	printf("*****7.��������*****\n");
	printf("*****8.��������*****\n");
	printf("*****9.�鿴�˵�*****\n");
	printf("*****0.�˳�����*****\n");
}

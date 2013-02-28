/************************************************************
Copyright (C) lintghi
FileName: LoadSearchSetup2.cpp
Author: lintghi Version : 3.0 Date:
Description: // ģ������
Version: // �汾��Ϣ
Function List: // ��Ҫ�������书��
1. -------
History: // ��ʷ�޸ļ�¼
<author> <time> <version > <desc>

***********************************************************/

#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#define ENGLISH_MAXSIZE 15
#define CHINESE_MAXSIZE 30
#define READINSTACH_MAXSIZE 81
#define SEARCHSTACK_MAXSIZE 15
#define LEN sizeof(WorData)
#define TURE 1
#define FLASH 0
#define YES 1
#define NO 0
#define MSVC 0
#define BACKSPACE printf("\b \b")
#define INTERFACE_COLOR_1 system("COLOR 0f")    //����
#define INTERFACE_COLOR_2 system("COLOR 0e")    //���
#define INTERFACE_COLOR_3 system("COLOR 0b")    //ǳ��

typedef struct WordataList
{
	char english[ENGLISH_MAXSIZE];           //���Ӣ�ĵ���
	char chinese[CHINESE_MAXSIZE];          //���������˼
	struct WordataList *next;
}WorData;

typedef struct ReadinStack
{
	char readin[READINSTACH_MAXSIZE];
	int top;
}ReadinStack;

typedef struct SearchStack
{
	//char search[SEARCHSTACK_MAXSIZE] -> WorData *search[SEARCHSTACK_MAXSIZE]
	WorData *search[SEARCHSTACK_MAXSIZE];    
	int top;
}SearchStack;

typedef struct SetUp  
{
	int speaktime;           //�Ķ��Ĵ���
	int speakdelay;          //�����ʶ��ļ������λ����
	int autospeak;           //�Ƿ��Զ��Ķ�
	int autoback;            //�ʶ����Զ�����
	int autoinsearch;       //��������Զ�������ҵ��ʽ���
	//char backspace;
	//char clearline;
	//char exit;
	//int maincolor;
	//int searchcolor;
	//int 
}SetUp;

//��������
/*************************************************
Function:	Loading()
Description: ���شʿ�
Calls: CreatMyList()
Called By: main()
Input: ����26����ĸ��ͷ��Ϣ������
Output: // �����������˵����
Return: ʧ�ܷ���NO������YES
Others: 
*************************************************/
int Loading(WorData *alphabet[]);  

/*************************************************
Function: 	CreatMyList(n) 
Description: ��������
Calls:none
Called By: Loading()
Input: �ļ�ָ�룬ָ��һ������ĸ���ļ���ָ��
Output: // �����������˵����
Return: ����ͷָ��
Others: 
*************************************************/
WorData *CreatMyList(FILE *open); 

//WorData *CreatList(FILE *fp);
/*************************************************
Function: SearchMoulde()
Description:����ģ�飬���ò��Һ������������ֵΪ������ʾ�Ƿ��˳������������ʶ�����
Calls: 	SearchWord()��YesOrNo()��SpeakWord()
Called By: main()
Input:  ����26����ĸ��ͷ��Ϣ������,����������Ϣ�Ľ���ַ
Output: // �����������˵����
Return: // ��������ֵ��˵��
Others: 
*************************************************/
void SearchMoulde(WorData *alphabet[],SetUp *setinfo);

/*************************************************
Function: SearchWord
Description: �������뵥���������е�λ��
Calls: InitReadinS(), InitSearchS(),PushReadinS(),PushSearchS(),FindLocat(),DisplayToChoose(),
Called By:    SearchMoulde()
Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
Table Updated: // ���޸ĵı����������ǣ�������ݿ�����ĳ���
Input:����26����ĸ��ͷ��Ϣ������
Output: // �����������˵����
Return: ���ҵĽ���ĵ�ַ
Others: // ����˵��
*************************************************/
WorData *SearchWord(WorData *alphabet[]);

/*************************************************
Function: WorData *FindLocat(ReadinStack *readin,WorData *head)
Description: ����������headΪ��ʼλ�ò����������ַ�����λ��
Calls:  no
Called By: SearchWord()
Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
Table Updated: // ���޸ĵı����������ǣ�������ݿ�����ĳ���
Input:   ��headΪ��ʼλ�õĵ�ַ��������ַ���ͷ��ַ
Output:no
Return: �����ַ�����λ��
Others: // ����˵��
*************************************************/
WorData *FindLocat(ReadinStack *readin,WorData *head);

/*************************************************
Function: FindToChoose
Description: ����ǰָ���λ�ú�ͺ�Ÿ���ַ����Findout[]������
Calls: none
Called By: SearchWord()
Input: ��ǰָ���λ�ú�Findout[]����ĵ�ַ
Output: �ı�Findout[]������ֵ
Return: 
Others: 
*************************************************/
void FindToChoose(WorData *current,WorData *Findout[]);

/*************************************************
Function: DisplayToChoose
Description: // ��ʾ�Ը���ĸ��֮ǰ�������ĸ���ɵ��ַ���Ϊǰ׺��ǰʮ�����ʣ��Թ��û�ѡ��
Calls: none
Called By:SearchWord()
Input: �����ʮ���������ڽ��ĵ�ַ������,����ʾ��ʮ�����ʺ󽫹�����¶�λ��ԭλ�ã��ȴ���������
Output:��ʾ���������ĸ���ɵ��ַ���Ϊǰ׺��ǰʮ������
Return:
Others: 
*************************************************/
void DisplayToChoose(WorData *Findout[],char *readin);

/*************************************************
Function: PrintResult
Description:��ʾ���뵥�ʵ�������˼
Calls: 
Called By: // ���ñ������ĺ����嵥
Input: 
Output: // �����������˵����
Return: // ��������ֵ��˵��
Others:
*************************************************/
void PrintResult(WorData *result);

/*************************************************
Function:SpeakWord
Description: �����û������ã��ʶ����ҽ��
Input:  ���ҽ���Ľ��ĵ�ַ������������Ϣ�Ľ��ĵ�ַ
Output: no
Return:no
Others: 
*************************************************/
void SpeakWord(WorData *result,SetUp *setupinfo);

/*************************************************
Function: InitReadInStack
Description: ��ʼ��һ��ջ
Calls:  no
Called By: SearchWord()
Input: no
Output: 
Return: ����ջ�ĵ�ַ
Others: 
*************************************************/
ReadinStack *InitReadinS();

/*************************************************
Function: EmptyReadinS
Description:�ж�ջReadinStack�Ƿ�Ϊ��
Calls: none
Called By: SearchWord()
Input: 
Output: 
Return: ����գ�����YES�����򷵻�NO
Others: // ����˵��
*************************************************/
int EmptyReadinS(ReadinStack *s);

/*************************************************
Function: PushReadinS
Description: ��x��ջ
Calls: SearchWord()
Called By: none
Input:  ջ��ͷ��ַ����Ԫ��x
Output: ��x�浽ջ��
Return: 
Others: 
*************************************************/
void PushReadinS(ReadinStack *s,char x);

/*************************************************
Function: PopReadinS
Description: ��ջ����ջ
Calls: 
Called By: SearchWord()
Input:ջ��ͷ��ַ
Output: 
Return: 
Others: 
*************************************************/
void PopReadinS(ReadinStack *s);

/*************************************************
Function: CleanReadinS
Description: ��ջ���
Calls: 
Called By: SearchWord()
Input: ջͷ��ַ
Output: 
Return: 
Others: 
*************************************************/
void CleanReadinS(ReadinStack *s);

/*************************************************
Function: InitSearchS
Description: ��ʼ��һ��ջ
Calls:
Called By: SearchWord()
Input: 
Output: 
Return: ����ջ�ĵ�ַ
Others: 
*************************************************/
SearchStack *InitSearchS();

/*************************************************
Function:EmptySearchS
Description: 
Calls: 
Called By: SearchWord()
Input: 
Output: 
Return: ����գ�����YES�����򷵻�NO
Others: 
*************************************************/
int EmptySearchS(SearchStack  *s);

/*************************************************
Function: PushSearchS
Description: ��current��ջ
Calls: 
Called By: SearchWord()
Input:ջ��ͷ��ַ����Ԫ��current
Output: 
Return:
Others: 
*************************************************/
void PushSearchS(SearchStack  *s,WorData *current);

/*************************************************
Function: PopSearchS
Description: ��ջ����ջ��������
Calls: EmptySearchS()
Called By: SearchWord()
Input:ջ��ͷ��ַ
Output: 
Return: ����ջ��Ԫ��
Others: 
*************************************************/
WorData *PopSearchS(SearchStack  *s);

/*************************************************
Function: CleanSearchS
Description: ���ջ
Calls: 
Called By: SearchWord()
Input: ջ��ͷ��ַ
Output:
Return: 
Others:
*************************************************/
void CleanSearchS(SearchStack *s);

/*************************************************
Function: LoadSetup
Description: �������ã�����ǵ�һ�����У������ļ���д��Ĭ�����ã������������
Calls: none
Called By:  SetupModule()
Input: 
Output:  ����ǵ�һ�����У���������Ĭ�����õ��ļ�
Return: �����ѱ�������
Others: 
*************************************************/
SetUp *LoadSetup();

/*************************************************
Function: DisplaySetup
Description: ��ʾ��ǰ����
Calls:  none
Called By: SetupModule
Input: ָ��ǰ�����û����õĽ��ĵ�ַ
Output: 
Return:
Others: 5.21	 ���ֲ�������ʾΪ1/0��Ϊ��ʾYES/NO
*************************************************/
void Displaysetup(SetUp *);

/*************************************************
Function: SaveSetup
Description: ���ֵ�ǰ���õ������ļ���
Calls: none
Called By: SetupModule()
Input:  ָ��ǰ�����û����õĽ��ĵ�ַ�����ڰѴ˽��д�뵽�����ļ���
Output:  none
Return:  none
Others: 
*************************************************/
void SaveSetup(SetUp *setinfo);

/*************************************************
Function: 	void SetupModule(SetUp *setinfo)
Description: ����ģ��
Calls: // �����������õĺ����嵥
Called By: // ���ñ������ĺ����嵥
Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
Table Updated: // ���޸ĵı����������ǣ�������ݿ�����ĳ���
Input: // �������˵��������ÿ����������
// �á�ȡֵ˵�����������ϵ��
Output: // �����������˵����
Return: // ��������ֵ��˵��
Others:  
*************************************************/
void SetupModule(SetUp *);

/*************************************************
Function:	void Destroy(WorData *alphabet[])
Description: �ͷŶ�ȡ�ʿ�����Ŀռ�
Called By: 	main()����
Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
Table Updated: // ���޸ĵı����������ǣ�������ݿ�����ĳ���
Input:  ����26����ĸ�������ͷָ�������
Output: no
Return: no
Others:  5.28  ����    
*************************************************/
//void Destroy(WorData *alphabet[]);

/*************************************************
Function:	int Select(int min,int max)
Description: ����ѡ����߰�װ�涨��ֵ�ķ�Χ���ط���Ҫ���ֵ�������min��max�ķ�Χ�򷵻أ������������
Calls: // �����������õĺ����嵥
Called By: // ���ñ������ĺ����嵥
Input�� �涨�����Сֵ��
Output: no
Return: ���ط��ϵ�ֵ
Others:	5.21		lintghi	��scanf�����ַ��ǳ�����ѭ����Ϊ����
*************************************************/
int Select(int min,int max);

/*************************************************
Function:	int YesOrNo()
Description: �ж������Ƿ�Ϊ y��Y��n��N�е�һ��������������ǣ���������
Input: NO
Output: // �����������˵����
Return: ��� y��Y����YES��n��N����NO��
Others: // ����˵��
*************************************************/
int YesOrNo();

/*************************************************
Function:	int IsAlphabet(char input)
Description: �������ĸ������YES
Input: ��������ַ�
Output: ��������֣�����YES�����򷵻�NO
Return: // ��������ֵ��˵��
Others: // ����˵��
*************************************************/
int IsAlphabet(char input);

/*************************************************
Function:	int IsDigital(char input)
Description: ��������֣�����YES
Input: ��������ַ�
Output:  ��������֣�����YES�����򷵻�NO
Return: // ��������ֵ��˵��
Others: // ����˵��
*************************************************/
int IsDigital(char input);

/*************************************************
Function:     int IsPrintChar(char input)
Description: ����ǿ���ʾ�ַ�����YES
Input:   ������ַ�
Output: 
Return: 
Others:
*************************************************/
int IsPrintChar(char input);      //5.28 add

/*************************************************
Function:     char ToLower(char input)
Description: ��inputת��ΪСд��ĸ
Input:   ������ַ�
Output: 
Return: 
Others:
*************************************************/
char ToLower(char input);
 

/*************************************************
Function:������
Description: ���ø�ģ��
Calls: // �����������õĺ����嵥
Called By: // ���ñ������ĺ����嵥
Input: // �������˵��������ÿ����������
// �á�ȡֵ˵�����������ϵ��
Output: // �����������˵����
Return: // ��������ֵ��˵��
Others: 
*************************************************/
void main()
{
	WorData *alphabet[26]={NULL};
	int chioce=1;
	int loaded = NO;
	SetUp *setinfo=NULL;  //����Ҫ��ʼ��
	
	INTERFACE_COLOR_3;
	system("title MyPowerWord  LinSoft");
	system("mode con cols=90 lines=35");
	
	if (Loading(alphabet) == NO) 
	{
		printf("\nLoading Error 000");
		return;
	}
	else
	{
		loaded = YES;
	}

	setinfo=LoadSetup();

	if (setinfo->autoinsearch==YES)
	{
		system("cls");
		printf("\nDo you want to set?(y/n):[ ]\b\b");
		if (YesOrNo() == YES) 
		{
			SetupModule(setinfo);
		}
		if (loaded == NO)
		{
			if (Loading(alphabet) == NO) 
			{
				printf("\nLoading Error 001");
				return;
			}
		}
		SearchMoulde(alphabet,setinfo);
	}
	else 
	{
		while (1)      //5.26 add
		{
			system("cls");
			printf("\n\n\n1.Search\n2.Set up\n3.exit\n");
			printf("Input you chioce:");
			chioce=Select(1,3);
			switch(chioce)
			{
				case 1: 
				{
					SearchMoulde(alphabet,setinfo);
					return;
				}
				case 2:
				{
					SetupModule(setinfo);
					break;
				}
				case 3:return;
			}
		}
	}
	//Destroy(alphabet);
}

/*************************************************
Function:	Loading()
Description: ���شʿ�
Calls: CreatMyList()
Called By: main()
Input: ����26����ĸ��ͷ��Ϣ������
Output: // �����������˵����
Return: ʧ�ܷ���NO������YES
Others: 	��filename�е�n.txt����m.txt֮ǰ��������SearchWord()������n��ͷ�ĵ��ʳ���
�ļ�z.txt����ʱ��ѭ������Ϊz.txt�е�����һ��#�ź����һ���ո��
*************************************************/
int Loading(WorData *alphabet[])        
{
	//����ָ���ַ�����ָ�����飬����ļ���. ��l.txt��д��.txt.
	char *filename[26] = {"a.txt","b.txt","c.txt","d.txt","e.txt","f.txt","g.txt","h.txt",
	"i.txt","j.txt","k.txt","l.txt","m.txt","n.txt","o.txt","p.txt","q.txt","r.txt","s.txt",
	"t.txt","u.txt","v.txt","w.txt","x.txt","y.txt","z.txt"};              

	//char *name=NULL;          //ָ��ָ���ָ�룬���ڶ�ȡ�ļ���
	int i=0;
	FILE *fp=NULL;
   
	INTERFACE_COLOR_2;
	
	printf("\n\n\n\n\n\n\n\n\n\n      - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r");
	printf("      ");
	for (i = 0; i < 26 ; i++ )        //25 -> 26,��26д��25,ʹz�޷�����
	{
		//name = filename[i];
		if ((fp = fopen(filename[i],"r"))==NULL) 
		{
			continue;  //rb ->r
		}
		
		alphabet[i] = CreatMyList(fp);
		#ifdef MSVC
			Sleep(50);
		#else
			sleep(50);
		#endif
		printf(" > ");                  //��Ϊ������
		fclose(fp);
		fp=NULL;
	}
	
	return 1;
}

/*************************************************
Function: 	CreatMyList(n) 
Description: ��������
Calls:none
Called By: Loading()
Input: �ļ�ָ�룬ָ��һ������ĸ���ļ���ָ��
Output: // �����������˵����
Return: ����ͷָ��
Others: 
*************************************************/
WorData *CreatMyList(FILE *open)      
{
	char readin='\0';            //��һ��û�Ӵ�������readin��ֵ�޷�ȷ��
	int i,j,flag;
	int k=0;
	WorData *p=NULL,*head=NULL,*q=NULL;

    while (1)      
	{
		if ((p=(WorData *)malloc(sizeof(WorData)))==NULL) 
		{
			printf("\nBuild Error 002");   return NULL;
		}
		else 
		{
			strset(p->english,'\0');      //5.23 add
			strset(p->chinese,'\0');
			p->next=NULL;
		}
		readin=fgetc(open);
		if (readin=='@') break;     //δ�Ӹ��У��ڶ�while����ѭ��
		i=0;
		j=0;
		flag=0;          //δ����ֵ����

    	while (readin!='#')
		{
			while (flag!=1)
			{
				if (readin >=20) p->english[i++]=readin;          //add   if (readin >=20)  �����ַ������뵽������
				readin=fgetc(open);
				if(readin==' ') flag=1;
			}
		    p->chinese[j++]=readin;
	        readin=fgetc(open);
		}
	   readin=fgetc(open);          //������#�ź���һ�����з���δ�Ӹ��У��ڵ�һ��readin�����뻻�з����µڶ���while��ѭ��
	   p->english[i]='\0';       
	   p->chinese[j]='\0';          //д�����
		if (k==0) 
		{
			head=p;
			q=p;
		}
		else 
		{
			q->next=p;
			q=p;
		}
		k++;
	}
	fclose(open);
	return head;
}

/*************************************************
Function: SearchMoulde()
Description:����ģ�飬���ò��Һ������������ֵΪ������ʾ�Ƿ��˳������������ʶ�����
Calls: 	SearchWord()��YesOrNo()��SpeakWord()
Called By: main()
Input:  ����26����ĸ��ͷ��Ϣ������,����������Ϣ�Ľ���ַ
Output: // �����������˵����
Return: // ��������ֵ��˵��
Others: 
*************************************************/
void SearchMoulde(WorData *alphabet[],SetUp *setinfo)
{
	char *tip={" Use = to backspace, @ to clear the line, ` to exit"};
	WorData *result=NULL;
	
	system("cls");
	INTERFACE_COLOR_1;
	
	system("cls");
	printf("\n%s\n",tip);
	#ifdef MSVC
		Sleep(1000);
	#else
		sleep(1000);
	#endif
	while (1)
	{
		//display the interface
		system("cls");
		
		result=SearchWord(alphabet);
		if (result!=NULL)
		{
			PrintResult(result);
			if (setinfo->autospeak==YES)
			{
				SpeakWord(result,setinfo);
			}
			else
			{
				printf("\n\nDo you want to speak the word?:[ ]\b\b");
				if (YesOrNo() == YES)
				{
					SpeakWord(result,setinfo);
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			system("cls");
			printf("\nDo you want to exit?:[ ]\b\b");
			if (YesOrNo()==YES)
			{
				return;
			}
			else
			{
				//break; //����
				continue;
			}
		}
	}//end of while(1)
}

/*************************************************
Function: SearchWord
Description: �������뵥���������е�λ��
Calls: InitReadinS(), InitSearchS(),PushReadinS(),PushSearchS(),FindLocat(),DisplayToChoose(),
Called By:    SearchMoulde()
Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
Table Updated: // ���޸ĵı����������ǣ�������ݿ�����ĳ���
Input:����26����ĸ��ͷ��Ϣ������
Output: // �����������˵����
Return: ���ҵĽ���ĵ�ַ
Others: 5.29	�������д��ĸ����������޸�
*************************************************/
WorData *SearchWord(WorData *alphabet[])            
{
	char input='\0';
	
	WorData *head=NULL,*current=NULL,*result=NULL;  //lack *
	WorData *Findout[10];
	ReadinStack *readins=NULL;
	SearchStack *searchs=NULL;
	
	readins=InitReadinS();       //��ʼ��
	searchs=InitSearchS();      
	while(1)
	{
		while (1)
		{
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n");     //��ӡ��ʮ������׼����ʾʮ�������Թ�ѡ��
			printf("Input:");
			
			input = getch();   //getche() -> getch()����һ����ĸ�����Ǵ�д����ת����Сд
			if (IsAlphabet(input) == YES)    //5.28 add   ���
			{
				putchar(input);
			}
			
			if (input == '`')
			{
				return NULL;
			}
			else if (IsAlphabet(input) == NO)  
			{
				break;     //IsAlphabet()�ж��Ƿ�Ϊ��ĸ���Ƿ���1
			}
			else
			{
				head = alphabet[ToLower(input) - 'a'];         //tolower() ��input�ַ�ת����Сд��ĸ��-'a'�õ�input�ַ���alphabet�����е�λ��   5.28
				current = head;
			}
			
			while (1)                
			{
				if (IsAlphabet(input) == YES) //���input����ĸ
				{
					PushReadinS(readins,input);
					PushSearchS(searchs,current);
					current=FindLocat(readins,current);
					FindToChoose(current,Findout);
					DisplayToChoose(Findout,readins->readin);
					if (current != NULL)  //���û�ҵ�
					{
						input=ToLower(getch());
						if (IsAlphabet(input) == YES)    //5.28 add   
						{
							putchar(input);
						}
						continue;
					}
				}
				else if (IsDigital(input) == YES) //�Ƿ�Ϊ���֣��Ƿ���1
				{
					result=Findout[input-'0'];
					return result;
				}
				else if (input == '=') //���� = �����˸��
				{
					PopReadinS(readins);
					if (EmptyReadinS(readins) == YES) break;      //5.28 add,������޸ģ�����a = b��������
					current=PopSearchS(searchs);        //�����ϴ���ָλ��
					current=FindLocat(readins,current);
					FindToChoose(current,Findout);
					DisplayToChoose(Findout,readins->readin);
					//BACKSPACE;     //��֮ǰ�����һ���ַ�����
				}
				else if (input == '@') //���� -  ���������
				{
					CleanReadinS(readins);
					CleanSearchS(searchs);
					break;       //��������
				}
				else if (input == '`')   //Esc��������Ǹ���
				{
					return NULL;
				}
				//else BACKSPACE;     //��������������������Ļ��ɾ�����Ѿ���������䣬�þ����ȥ��
				
				input = ToLower(getch());
				if (IsAlphabet(input) == YES)    //5.28 add   ���
				{
					putchar(input);
				}
			}//end of while (1)
		}//end of the frist while(1)
	}
}


/*************************************************
Function: WorData *FindLocat(ReadinStack *readin,WorData *head)
Description: ����������headΪ��ʼλ�ò����������ַ�����λ��
Calls:  no
Called By: SearchWord()
Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
Table Updated: // ���޸ĵı����������ǣ�������ݿ�����ĳ���
Input:   ��headΪ��ʼλ�õĵ�ַ��������ַ���ͷ��ַ
Output:no
Return: �����ַ�����λ��
Others: // ����˵��
*************************************************/
WorData *FindLocat(ReadinStack *readin,WorData *head)
{
	WorData *search = head;           //
	
	while (search != NULL)
	{
		//�����ִ�Сд�Ƚ�
		while (strnicmp(readin->readin,search->english,strlen(readin->readin))>0) search = search->next;       //5.28  if -> while
		return search;
	}
	return NULL;
}

/*************************************************
Function: FindToChoose
Description: ����ǰָ���λ�ú�ͺ�Ÿ���ַ����Findout[]������
Calls: none
Called By: SearchWord()
Input: ��ǰָ���λ�ú�Findout[]����ĵ�ַ
Output: �ı�Findout[]������ֵ
Return: 
Others: 
*************************************************/
void FindToChoose(WorData *current,WorData *Findout[])
{
	WorData *temp = current;
	int i=0;
	
	while(i < 10)              //����temp�Ƿ�Ϊ�գ������丳��Findout[i]
	{
		Findout[i] = temp;
		if (temp != NULL) 
		{
			temp = temp -> next;
		}
		i++;
	}
}

/*************************************************
Function: DisplayToChoose
Description: // ��ʾ�Ը���ĸ��֮ǰ�������ĸ���ɵ��ַ���Ϊǰ׺��ǰʮ�����ʣ��Թ��û�ѡ��
Calls: none
Called By:SearchWord()
Input: �����ʮ���������ڽ��ĵ�ַ������,����ʾ��ʮ�����ʺ󽫹�����¶�λ��ԭλ�ã��ȴ���������
Output:��ʾ���������ĸ���ɵ��ַ���Ϊǰ׺��ǰʮ������
Return:
Others: 
*************************************************/
void DisplayToChoose(WorData *Findout[],char *readin)
{
	int i;
	
	system("cls");
	for (i = 0;i < 10 ;i++)
	{
		//���ǰһ��Findout��ʮ��Ԫ�أ�����ǰû��ʮ����Ҫ��֮ǰ����ʾ����
		if (Findout[i] != NULL) 
		{
			printf("%d. %s\n",i,Findout[i]->english);
		}
		else
		{
			printf("                                                           \n");    
		}
	}
	printf("Input:%s",readin);
}

/*************************************************
Function: PrintResult
Description:��ʾ���뵥�ʵ�������˼
Calls: 
Called By: // ���ñ������ĺ����嵥
Input: 
Output: // �����������˵����
Return: // ��������ֵ��˵��
Others:
*************************************************/
void PrintResult(WorData *result) 
{
	printf("\n\n=============================================");
	printf("\n\n%s  %s",result->english,result->chinese);
	printf("\n\n=============================================");
}

/*************************************************
Function:SpeakWord
Description: �����û������ã��ʶ����ҽ��
Input:  ���ҽ���Ľ��ĵ�ַ������������Ϣ�Ľ��ĵ�ַ
Output: no
Return:no
Others: 
*************************************************/
void SpeakWord(WorData *result,SetUp *setupinfo)
{
	char doscom[30] = "speak.bat ";
	char *com=NULL;
	
	com = strcat(doscom,result->english);
	int i;

	while (1)  //5.29 add
	{
		for (i = 0; i < setupinfo->speaktime ; i++)
		{
			system(com);
			#ifdef MSVC
				Sleep(setupinfo->speakdelay);
			#else
				sleep(setupinfo->speakdelay);
			#endif
		}
		
		printf("\nDo you want to speak again?(y/n):[ ]\b\b");
		if (YesOrNo() == YES)
		{
			system(com);
			break;
		}
		else 
		{
			return;
		}
		
		if (setupinfo->autoback == NO) 
		{
			printf("\nDo you want to speak?(y/n):[ ]\b\b");
			if (YesOrNo() == YES)
			{
				break;
			}
			else 
			{
				return;
			}
		}
		break;
	}		
	return;
}

/*************************************************
Function: InitReadInStack
Description: ��ʼ��һ��ջ
Calls:  no
Called By: SearchWord()
Input: no
Output: 
Return: ����ջ�ĵ�ַ
Others: 
*************************************************/
ReadinStack *InitReadinS()
{
	ReadinStack *s=NULL;
	int i;
	s=(ReadinStack *)malloc(sizeof(ReadinStack));
	for (i = 0 ;i < READINSTACH_MAXSIZE ; i++)    //5.23  add 
	{
		s->readin[i]='\0';
	}
	s->top = -1;
	return s;
}

/*************************************************
Function: EmptyReadinS
Description:�ж�ջReadinStack�Ƿ�Ϊ��
Calls: none
Called By: SearchWord()
Input: 
Output: 
Return: ����գ�����YES�����򷵻�NO
Others: // ����˵��
*************************************************/
int EmptyReadinS(ReadinStack *s)
{
	if (s->top == -1) 
	{
		return YES;
	}
	else
	{
		return NO;
	}
}

/*************************************************
Function: PushReadinS
Description: ��x��ջ
Calls: SearchWord()
Called By: none
Input:  ջ��ͷ��ַ����Ԫ��x
Output: ��x�浽ջ��
Return: 
Others: 
*************************************************/
void PushReadinS(ReadinStack *s,char x)
{
	if (s->top==READINSTACH_MAXSIZE-1) 
	{
		return;
	}
	else
	{
		s->top++;
		s->readin[s->top]=x;
	}
}

/*************************************************
Function: PopReadinS
Description: ��ջ����ջ
Calls: 
Called By: SearchWord()
Input:ջ��ͷ��ַ
Output: 
Return: 
Others: 
*************************************************/
void PopReadinS(ReadinStack *s)
{
	if (EmptyReadinS(s)) 
	{
		return;
	}
	else
	{
		s->readin[s->top]='\0';
		s->top--;
	}
}

/*************************************************
Function: CleanReadinS
Description: ��ջ���
Calls: 
Called By: SearchWord()
Input: ջͷ��ַ
Output: 
Return: 
Others: 
*************************************************/
void CleanReadinS(ReadinStack *s)
{
	int i;
	for (i = 0; i<READINSTACH_MAXSIZE;i++)
	{
		s->readin[i]='\0';
	}
	s->top=-1;
}	

/*************************************************
Function: InitSearchS
Description: ��ʼ��һ��ջ
Calls:
Called By: SearchWord()
Input: 
Output: 
Return: ����ջ�ĵ�ַ
Others: 
*************************************************/
SearchStack *InitSearchS()
{
	SearchStack *s=NULL;
	int i;
	
	s = (SearchStack  *)malloc(sizeof(SearchStack));
	for (i =0;i < SEARCHSTACK_MAXSIZE; i++)
	{
		s->search[i]=NULL;
	}
	s->top = -1;
	return s;
}

/*************************************************
Function:EmptySearchS
Description: 
Calls: 
Called By: SearchWord()
Input: 
Output: 
Return: ����գ�����YES�����򷵻�NO
Others: 
*************************************************/
int EmptySearchS(SearchStack  *s)      //lack SearchStack  *s
{
	if (s->top == -1) 
	{
		return YES;
	}
	else 
	{
		return NO;
	}
}

/*************************************************
Function: PushSearchS
Description: ��current��ջ
Calls: 
Called By: SearchWord()
Input:ջ��ͷ��ַ����Ԫ��current
Output: 
Return:
Others: 
*************************************************/
void PushSearchS(SearchStack  *s,WorData *current)
{
	if (s->top == SEARCHSTACK_MAXSIZE-1) 
	{
		return;
	
	}
	else
	{
		s->top++;
		s->search[s->top] = current;
	}
}

/*************************************************
Function: PopSearchS
Description: ��ջ����ջ��������
Calls: EmptySearchS()
Called By: SearchWord()
Input:ջ��ͷ��ַ
Output: 
Return: ����ջ��Ԫ��
Others: 
*************************************************/
WorData *PopSearchS(SearchStack  *s)
{
	WorData *x = NULL;
	if (EmptySearchS(s)) 
	{
		return NULL;
	}
	else 
	{
		x = s->search[s->top];
		s->top--;          //lack s->
	}
	return x;
}

/*************************************************
Function: CleanSearchS
Description: ���ջ
Calls: 
Called By: SearchWord()
Input: ջ��ͷ��ַ
Output:
Return: 
Others:
*************************************************/
void CleanSearchS(SearchStack *s)
{
	s->top = -1;
}

/*************************************************
Function: LoadSetup
Description: �������ã�����ǵ�һ�����У������ļ���д��Ĭ�����ã������������
Calls: none
Called By:  SetupModule()
Input: 
Output:  ����ǵ�һ�����У���������Ĭ�����õ��ļ�
Return: �����ѱ�������
Others: 
*************************************************/
SetUp *LoadSetup()
{
	FILE *setinfofile = NULL;
	char *filelocate = {"setinfo.dat"};
	SetUp *setinfo=NULL;

	//��������ļ������ڣ���ʾ��һ�δ򿪣���ʱҪ�����ļ�
	if ((setinfofile = fopen(filelocate,"rb"))==NULL)             
	{
		if ((setinfofile = fopen(filelocate,"wb"))==NULL)
		{
			printf("\nOpen File Error 003");
			return NULL;
		}
		else
		{
			if ((setinfo=(SetUp *)malloc(sizeof(SetUp)))==NULL)
			{
				printf("\nBuild Error 004");
				return NULL;
			}
			else
			{
				//����Ĭ��ֵ:�ʶ�3�Σ����Ϊ���룬��ʾ���ʺ��Զ��ʶ������귵�ز��ҽ��棬����������Զ�������ҽ���
				setinfo->speaktime=3;
				setinfo->speakdelay=500;       //ms
				setinfo->autospeak=YES;
				setinfo->autoback=YES;
				setinfo->autoinsearch=YES;
				if (fwrite(setinfo,sizeof(SetUp),1,setinfofile) != 1)
				{
					printf("\nWrite Error 005");
					return NULL;
				}
				else
				{
					fclose(setinfofile);        //5.20���룬�ر��ļ�
					return setinfo;
				}
			}
		}
	}//����������
	else          //����ļ��Դ��ڣ�������������
	{
		if ((setinfo = (SetUp *)malloc(sizeof(SetUp))) == NULL)
		{
			printf("\nBuild Error 006");
			return NULL;
		}
		else
		{
			if (fread(setinfo,sizeof(SetUp),1,setinfofile) != 1)
			{
				printf("\nRead Error 007");
				return NULL;
			}
            else
			{
				return setinfo;
			}
		}
	}
}

/*************************************************
Function: DisplaySetup
Description: ��ʾ��ǰ����
Calls:  none
Called By: SetupModule
Input: ָ��ǰ�����û����õĽ��ĵ�ַ
Output: 
Return:
Others: 5.21	 ���ֲ�������ʾΪ1/0��Ϊ��ʾYES/NO
*************************************************/
void Displaysetup(SetUp *setinfo)
{
	system("cls");
	printf("\nNow Setup\n");
	printf("\n+==================================================+");
	printf("\nTime(s) Delay Autospeak Autoback Autoinsearch\n");
	
	printf(" %d\t",setinfo->speaktime);
	printf(" %2.1fs\t",(float)setinfo->speakdelay/1000);
	//printf("%d\t%d\t%d\t%d\t%d",setinfo->speaktime,setinfo->speakdelay,setinfo->autospeak,setinfo->autoback,setinfo->autoinsearch);
	if (setinfo->autospeak==YES)
	{
		printf(" YSE\t");
	}
	else
	{
		printf(" NO\t");
	}
	
	if (setinfo->autoback == YES)
	{
		printf("  YSE\t");
	}
	else
	{
		printf("  NO\t");
	}
	
	if (setinfo->autoinsearch == YES)
	{
		printf("  YSE\t");
	}
	else
	{
		printf("  NO\t");
	}
	printf("\n+==================================================+");
	printf("\n");
}

/*************************************************
Function: SaveSetup
Description: ���ֵ�ǰ���õ������ļ���
Calls: none
Called By: SetupModule()
Input:  ָ��ǰ�����û����õĽ��ĵ�ַ�����ڰѴ˽��д�뵽�����ļ���
Output:  none
Return:  none
Others: 
*************************************************/
void SaveSetup(SetUp *setinfo)
{
	FILE *setinfofile=NULL;
	char *filelocate={"setinfo.dat"};
	
	if ((setinfofile=fopen(filelocate,"wb")) == NULL)
	{
		printf("Open File Error 008");
		return;
	}
	else
	{
		if (fwrite(setinfo,sizeof(SetUp),1,setinfofile) != 1)
		{
			printf("Write Error 009");
			return;
		}
	}
	fclose(setinfofile);
}

/*************************************************
Function:	void Destroy(WorData *alphabet[])
Description: �ͷŶ�ȡ�ʿ�����Ŀռ�
Called By: 	main()����
Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
Table Updated: // ���޸ĵı����������ǣ�������ݿ�����ĳ���
Input:  ����26����ĸ�������ͷָ�������
Output: no
Return: no
Others:  5.28  ����    ԭ��alphabet[]δ����ֵ�����Ҳ����ļ�����ʧ��
*************************************************/
/*void Destroy(WorData *alphabet[])
{
	int i;
	WorData *tmp=NULL,*move=NULL;

	for (i = 0; i < 26 ; i++ )
	{
		move=alphabet[i];   
		if (move == NULL) 
		{
			continue;    //5.27 add
		}
		while (move != NULL)
		{
			tmp=move;
			move=move->next;
			free(tmp);
		} //end of while
	}//end of for
}
*/
/*************************************************
Function:	int Select(int min,int max)
Description: ����ѡ����߰�װ�涨��ֵ�ķ�Χ���ط���Ҫ���ֵ�������min��max�ķ�Χ�򷵻أ������������
Calls: // �����������õĺ����嵥
Called By: // ���ñ������ĺ����嵥
Input�� �涨�����Сֵ��
Output: no
Return: ���ط��ϵ�ֵ
Others:	5.21		lintghi	��scanf�����ַ��ǳ�����ѭ����Ϊ����
*************************************************/
int Select(int min,int max)
{
	char temp[30];  //add
	int input = 0;
	
	while (1)
	{
		//scanf("%d",&input);��scanf�����ַ�ʱ������ѭ������Ϊ����
		gets(temp);
		input=atoi(temp);     //�������ַ���ת��Ϊ��������
		
		if (input >= min && input <= max )
		{
			return input;
		}
		else     //5.21 add,
		{
			printf("Reinput:");
		}
	}
}
/*************************************************
Function: 	void SetupModule(SetUp *setinfo)
Description: ����ģ��
Calls: // �����������õĺ����嵥
Called By: // ���ñ������ĺ����嵥
Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
Table Updated: // ���޸ĵı����������ǣ�������ݿ�����ĳ���
Input: // �������˵��������ÿ����������
// �á�ȡֵ˵�����������ϵ��
Output: // �����������˵����
Return: // ��������ֵ��˵��
Others:  
*************************************************/
void SetupModule(SetUp *setinfo)
{
	INTERFACE_COLOR_3;
	setinfo=LoadSetup();
	Displaysetup(setinfo);
	
    printf("\n\nDo you want to set up?:[ ]\b\b");

	if (YesOrNo()==YES)
	{
		printf("\ntime(1~5):");
		setinfo->speaktime=Select(1,5);
		
		printf("\ndelay(s):");
		setinfo->speakdelay=Select(1,10)*1000;
		
		printf("\nautospeak(y/n):[ ]\b\b");
		setinfo->autospeak=YesOrNo();
		
		printf("\nautoback(y/n):[ ]\b\b");
		setinfo->autoback=YesOrNo();
		
	    printf("\nautoinsearch(y/n):[ ]\b\b");
		setinfo->autoinsearch=YesOrNo();   //lack ()

		system("cls");
		Displaysetup(setinfo);
		printf("\nDo you want to save it?:[ ]\b\b");
		if (YesOrNo()==YES)
		{
			SaveSetup(setinfo);
			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		printf("\nPress any key to back...");
		getche();
		return;
	}
}


/*************************************************
Function:	int YesOrNo()
Description: �ж������Ƿ�Ϊ y��Y��n��N�е�һ��������������ǣ���������
Input: NO
Output: // �����������˵����
Return: ��� y��Y����YES��n��N����NO��
Others: // ����˵��
*************************************************/
int YesOrNo()
{
	char input;
	while (1)
	{
		input=getch();
		
		if (input >20)      //������ǿ����ַ�������
		{
			putchar(input);
		}
		
		if (input == 'y' || input == 'Y' )
		{
			return YES;
		}
		else if (input == 'n' || input == 'N' )
		{
			return NO;
		}
		else    //5.30 add 
		{
			printf("\b%c\b",input);     //��������������Ч��
		}
	}
}

/*************************************************
Function:	int IsAlphabet(char input)
Description: �������ĸ������YES
Input: ��������ַ�
Output: ��������֣�����YES�����򷵻�NO
Return: // ��������ֵ��˵��
Others: // ����˵��
*************************************************/
int IsAlphabet(char input)
{
	if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'))
	{
		return TURE;
	}
	else
	{
		return FLASH;
	}
}
/*************************************************
Function:	int IsDigital(char input)
Description: ��������֣�����YES
Input: ��������ַ�
Output:  ��������֣�����YES�����򷵻�NO
Return: // ��������ֵ��˵��
Others: // ����˵��
*************************************************/
int IsDigital(char input)
{
	if (input >= '0' && input <= '9')
	{
		return TURE;
	}
	else 
	{
		return FLASH;
	}
}

/*WorData *CreatMyList()
{
	WorData *head,*p=NULL,*q;
	int end=1;
	int i=0;
	
	while (end !=0)
	{
		system("cls");
		p=(WorData *)malloc(sizeof(WorData));
		if (p==NULL) 
		{
			printf("ERROR");
			return NULL;
		}
		
		memset(p->english,'\0',ENGLISH_MAXSIZE);      //5.23 add
		memset(p->chinese,'\0',CHINESE_MAXSIZE);
		printf("q:");
		gets(p->english);
		printf("p:");
		gets(p->chinese);
		if (i==0) 
		{
			head=p;
			q=p;
		}
		else 
		{
			q->next=p;
			q=p;
		}
		i++;
		printf("\n(y/n):");
		end=YesOrNo();
	}
	p->next=NULL;
	return head;
}*/

/*************************************************
Function:     int IsPrintChar(char input)
Description: ����ǿ���ʾ�ַ�����YES
Input:   ������ַ�
Output: 
Return: 
Others:
*************************************************/
int IsPrintChar(char input)   //5.28 add
{
	if (input >=0 && input <= 20)
	{
		return NO;
	}
	else 
	{
		return YES;
	}
}

/*************************************************
Function:     char ToLower(char input)
Description: ��inputת��ΪСд��ĸ
Input:   ������ַ�
Output: 
Return: 
Others: 
*************************************************/
char ToLower(char input)       //5.26 add
{
	if (input >= 'A' && input <= 'Z')
	{
		input = input + 32;
	}
	return input;
}


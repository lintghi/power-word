/************************************************************
Copyright (C) lintghi
FileName: LoadSearchSetup2.cpp
Author: lintghi Version : 3.0 Date:
Description: // 模块描述
Version: // 版本信息
Function List: // 主要函数及其功能
1. -------
History: // 历史修改记录
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
#define INTERFACE_COLOR_1 system("COLOR 0f")    //亮白
#define INTERFACE_COLOR_2 system("COLOR 0e")    //金黄
#define INTERFACE_COLOR_3 system("COLOR 0b")    //浅绿

typedef struct WordataList
{
	char english[ENGLISH_MAXSIZE];           //存放英文单词
	char chinese[CHINESE_MAXSIZE];          //存放中文意思
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
	int speaktime;           //阅读的次数
	int speakdelay;          //两次朗读的间隔，单位毫秒
	int autospeak;           //是否自动阅读
	int autoback;            //朗读完自动返回
	int autoinsearch;       //进入软件自动进入查找单词界面
	//char backspace;
	//char clearline;
	//char exit;
	//int maincolor;
	//int searchcolor;
	//int 
}SetUp;

//函数声明
/*************************************************
Function:	Loading()
Description: 加载词库
Calls: CreatMyList()
Called By: main()
Input: 存有26个字母表头信息的数组
Output: // 对输出参数的说明。
Return: 失败返回NO，否则YES
Others: 
*************************************************/
int Loading(WorData *alphabet[]);  

/*************************************************
Function: 	CreatMyList(n) 
Description: 建立链表
Calls:none
Called By: Loading()
Input: 文件指针，指向一个存字母的文件的指针
Output: // 对输出参数的说明。
Return: 返回头指针
Others: 
*************************************************/
WorData *CreatMyList(FILE *open); 

//WorData *CreatList(FILE *fp);
/*************************************************
Function: SearchMoulde()
Description:搜索模块，调用查找函数，如果返回值为空则提示是否退出，否则按设置朗读单词
Calls: 	SearchWord()，YesOrNo()，SpeakWord()
Called By: main()
Input:  存有26个字母表头信息的数组,存有设置信息的结点地址
Output: // 对输出参数的说明。
Return: // 函数返回值的说明
Others: 
*************************************************/
void SearchMoulde(WorData *alphabet[],SetUp *setinfo);

/*************************************************
Function: SearchWord
Description: 搜索输入单词在链表中的位置
Calls: InitReadinS(), InitSearchS(),PushReadinS(),PushSearchS(),FindLocat(),DisplayToChoose(),
Called By:    SearchMoulde()
Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
Input:存有26个字母表头信息的数组
Output: // 对输出参数的说明。
Return: 查找的结果的地址
Others: // 其它说明
*************************************************/
WorData *SearchWord(WorData *alphabet[]);

/*************************************************
Function: WorData *FindLocat(ReadinStack *readin,WorData *head)
Description: 在链表中以head为开始位置查找所输入字符串的位置
Calls:  no
Called By: SearchWord()
Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
Input:   以head为开始位置的地址，输入的字符串头地址
Output:no
Return: 输入字符串的位置
Others: // 其它说明
*************************************************/
WorData *FindLocat(ReadinStack *readin,WorData *head);

/*************************************************
Function: FindToChoose
Description: 将当前指针的位置后和后九个地址存入Findout[]数组中
Calls: none
Called By: SearchWord()
Input: 当前指针的位置和Findout[]数组的地址
Output: 改变Findout[]数组中值
Return: 
Others: 
*************************************************/
void FindToChoose(WorData *current,WorData *Findout[]);

/*************************************************
Function: DisplayToChoose
Description: // 显示以该字母与之前输入的字母构成的字符串为前缀的前十个单词，以供用户选择
Calls: none
Called By:SearchWord()
Input: 存放有十个单词所在结点的地址的数组,当显示出十个单词后将光标重新定位在原位置，等待继续输入
Output:显示以输入的字母构成的字符串为前缀的前十个单词
Return:
Others: 
*************************************************/
void DisplayToChoose(WorData *Findout[],char *readin);

/*************************************************
Function: PrintResult
Description:显示输入单词的中文意思
Calls: 
Called By: // 调用本函数的函数清单
Input: 
Output: // 对输出参数的说明。
Return: // 函数返回值的说明
Others:
*************************************************/
void PrintResult(WorData *result);

/*************************************************
Function:SpeakWord
Description: 按照用户的设置，朗读查找结果
Input:  查找结果的结点的地址，存有设置信息的结点的地址
Output: no
Return:no
Others: 
*************************************************/
void SpeakWord(WorData *result,SetUp *setupinfo);

/*************************************************
Function: InitReadInStack
Description: 初始化一个栈
Calls:  no
Called By: SearchWord()
Input: no
Output: 
Return: 返回栈的地址
Others: 
*************************************************/
ReadinStack *InitReadinS();

/*************************************************
Function: EmptyReadinS
Description:判断栈ReadinStack是否为空
Calls: none
Called By: SearchWord()
Input: 
Output: 
Return: 如果空，返回YES。否则返回NO
Others: // 其它说明
*************************************************/
int EmptyReadinS(ReadinStack *s);

/*************************************************
Function: PushReadinS
Description: 将x进栈
Calls: SearchWord()
Called By: none
Input:  栈的头地址，和元素x
Output: 将x存到栈顶
Return: 
Others: 
*************************************************/
void PushReadinS(ReadinStack *s,char x);

/*************************************************
Function: PopReadinS
Description: 将栈顶出栈
Calls: 
Called By: SearchWord()
Input:栈的头地址
Output: 
Return: 
Others: 
*************************************************/
void PopReadinS(ReadinStack *s);

/*************************************************
Function: CleanReadinS
Description: 将栈清空
Calls: 
Called By: SearchWord()
Input: 栈头地址
Output: 
Return: 
Others: 
*************************************************/
void CleanReadinS(ReadinStack *s);

/*************************************************
Function: InitSearchS
Description: 初始化一个栈
Calls:
Called By: SearchWord()
Input: 
Output: 
Return: 返回栈的地址
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
Return: 如果空，返回YES。否则返回NO
Others: 
*************************************************/
int EmptySearchS(SearchStack  *s);

/*************************************************
Function: PushSearchS
Description: 将current进栈
Calls: 
Called By: SearchWord()
Input:栈的头地址，和元素current
Output: 
Return:
Others: 
*************************************************/
void PushSearchS(SearchStack  *s,WorData *current);

/*************************************************
Function: PopSearchS
Description: 将栈顶出栈，并返回
Calls: EmptySearchS()
Called By: SearchWord()
Input:栈的头地址
Output: 
Return: 返回栈顶元素
Others: 
*************************************************/
WorData *PopSearchS(SearchStack  *s);

/*************************************************
Function: CleanSearchS
Description: 清空栈
Calls: 
Called By: SearchWord()
Input: 栈的头地址
Output:
Return: 
Others:
*************************************************/
void CleanSearchS(SearchStack *s);

/*************************************************
Function: LoadSetup
Description: 加载设置，如果是第一次运行，建立文件，写入默认设置；否则读入设置
Calls: none
Called By:  SetupModule()
Input: 
Output:  如果是第一次运行，建立存有默认设置的文件
Return: 返回已保存设置
Others: 
*************************************************/
SetUp *LoadSetup();

/*************************************************
Function: DisplaySetup
Description: 显示当前设置
Calls:  none
Called By: SetupModule
Input: 指向当前存有用户设置的结点的地址
Output: 
Return:
Others: 5.21	 部分布尔量显示为1/0改为显示YES/NO
*************************************************/
void Displaysetup(SetUp *);

/*************************************************
Function: SaveSetup
Description: 保持当前设置到磁盘文件中
Calls: none
Called By: SetupModule()
Input:  指向当前存有用户设置的结点的地址，用于把此结点写入到磁盘文件中
Output:  none
Return:  none
Others: 
*************************************************/
void SaveSetup(SetUp *setinfo);

/*************************************************
Function: 	void SetupModule(SetUp *setinfo)
Description: 设置模块
Calls: // 被本函数调用的函数清单
Called By: // 调用本函数的函数清单
Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
Input: // 输入参数说明，包括每个参数的作
// 用、取值说明及参数间关系。
Output: // 对输出参数的说明。
Return: // 函数返回值的说明
Others:  
*************************************************/
void SetupModule(SetUp *);

/*************************************************
Function:	void Destroy(WorData *alphabet[])
Description: 释放读取词库链表的空间
Called By: 	main()函数
Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
Input:  存有26个字母的链表的头指针的数组
Output: no
Return: no
Others:  5.28  出错    
*************************************************/
//void Destroy(WorData *alphabet[]);

/*************************************************
Function:	int Select(int min,int max)
Description: 用于选择或者安装规定的值的范围返回符合要求的值，如果在min和max的范围则返回，否则继续输入
Calls: // 被本函数调用的函数清单
Called By: // 调用本函数的函数清单
Input： 规定的最大小值的
Output: no
Return: 返回符合的值
Others:	5.21		lintghi	当scanf输入字符是出现死循环改为以下
*************************************************/
int Select(int min,int max);

/*************************************************
Function:	int YesOrNo()
Description: 判断输入是否为 y、Y、n、N中的一个，如果不是它们，最新输入
Input: NO
Output: // 对输出参数的说明。
Return: 如果 y、Y返回YES，n、N返回NO。
Others: // 其它说明
*************************************************/
int YesOrNo();

/*************************************************
Function:	int IsAlphabet(char input)
Description: 如果是字母，返回YES
Input: 所输入的字符
Output: 如果是数字，返回YES，否则返回NO
Return: // 函数返回值的说明
Others: // 其它说明
*************************************************/
int IsAlphabet(char input);

/*************************************************
Function:	int IsDigital(char input)
Description: 如果是数字，返回YES
Input: 所输入的字符
Output:  如果是数字，返回YES，否则返回NO
Return: // 函数返回值的说明
Others: // 其它说明
*************************************************/
int IsDigital(char input);

/*************************************************
Function:     int IsPrintChar(char input)
Description: 如果是可显示字符返回YES
Input:   输入的字符
Output: 
Return: 
Others:
*************************************************/
int IsPrintChar(char input);      //5.28 add

/*************************************************
Function:     char ToLower(char input)
Description: 将input转换为小写字母
Input:   输入的字符
Output: 
Return: 
Others:
*************************************************/
char ToLower(char input);
 

/*************************************************
Function:主函数
Description: 调用各模块
Calls: // 被本函数调用的函数清单
Called By: // 调用本函数的函数清单
Input: // 输入参数说明，包括每个参数的作
// 用、取值说明及参数间关系。
Output: // 对输出参数的说明。
Return: // 函数返回值的说明
Others: 
*************************************************/
void main()
{
	WorData *alphabet[26]={NULL};
	int chioce=1;
	int loaded = NO;
	SetUp *setinfo=NULL;  //参数要初始化
	
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
Description: 加载词库
Calls: CreatMyList()
Called By: main()
Input: 存有26个字母表头信息的数组
Output: // 对输出参数的说明。
Return: 失败返回NO，否则YES
Others: 	错将filename中的n.txt放在m.txt之前，导致中SearchWord()查找以n开头的单词出错
文件z.txt读入时死循环，因为z.txt中倒数第一行#号后多了一个空格键
*************************************************/
int Loading(WorData *alphabet[])        
{
	//定义指向字符串的指针数组，存放文件名. 将l.txt错写成.txt.
	char *filename[26] = {"a.txt","b.txt","c.txt","d.txt","e.txt","f.txt","g.txt","h.txt",
	"i.txt","j.txt","k.txt","l.txt","m.txt","n.txt","o.txt","p.txt","q.txt","r.txt","s.txt",
	"t.txt","u.txt","v.txt","w.txt","x.txt","y.txt","z.txt"};              

	//char *name=NULL;          //指向指针的指针，用于读取文件名
	int i=0;
	FILE *fp=NULL;
   
	INTERFACE_COLOR_2;
	
	printf("\n\n\n\n\n\n\n\n\n\n      - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r");
	printf("      ");
	for (i = 0; i < 26 ; i++ )        //25 -> 26,把26写成25,使z无法读入
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
		printf(" > ");                  //作为进度条
		fclose(fp);
		fp=NULL;
	}
	
	return 1;
}

/*************************************************
Function: 	CreatMyList(n) 
Description: 建立链表
Calls:none
Called By: Loading()
Input: 文件指针，指向一个存字母的文件的指针
Output: // 对输出参数的说明。
Return: 返回头指针
Others: 
*************************************************/
WorData *CreatMyList(FILE *open)      
{
	char readin='\0';            //第一次没加此语句造成readin的值无法确定
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
		if (readin=='@') break;     //未加该行，第二while将死循环
		i=0;
		j=0;
		flag=0;          //未赋初值错误

    	while (readin!='#')
		{
			while (flag!=1)
			{
				if (readin >=20) p->english[i++]=readin;          //add   if (readin >=20)  控制字符不加入到单词中
				readin=fgetc(open);
				if(readin==' ') flag=1;
			}
		    p->chinese[j++]=readin;
	        readin=fgetc(open);
		}
	   readin=fgetc(open);          //由于在#号后还有一个换行符，未加该行，在第一个readin将读入换行符导致第二个while死循环
	   p->english[i]='\0';       
	   p->chinese[j]='\0';          //写入结束
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
Description:搜索模块，调用查找函数，如果返回值为空则提示是否退出，否则按设置朗读单词
Calls: 	SearchWord()，YesOrNo()，SpeakWord()
Called By: main()
Input:  存有26个字母表头信息的数组,存有设置信息的结点地址
Output: // 对输出参数的说明。
Return: // 函数返回值的说明
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
				//break; //出错
				continue;
			}
		}
	}//end of while(1)
}

/*************************************************
Function: SearchWord
Description: 搜索输入单词在链表中的位置
Calls: InitReadinS(), InitSearchS(),PushReadinS(),PushSearchS(),FindLocat(),DisplayToChoose(),
Called By:    SearchMoulde()
Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
Input:存有26个字母表头信息的数组
Output: // 对输出参数的说明。
Return: 查找的结果的地址
Others: 5.29	对输入大写字母的情况做了修改
*************************************************/
WorData *SearchWord(WorData *alphabet[])            
{
	char input='\0';
	
	WorData *head=NULL,*current=NULL,*result=NULL;  //lack *
	WorData *Findout[10];
	ReadinStack *readins=NULL;
	SearchStack *searchs=NULL;
	
	readins=InitReadinS();       //初始化
	searchs=InitSearchS();      
	while(1)
	{
		while (1)
		{
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\n");     //打印出十个空行准备显示十个单词以供选择
			printf("Input:");
			
			input = getch();   //getche() -> getch()，第一个字母可能是大写不能转换成小写
			if (IsAlphabet(input) == YES)    //5.28 add   如果
			{
				putchar(input);
			}
			
			if (input == '`')
			{
				return NULL;
			}
			else if (IsAlphabet(input) == NO)  
			{
				break;     //IsAlphabet()判断是否为字母，是返回1
			}
			else
			{
				head = alphabet[ToLower(input) - 'a'];         //tolower() 将input字符转换成小写字母，-'a'得到input字符在alphabet数组中的位置   5.28
				current = head;
			}
			
			while (1)                
			{
				if (IsAlphabet(input) == YES) //如果input是字母
				{
					PushReadinS(readins,input);
					PushSearchS(searchs,current);
					current=FindLocat(readins,current);
					FindToChoose(current,Findout);
					DisplayToChoose(Findout,readins->readin);
					if (current != NULL)  //如果没找到
					{
						input=ToLower(getch());
						if (IsAlphabet(input) == YES)    //5.28 add   
						{
							putchar(input);
						}
						continue;
					}
				}
				else if (IsDigital(input) == YES) //是否为数字，是返回1
				{
					result=Findout[input-'0'];
					return result;
				}
				else if (input == '=') //输入 = ，表退格键
				{
					PopReadinS(readins);
					if (EmptyReadinS(readins) == YES) break;      //5.28 add,如果不修改，输入a = b，将出错
					current=PopSearchS(searchs);        //返回上次所指位置
					current=FindLocat(readins,current);
					FindToChoose(current,Findout);
					DisplayToChoose(Findout,readins->readin);
					//BACKSPACE;     //将之前输入的一个字符擦掉
				}
				else if (input == '@') //输入 -  ，清空整行
				{
					CleanReadinS(readins);
					CleanSearchS(searchs);
					break;       //重新输入
				}
				else if (input == '`')   //Esc键下面的那个键
				{
					return NULL;
				}
				//else BACKSPACE;     //其他情况，将该输入从屏幕上删除，已经有以下语句，该句可以去掉
				
				input = ToLower(getch());
				if (IsAlphabet(input) == YES)    //5.28 add   如果
				{
					putchar(input);
				}
			}//end of while (1)
		}//end of the frist while(1)
	}
}


/*************************************************
Function: WorData *FindLocat(ReadinStack *readin,WorData *head)
Description: 在链表中以head为开始位置查找所输入字符串的位置
Calls:  no
Called By: SearchWord()
Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
Input:   以head为开始位置的地址，输入的字符串头地址
Output:no
Return: 输入字符串的位置
Others: // 其它说明
*************************************************/
WorData *FindLocat(ReadinStack *readin,WorData *head)
{
	WorData *search = head;           //
	
	while (search != NULL)
	{
		//不区分大小写比较
		while (strnicmp(readin->readin,search->english,strlen(readin->readin))>0) search = search->next;       //5.28  if -> while
		return search;
	}
	return NULL;
}

/*************************************************
Function: FindToChoose
Description: 将当前指针的位置后和后九个地址存入Findout[]数组中
Calls: none
Called By: SearchWord()
Input: 当前指针的位置和Findout[]数组的地址
Output: 改变Findout[]数组中值
Return: 
Others: 
*************************************************/
void FindToChoose(WorData *current,WorData *Findout[])
{
	WorData *temp = current;
	int i=0;
	
	while(i < 10)              //不管temp是否为空，都将其赋给Findout[i]
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
Description: // 显示以该字母与之前输入的字母构成的字符串为前缀的前十个单词，以供用户选择
Calls: none
Called By:SearchWord()
Input: 存放有十个单词所在结点的地址的数组,当显示出十个单词后将光标重新定位在原位置，等待继续输入
Output:显示以输入的字母构成的字符串为前缀的前十个单词
Return:
Others: 
*************************************************/
void DisplayToChoose(WorData *Findout[],char *readin)
{
	int i;
	
	system("cls");
	for (i = 0;i < 10 ;i++)
	{
		//如果前一个Findout有十个元素，而当前没有十个，要将之前的显示擦掉
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
Description:显示输入单词的中文意思
Calls: 
Called By: // 调用本函数的函数清单
Input: 
Output: // 对输出参数的说明。
Return: // 函数返回值的说明
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
Description: 按照用户的设置，朗读查找结果
Input:  查找结果的结点的地址，存有设置信息的结点的地址
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
Description: 初始化一个栈
Calls:  no
Called By: SearchWord()
Input: no
Output: 
Return: 返回栈的地址
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
Description:判断栈ReadinStack是否为空
Calls: none
Called By: SearchWord()
Input: 
Output: 
Return: 如果空，返回YES。否则返回NO
Others: // 其它说明
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
Description: 将x进栈
Calls: SearchWord()
Called By: none
Input:  栈的头地址，和元素x
Output: 将x存到栈顶
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
Description: 将栈顶出栈
Calls: 
Called By: SearchWord()
Input:栈的头地址
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
Description: 将栈清空
Calls: 
Called By: SearchWord()
Input: 栈头地址
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
Description: 初始化一个栈
Calls:
Called By: SearchWord()
Input: 
Output: 
Return: 返回栈的地址
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
Return: 如果空，返回YES。否则返回NO
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
Description: 将current进栈
Calls: 
Called By: SearchWord()
Input:栈的头地址，和元素current
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
Description: 将栈顶出栈，并返回
Calls: EmptySearchS()
Called By: SearchWord()
Input:栈的头地址
Output: 
Return: 返回栈顶元素
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
Description: 清空栈
Calls: 
Called By: SearchWord()
Input: 栈的头地址
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
Description: 加载设置，如果是第一次运行，建立文件，写入默认设置；否则读入设置
Calls: none
Called By:  SetupModule()
Input: 
Output:  如果是第一次运行，建立存有默认设置的文件
Return: 返回已保存设置
Others: 
*************************************************/
SetUp *LoadSetup()
{
	FILE *setinfofile = NULL;
	char *filelocate = {"setinfo.dat"};
	SetUp *setinfo=NULL;

	//如果设置文件不存在，表示第一次打开，此时要建立文件
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
				//设置默认值:朗读3次，间隔为半秒，显示单词后自动朗读，读完返回查找界面，进入软件后自动进入查找界面
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
					fclose(setinfofile);        //5.20加入，关闭文件
					return setinfo;
				}
			}
		}
	}//少了两个｝
	else          //如果文件以存在，读入设置数据
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
Description: 显示当前设置
Calls:  none
Called By: SetupModule
Input: 指向当前存有用户设置的结点的地址
Output: 
Return:
Others: 5.21	 部分布尔量显示为1/0改为显示YES/NO
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
Description: 保持当前设置到磁盘文件中
Calls: none
Called By: SetupModule()
Input:  指向当前存有用户设置的结点的地址，用于把此结点写入到磁盘文件中
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
Description: 释放读取词库链表的空间
Called By: 	main()函数
Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
Input:  存有26个字母的链表的头指针的数组
Output: no
Return: no
Others:  5.28  出错    原因：alphabet[]未赋初值，并且部分文件读入失败
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
Description: 用于选择或者安装规定的值的范围返回符合要求的值，如果在min和max的范围则返回，否则继续输入
Calls: // 被本函数调用的函数清单
Called By: // 调用本函数的函数清单
Input： 规定的最大小值的
Output: no
Return: 返回符合的值
Others:	5.21		lintghi	当scanf输入字符是出现死循环改为以下
*************************************************/
int Select(int min,int max)
{
	char temp[30];  //add
	int input = 0;
	
	while (1)
	{
		//scanf("%d",&input);当scanf输入字符时出现死循环，改为以下
		gets(temp);
		input=atoi(temp);     //将输入字符串转换为整型数字
		
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
Description: 设置模块
Calls: // 被本函数调用的函数清单
Called By: // 调用本函数的函数清单
Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
Input: // 输入参数说明，包括每个参数的作
// 用、取值说明及参数间关系。
Output: // 对输出参数的说明。
Return: // 函数返回值的说明
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
Description: 判断输入是否为 y、Y、n、N中的一个，如果不是它们，最新输入
Input: NO
Output: // 对输出参数的说明。
Return: 如果 y、Y返回YES，n、N返回NO。
Others: // 其它说明
*************************************************/
int YesOrNo()
{
	char input;
	while (1)
	{
		input=getch();
		
		if (input >20)      //如果不是控制字符，回显
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
			printf("\b%c\b",input);     //输入其他，均无效果
		}
	}
}

/*************************************************
Function:	int IsAlphabet(char input)
Description: 如果是字母，返回YES
Input: 所输入的字符
Output: 如果是数字，返回YES，否则返回NO
Return: // 函数返回值的说明
Others: // 其它说明
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
Description: 如果是数字，返回YES
Input: 所输入的字符
Output:  如果是数字，返回YES，否则返回NO
Return: // 函数返回值的说明
Others: // 其它说明
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
Description: 如果是可显示字符返回YES
Input:   输入的字符
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
Description: 将input转换为小写字母
Input:   输入的字符
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


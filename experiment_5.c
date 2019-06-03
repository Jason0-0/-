#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define N 30

//定义一个日期结构体（yyyy.mm.dd)
typedef struct date
{
	int year;
	int month;
	int day;
}DATE;
typedef union key
{
	int i;
	float f;
}KEY;
//定义结构体{Name.KEY}
typedef struct stat
{
	char Name[25];
	KEY Value;
}STAT;
//定义结构体{Name.ID.JoinTime.Wage.Avg}
typedef struct employee
{
	char Name[50];
	long ID;
	DATE JoinTime;
	float Wage;
	//float Avg;
}EMPLOYEE;
//定义联合体 以便于传入写文件函数中
typedef union wtr2file
{
	STAT s;
	EMPLOYEE e;
}WRITE2FILE;
static int n;
static int HasInput = 0;
void Input(EMPLOYEE* pE);
int Statics(EMPLOYEE* pE);
void DesWage(EMPLOYEE* pE);
void SortbyDict(EMPLOYEE* pE);
EMPLOYEE* Search_ID(EMPLOYEE* pE);
void Search_Name(EMPLOYEE* pE);
void ListRecord(EMPLOYEE* pE);

int main()
{
	printf("Number:180310320\nsubject No.7 - program No.1\n\n");

	//定义一个结构体数组
	EMPLOYEE stE[N] = { { NULL } };

	//定义指向结构体数组的指针
	EMPLOYEE* pE = stE;


	char cSelect;

	while (1)
	{
		printf("Input employee number(0<n<=30):");

		//输入检测，确保只能输入数字
		char c = NULL;
		int ans = 0;
		while (1)
		{
			c = getchar();
			if (c >= '0' && c <= '9')
			{
				ans = 10 * ans + (c - '0');
				continue;
			}
			else if (c == '\n')
			{
				n = ans;
				break;
			}
			else
			{
				printf("Invalid!\nInput employee number(0<n<=30):");
				while (getchar() != '\n');
			}
		}

		//检测输入是否在范围内
		if (n > 0 && n <= 30)
		{
			break;
		}
		printf("Beyond the scope! Please input again!\n");
	}

	//菜单
	while (1)
	{
		cSelect = NULL;
		printf("\n==========================================\n");
		printf("1.  Input record\n");
		printf("2.  Delete record\n");
		printf("3.  Sort in descending order by salary\n");
		printf("4.  Sort in dictionary order by name\n");
		printf("5.  Search by ID\n");
		printf("6.  Search by name\n");
		printf("7.  Search by hire date\n");
		printf("8.  Modify record\n");		//修改薪资
		printf("8.  Statistic\n");
		printf("0.  Exit\n");
		printf("=========================================\n\n");

		printf("Please input your choice: ");
		scanf(" %c", &cSelect);
		while (getchar() != '\n');
		putchar('\n');

		//选择
		switch (cSelect)
		{
		case '0':
			printf("End of the program!\n");
			exit(0);

		case '1':
			Input(pE);

			//将HasInput设为1，表示已输入
			HasInput = 1;
			break;
		case '2':

			//判断是否输入了数据，下同
			if (HasInput != 1)
			{
				printf("Please input data first!\n");
				break;
			}

			AvgWage(pE);
			break;
		case '3':
			if (HasInput != 1)
			{
				printf("Please input data first!\n");
				break;
			}
			DesWage(pE);
			break;
		case '4':
			if (HasInput != 1)
			{
				printf("Please input data first!\n");
				break;
			}
			SortbyDict(pE);
			break;
		case '5':
			if (HasInput != 1)
			{
				printf("Please input data first!\n");
				break;
			}
			Search_ID(pE);
			break;
		case '6':
			if (HasInput != 1)
			{
				printf("Please input data first!\n");
				break;
			}
			Search_Name(pE);
			break;
		case '7':
			if (HasInput != 1)
			{
				printf("Please input data first!\n");
				break;
			}
			ListRecord(pE);
			break;

		default:
			printf("Invalid! Please input again!\n");
			break;
		}
	}

	return 0;
}

void Input(EMPLOYEE* pE)
{

	int ret = 0;
	int retS = 0;
	int flag = 0;
	printf("Input employee's Name,ID,Wage(ID,Wage):\n\n");
	for (int i = 0; i < n; i++)
	{
		do
		{
			printf("[%d/%d]\n", i + 1, n);
			printf("Input Name: ");
			retS = scanf("%s", pE->Name);
			printf("Input ID,Wage: ");
			ret = scanf("%ld,%f", &pE->ID, &pE->Wage);
			if (pE->ID < 0)
			{
				ret = -1;
			}
			if (pE->Wage < 5000.0 || pE->Wage>20000.0 || ret != 2 || retS != 1)
			{
				printf("Invalid! Please input again!\n");
				flag = 1;
			}
			else
			{
				flag = 0;
			}

		} while (flag);
		putchar('\n');
		pE++;
	}
}

int Statics(EMPLOYEE* pE)//complete!
{
	float sum = 0.0;
	float avg;
	STAT StatofStaff[3]
		= {
			{{"Number of staff(s):"},{NULL} },
			{{"Sum of wage:"},{NULL} },
			{{"Average wage:"},{NULL} },
		};
	
	int i = 0;

	while(i< n)
	{
		if (pE->ID<0)
		{
			continue;
		}
		sum += pE->Wage;
		pE++;
		i++;
	}
	avg = sum / n;

	StatofStaff[0].Value.i = n;
	StatofStaff[1].Value.f = sum;
	StatofStaff[2].Value.f = avg;

	WRITE2FILE wStat[3];
	for (int i = 0; i < 3; i++)
	{
		wStat[i].s = StatofStaff[i];
	}

	WriteFile(wStat, 'S');
	
	//printf("Average wage of the employees: %.2f\n", avg);
}

void ListRecord(EMPLOYEE* pE)
{
	int i = 0;
	while (i < n)
	{
		if (pE->ID < 0)
		{
			continue;
		}
		printf("%d. NO.%d\t Name:%s\t Wage:%.2f\n", i + 1, pE->ID, pE->Name, pE->Wage);
		pE++;
		i++;
	}
}

EMPLOYEE* Search_ID(EMPLOYEE* pE)
{
	int key = -1;
	printf("Input the ID you want to Search_ID:");
	scanf("%d", &key);
	while(pE->Name!=NULL)
	{
		if (pE->ID == key)
		{
			printf("%d\t%s\t%.2f\n", pE->ID, pE->Name, pE->Wage);
			return pE;
		}
		pE++;

	}
	printf("No record!");
	return NULL;
}

void DesWage(EMPLOYEE* pE, EMPLOYEE* pArray[])
{
	//定义一个中间指针
	EMPLOYEE* pTemp = NULL;
	int i, j, k;

	//排序
	for (i = 0; i < n; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (pArray[j]->Wage > pArray[k]->Wage)
			{
				k = j;
			}
		}
		if (k != i)
		{
			//实现指针所存地址的交换
			pTemp = pArray[k];
			pArray[k] = pArray[i];
			pArray[i] = pTemp;
		}
	}


	


}

void SortbyDict(EMPLOYEE* pE, EMPLOYEE* pArray[])
{
	//定义一个EMPLOYEE类型的指针数组，分别指向EMPLOYEE数组strE的各项
	EMPLOYEE* pArray[N] = { NULL };
	for (int i = 0; i < n; i++)
	{
		pArray[i] = pE;
		pE++;
	}

	//定义一个中间指针
	EMPLOYEE* pTemp = NULL;
	int i, j, k;

	//排序
	for (i = 0; i < n; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (strcmp(pArray[j]->Name, pArray[k]->Name) < 0)
			{
				k = j;
			}
		}
		if (k != i)
		{
			//实现指针所存地址的交换
			pTemp = pArray[k];
			pArray[k] = pArray[i];
			pArray[i] = pTemp;
		}
	}


	//output the result
	printf("Sort in dictionary order by name: \n");
	for (int i = 0; i < n; i++)
	{
		printf("%d. NO.%d\t%s\tWage:%-6.2f\n", i + 1, pArray[i]->ID, pArray[i]->Name, pArray[i]->Wage);
	}
}

void Search_Name(EMPLOYEE* pE)
{
	char key[50] = { NULL };
	printf("Input the Name you want to Search:");
	gets(key);
	for (int i = 0; i < n; i++)
	{
		if (strcmp(pE->Name, key) == 0)
		{
			printf("%d\t%s\t%.2f\n", pE->ID, pE->Name, pE->Wage);
			return;
		}
		pE++;

	}
	printf("No record!");
}


void ReadFile(EMPLOYEE* pE)
{
	FILE* fp;
	int i;

	if ((fp = fopen("\data\staff.txt", "r")) == NULL)
	{
		printf("Failure to open staff.txt!\n");
		exit(0);
	}

	fscanf(fp, "%d", &n);

	for ( i = 0; i < n; i++)
	{
		fscanf("%ld %s %d/%d/%d %f ", &pE->ID, pE->Name, &pE->JoinTime.year, &pE->JoinTime.month, &pE->JoinTime.day, &pE->Wage/*, &pE->Avg*/);
		pE++;
	}

	fclose(fp);
}

/*void WriteFile(EMPLOYEE* pE)  //如何设计以达到一个函数可以接收两个不同类型的结构体呢？？
{
	FILE* fp;
	int i;
	if ((fp = fopen("\data\staff.txt", "w") == NULL))
	{
		printf("Failure to open staff.txt!\n");
		exit(-1);
	}

	i = 0;
	while (i<n)
	{
		if (pE->ID<0)
		{
			continue;
		}
		fprintf(fp, " %ld %s %d/%d/%d %f \n", pE->ID, pE->Name, pE->JoinTime.year, pE->JoinTime.month, pE->JoinTime.day, pE->Wage);
		pE++;
		i++;
	}
	fclose(fp);
}  */

void SortbyID(EMPLOYEE* pE, EMPLOYEE* pArray[])
{
	//定义一个EMPLOYEE类型的指针数组，分别指向EMPLOYEE数组strE的各项
	EMPLOYEE* pArray[N] = { NULL };
	for (int i = 0; i < n; i++)
	{
		pArray[i] = pE;
		pE++;
	}

	//定义一个中间指针
	EMPLOYEE* pTemp = NULL;
	int i, j, k;

	//排序
	for (i = 0; i < n; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (pArray[j]->ID > pArray[k]->ID)
			{
				k = j;
			}
		}
		if (k != i)
		{
			//实现指针所存地址的交换
			pTemp = pArray[k];
			pArray[k] = pArray[i];
			pArray[i] = pTemp;
		}
	}
	//output the result
	printf("Sort in descending order by ID: \n");
	for (int i = 0; i < n; i++)
	{
		printf("%d. NO.%ld\t%s\t%d/%d/%d\tWage:%-6.2f\n", i + 1, pArray[i]->ID, pArray[i]->Name,pArray[i]->JoinTime.year,pArray[i]->JoinTime.month,pArray[i]->JoinTime.day, pArray[i]->Wage);
	}
}

void SortbyTime(EMPLOYEE* pE,EMPLOYEE* pArray[])
{
	//定义一个EMPLOYEE类型的指针数组，分别指向EMPLOYEE数组strE的各项
	EMPLOYEE* pArray[N] = { NULL };
	for (int i = 0; i < n; i++)
	{
		pArray[i] = pE;
		pE++;
	}

	//定义一个中间指针
	EMPLOYEE* pTemp = NULL;
	int i, j, k;

	//排序
	for (i = 0; i < n; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (pArray[j]->JoinTime.year > pArray[k]->JoinTime.year)
			{
				k = j;
			}
			else if (pArray[j]->JoinTime.year==pArray[k]->JoinTime.year&&pArray[j]->JoinTime.month > pArray[k]->JoinTime.month)
			{
					k = j;
			}
			else if (pArray[j]->JoinTime.month == pArray[k]->JoinTime.month && pArray[j]->JoinTime.day > pArray[k]->JoinTime.day)
			{
						k = j;
			}
				
		}
		if (k != i)
		{
			//实现指针所存地址的交换
			pTemp = pArray[k];
			pArray[k] = pArray[i];
			pArray[i] = pTemp;
		}
	}
	//output the result
	printf("Sort in descending order by hire date: \n");
	for (int i = 0; i < n; i++)
	{
		printf("%d. NO.%ld\t%s\t%d/%d/%d\tWage:%-6.2f\n", i + 1, pArray[i]->ID, pArray[i]->Name, pArray[i]->JoinTime.year, pArray[i]->JoinTime.month, pArray[i]->JoinTime.day, pArray[i]->Wage);
	}
}

void SearchbyTime(EMPLOYEE* pE)
{
	DATE key = { 0,0,0 };
	printf("Please input the date of hired (yyyy/mm/dd)");
	scanf_s("%d/%d/%d", key.year, key.month, key.day);
	for (int i = 0; i < n; i++)
	{
		if (pE->JoinTime.year==key.year
			&&pE->JoinTime.month==key.month
			&&pE->JoinTime.day==key.month)		//结构体之间不能直接比较
		{
			printf("%d. NO.%ld\t%s\t%d/%d/%d\tWage:%-6.2f\n", i + 1, pE->ID, pE->Name, pE->JoinTime.year, pE->JoinTime.month, pE->JoinTime.day, pE->Wage);

		}
		pE++;
		
	}
}

void ModRec(EMPLOYEE* pE)
{
	//调用Searc_ID函数来得到需要修改的员工信息及地址
	EMPLOYEE* pMod;
	pMod = Search_ID(pE);

	char comfirm = NULL;
	int TempWage = -1;

	printf("Modify:\n\n%d %s ", pE->ID, pE->Name);
	scanf_s("%d",&TempWage);
	
	do
	{
		printf("\n\nSave changes?\t");
		while (getchar() != '\n');
		comfirm = getchar();
	} while (comfirm != 'y' && comfirm != 'Y' && comfirm != 'n' && comfirm != 'N');
	if (comfirm=='y'||comfirm=='Y')
	{
		pMod->Wage = TempWage;
		printf("Success!\n");
		return;
	}
	else
	{
		printf("Changes have not saved!\n");
		return;
	}
}

int DelRec(EMPLOYEE* pE)
{
	EMPLOYEE* pMod;
	pMod = Search_ID(pE);
	char comfirm = NULL;
	do
	{
		printf("Comfirm delect this record?\t");
		while (getchar() != '\n');
		comfirm = getchar();
	} while (comfirm != 'y' && comfirm != 'Y' && comfirm != 'n' && comfirm != 'N');
	
	if (comfirm=='y'||comfirm=='Y')
	{
		pMod->ID=-1;
		n--;
		return 1;
	}
	else
	{
		return -1;
	}

}

void Sort(EMPLOYEE* pE, void(*Func_Sorting))
{
	//定义一个EMPLOYEE类型的指针数组，分别指向EMPLOYEE数组strE的各项,并忽略已删除的项（ID值定义为-1的）
	EMPLOYEE* pArray[N] = { NULL };
	static char TypeofSort[15] = { NULL };
	int i = 0;
	while (i < n)
	{
		if (pE->ID < 0)
		{
			pE++;
			continue;
		}
		pArray[i] = pE;
		pE++;
		i++;
	}

	void (*Func_Sorting)(pE, pArray);

	//output the result
	printf("Sort in decending order by %s: \n",TypeofSort);
	i = 0;
	while (i < n)
	{
		if (pE->ID < 0)
		{
			continue;
		}
		printf("%d. NO.%d\t%s\tWage:%-6.2f\n", i + 1, pArray[i]->ID, pArray[i]->Name, pArray[i]->Wage);
	}

}

void WriteFile(WRITE2FILE* argc_w2f,char argc_c)//need to test 
{
	FILE* fp;
	int i;
	if ((fp = fopen("\data\staff.txt", "w") == NULL))
	{
		printf("Failure to open staff.txt!\n");
		exit(-1);
	}

	if (argc_c == 'E')
	{
		i = 0;
		while (i < n)
		{
			if (argc_w2f->e.ID < 0)
			{
				continue;
			}
			fprintf(fp, " %ld %s %d/%d/%d %f \n", argc_w2f->e.ID, argc_w2f->e.Name, argc_w2f->e.JoinTime.year, argc_w2f->e.JoinTime.month, argc_w2f->e.JoinTime.day, argc_w2f->e.Wage/*, pE->Avg*/);
			argc_w2f++;
			i++;
		}
	}
	else if (argc_c=='S')
	{
		fprintf("%s\t%d",argc_w2f->s.Name,argc_w2f->s.Value );
		argc_w2f++;
		fprintf("%s\t%f", argc_w2f->s.Name, argc_w2f->s.Value);
		argc_w2f++;
		fprintf("%s\t%f", argc_w2f->s.Name, argc_w2f->s.Value);	
	}
	fclose(fp);
}
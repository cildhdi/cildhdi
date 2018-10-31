#include <stdio.h>
#include <stdlib.h>
#define FILENAME "student.txt"
typedef struct Student
{
    int num;       //学生编号
    char name[10]; //学生姓名
    int grade;     //学生年级
    int chinese;   //语文成绩
    int math;      //数学成绩
    int english;   //英语成绩
    struct Student *next;//下一个节点的指针
}STUDENT, *PSTUDENT;
STUDENT g_head;    //头节点
void ShowMenu();//1.显示菜
int GetChoice();//2.获取用户选择的菜单的编号
PSTUDENT CreateStudent();//3.创建一个节点,它会返回一个新创建的学生信息节点的指针
int AddStudent(PSTUDENT pstu);//4.把学生信息节点加入到链表中
PSTUDENT GetPrevAddr(int num);//5.返回指定编号学生节点的上一个节点的指针
void ShowAll();//6.显示所有学生信息
void ShowStudent(int num);//7.显示编号为num的学生信息
int ShowStudentCount();//8.显示信息数量
void ModityStudent(int num);//9.修改学生信息，num为要修改的学生编号
int Question(const char *pstr);//10.获取用户的选择
int GetInputNum();//11.获取用户输入的学生编号
void DelStudent(int num);//12.删除编号为num的学生信息
void DelAll();//13.删除所有的学生信息
void SaveToFile();//14.把学生信息保存到文件当中
void LoadFromFile();//15.从文件中读取学生信息

int main()
{
    int running = 1;
    while(running)
    {
        switch(GetChoice())
        {
            case 0: exit(0);
            case 1: printf("你选择了菜单1\n");AddStudent(CreateStudent());break;
            case 2: printf("你选择了菜单2\n");DelStudent(GetInputNum());break;
            case 3: printf("你选择了菜单3\n");ShowStudent(GetInputNum());break;
            case 4: printf("你选择了菜单4\n");ModityStudent(GetInputNum());break;
            case 5: printf("你选择了菜单5\n");DelAll();break;
            case 6: printf("你选择了菜单6\n");ShowAll();break;
            case 7: printf("你选择了菜单7\n");ShowStudentCount();break;
            case 8: printf("你选择了菜单8\n");LoadFromFile();break;
            case 9: printf("你选择了菜单9\n");SaveToFile();break;
        }
        system("pause");
    }
    return 0;
}

void ShowMenu()//1.显示菜单
{
    system("cls");
    printf("-------------------------上海大学学生成绩管理系统-------------------------\n");
    printf("\n\t1.添加学生信息    2.删除某个学生信息    3.显示某个学生信息\n");
    printf("\t4.修改学生信息    5.删除所有学生信息    6.显示所有学生信息\n");
    printf("\t7.显示信息数量    8.读取文件学生信息    9.保存学生信息至文件\n");
    printf("\t0.退出系统\n");
    printf("\n-------------------------------------------------------------------------\n");
}

int GetChoice()//2.获取用户选择的菜单的编号
{
    int num;//保存用户选择的菜单编号
    ShowMenu();
    printf("请选择菜单(0-9):");
    while( scanf("%d", &num)!=1 || num < 0 || num > 9)
    {
        ShowMenu();
        printf("选择菜单错误，请重新选择(0-9):");
        fflush(stdin);//清空输入缓冲区
    }
    return num;
}

PSTUDENT CreateStudent()//3.创建一个节点,它会返回一个新创建的学生信息节点的指针
{
    int sex;
    PSTUDENT pstu = (PSTUDENT)malloc(sizeof(STUDENT));//在堆内存申请空间，存储学生信息
    if(!pstu)
    {
        printf("申请内存空间失败!\n");
        return NULL;
    }
    printf("请输入学生的编号(整型)：");
    while( scanf("%d", &pstu->_num)!=1 || GetPrevAddr(pstu->_num))
    {
        printf("学生编号输入错误或已经存在，请重新输入学生的编号(整型)：");
        fflush(stdin);
    }
    printf("请输入学生的姓名(小于10字符)：");
    scanf("%10s", pstu->_name);
    printf("请输入学生的年级(1-4)：");
    while( scanf("%d",&pstu->_grade)!=1 || pstu->_grade < 1 || pstu->_grade > 4)
    {
        printf("年级输入错误，请重新输入学生的年级(1-4)：");
        fflush(stdin);
    }
    printf("请输入学生的语文成绩(0-100)：");
    while( scanf("%d", &pstu->_chinese)!=1 || pstu->_chinese < 0 || pstu->_chinese > 100)
    {
        printf("成绩输入错误！请重新输入学生的语文成绩(0-100)：");
        fflush(stdin);
    }
    printf("请输入学生的数学成绩(0-100)：");
    while( scanf("%d", &pstu->_math)!=1 || pstu->_math < 0 || pstu->_math > 100)
    {
        printf("成绩输入错误，请重新输入学生的数学成绩(0-100)：");
        fflush(stdin);
    }
    printf("请输入学生的英语成绩(0-100)：");
    while( scanf("%d", &pstu->_english)!=1 || pstu->_english < 0 || pstu->_english > 100)
    {
        printf("成绩输入错误，请重新输入学生的英语成绩(0-100)：");
        fflush(stdin);
    }
    printf("添加成功!\n");
    pstu->_next = NULL;
    return pstu;
}

int AddStudent(PSTUDENT pstu)//4.把学生信息节点加入到链表中
{
    PSTUDENT ps = &g_head;
    if(!pstu)
    {
        return 0;
    }
    if(GetPrevAddr(pstu->_num))//判断一下该学生信息是不是已经存在
    {
        printf("编号为%d的学生信息已经存在！\n", pstu->_num);
        free(pstu);//释放该节点内存空间
        return 0;
    }
    while(ps->next)//找到当前链表的最后一个节点
        ps = ps->next;
    ps->next = pstu;//把新节点加入到最后那个节点的后面
    pstu->_next = NULL;
    return 1;
}

PSTUDENT GetPrevAddr(int num)//5.返回指定编号学生节点的上一个节点的指针
{
    PSTUDENT pstu = &g_head;
    while(pstu->_next)
    {
        if(pstu->_next->num == num)
            return pstu;
        pstu = pstu->_next;
    }
    return NULL;
}

void ShowAll()//6.显示所有学生信息
{
    PSTUDENT pstu = &g_head;
    printf("--------------------------------------------------------------------\n");
    printf("  编号      姓名      年级      语文成绩      数学成绩      英语成绩\n");
    printf("--------------------------------------------------------------------\n");
    while(pstu->_next)
    {
       printf("%4d", pstu->_next->num);
       printf("%10s", pstu->_next->name);
       printf("%10d", pstu->_next->grade);
       printf("%13d", pstu->_next->chinese);
       printf("%13d", pstu->_next->math);
       printf("%13d\n", pstu->_next->english);
       pstu = pstu->_next;
    }
    printf("--------------------------------------------------------------------\n");
}

void ShowStudent(int num)//7.显示编号为num的学生信息
{
    PSTUDENT pstu = GetPrevAddr(num);
    if(!pstu)
    {
        printf("没有编号为%d的学生信息。\n", num);
        fflush(stdin);
        return;
    }
    printf("--------------------------------------------------------------------\n");
    printf("  编号      姓名      年级      语文成绩      数学成绩      英语成绩\n");
    printf("--------------------------------------------------------------------\n");
    printf("%4d", pstu->_next->num);
    printf("%10s", pstu->_next->name);
    printf("%10d", pstu->_next->grade);
    printf("%13d", pstu->_next->chinese);
    printf("%13d", pstu->_next->math);
    printf("%13d\n", pstu->_next->english);
    pstu = pstu->_next;
    printf("--------------------------------------------------------------------\n");
    return;
}

int ShowStudentCount()//8.显示信息数量
{
    int count = 0;
    PSTUDENT pstu = &g_head;
    while(pstu->_next)
    {
        ++count;
        pstu = pstu->_next;
    }
    printf("\n当前共有%d位学生信息。\n", count);
    return count;
}

void ModityStudent(int num)//9.修改学生信息，参数为要修改的学生的编号
{
    PSTUDENT pstu = GetPrevAddr(num);//获取要修改的学生节点的上一个节点
    int choice;
    if(!pstu)
    {
        printf("没有编号为%d的学生信息。\n", num);
        return;
    }
    pstu = pstu->_next;//将要修改的学员节点的指针改为指向自己的
    printf("当前学生的姓名为%s,", pstu->_name);
    if(Question("确定要修改吗？"))
    {
        printf("请输入学生的姓名(小于10字符)：");
        scanf("%10s", pstu->_name);
    }
    printf("当前学生的年级为%d,", pstu->_grade);
    if(Question("确定要修改吗？"))
    {
        printf("请输入学生的年级(1-4)：");
        while( scanf("%d", &pstu->_grade)!=1 || pstu->_grade < 1 || pstu->_grade > 4)
        {
            printf("年级输入错误，请重新输入学生的年级：");
            fflush(stdin);
        }
    }
    printf("当前学生的语文成绩为%d,", pstu->_chinese);
    if(Question("确定要修改吗？"))
    {
        printf("请输入学生的语文成绩(0-100)：");
        while(scanf("%d", &pstu->_chinese)!=1 || pstu->_chinese < 0 || pstu->_chinese > 100)
        {
            printf("成绩输入错误！请重新输入学生的语文成绩(0-100)：");
            fflush(stdin);
        }
    }
    printf("当前学生的数学成绩为%d,", pstu->_math);
    if(Question("确定要修改吗？"))
    {
        printf("请输入学生的数学成绩(0-100)：");
        while(scanf("%d", &pstu->_math)!=1 || pstu->_math < 0 || pstu->_math > 100)
        {
            printf("成绩输入错误！请重新输入学生的数学成绩(0-100)：");
            fflush(stdin);
        }
    }
    printf("当前学生的英语成绩为%d,", pstu->_english);
    if(Question("确定要修改吗？"))
    {
        printf("请输入学生的英语成绩(0-100)：");
        while(scanf("%d", &pstu->_english)!=1 || pstu->_english < 0 || pstu->_english > 100)
        {
            printf("成绩输入错误！请重新输入学生的英语成绩(0-100)：");
            fflush(stdin);
        }
    }
    printf("修改完毕！\n");
}

int Question(const char *pstr)//10.获取用户的选择
{
    char answer;
    printf("%s请选择（y or n）：", pstr);
    while(1 != scanf(" %c", &answer) || (answer != 'y' && answer != 'n'))
    {
        printf("输入错误！%s请重新选择（y or n）：", pstr);
        fflush(stdin);//清空输入缓冲区,C库函数
    }
    if('y' == answer)
        return 1;
    else
        return 0;
}

int GetInputNum()//11.获取用户输入的学生的编号
{
    int num;
    printf("请输入学生的编号(整型)：");
    while( scanf("%d", &num)!= 1 )
    {
        printf("编号输入错误！请重新输入学生的编号(整型)：");
        fflush(stdin);
    }
    return num;
}

void DelStudent(int num)//12.删除编号为num的学生信息
{
    PSTUDENT pstu, ptmp;
    if(pstu = GetPrevAddr(num))
    {
        if(!Question("确定要删除该学生信息吗？"))
        {
            return;
        }
        ptmp = pstu->_next;
        pstu->_next = ptmp->next;
        free(ptmp);
        printf("删除了编号为%d的学生信息。\n", num);
    }
    else
    {
        printf("没有找到编号为%d的学生信息。\n", num);
    }
}

void DelAll()//13.删除所有的学生信息
{
    PSTUDENT pstu = g_head.next, ptmp;
    int count = 0;
    if(!Question("确定要删除当前所有的学生信息吗？"))
    {
        return;
    }
    while(pstu)
    {
        ptmp = pstu;
        pstu = pstu->_next;
        free(ptmp);
        ++count;
    }
    printf("共删除了%d位学生信息。\n", count);
    g_head.next = NULL;
}

void SaveToFile()//14.把学生信息保存到文件当中
{
    FILE *pf = fopen(FILENAME, "w+");
    PSTUDENT pstu = &g_head;
    int i = 0, count = ShowStudentCount();
    if(!pf)
    {
        printf("打开待写入的文件失败！\n");
        return;
    }
    if(!Question("确定要将当前学生信息保存到文件中吗？"))
    {
        fclose(pf);
        return;
    }
    fwrite(&count, 1, sizeof(count), pf);//把学生信息的数量先写入到文件头
    while(pstu->_next)
    {
        fwrite(pstu->_next, 1, sizeof(STUDENT), pf);//把每位学生信息写入文件
        ++i;
        pstu = pstu->_next;
    }
    fclose(pf);
    if(i == count)
    {
        printf("成功的写入了%d条学生信息。\n", count);
    }
    else
    {
        printf("应写入%d条学生信息，实际写入%d条学生信息。\n", count, i);
    }
}

void LoadFromFile()//15.从文件中读取学生信息
{
    int i, count = 0, repeat = 0;
    FILE *pf;
    PSTUDENT pstu;
    printf("提示：从文件中读取学生信息会询问是否清空当前学生信息（不清空表示合并所有信息）。\n");
    if((pf = fopen(FILENAME, "rb")) == NULL)
    {
        printf("文件还没有创建，请手动输入学生信息并保存!\n");
        return;
    }
    DelAll();//删除之前的所有学生信息，然后从文件中读取
    fread(&count, 1, sizeof count, pf);//获取学生信息的数量
    for(i = 0; i < count; ++i)
    {
        pstu = (PSTUDENT)malloc(sizeof(STUDENT));
        fread(pstu, 1, sizeof(STUDENT), pf);
        if(!AddStudent(pstu))
        {
            ++repeat;//保持有多少个和当前链表中相重复的学生信息
        }
    }
    fclose(pf);
    printf("文件读取完毕！新增学生信息%d条。\n", count - repeat);
}

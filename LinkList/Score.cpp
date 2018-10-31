#include <stdio.h>
#include <stdlib.h>
#define FILENAME "student.txt"
typedef struct Student
{
    int num;       //ѧ�����
    char name[10]; //ѧ������
    int grade;     //ѧ���꼶
    int chinese;   //���ĳɼ�
    int math;      //��ѧ�ɼ�
    int english;   //Ӣ��ɼ�
    struct Student *next;//��һ���ڵ��ָ��
}STUDENT, *PSTUDENT;
STUDENT g_head;    //ͷ�ڵ�
void ShowMenu();//1.��ʾ��
int GetChoice();//2.��ȡ�û�ѡ��Ĳ˵��ı��
PSTUDENT CreateStudent();//3.����һ���ڵ�,���᷵��һ���´�����ѧ����Ϣ�ڵ��ָ��
int AddStudent(PSTUDENT pstu);//4.��ѧ����Ϣ�ڵ���뵽������
PSTUDENT GetPrevAddr(int num);//5.����ָ�����ѧ���ڵ����һ���ڵ��ָ��
void ShowAll();//6.��ʾ����ѧ����Ϣ
void ShowStudent(int num);//7.��ʾ���Ϊnum��ѧ����Ϣ
int ShowStudentCount();//8.��ʾ��Ϣ����
void ModityStudent(int num);//9.�޸�ѧ����Ϣ��numΪҪ�޸ĵ�ѧ�����
int Question(const char *pstr);//10.��ȡ�û���ѡ��
int GetInputNum();//11.��ȡ�û������ѧ�����
void DelStudent(int num);//12.ɾ�����Ϊnum��ѧ����Ϣ
void DelAll();//13.ɾ�����е�ѧ����Ϣ
void SaveToFile();//14.��ѧ����Ϣ���浽�ļ�����
void LoadFromFile();//15.���ļ��ж�ȡѧ����Ϣ

int main()
{
    int running = 1;
    while(running)
    {
        switch(GetChoice())
        {
            case 0: exit(0);
            case 1: printf("��ѡ���˲˵�1\n");AddStudent(CreateStudent());break;
            case 2: printf("��ѡ���˲˵�2\n");DelStudent(GetInputNum());break;
            case 3: printf("��ѡ���˲˵�3\n");ShowStudent(GetInputNum());break;
            case 4: printf("��ѡ���˲˵�4\n");ModityStudent(GetInputNum());break;
            case 5: printf("��ѡ���˲˵�5\n");DelAll();break;
            case 6: printf("��ѡ���˲˵�6\n");ShowAll();break;
            case 7: printf("��ѡ���˲˵�7\n");ShowStudentCount();break;
            case 8: printf("��ѡ���˲˵�8\n");LoadFromFile();break;
            case 9: printf("��ѡ���˲˵�9\n");SaveToFile();break;
        }
        system("pause");
    }
    return 0;
}

void ShowMenu()//1.��ʾ�˵�
{
    system("cls");
    printf("-------------------------�Ϻ���ѧѧ���ɼ�����ϵͳ-------------------------\n");
    printf("\n\t1.���ѧ����Ϣ    2.ɾ��ĳ��ѧ����Ϣ    3.��ʾĳ��ѧ����Ϣ\n");
    printf("\t4.�޸�ѧ����Ϣ    5.ɾ������ѧ����Ϣ    6.��ʾ����ѧ����Ϣ\n");
    printf("\t7.��ʾ��Ϣ����    8.��ȡ�ļ�ѧ����Ϣ    9.����ѧ����Ϣ���ļ�\n");
    printf("\t0.�˳�ϵͳ\n");
    printf("\n-------------------------------------------------------------------------\n");
}

int GetChoice()//2.��ȡ�û�ѡ��Ĳ˵��ı��
{
    int num;//�����û�ѡ��Ĳ˵����
    ShowMenu();
    printf("��ѡ��˵�(0-9):");
    while( scanf("%d", &num)!=1 || num < 0 || num > 9)
    {
        ShowMenu();
        printf("ѡ��˵�����������ѡ��(0-9):");
        fflush(stdin);//������뻺����
    }
    return num;
}

PSTUDENT CreateStudent()//3.����һ���ڵ�,���᷵��һ���´�����ѧ����Ϣ�ڵ��ָ��
{
    int sex;
    PSTUDENT pstu = (PSTUDENT)malloc(sizeof(STUDENT));//�ڶ��ڴ�����ռ䣬�洢ѧ����Ϣ
    if(!pstu)
    {
        printf("�����ڴ�ռ�ʧ��!\n");
        return NULL;
    }
    printf("������ѧ���ı��(����)��");
    while( scanf("%d", &pstu->_num)!=1 || GetPrevAddr(pstu->_num))
    {
        printf("ѧ��������������Ѿ����ڣ�����������ѧ���ı��(����)��");
        fflush(stdin);
    }
    printf("������ѧ��������(С��10�ַ�)��");
    scanf("%10s", pstu->_name);
    printf("������ѧ�����꼶(1-4)��");
    while( scanf("%d",&pstu->_grade)!=1 || pstu->_grade < 1 || pstu->_grade > 4)
    {
        printf("�꼶�����������������ѧ�����꼶(1-4)��");
        fflush(stdin);
    }
    printf("������ѧ�������ĳɼ�(0-100)��");
    while( scanf("%d", &pstu->_chinese)!=1 || pstu->_chinese < 0 || pstu->_chinese > 100)
    {
        printf("�ɼ������������������ѧ�������ĳɼ�(0-100)��");
        fflush(stdin);
    }
    printf("������ѧ������ѧ�ɼ�(0-100)��");
    while( scanf("%d", &pstu->_math)!=1 || pstu->_math < 0 || pstu->_math > 100)
    {
        printf("�ɼ������������������ѧ������ѧ�ɼ�(0-100)��");
        fflush(stdin);
    }
    printf("������ѧ����Ӣ��ɼ�(0-100)��");
    while( scanf("%d", &pstu->_english)!=1 || pstu->_english < 0 || pstu->_english > 100)
    {
        printf("�ɼ������������������ѧ����Ӣ��ɼ�(0-100)��");
        fflush(stdin);
    }
    printf("��ӳɹ�!\n");
    pstu->_next = NULL;
    return pstu;
}

int AddStudent(PSTUDENT pstu)//4.��ѧ����Ϣ�ڵ���뵽������
{
    PSTUDENT ps = &g_head;
    if(!pstu)
    {
        return 0;
    }
    if(GetPrevAddr(pstu->_num))//�ж�һ�¸�ѧ����Ϣ�ǲ����Ѿ�����
    {
        printf("���Ϊ%d��ѧ����Ϣ�Ѿ����ڣ�\n", pstu->_num);
        free(pstu);//�ͷŸýڵ��ڴ�ռ�
        return 0;
    }
    while(ps->next)//�ҵ���ǰ��������һ���ڵ�
        ps = ps->next;
    ps->next = pstu;//���½ڵ���뵽����Ǹ��ڵ�ĺ���
    pstu->_next = NULL;
    return 1;
}

PSTUDENT GetPrevAddr(int num)//5.����ָ�����ѧ���ڵ����һ���ڵ��ָ��
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

void ShowAll()//6.��ʾ����ѧ����Ϣ
{
    PSTUDENT pstu = &g_head;
    printf("--------------------------------------------------------------------\n");
    printf("  ���      ����      �꼶      ���ĳɼ�      ��ѧ�ɼ�      Ӣ��ɼ�\n");
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

void ShowStudent(int num)//7.��ʾ���Ϊnum��ѧ����Ϣ
{
    PSTUDENT pstu = GetPrevAddr(num);
    if(!pstu)
    {
        printf("û�б��Ϊ%d��ѧ����Ϣ��\n", num);
        fflush(stdin);
        return;
    }
    printf("--------------------------------------------------------------------\n");
    printf("  ���      ����      �꼶      ���ĳɼ�      ��ѧ�ɼ�      Ӣ��ɼ�\n");
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

int ShowStudentCount()//8.��ʾ��Ϣ����
{
    int count = 0;
    PSTUDENT pstu = &g_head;
    while(pstu->_next)
    {
        ++count;
        pstu = pstu->_next;
    }
    printf("\n��ǰ����%dλѧ����Ϣ��\n", count);
    return count;
}

void ModityStudent(int num)//9.�޸�ѧ����Ϣ������ΪҪ�޸ĵ�ѧ���ı��
{
    PSTUDENT pstu = GetPrevAddr(num);//��ȡҪ�޸ĵ�ѧ���ڵ����һ���ڵ�
    int choice;
    if(!pstu)
    {
        printf("û�б��Ϊ%d��ѧ����Ϣ��\n", num);
        return;
    }
    pstu = pstu->_next;//��Ҫ�޸ĵ�ѧԱ�ڵ��ָ���Ϊָ���Լ���
    printf("��ǰѧ��������Ϊ%s,", pstu->_name);
    if(Question("ȷ��Ҫ�޸���"))
    {
        printf("������ѧ��������(С��10�ַ�)��");
        scanf("%10s", pstu->_name);
    }
    printf("��ǰѧ�����꼶Ϊ%d,", pstu->_grade);
    if(Question("ȷ��Ҫ�޸���"))
    {
        printf("������ѧ�����꼶(1-4)��");
        while( scanf("%d", &pstu->_grade)!=1 || pstu->_grade < 1 || pstu->_grade > 4)
        {
            printf("�꼶�����������������ѧ�����꼶��");
            fflush(stdin);
        }
    }
    printf("��ǰѧ�������ĳɼ�Ϊ%d,", pstu->_chinese);
    if(Question("ȷ��Ҫ�޸���"))
    {
        printf("������ѧ�������ĳɼ�(0-100)��");
        while(scanf("%d", &pstu->_chinese)!=1 || pstu->_chinese < 0 || pstu->_chinese > 100)
        {
            printf("�ɼ������������������ѧ�������ĳɼ�(0-100)��");
            fflush(stdin);
        }
    }
    printf("��ǰѧ������ѧ�ɼ�Ϊ%d,", pstu->_math);
    if(Question("ȷ��Ҫ�޸���"))
    {
        printf("������ѧ������ѧ�ɼ�(0-100)��");
        while(scanf("%d", &pstu->_math)!=1 || pstu->_math < 0 || pstu->_math > 100)
        {
            printf("�ɼ������������������ѧ������ѧ�ɼ�(0-100)��");
            fflush(stdin);
        }
    }
    printf("��ǰѧ����Ӣ��ɼ�Ϊ%d,", pstu->_english);
    if(Question("ȷ��Ҫ�޸���"))
    {
        printf("������ѧ����Ӣ��ɼ�(0-100)��");
        while(scanf("%d", &pstu->_english)!=1 || pstu->_english < 0 || pstu->_english > 100)
        {
            printf("�ɼ������������������ѧ����Ӣ��ɼ�(0-100)��");
            fflush(stdin);
        }
    }
    printf("�޸���ϣ�\n");
}

int Question(const char *pstr)//10.��ȡ�û���ѡ��
{
    char answer;
    printf("%s��ѡ��y or n����", pstr);
    while(1 != scanf(" %c", &answer) || (answer != 'y' && answer != 'n'))
    {
        printf("�������%s������ѡ��y or n����", pstr);
        fflush(stdin);//������뻺����,C�⺯��
    }
    if('y' == answer)
        return 1;
    else
        return 0;
}

int GetInputNum()//11.��ȡ�û������ѧ���ı��
{
    int num;
    printf("������ѧ���ı��(����)��");
    while( scanf("%d", &num)!= 1 )
    {
        printf("��������������������ѧ���ı��(����)��");
        fflush(stdin);
    }
    return num;
}

void DelStudent(int num)//12.ɾ�����Ϊnum��ѧ����Ϣ
{
    PSTUDENT pstu, ptmp;
    if(pstu = GetPrevAddr(num))
    {
        if(!Question("ȷ��Ҫɾ����ѧ����Ϣ��"))
        {
            return;
        }
        ptmp = pstu->_next;
        pstu->_next = ptmp->next;
        free(ptmp);
        printf("ɾ���˱��Ϊ%d��ѧ����Ϣ��\n", num);
    }
    else
    {
        printf("û���ҵ����Ϊ%d��ѧ����Ϣ��\n", num);
    }
}

void DelAll()//13.ɾ�����е�ѧ����Ϣ
{
    PSTUDENT pstu = g_head.next, ptmp;
    int count = 0;
    if(!Question("ȷ��Ҫɾ����ǰ���е�ѧ����Ϣ��"))
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
    printf("��ɾ����%dλѧ����Ϣ��\n", count);
    g_head.next = NULL;
}

void SaveToFile()//14.��ѧ����Ϣ���浽�ļ�����
{
    FILE *pf = fopen(FILENAME, "w+");
    PSTUDENT pstu = &g_head;
    int i = 0, count = ShowStudentCount();
    if(!pf)
    {
        printf("�򿪴�д����ļ�ʧ�ܣ�\n");
        return;
    }
    if(!Question("ȷ��Ҫ����ǰѧ����Ϣ���浽�ļ�����"))
    {
        fclose(pf);
        return;
    }
    fwrite(&count, 1, sizeof(count), pf);//��ѧ����Ϣ��������д�뵽�ļ�ͷ
    while(pstu->_next)
    {
        fwrite(pstu->_next, 1, sizeof(STUDENT), pf);//��ÿλѧ����Ϣд���ļ�
        ++i;
        pstu = pstu->_next;
    }
    fclose(pf);
    if(i == count)
    {
        printf("�ɹ���д����%d��ѧ����Ϣ��\n", count);
    }
    else
    {
        printf("Ӧд��%d��ѧ����Ϣ��ʵ��д��%d��ѧ����Ϣ��\n", count, i);
    }
}

void LoadFromFile()//15.���ļ��ж�ȡѧ����Ϣ
{
    int i, count = 0, repeat = 0;
    FILE *pf;
    PSTUDENT pstu;
    printf("��ʾ�����ļ��ж�ȡѧ����Ϣ��ѯ���Ƿ���յ�ǰѧ����Ϣ������ձ�ʾ�ϲ�������Ϣ����\n");
    if((pf = fopen(FILENAME, "rb")) == NULL)
    {
        printf("�ļ���û�д��������ֶ�����ѧ����Ϣ������!\n");
        return;
    }
    DelAll();//ɾ��֮ǰ������ѧ����Ϣ��Ȼ����ļ��ж�ȡ
    fread(&count, 1, sizeof count, pf);//��ȡѧ����Ϣ������
    for(i = 0; i < count; ++i)
    {
        pstu = (PSTUDENT)malloc(sizeof(STUDENT));
        fread(pstu, 1, sizeof(STUDENT), pf);
        if(!AddStudent(pstu))
        {
            ++repeat;//�����ж��ٸ��͵�ǰ���������ظ���ѧ����Ϣ
        }
    }
    fclose(pf);
    printf("�ļ���ȡ��ϣ�����ѧ����Ϣ%d����\n", count - repeat);
}

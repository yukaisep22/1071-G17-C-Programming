#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ID_STR_LEN 10   //��J���r�����
#define ID_NUM_LEN 11   //�ഫ���r�����

#define MAX 50

void InputID(char *str,int *array)  //��J�ɧ�Ĥ@�X�ഫ���Ʀr
{
    int region;

    if(str[0]>='A' && str[0]<='H')  //A(10)~H(17)
        region= (str[0]-'A')+10;
    else if(str[0] >='J' && str[0] <= 'N')  //J(18)~N(22)
        region= (str[0]-'J') + 18;
    else if(str[0] >='P' && str[0] <= 'V')  //P(23)~V(29)
        region= (str[0]-'P') + 23;
    else if(str[0] =='X' || str[0] == 'Y')  //X(30),Y(31)
        region= (str[0]-'X') + 30;
    else if(str[0] =='Z')   //Z(33)
        region= 33;
    else if(str[0] =='I')   //I(34)
        region= 34;
    else if(str[0] =='O')   //O(35)
        region= 35;

    array[0] = region/10;   //�N�ഫ�᪺�r���Q��ư��H10
    array[1] = region%10;   //�N�ഫ�᪺�r���Ӧ�ư��H10���l��

    for(int i=0; i<ID_STR_LEN-1; i++)
    {
        array[i+2] = (str[i+1] - '0');
    }
}

int CheckID(int *array)
{
    int sum= array[0] + array[10];  //�e����array[0]+�ˬd�X

    for(int i=1; i<=ID_NUM_LEN-2; i++)  //�G~�E�X�̧ǭ��W8�B7...2�B1
    {
        sum = sum+array[i]*(ID_STR_LEN-i);
    }
    if (sum%10==0)
        return 1;
    else
        return 0;
}

struct listnode
{
    char Id[MAX];
    char Name[MAX];
    char Gender[MAX];
    char Birthplace[MAX];
    struct listnode*next;
};

int main()
{
    char id[20];
    char name[20];
    char birthplace[20];
    char gender[20];
    int array[ID_NUM_LEN];
    int region=0;

    struct listnode*head=NULL;      //�إ�linked list�̰򥻻ݭn�T�ӫ��СAhead���Vlinked list���Ĥ@��struct�A
    struct listnode*current=NULL;   //current���V�ثe��إߪ�struct�Aprev�h���V�e�@��struct�A�ت��b���V�U�@��struct�A
    struct listnode*prev=NULL;      //���ϥΪ�pointer�A�@�߫��w��NULL�A�i�H�ǥѧP�_�O�_��NULL�P�_��pointer�O�_�Q�ϥΡC

    printf("Enter your ID : ");
    scanf("%s",&id);
    InputID(id,array);

    if(CheckID(array))
    {
        printf("This ID is valid\n");
    }
    else
    {
        printf("This ID is invalid,please re-enter.\n\n");
        return main();
    }

    printf("\nEnter your name : ");
    scanf("%s",&name);
    printf("\nEnter your gender : ");
    scanf("%s",&gender);
    printf("\nEnter your birthplace : ");
    scanf("%s",&birthplace);

    current=(struct listnode*)malloc(sizeof(struct listnode));  /*�C���s��ơA�ݭn�إߤ@�ӷs��struct�ɡA
                                                                  �N��malloc()�n�@���O����C*/
    if(current==NULL)
        exit(EXIT_FAILURE);

    current->next=NULL; //�s��node�@�w�Olinked list�̫�@��node�A�ҥH�Ncurrent->next��null�C

    strncpy(current->Id,id,MAX-1);  //�N��J����ƶ�Jstruct�C
    current->Id[MAX-1]='\0';

    strncpy(current->Name,name,MAX-1);
    current->Name[MAX-1]='\0';

    strncpy(current->Gender,gender,MAX-1);
    current->Gender[MAX-1]='\0';

    strncpy(current->Birthplace,birthplace,MAX-1);
    current->Birthplace[MAX-1]='\0';

    if(head==NULL)  //�Y�O�Ĥ@��node�A�h�N�ثe��node��head�C
        head=current;
    else            //�_�h�N�e�@��node���V�ثe��node�A����linked list���s���C
        prev->next=current;

    prev=current;   //�N�ثe��node���e�@��node�A�H�ƫ��V�U�@��node�C

    current=head;   //�N���ЦA�׫��V�Ĥ@��node�A�C����ܤ@��node��A�N���V�U�@��node�A�������NULL����C
    while(current!=NULL)
    {
        printf("\nID : %s   Name : %s"
               "\nGender : %s   Birthplace : %s\n"
               ,current->Id,current->Name,current->Gender,current->Birthplace);
        current=current->next;
    }
}

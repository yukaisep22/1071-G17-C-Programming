#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ID_STR_LEN 10   //輸入的字串長度
#define ID_NUM_LEN 11   //轉換的字串長度

#define MAX 50

void InputID(char *str,int *array)  //輸入時把第一碼轉換成數字
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

    array[0] = region/10;   //將轉換後的字母十位數除以10
    array[1] = region%10;   //將轉換後的字母個位數除以10取餘數

    for(int i=0; i<ID_STR_LEN-1; i++)
    {
        array[i+2] = (str[i+1] - '0');
    }
}

int CheckID(int *array)
{
    int sum= array[0] + array[10];  //前面的array[0]+檢查碼

    for(int i=1; i<=ID_NUM_LEN-2; i++)  //二~九碼依序乘上8、7...2、1
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

    struct listnode*head=NULL;      //建立linked list最基本需要三個指標，head指向linked list的第一個struct，
    struct listnode*current=NULL;   //current指向目前剛建立的struct，prev則指向前一個struct，目的在指向下一個struct，
    struct listnode*prev=NULL;      //未使用的pointer，一律指定為NULL，可以藉由判斷是否為NULL判斷此pointer是否被使用。

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

    current=(struct listnode*)malloc(sizeof(struct listnode));  /*每當有新資料，需要建立一個新的struct時，
                                                                  就用malloc()要一塊記憶體。*/
    if(current==NULL)
        exit(EXIT_FAILURE);

    current->next=NULL; //新的node一定是linked list最後一個node，所以將current->next接null。

    strncpy(current->Id,id,MAX-1);  //將輸入的資料填入struct。
    current->Id[MAX-1]='\0';

    strncpy(current->Name,name,MAX-1);
    current->Name[MAX-1]='\0';

    strncpy(current->Gender,gender,MAX-1);
    current->Gender[MAX-1]='\0';

    strncpy(current->Birthplace,birthplace,MAX-1);
    current->Birthplace[MAX-1]='\0';

    if(head==NULL)  //若是第一個node，則將目前的node當成head。
        head=current;
    else            //否則將前一個node指向目前的node，完成linked list的連接。
        prev->next=current;

    prev=current;   //將目前的node當成前一個node，以備指向下一個node。

    current=head;   //將指標再度指向第一個node，每當顯示一個node後，就指向下一個node，直到指到NULL為止。
    while(current!=NULL)
    {
        printf("\nID : %s   Name : %s"
               "\nGender : %s   Birthplace : %s\n"
               ,current->Id,current->Name,current->Gender,current->Birthplace);
        current=current->next;
    }
}

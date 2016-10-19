#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>

#define SIZE 10000

struct accountInfo
	{
		int accNo;
		char owner[30];
		float balance;
	};

void menu(struct accountInfo *account, int *numberOfAccounts, char*filename);
void register_account(struct accountInfo *acc, int *numberOfAccounts);
void print_account(struct accountInfo *acc, int *numberOfAccounts);
int search_account(struct accountInfo *account, int *numberOfAccounts);
void change_balance(struct accountInfo *account, int *numberOfAccounts);
void deregister_account(struct accountInfo *account, int *numberOfAccounts);
void sort_account(struct accountInfo *account, int *numberOfAccounts);
void write_file(struct accountInfo *account, int *numberOfAccounts, char *filename);

int main()
{
    struct accountInfo account[SIZE];
    int numberOfAccounts=0;
    char filename[30];
    FILE *fptr;
	printf("Enter File Name: ");
	gets(filename);
	
	fptr=fopen(filename,"r");
	if(fptr==NULL)
    {
        printf("New File Created.\n");
		getch();

    }
	if(fptr!=NULL)
	{
    while(fread (&account[numberOfAccounts],sizeof(account[numberOfAccounts]),1,fptr)==1)
        numberOfAccounts++;
	}
	
    menu(account,&numberOfAccounts,filename);

    return 0;
}

void menu(struct accountInfo *account, int *numberOfAccounts, char*filename)
{
    int opt;
    do{
		system("cls");
	printf("Press 1 To Register Account.\n");
	printf("Press 2 To Print All Accounts.\n");
	printf("Press 3 To Sort Accounts.\n");
	printf("Press 4 To Search For Accounts.\n");
	printf("Press 5 To Change Account Balance\n");
	printf("Press 6 To De-Register An Account.\n");
	printf("Press 7 To Quit.\n");
	if(*numberOfAccounts==10000)
	{
		printf("Memory Full.\a\n");
		printf("Please De-Register Match To Clear Some Memory [PRESS 6].\a\n");
	}
	printf("Enter Your Option: ");
	scanf("%d",&opt);
	system("cls");
	switch(opt)
	{
	case 1:
        register_account(account,numberOfAccounts);
        getch();
		break;
	case 2:
        print_account(account,numberOfAccounts);
        getch();
		break;
	case 3:
        sort_account(account,numberOfAccounts);
        getch();
		break;
	case 4:
        search_account(account,numberOfAccounts);
        getch();
		break;
	case 5:
        change_balance(account,numberOfAccounts);
        getch();
		break;
	case 6:
        deregister_account(account,numberOfAccounts);
        getch();
		break;
	case 7:
	    write_file(account,numberOfAccounts,filename);
	    printf("System Turning Off.");
		break;
	default:
		printf("Wrong Input.\n");
		break;
	}
	}while(opt!=7);

}

void register_account(struct accountInfo *account, int *numberOfAccounts)
{
    char accNo[7],cmp,name[30];
    int accNum,i,flag;
	printf("Account Registration:\n");
	printf("AccountNo.\tName\n");
    fflush(stdin);
	while(1)
	{
	    flag=0;
	    printf("Details: ");
	    if(*numberOfAccounts<10000)
        {
            fgets (accNo, sizeof (accNo), stdin);
            cmp=strcmp(accNo,"\n");
            if(cmp==0)
            {
                printf("Press Enter To Go Back To Main Menu.\n");
                break;
            }
            else
            {
                accNum = atoi (accNo);
            }
             gets(name);

             for(i=0;i<*numberOfAccounts;i++)
            {
                if(account[i].accNo==accNum)
                {
                    printf("Account Number Already Exists.\n");
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
               account[*numberOfAccounts].accNo=accNum;
               strcpy(account[*numberOfAccounts].owner,name);
               account[*numberOfAccounts].balance=0.0;
                *numberOfAccounts=*numberOfAccounts+1;
                printf("Registration Successful.\n");
            }

        }

        else
        {

            printf("Error: Memory Full.\a");
            break;
        }

	}
}

void print_account(struct accountInfo *account, int *numberOfAccounts)
{
    int i;
	for(i=0;i<*numberOfAccounts;i++)
	{
		printf("Account No.:%d\tOwner:%s\tBalance:%f\n",account[i].accNo,account[i].owner,account[i].balance);
	}
}

int search_account(struct accountInfo *account, int *numberOfAccounts)
{
	int opt,i,accNo,searchFlag;
	float min_balance,max_balance;
	char name[30];
	searchFlag=0;
	printf("\nChoose To Search The Accounts By Account Number, Owner Name Or Balance\n\n");
	printf("Press 1 To Search By Account Number.\n");
	printf("Press 2 To Search By Owner Name.\n");
    printf("Press 3 To Search By Balance.\n\n");

	printf("Enter Your Option: ");
	scanf("%d",&opt);
	switch(opt)
	{
	case 1:
		printf("Enter Account Number: ");
		scanf("%d",&accNo);
		printf("\nSearch Result.\n\n");
		for(i=0;i<*numberOfAccounts;i++)
		{
			if(account[i].accNo==accNo)
			{
				printf("# Account No.:%d\tOwner:%s\tBalance:%f\n",account[i].accNo,account[i].owner,account[i].balance);
				searchFlag=1;
			}
		}
		if(searchFlag==0)
		{
			printf("Not Found.\n");
		}
		break;
	case 2:

		printf("Enter Owner Name: ");
		scanf("%s",name);
        printf("\nSearch Result.\n\n");
		for(i=0;i<*numberOfAccounts;i++)
		{
		   if(strstr(account[i].owner,name))
		   {
			   printf("#. Account No.:%d\tOwner:%s\tBalance:%f\n",account[i].accNo,account[i].owner,account[i].balance);

			   searchFlag=1;
		   }
		}
		if(searchFlag==0)
		{
			printf("Not Found.\n");
		}
		break;

    case 3:
        printf("Enter Min Balance: ");
		scanf("%f",&min_balance);
		printf("Enter Max Balance: ");
		scanf("%f",&max_balance);
        printf("\nSearch Result.\n\n");
		for(i=0;i<*numberOfAccounts;i++)
		{
		   if(account[i].balance>=min_balance && account[i].balance<=max_balance )
		   {
			   printf("# Account No.:%d\tOwner:%s\tBalance:%f\n",account[i].accNo,account[i].owner,account[i].balance);

			   searchFlag=1;
		   }
		}
		if(searchFlag==0)
		{
			printf("Not Found.\n");
		}
		break;

        default:
		printf("Wrong Input.\n");
		break;

	}
    return searchFlag;
}

void change_balance(struct accountInfo *account, int *numberOfAccounts)
{
	int opt,i,accNo,searchFlag=0;
	float amount;
	printf("Enter 1 To Search Account Or 2 To Change Balance Directly.\n");
	printf("Enter: ");
	scanf("%d",&opt);
	switch(opt)
	{
    case 1:
        searchFlag=search_account(account,numberOfAccounts);

    case 2:
        if (searchFlag==1||opt==2)
        {
            printf("\nEnter Account Number For Which You Want To Change Balance For: ");
            scanf("%d",&accNo);
            searchFlag=0;
            for(i=0;i<*numberOfAccounts;i++)
            {
                if(account[i].accNo==accNo)
                {
                    searchFlag=1;
                    printf("Press 1 To Withdraw.\n");
                    printf("Press 2 To Deposit.\n");
                    printf("Enter Option: ");
                    scanf("%d",&opt);
                    if(opt==1)
                    {
                        printf("Enter Amount: ");
                        scanf("%f",&amount);
                        if(amount>account[i].balance)
                        {
                            printf("Insufficient Balance.");
                        }
                        else
                        {
                            account[i].balance-=amount;
                            printf("Withdrawal Was Successful");
                        }
                    }
                    if(opt==2)
                    {
                        printf("Enter Amount: ");
                        scanf("%f",&amount);
                        account[i].balance+=amount;
                        printf("Deposit Was Successful");
                    }

                }
            }
            if(searchFlag==0)
            {
                printf("Not Found.\n");
            }
        }
        break;

        default:
        printf("Wrong Input.\n");
        break;
	}


}

void deregister_account(struct accountInfo *account, int *numberOfAccounts)
{
	int accNo,i,index,searchFlag=0,balanceFlag=0,opt;

	printf("Enter 1 To Search Account Or 2 To De-register Account Directly.\n");
	printf("Enter: ");
	scanf("%d",&opt);
	switch(opt)
	{
    case 1:
        searchFlag=search_account(account,numberOfAccounts);
    case 2:
        if(searchFlag==1||opt==2)
        {
            printf("\nDe-register Account.\n\n");
            printf("Enter Account Number: ");
            scanf("%d",&accNo);
            searchFlag=0;
            for(i=0;i<*numberOfAccounts;i++)
            {
                if(account[i].accNo==accNo)
                {
                    searchFlag=1;
                    index=i;
                    if(account[index].balance==0)
                    {
                        balanceFlag=1;
                    }
                }

            }

            if(searchFlag==1&&balanceFlag==1)
            {
                 if(index<*numberOfAccounts-1)
                {
                    for(i=index;i<*numberOfAccounts-1;i++)
                    {
                        account[i]=account[i+1];
                    }
                    *numberOfAccounts=*numberOfAccounts-1;
                    printf("De-registration Successful.\n");

                }
                else
                {
                    if(index==*numberOfAccounts-1)
                    {
                        *numberOfAccounts=*numberOfAccounts-1;
                        printf("De-registration Successful.\n");
                    }
                }
            }
            if(searchFlag==0)
            {
                printf("Not Found.\n");
            }

            if(balanceFlag==0&&searchFlag==1)
            {
                printf("Error: Account is not empty.\n");
            }

        }
        break;

        default:
        printf("Wrong Input.\n");
        break;
	}
}

void sort_account(struct accountInfo *account, int *numberOfAccounts)
{
    int i=0,j=0,k,opt;
    char *string1,*string2;
    struct accountInfo temp;

    printf("Choose To Sort The Accounts By Account Number, Owner Name Or Balance.\n\n");
	printf("Press 1 To Sort By Account Number.\n");
	printf("Press 2 To Sort By Owner Last Name.\n");
    printf("Press 3 To Sort By Balance.\n\n");

    printf("Enter Option: ");
    scanf("%d",&opt);

    switch(opt)
    {
    case 1:

		for(i=0;i<*numberOfAccounts-1;i++)
		{
			for(j=i+1;j<*numberOfAccounts;j++)
			{
				if(account[i].accNo>account[j].accNo)
				{
					temp=account[i];
					account[i]=account[j];
					account[j]=temp;

				}
			}
		}
        break;


    case 2:
        for(i=0;i<*numberOfAccounts-1;i++)
        {
            for(j=i+1;j<*numberOfAccounts;j++)
            {
                k=1;
                string1=strrchr (account[i].owner,' ');
                string2=strrchr (account[j].owner,' ');

                while(string1[k]==string2[k]&&k<30)
                {
                    k++;
                }
                if(string1[k]>string2[k])
                {
                    temp=account[i];
                    account[i]=account[j];
                    account[j]=temp;

                }
            }
        }

        break;


    case 3:

        for(i=0;i<*numberOfAccounts-1;i++)
		{
			for(j=i+1;j<*numberOfAccounts;j++)
			{
				if(account[i].balance<account[j].balance)
				{
					temp=account[i];
					account[i]=account[j];
					account[j]=temp;

				}
			}
		}

        break;


        default:
        printf("Wrong Input.\n");

    }
    printf("Sorted Successfully.\n");
}

void write_file(struct accountInfo *account, int *numberOfAccounts, char *filename)
{
    int i;
	FILE *fptr;
	fptr=fopen(filename,"w");
	if(fptr==NULL)
	{
		printf("Error!");
		exit(1);
	}
	printf("Writing Into File....\n");
	for(i=0;i<*numberOfAccounts;i++)
	{
		fwrite(&account[i],sizeof(account[i]),1,fptr);
	}
	fclose(fptr);
}


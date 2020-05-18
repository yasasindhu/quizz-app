
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<string.h>
void menu();
void gametype();
void generalknowledge();
void rules();
void check_score();
void typeofquizz();
void leaderboard();
void levels(char* filename,int start,int end);
struct Player{
char name[50];
int points;
int lifes;
}player[100];
struct general {
    char ans;
char question[150]; //string to store questions
char option[150];//string to store options
char exp[150];//string store explanation
}general;

//char username[20];//to store username
int rec=0;
char username[200];
int main()
{
    system("color 3");
  int i,found=0;
    printf("WELCOME TO QUIZZ APP\n");
   int howMany;
    printf("USERNAME: ");
    gets(username);
    FILE *fp1;
    fp1=fopen("leaderboard.txt","r");
      for(int i=0; i<10000 && !feof(fp1); i++)
    {
        fscanf(fp1, "%s %d", player[i].name,&player[i].points);
        if(strcmp(player[i].name,username)==0)
            {
                rec=i;//taking index value to add present score with previous score
                found++;
            }
    howMany++;
    }
    if(found==0)
    {
    strcpy(player[rec].name,username);
    player[rec].points=0;
    player[rec].lifes=0;
    }
    printf("\n\n\n");
fclose(fp1);
     menu();
}

void menu(){
    system("cls");
int choice;//for user choice
    printf("1.view different types of qizz and select what u want to play\n");
    printf("2.game rules and how to play\n");
    printf("3.exit game\n");
   // printf("4.view leaderboard\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:gametype();
               break;
        case 2:rules();
               break;
        case 3:exit(0);
               break;
        /*case 4:leaderboard();
               break;*/
        default:printf("INVALID CHOICE\n");
                break;
    }
}

void gametype()
{
    int option;//to select option from below
    system("cls");
    printf("TYPES OF QUIZZ ARE:\n");
    printf("1.SPORTS\n");
    printf("2.ENTERTAINMENT\n");
    printf("3.Go to previous page\n");
    printf("enter your choice:");
    scanf("%d",&option);
    switch(option)
    {
        case 1:typeofquizz("sports.txt");
               break;
        case 2:typeofquizz("entertainment.txt");
               break;
        case 3:menu();
               break;
        default:printf("INVALID CHOICE\n");
                break;

    }
}

void typeofquizz(char* filename) {
int level;//to select any level
printf("enter your choice\n");
printf("1.EASY LEVEL\n");
printf("2.MEDIUM LEVEL\n");
printf("3.HARD LEVEL\n");
scanf("%d",&level);
switch(level)
{
    case 1:levels(filename,' ' ,'@');
           break;
     case 2:levels(filename,'@','#');
            break;
    case 3:levels(filename,'#',EOF);
           break;
    default :printf("invalid choice\n");
            break;
}
}

void levels(char* filename,int start,int end)
{
       system("cls");
    FILE * fp;
fp = fopen(filename, "r");
char c;//character comparision
char ans;//to store answer
int count=0;//for counting no.of chars purpose
do{
     int c = fgetc(fp);
   if (c ==start|| c==EOF)
   {
    break;
   }
} while ( c!= EOF && c!=start);
if(start=='@' || start=='#')
    ans=fgetc(fp);
do{
system("cls");
ans=fgetc(fp);
//printf("%c is req1\n",ans);
if(ans!=end){
int j=0;//conting no.of chars in a question string
	do
{
    int c = fgetc(fp);
   if (c == EOF || c == '\n' )
   {
    break;
   }
   else
   {
   general.question[j]=c;
    j++;
   }
} while ( c!= EOF && c!='\n');
for(count=0;count<j;count++)
    printf("%c",general.question[count]);
printf("\n");
        int k=0;//counting no of chars in options
	do
{
      int c = fgetc(fp);
   if ( c == EOF || c == '\n' )
   {
    break;
   }
   else
   {
   general.option[k]=c;
    k++;
   }
} while ( c!= EOF && c!='\n');
for(count=0;count<k;count++)
    printf("%c",general.option[count]);
printf("\n");
char ch;//to get user input
fflush(stdin);
ch=getchar();
printf("%c is ur choice %c is ans\n",ch,ans);
if(ch==ans){
    printf("CORRECT ANSWER\n");
    player[rec].points=player[rec].points+10;
}
else
    printf("WRONG ANSWER\n");
    printf("EXPLANATION:\n");
        int l=0;//counting no.of chars in explanation string
	do
{
      int c = fgetc(fp);
   if ( c == EOF || c == '\n' )
   {
    break;
   }
   else
   {
    general.exp[l]=c;
l++;
   }
} while ( c!= EOF && c!='\n');
for(count=0;count<l;count++)
    printf("%c",general.exp[count]);
printf("\n");
	getch();
}
else
    break;
}while (!feof(fp));
player[rec].lifes=player[rec].points/10;
fclose(fp);
check_score();
}

void rules()
{
    system("cls");
    char ch;
    FILE *fp;
    fp=fopen("rulesofquizz.txt","r");
    while((ch=getc(fp))!=EOF)
    {
        printf("%c",ch);
    }
    fclose(fp);
    getch();
    menu();
}

void check_score()
{
    system("cls");
    FILE *fp;
    fp=fopen("leaderboard.txt","a");
    fprintf(fp,"%s %d %d\n",player[rec].name,player[rec].points,player[rec].lifes);
     printf("hey %s your score is :%d\n",player[rec].name,player[rec].points);
    fclose(fp);
    int score=player[rec].points;
      FILE *fp1;
     int howMany=0;
      fp1=fopen("leaderboard.txt","r");
      for(int i=0; i<10000 && !feof(fp1); i++)
    {
        fscanf(fp1, "%s %d %d", player[i].name, &player[i].points,&player[i].lifes);
       //if(player[i].points>0 && player[i].lifes>0)
    //    printf("name: %s, points: %d ,lifes: %d\n\n", player[i].name, player[i].points,player[i].lifes);
    howMany++;
    }
    printf("Do you want to see Leaderboard\n");
    printf("If yes enter y else enter n\n");
    fflush(stdin);
    char ch=getch();
    if(ch=='y'){
    int i,j;
     struct Player temp;
    char tempName[20];
    printf("\n\n\nLeaderboard\n\n\n");

    //SORT WITH BUBBLESORT
    for(i=0; i<howMany; i++)
    {
        for(j=0; j<howMany-1; j++)
        {
            if(player[j].points<player[j+1].points)
            {
                temp = player[j];
                player[j] = player[j+1];
                player[j+1] = temp;
            }
        }
    }
    fclose(fp1);
    FILE *fp2 = fopen("leaderboard.txt", "w");
    void rewind ( FILE * fp2 );
    //WRITE SORTED SCORES TO TEXTFILE
     j=0;
   for(i=0;i<howMany; i++)
    {
       if(player[i].name[j]>='a' && player[i].name[j]<='z')
{
                    if( strcmp(player[i].name,username)!=0 && player[i].points>0 && player[i].lifes>0)
    {printf("%s %d %d\n", player[i].name, player[i].points,player[i].lifes);
        fprintf(fp2, "%s %d %d\n", player[i].name, player[i].points,player[i].lifes);
    }
 else if(strcmp(player[i].name,username)==0 && score==player[i].points)
    {
        printf("%s %d %d\n", player[i].name, player[i].points,player[i].lifes);
        fprintf(fp2, "%s %d %d\n", player[i].name, player[i].points,player[i].lifes);
    }
    else if(strcmp(player[i].name,username)!=0 && player[i].points==0)
    {printf("%s %d %d\n", player[i].name, player[i].points,player[i].lifes);
        fprintf(fp2, "%s %d %d\n", player[i].name, player[i].points,player[i].lifes);
    }
    }
    }
    fclose(fp2);
    }
    else
        exit(0);
}
/*void leaderboard()
{

    FILE *fp1;
      int howMany=0;
      fp1=fopen("leaderboard.txt","r");
       system("pause");
      for(int i=0; i<10000 && !feof(fp1); i++)
    {
        fscanf(fp1, "%s %d %d", player[i].name, &player[i].points,&player[i].lifes);
       //player[i].points>0 && player[i].lifes>0)
       if(!feof(fp1))
        printf("name: %s, points: %d ,lifes: %d\n\n", player[i].name, player[i].points,player[i].lifes);
    howMany++;
    }

    system("pause");
    system("cls");
menu();
}
*/

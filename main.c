#include <stdio.h>
#include <stdlib.h>

struct board
{
    int ref;
    int vis;
}mat[20][7];

int arr[52],point[7]={0,1,2,3,4,5,6},found[4]={0};

int validate(int a, int b)
        { if(a%13==((b%13)-1))
             if(((a<=26)&&(b>26))||((a>26)&&(b<=26)))
			      return 1;
			      printf("\nNot compatible");
			return 0;
	}

void Sinsert(int rows,int cols,int cold)
	{
		int l=0,temp;
		if(mat[rows][cols].vis==1)
		l=validate(mat[rows][cols].ref,mat[point[cold]][cold].ref);
		if(l==1)
		{
		    int j=0;
			for(int i=rows;i!=-1;i++)
			{
				for(;j<20;j++)
				{
					if(mat[j][cold].vis==(-1))
					{
						temp=mat[rows][cols].ref;
						mat[rows][cols].ref=mat[j][cold].ref;
						mat[j][cold].ref=temp;
						mat[rows][cols].vis=-1;
						mat[j][cold].vis=1;
						point[cols]--;
						break;
					}
				}
			}
			point[cold]=j;
			//show();
		}
		else
		{
			printf("\nThe given card cannot be inserted!!!!");
		}

	}

int Ginsert(int Ref, int col)
		{ int a;
		   a=point[col];
		   //printf("%d",validate(Ref,mat[a][col].ref));
		   if(validate(Ref,mat[a][col].ref)==1)
			{ mat[a+1][col].ref=Ref;
			  mat[a+1][col].vis=1;
			   point[col]++;
			   return 1;
			}
	        printf("\nCannot Insert thru Ginsert\n");
			return 0;
		 }

/*void shift(int row,int col, int col2 )
		{
          int d;
		  if(row==point[col])
		    d=Ginsert(mat[row][col].ref,col2);
		  else
		    Sinsert(row,col,col2);
        }*/



void board()
{
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<7;j++)
            mat[i][j].vis=-1;
    }
    int r=0;
    for(int i=0;i<7;i++)
    {
        for(int j=i;j<7;j++,r++)
        {
            mat[i][j].ref=arr[r];
            if(i==j)
                mat[i][j].vis=1;
            else
                mat[i][j].vis=0;
        }
    }
}

void show()
{
    printf("1.S1 2.S2 3.S3 4.S4 5.S5 6.S6 7.S7 8.S8 9.S9 10.S1 11.S11 12.S12 13.S13 \n14.C1 15.C2 16.C3 17.C4 18.C5 19.C6 20.C7 21.C8 22.C9 23.C10 24.C11 25.C12 26.C13\n27.D1 28.D2 29.D3 30.D4 31.D5 32.D6 33.D7 34.D8 35.D9 36.D10 37.D11 38.D12 39.D13\n40.H1 41.H2 42.H3 43.H4 44.H5 45.H6 46.H7 47.H8 49.H10 50.H11 51.H12 52.H13\n");
    for(int i=0;i<19;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(mat[i][j].vis==0 && mat[i+1][j].vis==-1)
                mat[i][j].vis=1;
        }
    }


    for(int i=0;i<20;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(mat[i][j].vis==0)
                printf("0\t");
            if(mat[i][j].vis==1)
                printf("%d\t",mat[i][j].ref);
            if(mat[i][j].vis==-1)
                printf(" \t");
        }
        printf("\n");
    }
    printf("\nfoundation list\nspades\tclubs\tdiamonds\thearts\n%d\t%d\t%d\t\t%d",found[0],found[1],found[2],found[3]);
}

void foundation(int r,int col)
{
    for(int i=1;i<5;i++)
    {
        if((r>=13*(i-1))&&(r<=13*i)&&(r%13==((found[i-1])+1)%13))
        {
            found[i-1]==r;
            point[col]--;
        }
    }
    if(found[0]+found[1]+found[2]+found[3]==130)
    {
        printf("\n ******congrats you won*******\n");
        exit(0);
    }
}

int toptofnd(int r)
{
    int b=0;
    for(int i=1;i<5;i++)
    {
        if((r>13*(i-1))&&(r<=13*i)&&(r%13==((found[i-1])+1)%13))
        {
            found[i-1]==r;
            b=1;
        }
    }
    if(found[0]+found[1]+found[2]+found[3]==130)
    {
        printf("\n ******congrats you won*******\n");
        exit(0);
    }
    return b;
}

int main()
{
    for(int i=0;i<52;i++)
    {
        arr[i]=i+1;
    }
    for (int i = 0; i < 52; i++) {    // shuffle array
    int temp = arr[i];
    int randomIndex = rand() % 52;

    arr[i]           = arr[randomIndex];
    arr[randomIndex] = temp;
   }
    board();
    show();

    int choice,c1,c2,r1,i=28,b,j;
    //arr[28]=27;

    do
    {
     printf("\n 1.shift cards on board \n 2.use top list cards. \n 3.enter a card in foundation list.\n Enter a choice");
     scanf("%d",&choice);

     switch(choice)
     {
     case 1:
        printf("\n move from which row and column \n");
        scanf("%d%d",&r1,&c1);
        printf("\n move to which column\n");
        scanf("%d",&c2);
        Sinsert(r1,c1,c2);
        show();
        break;
     case 2:
        if(i==52)
            i=28;
        for(;arr[i]<0;i++);
        printf("\n Top list card is %d..... Do you want to insert it(0/1)??\n enter -1 for direct top to foundation \n",arr[i]);
        scanf("%d",&b);
        if(b==1)
            {
                printf("\n where to move??\n");
                scanf("%d",&c2);
                j=Ginsert(arr[i],c2);
                if(j==1)
                arr[i]=-1;
            }
        if(b==-1)
        {
            j=toptofnd(arr[i]);
            if(j==1)
            arr[i]=-1;
        }
        i++;
        show();
        break;

     case 3:
        printf("\n enter column to insert card in foundation list.\n");
        scanf("%d",&c1);
        foundation(mat[point[c1]][c1].ref,c1);
        mat[point[c1]][c1].vis=-1;
        show();
        break;

     }
    }while(choice!=0);

    return 0;
}

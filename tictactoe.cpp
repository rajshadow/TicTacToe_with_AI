#include<iostream>
#include<conio.h>

using namespace std;
int g[4][4],player,turn,x,y,full;
//player indicated player 1 or player 2
//turn indicates which player goes next
//x and y stand for grid coordinates
//full==1 indicates the grid is full
char name[3][20];

void initialise()
{
	int i;
	for(i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			g[i][j]=0;

	full=0;
	player=0;
	turn=0;
}

int check()
{
	int ctr=0,i,j;

	if(full==1)
		return 2;

	for(i=x,j=1;j<=3;j++)
		if(g[x][y]==g[x][j])
			ctr++;
	if(ctr==3)
		return 1;

	ctr=0;
	for(i=1,j=y;i<=3;i++)
		if(g[x][y]==g[i][y])
			ctr++;
	if(ctr==3)
		return 1;

	ctr=0;
	if(x==y)
		for(i=1;i<=3;i++)
			if(g[x][y]==g[i][i])
				ctr++;
	if(ctr==3)
		return 1;

	ctr=0;
	if(x+y==4)
		for(i=1;i<=3;i++)
			if(g[x][y]==g[i][4-i])
				ctr++;
	if(ctr==3)
		return 1;

	return 0;
}

void grid()
{
	int i,j,k;
	system("cls");
	full=1;

	cout<<"\n";
	for(i=1;i<=3;i++)
	{
		for(k=1;k<=2;k++)
		{
			for(j=1;j<=2;j++)
				cout<<"           +";
			cout<<"\n";
		}

		for(j=1;j<=3;j++)
		{
			if(g[i][j]==0)
			{
				cout<<"           ";       //11spaces
				full=0;
			}
			if(g[i][j]==1)
				cout<<"     X     ";
			if(g[i][j]==2)
				cout<<"     O     ";
			if(j!=3)
				cout<<"+";
		}

		cout<<"\n";
		for(k=1;k<=2;k++)
		{
			for(j=1;j<=2;j++)
				cout<<"           +";
			cout<<"\n";
		}
		if(i!=3)
			for(j=1;j<=3;j++)
				cout<<" + + + + + +";
		cout<<"\n";
	}
}

void analyse()
{
	
	int win=0,i,j;
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
			if(g[i][j]==0)
			{
				g[i][j]=2;
				x=i;y=j;
				win=check();
				if(win==1||win==2)
					return;
				else
					g[i][j]=0;
			}
	}
	for(i=1;i<=3;i++)
		for(j=1;j<=3;j++)
			if(g[i][j]==0)
			{
				g[i][j]=1;
				x=i;y=j;
				win=check();
				if(win==1)
				{
					g[i][j]=2;
					x=i;y=j;
					return;
				}
				else
					g[i][j]=0;
			}

	if(g[2][1]==0)
	{
		g[2][1]=2;
		x=2;y=1;
		return;
	}
	if(g[2][1]==2 && g[1][3]==0)
	{
		g[1][3]=2;
		x=1;y=3;
		return;
	}
	if(g[2][1]==2 && g[1][3]==2 && g[1][1]==0)
	{
		g[1][1]=2;
		x=1;y=1;
		return;
	}
	
	if((g[1][1]==1 || g[2][1]==1) && g[3][3]==0)
	{
		g[3][3]=2;
		x=y=3;
		return;
	}
	if((g[1][3]==1 || g[2][3]==1) && g[3][1]==0)
	{
		g[3][1]=2;
		x=3;y=1;
		return;
	}
	if((g[3][1]==1 || g[2][1]==1) && g[1][3]==0)
	{
		g[1][3]=2;
		x=1;y=3;
		return;
	}
	if((g[3][3]==1 || g[3][2]==1) && g[1][1]==0)
	{
		g[1][1]=2;
		x=y=1;
		return;
	}

	if(g[2][2]==0)
	{
		g[2][2]=2;
		x=y=2;
		return;
	}

	/*for(i=1;i<=3;i++)
		for(j=1;j<=3;j++)
			if((i+j==4 || i==j) && g[i][j]==0)
			{
				g[i][j]=2;
				x=i;y=j;
				return;
			}
    */
	for(i=1;i<=3;i++)
		for(j=1;j<=3;j++)
			if(g[i][j]==0)
			{
				g[i][j]=2;
				x=i;y=j;
				return;
			}

	return;
}

void findPos(int num,int player)
{
	int ctr=1,i,j;
	for(i=3;i>=1;i--)
	{
		for(j=1;j<=3;j++)
		{
			if(num==ctr)
			{
				if(g[i][j]!=0)
				{
					turn=-1;
					return;
				}
				g[i][j]=player;
				x=i;
				y=j;	
				return;
            }
			ctr++;
		}
						
	}
}

int comp_play()
{
	int num,win=0,i,j,repeat;
	system("cls");
	cout<<"1)Do you want to start."
		<<"\n2)Let computer start.\n";
	cin>>turn;
	grid();

	while(1)
	{
		if(win==0)
		{
			if(turn==1)
			{
				cout<<"\n"<<name[1]<<" 's turn";
				cin>>num;
				findPos(num,1);				
			}
			else
				if(turn==2)
					analyse();
			

			turn=(turn==1)?2:1;
		}
		
		if(win==1||win==2)
			return win;

		grid();
		win=check();
		
	}

}

int double_play()
{
	int num,win=0;
	grid();
	while(1)
	{
		
		if(win==0)
		{
			player=(player==1)?2:1;

			cout<<"\n"<<name[player]<<"'s turn.";
			cin>>num;
			findPos(num,player);
		}

		if(win==1||win==2)
			return win;

		grid();
		win=check();
	}
}

void main()
{
	int win;
	char opt,opt1='y';

	while(1)
	{
		initialise();
		system("cls");
		cout<<"1)single player Vs Computer.\n"
			<<"2)Multiplayer.\n";
		opt=getch();
		system("cls");
		switch(opt)
		{
			case '2':
			{
				cout<<"Enter names of the players.:\n";
				cin>>name[1]>>name[2];
				win=double_play();
				cout<<"\nThe game is over...press any key to continue...";
				getch();
				system("cls");

				if(win==1)
					cout<<name[player]<<" pawned "<<name[3-player];
				if(win==2)
					cout<<"draw...";	
				getch();
				break;
			}
			case '1':
			{
				cout<<"Enter the name of the player:\n";
				cin>>name[1];
				win=comp_play();
				cout<<"\nThe game is over...press any key to continue...";
				getch();
				system("cls");
				if(win==1&&turn==1)
					cout<<name[1]<<" lost a well fought battle.";
				else
					if(win==2)
						cout<<"draw...";
					else
						if(win==1&&turn==2)
							cout<<"Congratulations...you managed to beat the computer!!!..."<<name[1]<<" is the champion of tictactoe!!";
				getch();
				break;

			}
		}
		system("cls");
		cout<<"Continue??... (y/n)";
				opt1=getch();
		if(opt1=='n')
			return;
	}
}







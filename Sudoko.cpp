/*
Zakriya Paracha
Wajeeha Tahir
Number of possible solutions are 6,670,903,752,021,072,936,960.
Day 6
*/

//colors:
//0 = Black, 8 = Gray, 1 = Blue, 9 = Light Blue, 2 = Green, a = Light Green
//3 = Aqua b = Light Aqua, 4 = Red c = Light Red, 5 = Purple d = Light Purple
//6 = Yellow e = Light Yellow, 7 = White f = Bright White

#include <windows.h>
#include <time.h>
#include<iostream>
#include<string>
#include <fstream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

using namespace std;

char board[9][9][2];
char problem[9][9][2];
int random = 5; //keep it below 5 to prevent stucking
int col_board = 7; //0-7 
int col_fix = 3; //0-7 
int col_pos = 1;  //0-7
int col_npos = 4; //0-7'
int col_win = 5; //0-7
int col_timer = 7; //0-7
int delay;
int step = 0;
time_t start_time;
time_t current_time;

/*
//"Save_board()"saves the time, no of moves and the board in a file
void save_board()
{
	fstream board;
	board.open("board.txt", ios::out);
	time_t current_time;
	current_time = time(NULL);
	board << step << endl;
	board << current_time - start_time - 4 << endl;

	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (problem[x][y][0] == ' ')
			{
				board << '0' << " ";
			}
			else
			{
				if (problem[x][y][1] == 1)
				{
					board << char(problem[x][y][0] + 10) << " ";
				}
				if (problem[x][y][1] == 2)
				{
					board << char(problem[x][y][0] + 20) << " ";
				}
				if (problem[x][y][1] == 3)
				{
					board << char(problem[x][y][0] + 30) << " ";
				}
			}

		}
		board << "\n";
	}
	board.close();
	cout << "your game is saved\n";
	cout << "-----------------------------------------------";
}

//"load_board()"loads the time, no of moves and the board in a file
void load_board()
{


	fstream board;
	board.open("board.txt", ios::in);
	board >> step;
	board >> delay;
	step--;
	current_time = time(NULL);
	start_time = current_time - delay;

	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			char temp;
			board >> temp;
			if (temp == '0')
			{
				problem[x][y][0] = ' ';
			}
			if (temp > 58 && temp < 68)
			{
				problem[x][y][0] = char(temp - 10);
				problem[x][y][1] = 1;
			}
			if (temp > 68 && temp < 78)
			{
				problem[x][y][0] = char(temp - 20);
				problem[x][y][1] = 2;
			}
			if (temp > 78 && temp < 88)
			{
				problem[x][y][0] = char(temp - 30);
				problem[x][y][1] = 3;
			}
		}
	}

	board.close();
}
*/

//"color_change()" change the colour of the console
void color_change(int col)
{
	HANDLE  hConsole; //make an object of Handle
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, col); //change the console colour
}

//"timer()" print out the time elapsed after the start of the game
void timer(int delay) {

	int sec = 0, min = 0, hour = 0;  //initialinze time

	time_t current_time;
	current_time = time(NULL);
	int time_ellapsed = current_time - start_time; //calculate time passed using the currunt time and the time in start of the game 
	sec = time_ellapsed - delay;

	//use two while loops to give time in hh:mm:ss 
	while (sec > 60)
	{
		min++;
		sec -= 60;
	}
	while (min > 60)
	{
		hour++;
		min -= 60;
	}
	//print out the time
	color_change(col_timer);
	cout << "Time elapsed: " << hour << "h " << min << "m " << sec << "s " << endl;
	color_change(col_board);
}

//"possible()" check if number "n", is possible in vertix (x,y) in the board "table"  
bool possible(char table[9][9][2], int x, int y, int n)
{
	int xa = (floor(x / 3)) * 3; //range 0,3,6
	int ya = (floor(y / 3)) * 3; //range 0,3,6
	for (int k = 0; k < 9; k++)
	{
		if (table[x][k][0] == n + 48)return false;   //if there is "n" in the col
		else if (table[k][y][0] == n + 48)return false; //if there is "n" in the row
	}
	for (int i = 0; i < 3; i++)   //ittrate from the 3x3 array to check for reaccurence
	{
		for (int j = 0; j < 3; j++)
		{
			if (table[xa + i][ya + j][0] == n + 48)return false; //if there is "n" in the 3x3 array. 
		}
	}
	return true; //if the parameter "n" is not present in the row, col or 3x3 array of the vertix(x,y)then return true .
}
//"solve()" is a recursive func, that take an empty or semi-filled board and use backtracking to solve it.
//we will solve the "board" array to keep as our solution.
bool solve(void)
{
	if (board[8][8][0] != ' ')return true; //if last vertex of board is filled, break from the recurrsive loop (Base Case)

	for (int x = 0; x < 9; x++) //move in the row 
	{
		for (int y = 0; y < 9; y++) //move in the colomn
		{
			if (board[x][y][0] == ' ') //if space is empty then add a number
			{
				for (int n = 1; n < 10; n++) //loop through 1-9, if any number is possible add it and solve the board
				{
					if (possible(board, x, y, n))
					{
						board[x][y][0] = n + 48;
						if (solve())return true; //if the solve is compleate then, break the recursive loop
						board[x][y][0] = ' '; //if the board is not solved in the next vertex, empty this vertex and repeat (Backtraking)
					}
				}
				return false; //if there is no possible solution, return to the last vertex
			}

		}
	}
}


//"set_board()", clear both arrays "board" & "problem"
//"set_board()", clear enter random possible numbers(1-9) in the first row of "board" 
//"set_board()", calls "solve()" on the first row randomly filled to return a random solution  
void set_board(void)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j][0] = ' '; //set all the values in "board" to a space
			problem[i][j][0] = ' ';//set all the values in "problem" to a space
		}
	}
	for (int i = 0; i < 6; i++) //we will add 6 random number in random places in first row
	{
		int x = 0, y = rand() % 9, n = rand() % 9 + 1;

		if (possible(board, x, y, n) && board[x][y][0] == ' ' && !(x == y && x == 8))
		{
			board[x][y][0] = n + 48;
		}
		else i--;
	}
	solve(); //solve the partially filled board
}

//"show()" will printout the board, and will color code them according to the refrence no in third dimention.
void show(void)
{
	//system("cls");
	//cout << "-----------------------------------------------\n";
	color_change(col_board);
	cout << "    1    2    3    4    5    6    7    8    9  \n";
	cout << "   ===  ===  ===  ===  ===  ===  ===  ===  === \n";

	for (int x = 0; x < 9; x++)
	{
		cout << char(49 + x) << "|| ";

		for (int y = 0; y < 9; y++)
		{
			if (problem[x][y][1] == 1) //if the number in vertex(x,y) was computer saved.
			{
				color_change(col_fix);
				cout << problem[x][y][0];
			}
			else
			{
				int numx = problem[x][y][0] - 48;//refill the cleared vertex
				problem[x][y][0] = ' '; //empty the vertex(x,y) to check the possibilty

				if (possible(problem, x, y, numx)) // if added element its possible
				{
					problem[x][y][0] = numx + 48;//refill the cleared vertex
					color_change(col_pos);
					cout << problem[x][y][0];
				}
				else if (!possible(problem, x, y, numx)) //if added element is not possible
				{
					problem[x][y][0] = numx + 48;//refill the cleared vertex
					color_change(col_npos);
					cout << problem[x][y][0];
				}
				else //if there was a space
				{
					problem[x][y][0] = numx + 48;//refill the cleared vertex
					cout << problem[x][y][0];
				}
			}
			color_change(col_board);
			cout << " || ";
		}

		cout << "\n   ===  ===  ===  ===  ===  ===  ===  ===  === \n";
	}

	color_change(col_board);
	color_change(7);

	cout << "-----------------------------------------------\n";
	cout << "No of steps: " << step << endl;
	timer(0); //show the time with 0 sec delay



}

//"make_problem()" will ask user for the number of hind and add the requried no of hints in "problem" on random from the "board"  
void make_problem(void)
{

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			problem[i][j][1] = 0;
		}
	}

	int hint;
	cout << "\nHow many hints do you want(20-80): "; cin >> hint;
	if (hint <= 80 && hint >= 1) {
		cout << "-----------------------------------------------\n";
		for (int i = 0; i < hint; i++)
		{
			int x = rand() % 9, y = rand() % 9, n = rand() % 9 + 1;

			if (problem[x][y][0] == ' ')
			{
				problem[x][y][0] = board[x][y][0];
				problem[x][y][1] = 1;	// 1 in third dimention indicate that it is a fixed number added by device
			}
			else i--;
		}
	}
	else
	{
		cout << "Wrong input, try again";
		make_problem();
	}
}

//"win()" itterate through all the row and colms and return true if whole board is solved.
bool win(void)
{
	for (int x = 0; x < 9; x++) //moving in the row
	{
		for (int y = 0; y < 9; y++) //moving in coloumn
		{
			if (problem[x][y][0] == ' ')// if any vertax is empty, game is not over yet
			{
				return false;
			}
			int numx = problem[x][y][0] - 48;
			problem[x][y][0] = ' '; //clearing the vertix to check for possibility
			if (!possible(problem, x, y, numx)) // if its not possible 
			{
				problem[x][y][0] = numx + 48; //refill the cleared vertex
				return false;//game is not over yet
			}
			problem[x][y][0] = numx + 48;//refill the cleared vertex
		}
	}
	return true;
}

//"add_element()" ask user to enter a number on specified vertix, and then it calls the show function to print the change
void add_element(void)
{
	while (true) {
		step++;
		char choice;
		int x, y, num;
		cout << "-----------------------------------------------\n";
		cout << "(-1) to quit\n";
		cout << "Enter the row(1-9): "; cin >> x;
		// if user want to exit
		if (x == -1)
		{
			exit(1);
		}

		cout << "Enter the col(1-9): "; cin >> y;
		// if user want to exit
		if (y == -1)
		{
			exit(1);
		}

		cout << "Enter the number(1-9): "; cin >> num;
		// if user want to exit
		if (num == -1)
		{
		exit(1);
		}
		cout << "-----------------------------------------------\n";

		if ((x - 1 >= 0 && x - 1 < 9) && (y - 1 >= 0 && y - 1 < 9) && (num > 0 && num < 10))
		{
			if (problem[x - 1][y - 1][1] != 1)
			{
				if (possible(problem, x - 1, y - 1, num))
				{
					problem[x - 1][y - 1][0] = num + 48;
					problem[x - 1][y - 1][1] = 2;         // 2 in third dimention indicate  that it is a possible number added by user
					show();
				}

				else if (!possible(problem, x - 1, y - 1, num))
				{
					problem[x - 1][y - 1][0] = num + 48;
					problem[x - 1][y - 1][1] = 3;         // 3 in third dimention indicate that it is a not valid number added by user
					show();
				}
				if (win())
				{
					return;
				}
			}
			else
			{
				cout << "There is a fixed number at the vertix you want to add the number, try again \n";
			}
		}
		else
		{
			cout << "Wrong Input, try again\n";
		}
	}
}
//"win_animation()" print out the fully solved function with an animation.
void win_anim(void)
{
	color_change(col_board);
	cout << "    1    2    3    4    5    6    7    8    9  \n";
	cout << "   ===  ===  ===  ===  ===  ===  ===  ===  === \n";

	for (int x = 0; x < 9; x++)
	{
		cout << char(49 + x) << "|| ";
		for (int y = 0; y < 9; y++)
		{
			color_change(col_win);
			cout << problem[x][y][0];
			Sleep(50); //sleep for 50 sec after printing each vertex to give the animation
			color_change(col_board);
			cout << " || ";
		}

		cout << "\n   ===  ===  ===  ===  ===  ===  ===  ===  === \n";
	}
	timer(4);
	cout << "-----------------------------------------------";
	color_change(col_board);
	color_change(7);
}

int main()
{
	cout << "----------------Welcome to Sudoko--------------\n";
	cout << "-----------------------------------------------\n";
	srand(time(NULL));

	while (true)
	{
		char choice;
		{
			start_time = time(NULL);
			set_board();
			make_problem();
			show();
			add_element();

			color_change(col_win);
			cout << "-----------------Game End-You Won--------------\n";
			color_change(7);

			win_anim();

		}

		//if user want to leave the game
		bool out = false;
		do
		{
			cout << "\nDo you want to play again(y/n): "; cin >> choice;
			cout << "-----------------------------------------------\n";
			if (choice == 'n' || choice == 'N')
			{
				exit(1);
			}
			if (choice == 'y' || choice == 'Y')
			{
				out = true;
			}
		} while (!out);
	}
}

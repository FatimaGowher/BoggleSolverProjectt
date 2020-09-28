

#include <iostream>
#include <fstream>
#include<map>
#include <string>
#include "cmake-build-debug/Dictionary.h"

using namespace std;
const int Num_Rows = 4;
const int Num_Cols = 4;
string choice;


void Search(int visited[Num_Rows][Num_Cols], int Count, int i, int j, string Matrix[Num_Rows][Num_Cols], string Path,
            Dictionary dict);
void print(int i, int j, string Matrix[Num_Rows][Num_Cols],int visited[Num_Rows][Num_Cols]);
void Visit(int visited[Num_Rows][Num_Cols]);
void BoggleSolver(int visited[Num_Rows][Num_Cols], int Count, int i, int j, string Matrix[Num_Rows][Num_Cols], string Path, Dictionary dict);


map<string,int>m;

// Entry point of the program to test
int main()
{

    Dictionary dict("dictionary.txt");



    string Matrix[Num_Rows][Num_Cols];
    int visited[Num_Rows][Num_Cols];
    int row;
    int col;

    cout << "Size " << dict.wordCount() << endl;

    if (dict.isPrefix("h"))
        cout << "Prefix Found" << endl;
    else
        cout << "No Prefix Found" << endl;

    if (dict.isWord("ala"))
        cout << "Word Found" << endl;
    else
        cout << "No Word Found" << endl;

    cout << "Enter Board" << endl;
    cout << "---------------" << endl;
    for (row = 0; row < Num_Rows; row++)
    {
        for (col = 0; col < Num_Cols; col++)
        {
            cin >> Matrix[row][col];
        }

    }


    //string choice;
    cout << "Would you like to print the board (Yes/No)?" << choice << endl;
    cin >> choice;

    BoggleSolver(visited, 0, 0, 0, Matrix, "", dict);

    // if (choice == "Yes")
   // {
   /*
        Visit(visited);
        for (int i = 0; i < Num_Rows; i++)
        {
            for (int j = 0; j < Num_Cols; j++)
            {
                Visit(visited);
                BoggleSolver(visited, 0, i, j, Matrix, "", dict);
            }
        } */
   // }

    //else if (choice == "No")
    //{

       // cout << "Goodbye" << endl;

    //}


    return 0;
}


void Visit(int visited[Num_Rows][Num_Cols])
{
    for (int row = 0; row < Num_Rows; row++)
    {
        for (int col = 0; col < Num_Cols; col++)
        {
            visited[row][col] = 0;
            //cout << visited[row][col] << "\t";
        }
        cout << endl;
    }
}

void print(int i, int j, string Matrix[Num_Rows][Num_Cols], int visited[Num_Rows][Num_Cols])
{
    for (i = 0; i < Num_Rows; i++)
    {
        for (j = 0; j < Num_Cols; j++)
        {
            if (visited[i][j] > 0)
            {
                cout << "'" << Matrix[i][j] << "'" << "\t";
            }
            else
                cout << Matrix[i][j] << "\t";
        }

        cout << "\t";

        for (j = 0; j < Num_Cols; j++)
        {
            cout << visited[i][j] << "\t";
        }

        cout << endl;
    }
}


void Search(int visited[Num_Rows][Num_Cols], int Count, int i, int j, string Matrix[Num_Rows][Num_Cols], string Path, Dictionary dict) 				//matrix = boardn
{
    if (i < 0 || j < 0)
        return;
    if (i >= Num_Rows || j >=Num_Cols)
        return;
    if (visited[i][j] >= 1)
        return;



    Path = Path + Matrix[i][j];

    bool a = dict.isPrefix(Path);
   //cout<<endl<<Count<<endl;

    if(a)
    {
        Dictionary NewDict;
        bool b = dict.isWord(Path);
        visited[i][j] = Count + 1;
        if (b)
        {
            if(m[Path]==0)
            {
                m[Path] = 1;
                //visited[i][j] = Count + 1;
                //make new dictionary if word is not in there
                cout << "Word: ";
                cout << Path;

                    cout << "\t" << endl;

                    cout << "Number of Words added: " << m.size() << endl;


                    //cout<<"Words added to new dictionary: "<<endl;
                   // cout << NewDict.wordCount() << endl;

                if (choice == "Yes") {


                    print(i, j, Matrix, visited);
                }
                //print(i,j);
            }
        }

       // cout<<endl<<Path<<endl;
        Search(visited, Count + 1, i - 1, j-1, Matrix, Path, dict);
        Search(visited, Count + 1, i - 1, j, Matrix, Path, dict);
        Search(visited, Count + 1, i - 1, j+1, Matrix, Path, dict);
        Search(visited, Count + 1, i, j+1, Matrix, Path, dict);

        Search(visited, Count + 1, i + 1, j+1, Matrix, Path, dict);
        Search(visited, Count + 1, i + 1, j, Matrix, Path, dict);
        Search(visited, Count + 1, i + 1, j-1, Matrix, Path, dict);
        Search(visited, Count + 1, i , j-1, Matrix, Path, dict);


       // Path.erase(Path.length()-1);

        //visited[i][j]=visited[i][j]-1;

    }
}

void BoggleSolver(int visited[Num_Rows][Num_Cols], int Count, int i, int j, string Matrix[Num_Rows][Num_Cols], string Path, Dictionary dict) {


    for (int i = 0; i < Num_Rows; i++) {
        for (int j = 0; j < Num_Cols; j++) {
            Visit(visited);
            Search(visited, 0, i, j, Matrix, "", dict);
        }


    }
}

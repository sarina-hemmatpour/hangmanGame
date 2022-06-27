#include <iostream>
#include <vector>
#include "termcolor.hpp"
using namespace std;

char word[20][16];
char description[20][100];
int WSsize=0;

enum status{easy,medium,hard};
status gameStatus[20];

int GEM=0;
int level=0;

void MainMenu();

void firstMenu();
void addNewWords();
void cinWord(int nmbr);
void difficulty(int wordNmbr);
int W(char letter);
int repeatation(vector<char> &vec , char letter);
int SUM(vector<char> vecWord,int &SofR,int &count);
void List();
void print(int x);

void game();
void allowed_fault(int &f);
void gamePrint(vector<char> G,vector<bool> GV, int F ,int DF, vector<char> GWcheck , bool h);
bool check_char(char c,vector<char> WG,vector<char> &WGcheck);
bool completeWord_check(vector<char> WGcheck);
void replace(char c,vector<char> &vec, int index);

int main()
{
    MainMenu();
}

//main menu
void MainMenu()
{
    while (1)
    {
        system("clear");
        int rowNMBR;

        cout<<"choose:"<<endl;
        cout<<"1.Add new words"<<endl<<"2.Start"<<endl<<"3.End"<<endl;

        cin>>rowNMBR;

        switch (rowNMBR)
        {
            case 1:
                system("clear");
                firstMenu();
                break;
            case 2:
                system("clear");
                game();
                break;
            case 3:
                break;
            default:
                cout<<"Wrong input!"<<endl;
        }
        if (rowNMBR==3)
        {
            system("clear");
            cout<<"THE END!!!"<<endl;
            break;
        }
    }
}

// ////////////////////////////////////////////////////////////////////////////////////////
//Menu for the first part
void firstMenu()
{
    while (1)
    {
        int rowNMBR;

        cout<<"choose:"<<endl;
        cout<<"1.List of words"<<endl<<"2.Add new words"<<endl<<"3.back"<<endl;
        cin>>rowNMBR;

        switch (rowNMBR)
        {
            case 1:
                system("clear");
                List();
                break;
            case 2:
                system("clear");
                addNewWords();
                break;
            case 3:
                break;
            default:
                cout<<"Wrong input!"<<endl;
                break;
        }
        if (rowNMBR==3)
        {
            system("clear");
            break;
        }
    }
}

//showing the list of words
void List()
{
    if (word[0][0]==NULL)
    {
        cout<<"The list of words is empty!";
    }
    else
    {
        for (int i = 0; word[i][0]!=NULL ; ++i)
        {
            cout<<i+1<<".";
            print(i);
            cout<<endl;
        }
    }
    cout<<endl<<"Type anything to exit: ";
    char anything;
    cin>>anything;
    system("clear");
}
void print(int x)
{
    //word:
    cout<<"Word: ";
    for (int i = 0; word[x][i]!=NULL ; ++i)
    {
        cout<<word[x][i];
    }
    cout<<endl;

    //description:
    cout<<"Description: ";
    for (int i = 0; description[x][i]!=NULL ; ++i)
    {
        cout<<description[x][i];
    }
    cout<<endl;

    //difficulty:
    cout<<"Status:   ";
    if (gameStatus[x]==0)
    {
        cout<<termcolor::bold<<termcolor::green<<"easy"<<endl;
        cout<<termcolor::reset;
    }
    else if(gameStatus[x]==1)
    {
        cout<<termcolor::bold<<termcolor::yellow<<"medium"<<endl;
        cout<<termcolor::reset;
    }
    else if(gameStatus[x]==2)
    {
        cout<<termcolor::bold<<termcolor::red<<"hard"<<endl;
        cout<<termcolor::reset;
    }
}

//adding new words
void addNewWords()
{
    while (1)
    {
        char yesXno;
        cout<<"Do you want to add a new word?(y or n)"<<endl;
        cin>>yesXno;
        if (yesXno=='y')
        {
            if (WSsize==20)
            {
                cout<<"Sorry!!!You can add NO more words!!!"<<endl;
                break;
            }
            else
            {
                cinWord(WSsize);
                WSsize++;
            }

        }//user wants to add a new word
        else if(yesXno=='n')
        {
            system("clear");
            break;
        }//user ignores
    }
}

//this function gets the word information
void cinWord(int nmbr)
{
    cout<<"_____________________________________________________________"<<endl;
    cout<<"Enter a new word: ";
    cin.ignore();
    cin.getline(word[nmbr], sizeof(word[nmbr]));
    difficulty(nmbr);

    cout<<"Enter the new word's description: ";
    //cin.ignore();
    cin.getline(description[nmbr], sizeof(description[nmbr]));
    cout<<"_____________________________________________________________"<<endl;

}

//taeene mizan sakhtiye bazi
void difficulty(int wordNmbr)
{
    //creating a copy of the word
    vector<char> wordCopy;
    for (int i = 0; word[wordNmbr][i]!=NULL  ; ++i)
    {
        wordCopy.push_back(word[wordNmbr][i]);
    }

    //length of the word
    int L=wordCopy.size();

    int sumOFrepeatation=0;

    //number of letters
    int D=0;

    int surat=SUM(wordCopy,sumOFrepeatation,D);

    float taqsim=surat/sumOFrepeatation;
    float difficulty=((L*L)*(D)*(taqsim))/26;
    cout<<difficulty<<endl;

    if (0<=difficulty && difficulty<10)
    {
        gameStatus[wordNmbr]=easy;
    }
    else if(10<=difficulty && difficulty<20)
    {
        gameStatus[wordNmbr]=medium;
    }
    else if(difficulty>=20)
    {
        gameStatus[wordNmbr]=hard;
    }
}

//value of each letter
int W(char letter)
{
    int value;
    if(letter=='a'|| letter=='b'|| letter=='c'|| letter=='d'|| letter=='e'|| letter=='f'|| letter=='g'|| letter=='h'||
            letter=='i'|| letter=='j'|| letter=='k'|| letter=='l'|| letter=='m'|| letter=='n'|| letter=='o')
    {
        value=1;
    }
    else if(letter=='p'|| letter=='q'|| letter=='r'|| letter=='s'|| letter=='t'|| letter=='u'||
            letter=='z'|| letter=='y'|| letter=='x'|| letter=='w'|| letter=='v' )
    {
        value=2;
    }
    return value;
}

//repeatation of each letter
int repeatation(vector<char> &vec , char letter)
{
    int count=0;
    for (int i = 0; i<vec.size() ; ++i)
    {
        if (letter==vec[i])
        {
            count++;
            vec[i]='.';
        }
    }
    return count;
}

//sum
int SUM(vector<char> vecWord,int &SofR,int &count)
{
    vector<char> COPY_vecword;
    for (int i = 0; vecWord[i]!=NULL  ; ++i)
    {
        COPY_vecword.push_back(vecWord[i]);
    }

    int sum=0;
    int old_SofR=0;
    for (int i = 0; i<vecWord.size() ; ++i)
    {
        if(vecWord[i]!='.' && vecWord[i]!=' ')
        {
            old_SofR=SofR;
            SofR+=repeatation(vecWord,COPY_vecword[i]);
            sum+=W(COPY_vecword[i])*(SofR-old_SofR);

            count++;
        }

    }
    return sum;
}

// ////////////////////////////////////////////////////////////////////////////////////////
//game starts
void game()
{
    if (word[0][0]==NULL)
    {
        cout<<"The List of words is empty!!!Add some if you want to play."<<endl;
    }
    else
    {
        while (level<=WSsize)
        {
            //maqadire avaliye :
            //+++++++++++++++++++++++++++++++++++++++++++++++
            //taeene mizan fault
            int fault;
            int Done_fault=0;
            allowed_fault(fault);

            //taeene kalemeye bazi dar in level
            vector<char> wordGame;
            for (int i = 0; word[level][i]!=NULL ; ++i)
            {
                wordGame.push_back(word[level][i]);
            }

            //taeene jahaye khali
            vector<char> wordGame_check;
            wordGame_check.clear();
            for (int i = 0; i<wordGame.size() ; ++i)
            {
                wordGame_check.push_back('-');
            }

            //guess:
            vector<char> guess;
            guess.clear();
            vector<bool> guessValue;
            guessValue.clear();
            // ++++++++++++++++++++++++++++++++++++++++++++++
            bool help=false;
            bool breakLevelUP=false;
            while (1)
            {

                bool BreakLoop= false;
                gamePrint(guess,guessValue,fault,Done_fault,wordGame_check,help);

                help= false;
                //Player gusses:
                cout<<"  What's your guess : ";
                char Guess;
                cin>>Guess;
                guess.push_back(Guess);


                //check:
                if (guess[guess.size()-1]=='*')
                {
                    break;
                }//player wants to end the game

                else if(guess[guess.size()-1]=='?')
                {
                    if(GEM>=3)
                    {
                        GEM-=3;
                        for (int i = 0;  i<wordGame.size() ; ++i)
                        {
                            if (wordGame_check[i]=='-')
                            {
                                char c=wordGame[i];
                                replace(c,wordGame_check,i);
                                break;
                            }
                        }
                    }
                    else
                    {
                        help= true;
                    }

                }//player wants to get a guid

                else
                {
                    //check:
                    char check=guess[guess.size()-1];
                    guessValue.push_back(check_char(check,wordGame,wordGame_check)) ;

                    if(guessValue[guess.size()-1]== true)
                    {
                        //check if the word is completed in order to level up

                        if(completeWord_check(wordGame_check))
                        {
                            GEM+=5;
                            level++;
                            breakLevelUP= true;
                        }//level up

                    }//true guess
                    else
                    {
                        Done_fault++;

                        if(Done_fault<=fault)
                        {
                            system("clear");
                        }//continue game
                        else
                        {
                            BreakLoop=true;
                        }//game over player stays in this level
                    }//false guess
                }
                if(BreakLoop || breakLevelUP)
                {
                    break;
                    //in order to level up
                }
            }


            if (guess[guess.size()-1]=='*')
            {
                break;
            }
        }
        system("clear");
        if (level==WSsize)
        {
            system("clear");
            cout<<"CONGRATES!!!!GAME IS FINISHED SUCCESSFULLY!!!!"<<endl;
        }
    }

}

//taeene tedad fault
void allowed_fault(int &f)
{
    if (gameStatus[level]==easy)
    {
        f=3;
    }
    if (gameStatus[level]==medium)
    {
        f=5;
    }
    if (gameStatus[level]==hard)
    {
        f=7;
    }

}

void gamePrint(vector<char> G,vector<bool> GV, int F ,int DF, vector<char> GWcheck, bool h)
{
    system("clear");

    if(h)
    {
        cout<<termcolor::red<<"There is not enough GEM!!!Gain more."<<endl;
        cout<<termcolor::reset;
    }//if the player needs help and doesnt have enough gem

    cout<<termcolor::green<<"GEM: "<<GEM<<termcolor::red<<"               fault: "<<DF<<" of "<<F<<endl;
    cout<<termcolor::reset;

    cout<<"  Description : ";
    for (int i = 0; description[level][i]!=NULL ; ++i)
    {
        cout<<description[level][i];
    }
    cout<<endl;

    cout<<"  Guess : ";
    for (int i = 0; i <(GWcheck.size()); ++i)
    {
        cout<<GWcheck[i];
    }
    cout<<endl;

    cout<<"  ";
    for (int i = 0; i<G.size() && G[i]!='?' ; ++i)
    {
        if (GV[i]== false)
        {
            cout<<termcolor::red;
        }
        else if(GV[i]== true)
        {
            cout<<termcolor::green;
        }
        cout<<G[i]<<" ";
        cout<<termcolor::reset;
    }
    cout<<endl;
}

//check if this char exists in the word
bool check_char(char c,vector<char> WG,vector<char> &WGcheck)
{
    bool value=false;
    for (int i = 0; i<WG.size() ; ++i)
    {
        if (WG[i]==c)
        {
            value= true;
            replace(c,WGcheck,i);
        }
    }
    return value;
}

//check if level up is allowed
bool completeWord_check(vector<char> WGcheck)
{
    for (int i = 0; i<WGcheck.size() ; ++i)
    {
        if (WGcheck[i]=='-')
        {
            return false;
            //the word is not completed
        }
    }
    return true;
    //the word is completed
}

void replace(char c,vector<char> &vec, int index)
{
    vector<char> copy;
    for (int i = 0; i<vec.size() ; ++i)
    {
        copy.push_back(vec[i]);
    }

    vec.clear();

    for (int j = 0; j<copy.size() ; ++j)
    {
        if (j==index)
        {
            vec.push_back(c);
        }
        else
        {
            vec.push_back(copy[j]);
        }
    }
}
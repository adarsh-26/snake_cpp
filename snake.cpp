#include<iostream>
#include<conio.h>  //to access getch function
#include<Windows.h> //to access sleep function
using namespace std;

//global variables to get accessed throughout the program
enum Direction{STOP = 0, LEFT, RIGHT, UP, DOWN};  //to create enumerated datatype
Direction dir;
bool gameOver;
const int height = 20;
const int width = 20;
int headX, headY, fruitX, fruitY, score;
int tailx[100], taily[100];
int tail_len;

void setup(); //initial set up when our program runs
void draw();  //how to draw snake,fruit, border, and display score in our setup
void input();  //taking direction input from keyboard to move snake
void logic();  //to implement logic
char m;
string mode;
char l;
string level;

int main(){


    char start;
    cout << "\t-------------------------------" << endl;
    cout << "\t\t :Snake King:" << endl;
    cout << "\t-------------------------------" << endl;
    label : cout << "\t select mode : press 's' for safe border mode, press 'd' for danger border mode ";
    cin >> m;
    if (tolower(m)=='s'){
        mode="Safe Border Mode";
    }
    else if (tolower(m)=='d'){
        mode="Danger Border Mode";
    }
    else{
        cout<<"Please select accurately";
        goto label;
    }
    label2 : cout << "Select desiring level : press 'e' for easy level , press 'm' for moderate level, select 'h' for hard level ";
    cin >> l;
    if (tolower(l)=='e'){
        level="Easy level";
    }
    else if (tolower(l)=='m'){
        level="Moderate level";
    }
    else if (tolower(l)=='h'){
        level="Hard level";
    }
    else{
        cout<<"Please select accurately";
        goto label2;
    }

    cout << "\tPress 's' to start the game: ";
    cin >> start;
    if(tolower(start) == 's'){
        setup();

        while(!gameOver){
            draw();
            input();
            logic();
            if (l=='e')
            Sleep(300);  //from window library
            else if (l=='m')
            Sleep(150);
            else
            Sleep(50);

            //system("cls");  //to remove prev screen and display the next screen
        }
        if(gameOver){
            cout<<" Game Over your score is " << score;
        }
    }

}

void setup(){
    gameOver = false;
    dir = STOP;
    headX = width/2;
    headY = height/2;
    fruitX = rand()%width;
    fruitY = rand()%height;
    score = 0;
}

void draw(){
    system("cls"); //to remove prev screen and display the next screen
    cout<< "your mode is " << mode <<"\n";
    cout <<"Your game difficulty is " << level <<"\n";
    // Uper Border
    cout << "\t\t";
    for(int i = 0; i < width+4; i++){
        cout << "|";
    }
    cout << endl;

    // Snake, fruit, space and side borders
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            // left border
            if(j == 0){
                cout << "\t\t||";
            }
            // snake head
            if(i == headY && j == headX){
                cout << "O";
            }
            // fruit
            else if(i == fruitY && j == fruitX){
                cout << "*";
            }
            // space, snake tail
            else{
                bool print = false;
                // tail
                for(int k = 0; k < tail_len; k++){
                    if(tailx[k] == j && taily[k] == i){
                        cout << "o";
                        print = true;
                    }
                }
                // space
                if(!print){     //if tail is not printed only we print empty space
                    cout << " ";
                }
            }
            // right border
            if(j == width-1){
                cout << "||";
            }
        }
        cout << endl;
    }
    // Lower Border
    cout << "\t\t";
    for(int i = 0; i < width+4; i++){
        cout << "|";
    }
    cout << endl;
    cout << "\t\t\tScore: " << score << endl;
}

void input(){
    if(_kbhit())       //used to determine if a key has been pressed or not (from conio library)
    switch (getch())    //from conio library
    {
    case 'a':
        dir = LEFT;
        break;
    case 'd':
        dir = RIGHT;
        break;
    case 'w':
        dir = UP;
        break;
    case 's':
        dir = DOWN;
        break;
    default:
        break;
    }
}

void logic(){
    // tail logic
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = headX;
    taily[0] = headY;
    for(int i = 1; i < tail_len; i++){
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    // direction logic
    switch (dir)
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;
    }

    // touch walls
    if (m=='s'){
    if(headX >= width){
        headX = 0;
    }
    else if(headX < 0){
        headX = width - 1;
    }
    if(headY >= height){
        headY = 0;
    }
    else if(headY < 0){
        headY = height - 1;
    }
    }
    else {
    if(headX >= width){
        gameOver = true;
        cout<<" Game Over due to hitting danger wall your score is " << score;
    }
    else if(headX < 0){
        gameOver = true;
                cout<<" Game Over due to hitting danger wall your score is " << score;

    }
    if(headY >= height){
        gameOver = true;
                cout<<" Game Over due to hitting danger wall your score is " << score;

    }
    else if(headY < 0){
        gameOver = true;
                cout<<" Game Over due to hitting danger wall your score is " << score;

    }

    }

    // snake bite itself
    for(int i = 0; i < tail_len; i++){
        if(tailx[i] == headX && taily[i] == headY){
            gameOver = true;
                    cout<<" Game Over due to hitting snake's body your score is " << score;

        }
    }

    // snake eat fruit
    if(headX == fruitX && headY == fruitY){
        score += 10;
        fruitX = rand()%width;
        fruitY = rand()%height;
        tail_len++;
    }

}

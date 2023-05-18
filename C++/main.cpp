
//patnashki
//#include <iostream>
//#include <Windows.h>
//using namespace std;
//void getClick(int& x, int& y)
//{
//    HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
//    INPUT_RECORD inputRec;
//    DWORD events;
//    COORD coord;
//    bool clicked = false;
//
//    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
//    SetConsoleMode(hConsoleIn, fdwMode);
//
//    while (!clicked) {
//
//        ReadConsoleInput(hConsoleIn, &inputRec, 1, &events);
//
//        if (inputRec.EventType == MOUSE_EVENT) {
//            if (inputRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
//                coord = inputRec.Event.MouseEvent.dwMousePosition;
//                x = coord.X;
//                y = coord.Y;
//                clicked = true;
//            }
//        }
//        if (GetAsyncKeyState(VK_ESCAPE)) {
//            cout << "Exiting" << endl;
//            break;
//        }
//        else if (inputRec.EventType == KEY_EVENT) {
//        }
//    }
//}
//void createfield(int*& field, int y, int size){
//    field = new int[size] {};
//    int* count = new int[size] {};
//    srand(time(0));
//    int anw{};
//    for (size_t i = 0; i < size - 1; i++){
//        anw = rand() % (size - 1) + 1;
//        if (count[anw - 1] < 1){
//            field[i] = anw;
//            count[anw - 1]++;
//        }
//        else
//            i--;
//    }
//}
//int main(){
//    int* game{};
//    int num1{};
//    int num2{};
//    cout << "choose game size: " << endl;
//    cout << "1 3x3" << endl;
//    cout << "1 4x4" << endl;
//    getClick(num1, num2);
//    while (num2 < 1 && num2 > 3){
//        cout << "invalid input, re-enter: " << endl;
//        getClick(num1, num2);
//    }
//    while (num2 != 1 && num2 != 2)
//        getClick(num1, num2);
//    int size{};
//    if (num2 == 1)
//        size = 9;
//    else if (num2 == 2)
//        size = 16;
//    createfield(game, num2, size);
//    int first_number[17]{80, 160, 240, 320, 81, 161, 241,
//                         321, 82, 162, 242, 322, 83, 163, 243, 323 };
//    int second_number[10]{80, 160, 240, 81, 161, 241, 82, 162, 242 };
//    bool close = true;
//    int time1 = time(0);
//    int move{};
//    while (close){
//        system("cls");
//        for (size_t i = 0; i < size; i++){
//            cout << '\t';
//            if (size == 9){
//                cout << game[i] << ' ';
//                if ((i + 1) % 3 == 0)
//                    cout << endl;
//            }
//            else{
//                cout << game[i] << ' ';
//                if ((i + 1) % 4 == 0)
//                    cout << endl;
//            }
//        }
//        int choice{};
//        int m{};
//        int i{};
//        while (m == 0){
//            getClick(num1, num2);
//            choice = (num1 *= 10) + num2;
//            int vac{};
//            if (size == 9){
//                for (; second_number[vac] != 0; vac++){
//                    if (choice == second_number[vac]){
//                        m++;
//                        i = vac;
//                        break;
//                    }
//                }
//            }
//            else{
//                for (; first_number[vac] != 0; vac++){
//                    if (choice == first_number[vac] || choice == first_number[vac] + 10){
//                        m++;
//                        i = vac;
//                        break;
//                    }
//                }
//            }
//        }
//        if (size == 9){
//            if (game[i + 1] == 0){
//                int r = game[i];
//                game[i] = game[i + 1];
//                game[i + 1] = r;
//            }
//            else if (game[i - 1] == 0){
//                int r = game[i];
//                game[i] = game[i - 1];
//                game[i - 1] = r;
//            }
//            else if (game[i + 3] == 0){
//                int r = game[i];
//                game[i] = game[i + 3];
//                game[i + 3] = r;
//            }
//            else if (game[i - 3] == 0){
//                int r = game[i];
//                game[i] = game[i - 3];
//                game[i - 3] = r;
//            }
//        }
//        else{
//            if (game[i + 1] == 0){
//                int r = game[i];
//                game[i] = game[i + 1];
//                game[i + 1] = r;
//            }
//            else if (game[i - 1] == 0){
//                int r = game[i];
//                game[i] = game[i - 1];
//                game[i - 1] = r;
//            }
//            else if (game[i + 4] == 0){
//                int r = game[i];
//                game[i] = game[i + 4];
//                game[i + 4] = r;
//            }
//            else if (game[i - 4] == 0){
//                int r = game[i];
//                game[i] = game[i - 4];
//                game[i - 4] = r;
//            }
//        }
//        int finish{};
//        for (size_t i = 0; i < size - 1; i++){
//            if (game[i] == i + 1)
//                finish++;
//        }
//        if (finish == size - 1)
//            close = false;
//    }
//    int** arr = new int*[2]();
//    arr[0] = new int[3]();
//    int time2 = time(0) - time1;
//    cout <<" seconds for did this" << time2 << endl;
//    cout << "for " << move << " moves";
//    return 0;
//}
//


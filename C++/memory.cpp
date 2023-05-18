
//#include <iostream>
//#include <Windows.h>
//#include <ctime>
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
//void createf(int*& field, int y, int size)
//{
//    field = new int[size] {};
//    int* count = new int[size] {};
//
//    srand(time(0));
//    int random{};
//    for (size_t i = 0; i < size; i++)
//    {
//        random = rand() % (size / 2) + 1;
//        if (count[random - 1] < 2)
//        {
//            field[i] = random;
//            count[random - 1]++;
//        }
//        else
//        {
//            i--;
//        }
//    }
//}
//void printf(int* field, int numbers[], int size, int choise, int& boolean){
//    system("cls");
//    for (size_t i = 0; i < size; i++){
//        if (choise == numbers[i]){
//            if (field[i] != 20){
//                cout << "\t" << field[i];
//                boolean = i;
//            }
//            else cout << "\t ";
//        }
//        else{
//            if (field[i] != 20) cout << "\t* ";
//            else cout << "\t ";
//        }
//        if ((i + 1) % 4 == 0) cout << endl;
//    }
//}
//int main(){
//    int* field{};
//    char word{};
//    bool stop = true;
//    int numbers[33]{ 80, 160, 240, 320, 81, 161, 241, 321,
//                     82, 162, 242, 322, 83, 163, 243,
//                     323, 84, 164, 244, 324, 85, 165, 245, 325};
//    int x{}, y{}, size{}, moveCount{}, per{};
//    int time1 = time(0);
//    int first_choice{}, second_choise{};
//    int first = 50, second = 50;
//    cout << "add field size: " << endl
//         << "1. 4x4" << endl
//         << "2. 6x6" << endl;
//    getClick(x, y);
//    while (y < 1 && y > 3){
//        cout << "Invalid input, enter again pls: " << endl;
//        getClick(x, y);
//    }
//    while (y != 1 && y != 2){
//        getClick(x, y);
//    }
//    if (y == 1){
//        size = 16;
//    }
//    else if (y == 2) {
//        size = 32;
//    }
//    createf(field, y, size);
//    while (stop){
//        system("cls");
//        for (size_t i = 0; i < size; i++){
//            if (field[i] != 20) cout << "\t* ";
//            else cout << "\t ";
//            if ((i + 1) % 4 == 0) cout << endl;
//        }
//        while (per == 0){
//            getClick(x, y);
//            first_choice = (x *= 10) + y;
//            for (size_t i = 0; numbers[i] != 0; i++){
//                if (first_choice == numbers[i]){
//                    per++;
//                    break;
//                }
//            }
//        }
//        printf(field, numbers, size, first_choice, first);
//        second_choise = first_choice;
//        per--;
//        while (second_choise == first_choice){
//            while (per == 0){
//                getClick(x, y);
//                second_choise = (x *= 10) + y;
//                for (size_t i = 0; numbers[i] != 0; i++){
//                    if (second_choise == numbers[i]){
//                        per++;
//                        break;
//                    }
//                }
//            }
//            per--;
//        }
//
//        printf(field, numbers, size, second_choise, second);
//
//        if (field[second] == field[first]){
//            field[second] = 20;
//            field[first] = 20;
//        }
//        int s{};
//        for (size_t i = 0; i < size; i++){
//            if (field[i] == 20) s++;
//        }
//        moveCount++;
//        if (s == size){
//            system("cls");
//            cout << "you win!" << endl;
//            stop = false;
//            break;
//        }
//        cout << "press any key to continue: ";
//        cin >> word;
//    }
//    int time2 = time(0) - time1;
//    cout << "second for win " << time2 << endl;
//    cout << "for " << moveCount << "move";
//    cin.ignore();
//    return 0;
//}
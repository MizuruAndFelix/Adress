#include <fstream>
#include <iostream>
#include <locale.h>
#include <windows.h>
#include <string>
using namespace std;


class Adresa
{
private:
    string city;
    string street;
    int home;
    int room;
    string full; //шоб полный адресс хранить
public:
    Adresa(string city_, string street_, int home_, int room_)
    {
        city = city_;
        street = street_;
        home = home_;
        room = room_;
    }
    string fullAddress();
};


string Adresa::fullAddress() //полный адресс в строку
{
    full = city + " " + street + " " + to_string(home) + " " + to_string(room);
    return full;
}

std::string* createDinamicStringArr(const int numbersAdress)// функклия для динамического массива
{
    std::string* stringArr = new std::string[numbersAdress]
    {
    };
    return stringArr;
}
void deleteTextArr(std::string* stringArr, const int numbersAdress) //удалить массив чтоб не забивать память
{
    delete[] stringArr;
}

int fullAddressPrint(string* arrAdress,const int numbersAdress) //ФУНКЦИЯ (НЕ МЕТОД) печать в файл
{
    ofstream fileOut("out.txt");
    if (fileOut.is_open())
    {
        std::cout << "File out.txt is open." << std::endl;

        fileOut << "Число адресов: " << numbersAdress << endl;
        fileOut << "Формат вывода адреса: <название города>, <название улицы>, <номер дома>, <номер квартиры>.\n";

        for (int i = numbersAdress - 1; i >= 0; i--) //надо проверить корректность номеров
        {//если чо переделать на (int i = numbersAdress ; i >= 1; i--)
            fileOut << "Адресс #" << numbersAdress - i << " " << arrAdress[i] << endl;
        }
        fileOut.close();
    }
    else
    {
        std::cout << "Eror file out.txt is not open!" << std::endl;
        return 0;
    }
}


int main()
{
    setlocale(LC_ALL, "Russian"); 
    system("chcp 1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); //попытка в кирилицу(половинный успех)

    cout << "start\n";

    string city_m = {};
    string street_m = {};
    int home_m = 0;
    int room_m = 0;
    int numbersAdress = 0;

    std::ifstream fileIn("in.txt"); // Открываю и проверяю
    if (fileIn.is_open())
    {
        std::cout << "File in.txt is open." << std::endl;
    }
    else
    {
        std::cout << "Eror! File in.txt is not open!" << std::endl;
        return 0;
    }


    fileIn >> numbersAdress;
    string* arrAdress = createDinamicStringArr(numbersAdress);

    for (int i = 0; i < numbersAdress; i++)
    {
        fileIn >> city_m >> street_m >> home_m >> room_m;
        Adresa adress(city_m, street_m, home_m, room_m);
        arrAdress[i] = adress.fullAddress();
    }

    fileIn.close(); //закрыт

    fullAddressPrint(arrAdress, numbersAdress); //печать

    deleteTextArr(arrAdress, numbersAdress);//память очищена

    if (!fileIn.is_open()) //на всякий случай
    {
        cout << "End\n";
        return 0;
    }
    else
    {
        cout << "Файл open.txt не закрылся!\n";
        return 0;
    }
}

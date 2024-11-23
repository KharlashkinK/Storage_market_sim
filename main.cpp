#include <iostream>
#include <windows.h> // действия с консолью
#include <string>
#include <cstdlib> // рандом
#include <ctime>   // инит рандома для еще большего рандома 
#include <map>
#include <vector>

using namespace std;

int random_number(int random_range) {  // генератор случайных чисел, чтобы часто его не писать

    int random_final = rand() % random_range;
    return random_final;
}
void clear(HANDLE HANDLE, COORD COORD) { // очищение строчки вывода
    for (int i = 0; i < 200; i++)
    {
        cout << " ";
    }
    SetConsoleCursorPosition(HANDLE, COORD);
    
}
class kassa {
public:
	bool kassa_line[10]; // эмуляция кассы 

    void kassa_init() {
        for (int i = 0; i < 10; i++) {
            kassa_line[i] = 0;
        }
    } // заполняем дорогу к кассе нулями, покупатель будет отображиться как единица (1)
    void kassa_write() {
        for (int i = 0; i < 10; i++) {
            cout << " " << kassa_line[i];
        }
    }

};

class custumer {
public:
    int is_alive;
    string NAMES[5] = { "Kons", "Cool Guy", "Bogdan", "Antor", "Vlad"}; // имена
    map <string, int> goods; // товары, типа как база данных 
    vector<std::string> goods_name;// названия товаров 
    vector<std::string> person_goords; // товары клиета
    string Name; 
    int rand_val{ 4 }; // кол-во товаров
    int sum_of_vals;

    void goods_select() { // выбор товаров и вычисление их суммы 
         
        for (const auto& pair : goods) {
            goods_name.push_back(pair.first);
        }
        for (int i = 0; i < rand_val; ++i) {
            int randomIndex = std::rand() % goods_name.size();
            person_goords.push_back(goods_name[randomIndex]);
            sum_of_vals += goods[goods_name[randomIndex]];
        }

    }
    void name_init() { //случайное имя
        int rand = random_number(4);
        Name = NAMES[rand];
    }

    void map_init() {
        goods["apples"] = 15;
        goods["chips"] = 5;
        goods["lit energe"] = 52; // )
        goods["bread"] = 3;
        goods["milk"] = 2;
        goods["eggs"] = 5;
        goods["chiken"] = 7;
    } // заполняем список через функцию 
};



void action(short x) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, x };
    SetConsoleCursorPosition(hConsole, coord);
    custumer customer;
    kassa kassa;
    customer.map_init();
    customer.name_init();
    kassa.kassa_init();
    customer.goods_select();
    customer.is_alive = 1;
    int random;
    // ^^^^^
    // инициализация и выполнение опеределение необходимых классов
    
    //спавн покупателя и появление его на линии
    if (customer.is_alive == 1) //если покупатель существует
    {
        for (int i = 0; i < 10; i++) { // ходьба
            kassa.kassa_line[i] = 1; 
            random = random_number(6);
            SetConsoleCursorPosition(hConsole, coord);
            kassa.kassa_write();
            //вывод
            Sleep(1000 * random); // прерывание, в секундах
            if (kassa.kassa_line[9] == 1) {
                //write goods
                COORD coord1 = { 0 , x+1 };
                clear(hConsole, coord1);
                cout << " " << customer.Name;
                cout << " купил: ";
                for (const auto& item : customer.person_goords) {
                    cout << " " << item << ", ";
                }
                cout << " за: " << customer.sum_of_vals << " рублей";
            }
            kassa.kassa_line[i] = 0;
            random = 1;
        }
    }



}

int main() {

    setlocale(LC_ALL, "ru-RU");
    srand(static_cast<unsigned int>(std::time(0)));

    for (int i = 0; i < 3; i++) {
        action(0);
        action(2);
        action(4);
    } 
    // не вышло сделать при помощи потоков


	return 0;
}
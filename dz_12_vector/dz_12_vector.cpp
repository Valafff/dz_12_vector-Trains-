// ДЗ с 510 строки
#include <iostream>
#include <time.h>
#include <Windows.h>//	Sleep;
#include <string>
#include<conio.h>
#include<vector>
#include <algorithm>
//#include "menu.h"
using namespace std;
enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//получаем дискриптор активного окна
void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, esc = 27 };
void setCursor(int x, int y)
{
	COORD myCoords = { x,y };//инициализируем передаваемыми значениями объект координат
	SetConsoleCursorPosition(hStdOut, myCoords);
}
class MENU
{
	class SUBMENU
	{
		size_t count_y_slots{ 0 };
		size_t step_Y{ 0 };
		size_t sub_start_X{ 0 };
		size_t sub_start_Y{ 0 };
		size_t menupoint_Y{ 0 };
		size_t quit_Y{ 0 };

		Color text_Y{ Red };
		Color background_Y{ White };
		Color text_default_Y{ White };
		Color background_default_Y{ Black };

		string* y_list{ nullptr };

	public:

		SUBMENU() :SUBMENU(2, Red, White)
		{
			for (size_t i = 0; i < count_y_slots; i++)
			{
				y_list[i] += "SUB_";
				y_list[i] += to_string(i);
			}
			//y_list[0] = "SUB_1";
			//y_list[1] = "SUB_2";
		}
		SUBMENU(const size_t def_size) :SUBMENU(def_size, Red, White)
		{
			for (size_t i = 0; i < def_size; i++)
			{
				y_list[i] += "SUB_";
			}
		}
		SUBMENU(const size_t f_count_Y, const Color textcolor, const Color backgroung_color, const size_t X = 0, const size_t Y = 0, const size_t f_step_Y = 1)
		{
			count_y_slots = f_count_Y;
			y_list = new string[f_count_Y];
			step_Y = f_step_Y;
			text_Y = textcolor;
			background_Y = backgroung_color;
			quit_Y = f_count_Y;
			sub_start_X = X;
			sub_start_Y = Y;
			menupoint_Y = 1;

		}
		~SUBMENU()
		{
			if (y_list != nullptr)
			{
				delete[] y_list;
			}
		}
		void setCount_Y_slots(const size_t& f_size)
		{
			count_y_slots = f_size;
			if (y_list != nullptr)
			{
				delete[] y_list;
			}
			//!!!ОБЯЗАТЕЛЬНО НУЛЕВОЙ УКАЗАТЕЛЬ - ИНАЧЕ ДЕСТРУКТОР БУДЕТ ПЫТАТЬСЯ ОСВОБОДИТЬ ПАМЯТЬ ДВА РАЗА!!!
			y_list = nullptr;
			for (size_t i = 0; i < f_size; i++)
			{
				y_list = new string[f_size];
			}
			for (size_t i = 0; i < f_size; i++)
			{
				y_list[i] += "SUB_";
				y_list[i] += to_string(i);
			}
		}
		void setY_step(const size_t& f_size)
		{
			step_Y = f_size;
		}
		void set_BackGround_Y(const Color& f_color)
		{
			background_Y = f_color;
		}
		void set_Text_Y(const Color& f_color)
		{
			text_Y = f_color;
		}
		void setQuit_Y(const size_t f_size)
		{
			quit_Y = f_size;
		}
		void setSubStart_X(const size_t X)
		{
			sub_start_X = X;
		}
		void setSubStart_Y(const size_t Y)
		{
			sub_start_Y = Y;
		}
		void setMenupoint(const size_t f_menu)
		{
			menupoint_Y = f_menu;
		}
		void setY_list(const size_t index, const string f_name)
		{
			y_list[index] = f_name;
		}

		Color getBackground_Y() const
		{
			return background_default_Y;
		}
		size_t getCount_y_slots()
		{
			return count_y_slots;
		}

		// Освобождение вновь выделенной памяти для y_list Т.К. ДЕСТРУКТОР ПЫТАЕТСЯ БАХНУТЬ ПАМЯТЬ ПО АДРЕСУ, КОТОРАЯ ВЫДЕЛЯЛАЛСЬ КОНСТРУКТОРОМ
		void delMem()
		{
			if (y_list != nullptr)
			{
				delete[] y_list;
				y_list = nullptr;
			}
		}

		// ПЕЧАТЬ ПОДМЕНЮ ПО ВЕРТИКАЛИ
		void menuPrint_Y(const size_t& menupoint, const size_t& f_step_X)
		{
			for (size_t i = 0; i < count_y_slots; i++)
			{
				setCursor(f_step_X, sub_start_Y + i * step_Y + 1);
				if (i == menupoint)
				{
					setColor(text_Y, background_Y);
				}
				else
				{
					setColor(text_default_Y, background_default_Y);
				}
				cout << y_list[i];
			}
			setColor(text_default_Y, background_default_Y);
		}
		//ОЧИСТКА ПРЕДЫДУЩЕГО ПОДМЕНЮ(по умолчанию происходит с координат 0,1) количество строк для очистки передается как аргумент, длина строки передается как аргумент
		void cleanSubMenuZone(const size_t count_row, const size_t string_length, size_t f_start_x = 0, size_t f_start_y = 1)
		{
			setCursor(f_start_x, f_start_y);
			setColor(getBackground_Y(), getBackground_Y());
			char** cleanarr = new char* [count_row];
			for (size_t i = 0; i < count_row; i++)
			{
				cleanarr[i] = new char[string_length];
			}
			for (size_t i = 0; i < count_row; i++)
			{
				for (size_t j = 0; j < string_length; j++)
				{
					cleanarr[i][j] = '@';
					cout << cleanarr[i][j];
				}
				cout << endl;
			}
			if (cleanarr != nullptr)
			{
				for (size_t i = 0; i < count_row; i++)
				{
					delete[] cleanarr[i];
				}
				delete[] cleanarr;
			}
		}
	};

	size_t count_x_slots{ 0 };
	size_t step_X{ 0 };
	size_t quit{ 0 };
	size_t start_X{ 0 };
	size_t start_Y{ 0 };
	size_t menupoint{ 0 };

	Color text{ Red };
	Color background{ White };
	Color text_default{ White };
	Color background_default{ Black };

	//SUBMENU aaa;
	//SUBMENU aaa(10);

	string* x_list;
	SUBMENU* sub_menu;

	// ПЕЧАТЬ МЕНЮ ДЛЯ ГОРИЗОНТАЛИ
	void menuPrint_X(const size_t menupoint)
	{
		for (size_t i = 0; i < count_x_slots; i++)
		{
			setCursor(start_X + i * step_X, start_Y);
			if (i == menupoint)
			{
				setColor(text, background);
			}
			else
			{
				setColor(text_default, background_default);
			}
			cout << x_list[i];
		}
		setColor(text_default, background_default);
	}

public:

	MENU() :MENU(4, 18, Red, White)
	{
		x_list[0] = "MENU_1";
		x_list[1] = "MENU_2";
		x_list[2] = "MENU_3";
		x_list[3] = "QUIT";
	}
	//// Далее, через конструктор копирования инициализировать объект
	//MENU(int size): MENU(4, 18, Red, White)
	//{
	//	SUBMENU aaa(size);
	//}
	MENU(const size_t f_count_X, const size_t f_step_X, const Color textcolor, const Color backgroung_color, const size_t X = 0, const size_t Y = 0, const size_t f_step_Y = 1)
	{
		x_list = new string[f_count_X];
		sub_menu = new SUBMENU[f_count_X];
		count_x_slots = f_count_X;
		step_X = f_step_X;
		text = textcolor;
		background = backgroung_color;
		quit = f_count_X;
		start_X = X;
		start_Y = Y;
		menupoint = 0;
	}
	~MENU()
	{
		//ВЫЗОВ МЕТОДА ОСВОБОЖДЕНИЯ ПЕРЕВЫДЕЛЕННОЙ ПАМЯТИ ДЛЯ y_list
		this->sub_menu->delMem();
		if (x_list != nullptr)
		{
			delete[] x_list;
		}
		if (sub_menu != nullptr)
		{
			delete[] sub_menu;
		}
	}
	// Установка цвета текста для ГОРИЗОНТАЛЬНОЙ строки
	void setColorText(const Color textcolor)
	{
		text = textcolor;
	}
	// Установка цвета текста для ВЕРТИКАЛЬНОЙ строки
	void setColorText_Y(const Color textcolor)
	{
		for (size_t i = 0; i < count_x_slots; i++)
		{
			sub_menu[i].set_Text_Y(textcolor);
		}
	}
	// Установка цвета фона для ВЕРТИКАЛЬНОЙ строки
	void setColorBackGround_Y(const Color backcolor)
	{
		for (size_t i = 0; i < count_x_slots; i++)
		{
			sub_menu[i].set_BackGround_Y(backcolor);
		}
	}
	// Установка цвета заднего фона ГОРИЗОНТАЛЬНОЙ строки
	void setColorBackground(const Color f_bakground)
	{
		background = f_bakground;
	}
	// Установка дефолтного цвета текста по умолчанию ГОРИЗОНТАЛЬНАЯ строка
	void setColorTextDefault(const Color f_def_text)
	{
		text_default = f_def_text;
	}
	//Установка заднего фона по умолчанию ГОРИЗОНТАЛЬНАЯ строка
	void setColorBackgroundDefault(const Color f_def_background)
	{
		background_default = f_def_background;
	}
	// Задание количества слотов меню по ГОРИЗОНТАЛИ
	void setCount_X_Slots(const size_t f_count)
	{
		count_x_slots = f_count;
	}
	// Задание количества слотов меню по ВЕРТИКАЛИ для подменю
	void setCount_Y_Slots(const size_t f_index, const size_t f_count)
	{
		sub_menu[f_index].setCount_Y_slots(f_count);

	}
	// Задание названий пунктов меню по ГОРИЗОНТАЛИ
	void setName_X_list(const size_t index, const string f_name)
	{
		x_list[index] = f_name;
	}
	// Задание названий пунктов меню по ВЕРТИКАЛИ
	void setName_Y_list(const size_t index_x, const size_t index_y, const string f_name)
	{
		sub_menu[index_x].setY_list(index_y, f_name);
	}
	// Установка шага по ГОРИЗОНТАЛИ
	void set_X_step(const size_t f_step)
	{
		step_X = f_step;
	}
	// получение длины списка по ГОРИЗОНТАЛИ
	size_t getSizeX()
	{
		return count_x_slots;
	}
	// получение последнего индекса списка по ГОРИЗОНТАЛИ
	size_t getLast_IndexX()
	{
		return count_x_slots - 1;
	}
	// Получение индекса выбранного меню по ГОРИЗОНТАЛИ
	size_t getMenuIndex()
	{
		return menupoint;
	}
	// Определение максимального количества строк
	size_t getMaxRow()
	{
		size_t temp(0);
		for (size_t i = 0; i < count_x_slots; i++)
		{
			if (sub_menu[i].getCount_y_slots() > temp)
			{
				temp = sub_menu[i].getCount_y_slots();
			}
		}
		return temp;
	}

	// Назначение клавиш, возврат выбранного пункта меню для ГОРИЗОНТАЛИ И ВЕРТИКАЛИ
	size_t SelectMenuItem(const size_t f_lastmenu, const size_t f_lastmenu_Y, const bool f_flag)
	{
		size_t menupoint;
		size_t menupoint_Y;
		if (f_lastmenu == 0)
		{
			menupoint = 1;
		}
		else
		{
			menupoint = f_lastmenu;
		}
		if (f_lastmenu_Y == 0)
		{
			menupoint_Y = 1;
		}
		else
		{
			menupoint_Y = f_lastmenu_Y;
		}

		size_t lastmenupoint = 1;
		size_t maxrow = getMaxRow();
		//ВЫХОД - последний член списка
		size_t key(0);
		do
		{
			if (menupoint != lastmenupoint)
			{
				if (key == Left or key == Right)
				{
					menupoint_Y = 1;
				}
				lastmenupoint = menupoint;
				sub_menu[menupoint - 1].cleanSubMenuZone(maxrow, 100);
			}
			menuPrint_X(menupoint - 1);
			sub_menu[menupoint - 1].menuPrint_Y(menupoint_Y - 1, step_X * (menupoint - 1));

			key = _getch();
			if (key == Right)
			{
				if (menupoint <= count_x_slots)
				{
					menupoint++;
				}
				if (menupoint > count_x_slots)
				{
					menupoint = 1;
				}
			}
			if (key == Left)
			{
				if (menupoint >= 1)
				{
					menupoint--;
				}
				if (menupoint < 1)
				{
					menupoint = count_x_slots;
				}
			}
			if (key == Down)
			{
				if (menupoint_Y <= sub_menu[menupoint - 1].getCount_y_slots())
				{
					menupoint_Y++;
				}
				if (menupoint_Y > sub_menu[menupoint - 1].getCount_y_slots())
				{
					menupoint_Y = 1;
				}
			}
			if (key == Up)
			{
				if (menupoint_Y >= 1)
				{
					menupoint_Y--;
				}
				if (menupoint_Y < 1)
				{
					menupoint_Y = sub_menu[menupoint - 1].getCount_y_slots();
				}
			}
			if (key == Enter)
			{
				if (sub_menu[menupoint - 1].getCount_y_slots() != 0)
				{
					//От 1 до 100 - коды только горизонтального меню, выводится код от 101 до 200 - MENU_1, SUB_1 - SUB_N по ВЕРТИКАЛИ, MENU_2, SUB_1 - SUB_N  201-300...
					return menupoint_Y + (menupoint * 100);
				}
				else
				{
					return menupoint;
				}
			}
		} while (key != Enter);
		return this->quit;
	}
};

void cleanZone(const size_t X, const size_t Y, const size_t row, const size_t col, const Color color = Black)
{
	Color temptxtcol = White;
	Color tempbackcol = Black;

	setCursor(X, Y);
	setColor(color, color);
	vector <char> cln;
	cln.assign(row * col, '@');
	int count = 1;
	for (auto symbol : cln)
	{
		cout << symbol;
		count++;
		if (count % col == 0)
		{
			cout << endl;
		}
	}
	setColor(temptxtcol, tempbackcol);
	setCursor(X, Y);
}

void formatPrint(const size_t col_size, const string& originalstr)
{

	size_t tempindex = 1;
	for (auto s : originalstr)
	{
		tempindex++;
		cout << s;
		if (tempindex % col_size == 0)
		{
			cout << endl;
		}
	}
}
//класс Поезд
// /*номер поезда
// Начальная станцияконечная станция
// время отбытиявремя прибытия
// заполнение всех полей случайным образом через set-методыget-методы для всех полейпоказать поезд*/
// /*Класс ЖД Вокзалсоздать vector поездов в котором реализовать возможностьдобавление поездоввывод всех поездоввывод данных о конкретном поезде (по номеру поезда)
// метод для формирования vector с поездами, соответствующими передаваемому в метод направлению (конечная станция)отсортировать поезда по времени отправления (через стандартную функцию sort это будет +)*/
//класс Поезд
/*
номер поезда
Начальная станция
конечная станция
время отбытия
время прибытия

заполнение всех полей случайным образом через set-методы
get-методы для всех полей
показать поезд

Класс ЖД Вокзал
создать vector поездов в котором реализовать возможность

добавление поездов
вывод всех поездов
вывод данных о конкретном поезде (по номеру поезда)
метод для формирования vector с поездами, соответствующими передаваемому в метод направлению (конечная станция)-Метод возвращает вектор с отобранными поездами
отсортировать поезда по времени отправления (через стандартную функцию sort это будет +)

*/

class Train
{
	size_t default_number_length = 4;

	string train_number;
	string departure_station;
	string arrival_station;
	struct Time
	{
		int hours;
		int minuts;
	};
	Time departure_time;
	Time arrival_time;

public:	

	void setNumber_train(const string& number)
	{ 
		if (number.size() <= default_number_length)
		{
			train_number = number;
		}
		else
		{
			train_number.assign(number, default_number_length);
		}
	}

	void setDeparture_station(const string& station)
	{
		departure_station = station;
	}

	void setArrival_station(const string& station)
	{
		arrival_station = station;
	}

	void setDeparture_time(const int& hour, const int& minute)
	{
		if (hour >=0 and hour <= 23)
		{
			departure_time.hours = hour;
		}
		else
		{
			departure_time.hours = 0;
		}
		if (minute >= 0 and minute <=59)
		{
			departure_time.minuts = minute;
		}
		else
		{
			departure_time.minuts = 0;
		}
	}

	void setArrival_time(const int& hour, const int& minute)
	{
		if (hour >= 0 and hour <= 23)
		{
			arrival_time.hours = hour;
		}
		else
		{
			arrival_time.hours = 0;
		}
		if (minute >= 0 and minute <= 59)
		{
			arrival_time.minuts = minute;
		}
		else
		{
			arrival_time.minuts = 0;
		}
	}
	string getTrain_number()
	{
		return train_number;
	}
	string getDeparture_station()
	{
		return departure_station;
	}
	string getArrival_station()
	{
		return arrival_station;
	}
	size_t getDeparture_H_time()
	{
		return departure_time.hours;
	}
	size_t getDeparture_M_time()
	{
		return departure_time.minuts;
	}
	size_t getArrival_H_time()
	{
		return arrival_time.hours;
	}
	size_t getArrival_M_time()
	{
		return arrival_time.minuts;
	}
	Time getDeparture_time()
	{
		return departure_time;
	}
	Time getArrival_time()
	{
		return arrival_time;
	}
	string randomDeparture()
	{
		vector <string> station{ "СИТИ-17", "ЧЕРНАЯ-МЕЗА", "РЕЙВЕНХОЛМ", "НОВА-ПРОСПЕКТ", "БЕЛАЯ РОЩА", "ЦИТАДЕЛЬ", "СИТИ-8", "СИТИ-11", "СИТИ-12", "СИТИ-13" };
		return station[rand() % station.size()];
	}
	string randomArrival(const string& start_station)
	{
		vector <string> station{ "СИТИ-17", "ЧЕРНАЯ-МЕЗА", "РЕЙВЕНХОЛМ", "НОВА-ПРОСПЕКТ", "БЕЛАЯ РОЩА", "ЦИТАДЕЛЬ", "СИТИ-8", "СИТИ-11", "СИТИ-12", "СИТИ-13" };
		size_t count(0), index(0);
		for (string str:station)
		{
			if (str == start_station)
			{
				index = count;
			}
			count++;
		}
		station.erase(station.begin() + index);
		return station[rand() % station.size()];
	}
	string randomTrainName()
	{
		string resultName;
		size_t number;
		vector <string> liter{ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
		
		resultName = liter[rand() % liter.size()];
		for (size_t i = 0; i < default_number_length-1; i++)
		{
			resultName.append(to_string(number = rand() % 10));
		}
		return resultName;
	}
	Time randomTime()
	{
		Time random;
		random.hours = (int)rand() % 24;
		random.minuts = (int)rand() % 60;
		return random;
	}
	string timeToString(const Time& t)
	{
		string temp{};
		int h{ t.hours }, m{t.minuts};
		if (h < 10)
		{
			temp.assign("0");
			temp.append(to_string(h));
		}
		else
		{
			temp.assign(to_string(h));
		}
		temp.append(":");
		if (m < 10)
		{
			temp.append(to_string(0));
			temp.append(to_string(m));
		}
		else
		{
			temp.append(to_string(m));
		}
		return temp;
	}
	void getTrainInfo()
	{
		cout << "Номер поезда: " << train_number << endl;
		cout << "Станция отправления: " << departure_station << endl;
		cout << "Станция прибытия: " << arrival_station << endl;
		cout << "Время отправления: " << timeToString(departure_time) << endl;
		cout << "Время прибытия: " << timeToString(arrival_time);
	}

	Train()
	{
		train_number = randomTrainName();
		departure_station = randomDeparture();
		arrival_station = randomArrival(departure_station);
		departure_time.hours = randomTime().hours;
		departure_time.minuts = randomTime().minuts;
		arrival_time.hours = randomTime().hours;
		arrival_time.minuts = randomTime().minuts;
	}
	~Train()
	{
	}
	Train &operator=(const Train& r)
	{
		train_number = r.train_number;
		departure_station = r.departure_station;
		arrival_station = r.arrival_station;
		departure_time.hours = r.departure_time.hours;
		departure_time.minuts = r.departure_time.minuts;
		arrival_time.hours = r.arrival_time.hours;
		arrival_time.minuts = r.arrival_time.minuts;
		return *this;
	}
};

class TrainStation
{
	vector <Train> trains;

public:

	void TuTu_lair(const size_t & size)
	{
		for (size_t i = 0; i < size; i++)
		{
			trains.emplace_back(Train());	
		}

	}
	//TrainStation();
	//~TrainStation();
	void showTrains()
	{
		int step = 15;
		setCursor(step*0, 6);
		cout << "Номер \nпоезда";
		for (size_t i = 0; i < trains.size(); i++)
		{
			setCursor(0, 9+i);
			cout << trains[i].getTrain_number() << endl;;
		}

		setCursor(step*1, 6);
		cout << "Станция";
		setCursor(step * 1, 7);
		cout << "отправления";
		for (size_t i = 0; i < trains.size(); i++)
		{
			setCursor(step*1, 9 + i);
			cout << trains[i].getDeparture_station();
		}
		setCursor(step*2, 6);
		cout << "Время";
		setCursor(step * 2, 7);
		cout<< "отправления";
		for (size_t i = 0; i < trains.size(); i++)
		{
			setCursor(step*2, 9 + i);
			cout << trains[i].timeToString(trains[i].getDeparture_time());
		}
		setCursor(step * 3, 6);
		cout << "Станция";
		setCursor(step * 3, 7);
		cout << "назначения";
		for (size_t i = 0; i < trains.size(); i++)
		{
			setCursor(step * 3, 9 + i);
			cout << trains[i].getArrival_station();
		}
		setCursor(step * 4, 6);
		cout << "Время";
		setCursor(step * 4, 7);
		cout << "прибытия";
		for (size_t i = 0; i < trains.size(); i++)
		{
			setCursor(step * 4, 9 + i);
			cout << trains[i].timeToString(trains[i].getArrival_time());
		}
	}

	void showTrains(vector <Train>& trains)
	{
		int step = 15;
		setCursor(step * 0, 6);
		cout << "Номер \nпоезда";
		for (size_t i = 0; i < trains.size(); i++)
		{
			setCursor(0, 9 + i);
			cout << trains[i].getTrain_number() << endl;;
		}

		setCursor(step * 1, 6);
		cout << "Станция";
		setCursor(step * 1, 7);
		cout << "отправления";
		for (size_t i = 0; i < trains.size(); i++)
		{
			setCursor(step * 1, 9 + i);
			cout << trains[i].getDeparture_station();
		}
		setCursor(step * 2, 6);
		cout << "Время";
		setCursor(step * 2, 7);
		cout << "отправления";
		for (size_t i = 0; i < trains.size(); i++)
		{
			setCursor(step * 2, 9 + i);
			cout << trains[i].timeToString(trains[i].getDeparture_time());
		}
		setCursor(step * 3, 6);
		cout << "Станция";
		setCursor(step * 3, 7);
		cout << "назначения";
		for (size_t i = 0; i < trains.size(); i++)
		{
			setCursor(step * 3, 9 + i);
			cout << trains[i].getArrival_station();
		}
		setCursor(step * 4, 6);
		cout << "Время";
		setCursor(step * 4, 7);
		cout << "прибытия";
		for (size_t i = 0; i < trains.size(); i++)
		{
			setCursor(step * 4, 9 + i);
			cout << trains[i].timeToString(trains[i].getArrival_time());
		}
	}
	size_t size()
	{
		return trains.size();
	}

	int getNamePosition(const string & input)
	{
		string temp;
		for (size_t i = 0; i < trains.size(); i++)
		{
			temp = trains[i].getTrain_number();
			if (temp == input)
			{
				return i;
			}
		}
		return -1;
	}

	void getTrainInfo(const int& index)
	{
		if (index != -1)
		{
			trains[index].getTrainInfo();
		}
		else
		{
			cout << "Номер в списке не найден";
		}

	}
	void setNew_train()
	{
		system("chcp 1251 > NUL");
		Train temp;
		string tempstr;
		int temp_h, temp_m;
		cout << "Введите номер поезда: ";
		getline(cin, tempstr);
		temp.setNumber_train(tempstr);
		cout << "Введите станцию отправления: ";
		getline(cin, tempstr);
		temp.setDeparture_station(tempstr);
		cout << "Введите станцию назначения: ";
		getline(cin, tempstr);
		temp.setArrival_station(tempstr);
		cout << "Введите часы отправления: ";
		cin >> temp_h;
		cout << "Введите минуты отправления: ";
		cin >> temp_m;
		temp.setDeparture_time(temp_h, temp_m);
		cout << "Введите часы назначения: ";
		cin >> temp_h;
		cout << "Введите минуты назначения: ";
		cin >> temp_m;
		temp.setArrival_time(temp_h, temp_m);
		trains.push_back(temp);
		cout << "Данные введены";
		system("chcp 866 > NUL");
	}
	void deleteTrain(const int index)
	{
		if (index-1 >= 0 and index-1 < trains.size())
		{
			trains.erase(trains.begin() + index-1);
		}
	}
	vector <Train> searchBy_station(const string &str)
	{
		vector <Train> input;
		for (Train tr : trains)
		{
			if (tr.getArrival_station() == str)
			{
				input.push_back(tr);
			}
		}
		return input;
	}

	static bool isTime(Train time1, Train time2)
	{
		return time1.getDeparture_H_time() * 60 + time1.getDeparture_M_time() < time2.getDeparture_H_time() * 60 + time2.getDeparture_M_time();
	}
	void sortTrainBy_timedeparture()
	{
		sort(trains.begin(), trains.end(), isTime);
	}
};

//добавление поездов
//вывод всех поездов
//вывод данных о конкретном поезде(по номеру поезда)
//метод для формирования vector с поездами, соответствующими передаваемому в метод направлению(конечная станция) - Метод возвращает вектор с отобранными поездами
//отсортировать поезда по времени отправления(через стандартную функцию sort это будет + )


int main()
{
	setlocale(LC_ALL, "rus");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	srand(time(NULL));
	MENU menu(3, 18, Black, LightCyan);
	menu.setColorText_Y(Black);
	menu.setColorBackGround_Y(LightGray);
	menu.setName_X_list(0, "ЧТЕНИЕ ДАННЫХ");
	menu.setName_X_list(1, "ВВОД ДАННЫХ");
	menu.setName_X_list(2, "ВЫХОД");
	menu.setCount_Y_Slots(0, 3);
	menu.setCount_Y_Slots(1, 4);
	menu.setCount_Y_Slots(2, 0);

	menu.setName_Y_list(0, 0, "Вывести список поездов");
	menu.setName_Y_list(0, 1, "Вывести данные о поезде");
	menu.setName_Y_list(0, 2, "Вывести список поездов по станции назначения");

	menu.setName_Y_list(1, 0, "Ввести данные о новом поезде");
	menu.setName_Y_list(1, 1, "Удалить поезд");
	menu.setName_Y_list(1, 2, "Сформировать список поездов по станции назначения");
	menu.setName_Y_list(1, 3, "Отсортировать по времени отправления");

	// Переменные меню
	size_t select(0);
	size_t lastmenu(0);
	size_t lastmenu_Y(0);
	bool flag(false);
	

	TrainStation station_01;
	vector <Train> selected_trains;

	int def_size = 10;
	int temp;
	station_01.TuTu_lair(def_size);

	string search;

	do
	{
		select = menu.SelectMenuItem(lastmenu, lastmenu_Y, flag);
		cleanZone(0, 6, 20, 110);
		// Вывод данных поездов на экран
		if (select == 101)
		{
			station_01.showTrains();
		}
		// Вывод данных о поезде
		if (select == 102)
		{
			cout << "Введите номер поезда: ";
			getline(cin, search);
			station_01.getTrainInfo(station_01.getNamePosition(search));
		}
		// Вывод списка поездов по станции следования
		if (select == 103)
		{
			station_01.showTrains(selected_trains);
		}

		//Добавление поезда
		if (select == 201)
		{
			station_01.setNew_train();
		}
		// Удаление поезда
		if (select == 202)
		{
			cout << "Введите позицию от 1 до "; cout << station_01.size(); cout << " для удаления: ";
			cin >> temp;
			station_01.deleteTrain(temp);
		}
		//Формирование списка поездов по станции следования
		if (select == 203)
		{
			cout << "Введите название станции: ";
			system("chcp 1251 > NUL");
			getline(cin, search);
			system("chcp 866 > NUL");
			selected_trains = station_01.searchBy_station(search);
		}
		// Сортировка поездов по времени отправления
		if (select == 204)
		{
			station_01.sortTrainBy_timedeparture();
		}

		// Вспомогательные переменные для фиксирования выбранной позиции меню
		if (select < 101)
		{
			lastmenu = select;
		}
		else
		{
			lastmenu = select / 100;
			lastmenu_Y = select % (100 * lastmenu);
			flag = true;
		}
	} while (select != menu.getSizeX());
	return 0;
}
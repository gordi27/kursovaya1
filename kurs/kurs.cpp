#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

/*********************************************************************
 *              П Р О Т О Т И П Ы    Ф У Н К Ц И Й                   *
 *********************************************************************/
void StartInput(); // начальное заполнение списка студентов из файла
void Delete(int); // удаление студентов из файла
void NewStudent(); // добавление нового студента в список
void Clear(); // удаление всех элементов списка
void Print(int); // вывод списка на экран или в файл
void Sort(); // сортировка списка

/*********************************************************************
 *              С Т Р У К Т У Р А    Д А Н Н Ы Х                     *
 *********************************************************************/
struct StudentsBase
{
	char student_name[100]; // ФИО студента
	char group[100]; // номер группы
	char brith_date[100]; // дата рождения
	char home_address[100]; // домашний адрес
	int admission_year; // год поступления 
	char session_results[100]; // результаты сессий

	// указатели на следующий и предыдущий элементы списка
	struct StudentsBase* next = NULL;
	struct StudentsBase* prev = NULL;
};

/*******************************************************************
 *           Г Л О Б А Л Ь Н Ы Е   П Е Р Е М Е Н Н Ы Е             *
 *******************************************************************/
StudentsBase* head = NULL; // указатель на начальный элемент списка
StudentsBase* last = NULL; // указатель на последний элемент списка

StudentsBase* current; // указатель на текущий элемент списка

StudentsBase* q; // вспомогательный указатель для вставки и удаления
StudentsBase* p; // вспомогательный указатель для сортировки

// начальное заполнение списка студентов из файла
void StartInput()
{
	// открытие файла для чтения
	FILE* f_in;
	f_in = fopen("Base.txt", "r");

	char char_array[256];
	char int_array[100];

	int i;
	int q;

	// проверка на наличие файла
	if (f_in == NULL)
	{
		cout << "\nФайл не найден!";
	}

	else
	{
		// чтение данных и заполнение файла
		while (fgets(char_array, 256, f_in) != NULL)
		{
			current = new StudentsBase; // выделение памяти для нового студента

			q = 0;
			i = 0;

			// чтение и добавление ФИО студента
			while (char_array[i] != ';')
			{
				current->student_name[q] = char_array[i];
				i++;
				q++;
			}
			current->student_name[q] = '\0';

			q = 0;
			i++;

			// чтение и добавление номера группы
			while (char_array[i] != ';')
			{
				current->group[q] = char_array[i];
				i++;
				q++;
			}
			current->group[q] = '\0';

			q = 0;
			i++;

			// дата рождения
			while (char_array[i] != ';')
			{
				current->brith_date[q] = char_array[i];
				i++;
				q++;
			}
			current->brith_date[q] = '\0';

			q = 0;
			i++;

			// домашний адрес
			while (char_array[i] != ';')
			{
				current->home_address[q] = char_array[i];
				i++;
				q++;
			}
			current->home_address[q] = '\0';

			q = 0;
			i++;

			// результаты сессий
			while (char_array[i] != ';')
			{
				current->session_results[q] = char_array[i];
				i++;
				q++;
			}
			current->session_results[q] = '\0';

			q = 0;
			i++;

			// год поступление
			while (char_array[i] != ';')
			{
				int_array[q] = char_array[i];
				i++;
				q++;
			}
			int_array[q] = '\0';
			current->admission_year = atoi(int_array);

			// добавление студента в конец списка
			if (head == NULL) // если список пустой
			{
				// текущий элемент становится начальным и конечным
				head = current;
				last = head;
			}

			else
			{
				last->next = current;
				current->prev = last;
				last = current; // текущий элемент становится последним в списке
			}

			// очистка буфера ввода
			for (int i = 0; i != 256; i++)
			{
				char_array[i] = '\0';
			}
		}
		fclose(f_in);
	}
}//StartInput

// добавление нового студента в список
void NewStudent()
{
	current = new StudentsBase;

	// ввод данных
	cout << "\nФИО студента: ";
	cin.ignore();
	cin.getline(current->student_name, 100);
	cout << "Номер группы: ";
	cin.getline(current->group, 100);
	cout << "Дата рождения: ";
	cin.getline(current->brith_date, 100);
	cout << "Домашний адрес: ";
	cin.getline(current->home_address, 100);
	cout << "Результат сессий: ";
	cin.getline(current->session_results, 100);

	char int_array[100];
	cout << "Год поступления: ";
	cin.getline(int_array, 100);
	current->admission_year = atoi(int_array);

	// добавление студента в конец списка
	if (head == NULL) // список пуст
	{
		// новый студент становится начальным
		head = current;
		// и последним элементом списка
		last = head;
	}

	else
	{
		last->next = current;
		current->prev = last;
		last = current; // новый студент становится последним в списке
	}
}//NewStudent

// удаление студента из списка
void Delete(int num)
{
	int i = 1;
	int flag = 0; // удален ли студент (1 - да, 0 - нет)

	current = head;

	// поиск студента по номеру в писке
	while (i != num)
	{
		// перемещаем, пока не достигнем эл-та с нужным номером
		current = current->next;
		i++;
	}

	// удаление из списка
	if (current == head) // является ли удаляемый начальным элементом
	{
		head = current->next; // обновление указателя head на следующий элемент
		head->prev = NULL; // обнуление prev у нового нач-го элемента
		flag = 1;
	}

	if (current == last) // является ли удаляемый последним элементов
	{
		last = current->prev; // обновление указателя head на предыдущий элемент
		last->next = NULL; // обнуление next у нового посл-го элемента
		flag = 1;
	}

	if (flag == 0) // студент ни начальный, ни последний элемент
	{
		/* указатели prev и next переставляются так,
		чтобы удаленный элемент больше не участвовал в связи
		между соседними элементами списка */
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}

	delete current;
}//Delete

// вывод списка на консоль или в файл
void Print(int command)
{
	int type; // тип вывода (консоль/файл)
	cout << "Выберите тип вывода:\n1. На консоль\n2. В файл\n";
	cout << "Ввод: \n";
	cin >> type;

	int i = 1;

	// проверка наличия студентов в списке
	if (head == NULL)
	{
		cout << "\nСписок пуст! \n";
	}

	else
	{
		current = head; // текущий элемент становится начальным

		// вывод на консоль
		if (type == 1)
		{
			while (current)
			{
				cout << '\n';
				cout << i << ". " << current->student_name << " (" << current->group << "):";
				cout << "\n Дата рождения: " << current->brith_date;
				cout << "\n Домашний адрес: " << current->home_address;
				cout << "\n Результат сессий: " << current->session_results;
				cout << "\n Год поступления: " << current->admission_year;


				current = current->next; // переход к следующему элементу
				i++;
			}
		}

		// вывод в файл
		else if (type == 2)
		{
			FILE* f_out;
			f_out = fopen("Output.txt", "a"); // открытие файла для добавления данных

			current = head; // возвращение указателя в начало списка

			while (current)
			{
				fprintf(f_out, "\n%d. %s (%s):", i, current->student_name, current->group);
				fprintf(f_out, "\nДата рождения: %s", current->brith_date);
				fprintf(f_out, "\nДомашний адрес: %s", current->home_address);
				fprintf(f_out, "\nРезультат сессий: %s", current->session_results);
				fprintf(f_out, "\nГод поступления: %d", current->admission_year);

				current = current->next; // переход к следующему элементу
				i++;
			}
			fclose(f_out);
		}
		cout << "\n";
	}
}//Print

// сортировка списка
void Sort()
{
	int command;
	cout << "\nПо какому критерию сортировать?\n1. По фамилии\n2. По году поступления\n3. По номеру группы\n4. По результату сессий\n";
	cout << "Ввод: \n";
	cin >> command;;

	// сортировка по фамилии (методом пузырка)
	if (command == 1)
	{
		p = NULL;
		while (p != head)
		{
			current = head;
			while (current->next != p)
			{
				if (strcmp(current->student_name, current->next->student_name) > 0) // сравнение двух строк
				{
					q = current->next;

					q->prev = current->prev;
					if (current->prev != NULL) current->prev->next = q;
					else head = q;

					current->next = q->next;
					if (q->next != NULL) q->next->prev = current;
					else last = current;

					q->next = current;
					current->prev = q;

					continue;
				}
				current = current->next;
			}
			p = current;
		}
	}

	// сортировка по году поступления
	if (command == 2)
	{
		p = NULL;
		while (p != head)
		{
			current = head;
			while (current->next != p)
			{
				if (current->admission_year > current->next->admission_year)
				{
					q = current->next;

					q->prev = current->prev;
					if (current->prev != NULL) current->prev->next = q;
					else head = q;

					current->next = q->next;
					if (q->next != NULL) q->next->prev = current;
					else last = current;

					q->next = current;
					current->prev = q;

					continue;
				}
				current = current->next;
			}
			p = current;
		}
	}

	// сортировка по номеру группы
	if (command == 3)
	{
		p = NULL;
		while (p != head)
		{
			current = head;
			while (current->next != p)
			{
				if (strcmp(current->group, current->next->group) > 0)
				{
					q = current->next;

					q->prev = current->prev;
					if (current->prev != NULL) current->prev->next = q;
					else head = q;

					current->next = q->next;
					if (q->next != NULL) q->next->prev = current;
					else last = current;

					q->next = current;
					current->prev = q;

					continue;
				}
				current = current->next;
			}
			p = current;
		}
	}

	// сортировка по результатам сессии
	if (command == 4)
	{
		p = NULL;
		while (p != head)
		{
			current = head;
			while (current->next != p)
			{
				if (strcmp(current->session_results, current->next->session_results) > 0)
				{
					q = current->next;

					q->prev = current->prev;
					if (current->prev != NULL) current->prev->next = q;
					else head = q;

					current->next = q->next;
					if (q->next != NULL) q->next->prev = current;
					else last = current;

					q->next = current;
					current->prev = q;

					continue;
				}
				current = current->next;
			}
			p = current;
		}
	}
}//Sort

// удаление всех элементов списка
void Clear()
{
	while (head) // пока есть хотя бы один элемент
	{
		current = head->next; // сохранение указателя на следующий элемент после нач-го
		delete head;
		head = current; // обновление нач-го элемента
	}
	last = NULL; // после удаления всех элементов последнего больше нет
}//Clear


int main()
{
	system("chcp 1251 > nul");

	int command; // действие зависит от выбора номера команды

	do
	{
		// вывод меню
		cout << "*****Учет студентов в деканате*****\n\n";
		cout << "Выберите действие: \n1.Вывод базы\n2.Добавление студента в базу\n3.Заполнение базы из файла\n4.Сортировка\n5.Удаление студента из базы\n6.Очистка базы данных\n0.Выход\n";
		cout << "Ввод: \n";

		// выбор действия
		cin >> command;

		// вывод базы
		if (command == 1)
		{
			cout << "\nВывод на экран:";
			Print(2);
		}

		// добавление студента в базу
		if (command == 2)
		{
			cout << "\n\nДобавление нового студента в базу";
			NewStudent();
			cout << "\nСтудент добавлен в базу";
		}

		// заполнение базы из файла
		if (command == 3)
		{
			StartInput();
		}

		// сортировка
		if (command == 4)
		{
			Sort();
		}

		// удаление студента из базы
		if (command == 5)
		{
			if (head == NULL)
				cout << "Список пуст!";
			else
			{
				cout << "\nКакого студента удалить из базы?";
				Print(1);
				cout << "\n\nВвод: ";
				int student_to_delete;
				cin >> student_to_delete;
				Delete(student_to_delete);
			}
		}

		// очистка базы данных
		if (command == 6)
		{
			cout << "Очистка базы данных";
			Clear();
			cout << "\n\nБаза данных очищена";
		}

		cout << "\n";
	} while (command != 0);

	Clear();
}//main

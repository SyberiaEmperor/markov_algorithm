#include"terminal.h"
#include<codecvt>

int enter_menu()
{
	cout << "1.Установить схему" << endl;
	cout << "2.Установить схему из файла" << endl;
	cout << "3.Ввести слово" << endl;
	cout << "4.Помощь" << endl;
	cout << "5.Выйти" << endl;

	string s = "3";
	cin >> s;

	int n = stoi(s);
	return n;
}

void set_system(istream& input_stream, markov_engine& me, parser& p)
{
	cout << "Введите размерность схемы: " << endl;
	string s = "1";
	cin >> s;

	int n = stoi(s);

	if (n < 0)
		throw invalid_argument("Некорректный ввод");

	vector<string> input = vector<string>();

	for (int i = 0; i < n; i++)
	{
		cout << i << ":" << endl;
		string str = "";
		input_stream >> str;
		input.push_back(str);
	}

	me.set_system(p.get_subs(input));

	cout << "Схема успешно установлена" << endl;
}

void set_system_from_file(string& filename, markov_engine& me, parser& p)
{
	ifstream ifs(filename);

	if (!ifs)
		throw invalid_argument("Не удаётся открыть файл");

	vector<string> input = vector<string>();

	int count = 0;

	while (ifs)
	{
		string str = "";

		ifs >> str;

		if (!count && str != "<")
			throw invalid_argument("Неверный формат файла");

		if (str == ">")
			break;

		if (count > 0)
			input.push_back(str);

		count++;
	}

	ifs.close();

	me.set_system(p.get_subs(input));
}

void read_file(markov_engine& me, parser& p)
{
	string filename = "";

	cout << "Введите имя файла: " << endl;
	cin >> filename;

	if (filename.find(".txt")==string::npos)
		throw invalid_argument("Некорректный ввод");

	set_system_from_file(filename, me, p);

	cout << "Схема успешно установлена" << endl;
}

void enter_word(markov_engine& me, parser& p)
{
	cout << "Введите слово: " << endl;
	string str = "";
	cin.clear();
	cin.ignore();
	getline(cin, str);
	
	cout << "Результат: " << me.apply_word(p.check_word(str)) << endl;
}

void help_m()
{
	ifstream ifs("help.txt");
	ifs.imbue(locale(ifs.getloc(), new codecvt_utf8<wchar_t>));
	while (ifs)
	{
		string str;
		getline(ifs, str);
		cout << str << endl;
	}
}

void terminal(istream& input_stream)
{
	int end = false;

	parser p;
	markov_engine me;

	while (!end)
	{
		try
		{
		int answer = enter_menu();

		switch (answer)
		{
		case 1:
			set_system(input_stream, me, p);
			break;
		case 2:
			read_file(me, p);
			break;
		case 3:
			enter_word(me,p);
			break;
		case 4:
			help_m();
			break;
		case 5:
			end = true;
			break;
		default:
			cin.clear();
			cerr << "Некорректный ввод" << endl;
			break;
		}


		}
		catch (invalid_argument e)
		{
			cerr << e.what() << endl;
		}
		catch (exception e)
		{
			cerr << "Некорректный ввод" << endl;
		}
	}
}
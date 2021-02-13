#include"terminal.h"
#include<codecvt>

int enter_menu()
{
	cout << "1.���������� �����" << endl;
	cout << "2.������ �����" << endl;
	cout << "3.������" << endl;
	cout << "4.�����" << endl;

	string s = "3";
	cin >> s;

	int n = stoi(s);
	return n;
}

void set_system(istream& input_stream, markov_engine& me, parser& p)
{
	cout << "������� ����������� �����: " << endl;
	string s = "1";
	cin >> s;

	int n = stoi(s);

	if (n < 0)
		throw invalid_argument("������������ ����");

	vector<string> input = vector<string>();

	for (int i = 0; i < n; i++)
	{
		cout << i << ":" << endl;
		string str = "";
		input_stream >> str;
		input.push_back(str);
	}

	me.set_system(p.get_subs(input));

	cout << "����� ������� �����������" << endl;
}

void enter_word(markov_engine& me, parser& p)
{
	cout << "������� �����: " << endl;
	string str = "";
	cin.clear();
	cin.ignore();
	getline(cin, str);
	
	cout << "���������: " << me.apply_word(p.check_word(str)) << endl;
}

void help_m()
{
	wifstream ifs("help.txt");
	ifs.imbue(locale(ifs.getloc(), new codecvt_utf8<wchar_t>));
	while (ifs)
	{
		wstring str;
		getline(ifs, str);
		wcout << str << endl;
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
			enter_word(me,p);
			break;
		case 3:
			help_m();
			break;
		case 4:
			end = true;
			break;
		default:
			cin.clear();
			cerr << "������������ ����" << endl;
			break;
		}


		}
		catch (invalid_argument e)
		{
			cerr << e.what() << endl;
		}
		catch (exception e)
		{
			cerr << "������������ ����" << endl;
		}
	}
}
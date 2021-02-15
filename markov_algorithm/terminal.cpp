#include"terminal.h"
#include<codecvt>

int enter_menu()
{
	cout << "1.���������� �����" << endl;
	cout << "2.���������� ����� �� �����" << endl;
	cout << "3.������ �����" << endl;
	cout << "4.������" << endl;
	cout << "5.�����" << endl;

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

void set_system_from_file(markov_engine& me, parser& p)
{
	string filename = "";

	cout << "������� ��� �����: " << endl;
	cin >> filename;

	if (filename.find(".txt")==string::npos)
		throw invalid_argument("������������ ����");

	ifstream ifs(filename);

	if (!ifs)
		throw invalid_argument("�� ������ ������� ����");

	vector<string> input = vector<string>();

	int count = 0;

	while (ifs)
	{
		string str = "";

		ifs >> str;

		if (!count && str != "<")
			throw invalid_argument("�������� ������ �����");

		if (str == ">")
			break;

		if(count>0)
		input.push_back(str);

		count++;
	}

	ifs.close();

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
			set_system_from_file(me, p);
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
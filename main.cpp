#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Date_t //���� � �����������, ����� �� ������ �� ���������� �����, ������� � �������� � ����� � ��������
{
	Date_t(unsigned short day = 0, unsigned short month = 0, unsigned short year = 0) : day(day), month(month), year(year) {} //������� �� �����������
	string GetDate() //��������� �� GetDate
	{
		string ret = "";
		stringstream ss;
		if (this->day < 10)
		{
			ss << 0;
		}
		ss << this->day << '/';
		if (this->month < 10)
		{
			ss << 0;
		}
		ss << this->month << '/' << this->year;
		ret = ss.str();
		return ret;
	}

private:
	unsigned short day, month, year; // ������ �� ����������� 
};

struct Time_t  // ����� ��������� � ����� ���������� ����������������� �� ��������
{
	Time_t(unsigned short hour = 0, unsigned short minute = 0) : hour(hour), minute(minute) {}
	string GetTime()
	{
		string ret = "";
		stringstream ss;
		ss << this->hour << ':';
		if (this->minute < 10)
		{
			ss << 0;
		}
		ss << this->minute;
		ret = ss.str();
		return ret;
	}

private:
	unsigned short hour, minute; 
};


class Concert
{
public:
	Concert(string city = "", Date_t date = Date_t(), Time_t startTime = Time_t(), Time_t duration = Time_t(), vector<string> songs = vector<string>()) : city(city), date(date), startTime(startTime), duration(duration), songs(songs) {}
	
	string GetCity()
	{
		return this->city;
	}

	Date_t GetDate()
	{
		return this->date;
	}

	Time_t GetStartTime()
	{
		return this->startTime;
	}

	Time_t GetDuration()
	{
		return this->duration;
	}

	vector<string>& GetSongs() // ��������� ������ �� �� ���� ��-����� �� ������ � �������
	{
		return this->songs;
	}

private: // ����� �� �������� �� ���� �������
	string city;
	Date_t date;
	Time_t startTime, duration;
	vector<string> songs; //�������� � �����
};

int main() // ������ �� ������ �������
{
	Concert concerts[5]{ // ���������� �����-����� �� ���� �������
		Concert("Sofia", Date_t(1, 10, 2018), Time_t(10, 0), Time_t(6, 0), {"Jar", "Zemya", "..."}),
		Concert("Plovdiv", Date_t(3, 10, 2018), Time_t(11, 0), Time_t(5, 30), {"Zemya", "Chyma", "..."}),
		Concert("Varna", Date_t(5, 10, 2018), Time_t(12, 0), Time_t(5, 0), {"Chyma", "Garvan", "..."}),
		Concert("Burgas", Date_t(7, 10, 2018), Time_t(13, 0), Time_t(5, 0), {"Garvan", "Nebe", "..."}),
		Concert("Veliko Tarnovo", Date_t(9, 10, 2018), Time_t(14, 0), Time_t(5, 30), {"Nebe", "Pepel", "..."})
	};
	map<string, vector<unsigned short>> songsToConcert; //�������� ����� �� ���� map ��� ������������ string � vector �� ����������� �����
	for (unsigned short i = 0; i < 5; i++) //������� ����� ����� ��������
	{
		for (vector<string>::iterator iter = concerts[i].GetSongs().begin(); iter != concerts[i].GetSongs().end(); iter++) //������� ����� ����� ����� ����� �� �� ������� �� �������� [i] (*iter � ����� �� �������)
		{
			if (songsToConcert.find(*iter) == songsToConcert.end()) //��� ����� �� ������� �� � �������� � map-�
			{
				songsToConcert.insert(make_pair(*iter, vector<unsigned short>({ i }))); //������ ����� �� ������� � map-� ���� ���������� � vector � ���� ������� (������ �� �������� (i))
			}
			else // ��� ���� � �������� � map-�
			{
				if (find(songsToConcert.find(*iter)->second.begin(), songsToConcert.find(*iter)->second.end(), i) == songsToConcert.find(*iter)->second.end()) //������ �� �������� �� ��������� ��� vector-�
				{
					songsToConcert.find(*iter)->second.push_back(i); //������ ������ �� �������� �� �������� �����
				}
			}
		}
	}
	bool exit_while = false;
	while (exit_while == false)
	{
		int choice = -1;
		cout << "Get info by:\n1) City\n2) Song name\n\n0) Exit\n\n"; // ������ ����
		cin >> choice;
		while (choice >= 0 && choice <= 2)
		{
			if (choice == 1) //�������, ����� ������ �� ����������� �� ������� � ��� ���� ���� � �������� � ����� � ����������������� ��
			{
				choice = -1;
				while (choice < 0 || choice > 5)
				{
					cout << "\nChoose city:\n";
					for (unsigned short i = 0; i < 5; i++)
					{
						cout << i + 1 << ") " << concerts[i].GetCity() << '\n';
					}
					cout << "\n0) Back\n\n";
					cin >> choice;
				}
				if (choice-- == 0) //������ �� ������
				{
					break;
				}
				cout << "\nCity: " << concerts[choice].GetCity() << "\nDate: " << concerts[choice].GetDate().GetDate() << "\nStarts at: " << concerts[choice].GetStartTime().GetTime() << "\nDuration: " << concerts[choice].GetDuration().GetTime();
			}
			else if (choice == 2) //�������, ����� ������ �� ����������� �� ������� ��� ����� � ��� ���� �� �� ���
			{
				choice = -1;
				while (choice < 0 && choice > songsToConcert.size())
				{
					cout << "\nChoose song:\n"; 
					unsigned short n = 1;
					for (map<string, vector<unsigned short>>::iterator iter = songsToConcert.begin(); iter != songsToConcert.end(); iter++) //������ �� ������� ������� �� �������
					{
						cout << n++ << ") " << iter->first << '\n'; //������� ������� �� �������
					}
					cout << "\n0) Back\n\n";
					cin >> choice;
				}
				if (choice == 0) //������ �� ������
				{
					break;
				}
				map<string, vector<unsigned short>>::iterator _iter = songsToConcert.begin(); //��������� ��������� �� ��������� �����
				for (unsigned short i = 0; i < choice - 1; i++)
				{
					_iter++;
				}
				cout << "Song is going to be played in:\n";
				for (vector<unsigned short>::iterator iter = _iter->second.begin(); iter != _iter->second.end(); iter++) //�������� ������ ������� / �������� � ����� �� �� ������� �������
				{
					cout << concerts[*iter].GetCity() << '\n'; // ������� �� ����������� ��� ����� � ��� ���� �� �
				}
			}
			else
			{
				exit_while = true;
			}
			choice = -1;
			cout << "\n\n";
		}
	}
	return 0;
}

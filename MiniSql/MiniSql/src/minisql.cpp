#include <iostream>
#include <string>
#include <fstream>
#include "Exception.h"
#include "InterpreterManager\Interpreter.h"
#include "CatalogManager\CatalogManager.h"

using namespace std;

int main()
{
	cout << "---------------MiniSql---------------" << endl;

	Interpreter it;

	/*string sql;
	ifstream in("student.txt");
	while (1)
	{
		string line;
		getline(cin, line);
		if (line == "quit")
			break;
		sql += (line + ' ');
		if (sql.find(';') < sql.length())
		{
			sql.erase(sql.end() - 2);
			cout << "------------------" << endl << sql << endl;
			try
			{
				it.executeSql(sql);
			}
			catch (exception e)
			{
				cout << e.what() << endl;
			}
			sql.clear();
		}
	}*/
	RECORDBUFFER buffer;

	it.setRecordBuffer(buffer);
	cout << "gansidui@minisql--->";
	
	string sql;
	while (1)
	{
		string line;
		getline(cin, line);

		sql += (line + ' ');
		//find a semicolon
		if (line.find_first_of(';') < line.size())
		{
			while (sql.back() == ' ' || sql.back() == '\t')
				sql = sql.substr(0, sql.length() - 1);
			if (sql.back() != ';')
				cout << "ERROR: There is some characters at the end of the sql after the semicolon;" << endl;
			else
			{
				try
				{
					sql = sql.substr(0, sql.length() - 1);
					cout << "for test: " << sql << endl;
					it.executeSql(sql);
					for (auto vec : buffer)
					{
						for (auto key : vec)
							cout << key << "  ";
						cout << endl;
					}
					cout << buffer.size() << endl;
					buffer.clear();
				}
				catch (exception& e)
				{
					cout << e.what() << endl;
				}
				catch (Quit q)
				{
					return 0;
				}
			}
			cout << "gansidui@minisql--->";
			sql.clear();
		}
		else
			cout << "--->";
	}
}
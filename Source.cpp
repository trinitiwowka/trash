//
//  main.cpp
//  yana
//
//  Created by Yana on 10/16/16.
//  Copyright © 2016 Yana. All rights reserved.
//
// A*(B*C)  or  (A*B)*C

#include <iostream>
#include <string>
using namespace std;

enum SIGN
{
	DIZ,
	CON,
	IMPL,
	EQUIV
};
string Input;
string const char_sign("1234");
char  A_char[] = { "00001111" };
char  B_char[] = { "00110011" };
char  C_char[] = { "01010101" };

bool check_input_abc(string& _inp)
{
	string tmp[]= { "aA","bB","cC" };
	int res = 0;
	for (size_t i = 0; i < 2; i++)
	{
		if (_inp.find(tmp[0][i]) != string::npos)
			res++;
		if (_inp.find(tmp[1][i]) != string::npos)
			res++;
		if (_inp.find(tmp[2][i]) != string::npos)
			res++;
	}
	if (res == 3)
		return true;
	return false;
}
int check_variant(string &_inp)
{
	if (_inp.find(")") == _inp.size() - 1)
		return 1;
	return 2;
}
bool find_symbol(string& _string, SIGN* _current_sign)
{
	int tmp_counter = 0;

	for (int i = 0; i<_string.length(); i++)
	{

		if (_string[i] == char_sign[0]) {

			_current_sign[tmp_counter] = DIZ;
			tmp_counter++;
		}

		if (_string[i] == char_sign[1]) {

			_current_sign[tmp_counter] = CON;
			tmp_counter++;
		}

		if (_string[i] == char_sign[2]) {

			_current_sign[tmp_counter] = IMPL;
			tmp_counter++;
		}

		if (_string[i] == char_sign[3]) {

			_current_sign[tmp_counter] = EQUIV;
			tmp_counter++;
		}
	}
	if (tmp_counter != 2)
		return false;
	return true;
}
bool check_input(string & _input)
{
	auto find1 = _input.find("(");
	auto find2 = _input.find(")");
	if (find1 != string::npos)
		if (find2 != string::npos)
			return true;

	return false;
}

void draw(string& _input, const SIGN* _current_sign, int variant)
{
	//cout<<_input;
	cout << "A  B  C  " << _input << endl;
	int A = 0, B = 0, C = 0;
	bool result = false;

	//A*(B*C)  or  (A*B)*C

	for (int i = 0; i<8; ++i)
	{

		A = A_char[i] - '0';
		B = B_char[i] - '0';
		C = C_char[i] - '0';

		if (variant == 1)
		{
			switch (_current_sign[1])
			{
			case DIZ:
			{
				result = B || C;
				break;
			}
			case CON:
			{
				result = B&&C;
				break;
			}
			case IMPL:
			{
				if (B == 1 && C == 0)
					result = 0;
				else
					result = 1;
				break;
			}
			case EQUIV:
			{
				result = (B == C);
				break;
			}

			default:
				break;
			}

			switch (_current_sign[0])
			{
			case DIZ:
			{
				result = result || A;
				break;
			}
			case CON:
			{
				result = result&&A;
				break;
			}
			case IMPL:
			{
				if (A == 1 && result == 0)
					result = 0;
				else
					result = 1;
				break;
			}
			case EQUIV:
			{
				result = (result == A);
				break;
			}
			default:
				break;
			}

		}

		if (variant == 2)
		{
			switch (_current_sign[1])
			{
			case DIZ:
			{
				result = A || B;
				break;
			}
			case CON:
			{
				result = A&&B;
				break;
			}
			case IMPL:
			{
				if (A == 1 && B == 0)
					result = 0;
				else
					result = 1;
				break;
			}
			case EQUIV:
			{
				result = (A == B);
				break;
			}

			default:
				break;
			}

			switch (_current_sign[0])
			{
			case DIZ:
			{
				result = result || C;
				break;
			}
			case CON:
			{
				result = result&&C;
				break;
			}
			case IMPL:
			{
				if (result == 1 && C == 0)
					result = 0;
				else
					result = 1;
				break;
			}
			case EQUIV:
			{
				result = (result == C);
				break;
			}
			default:
				break;
			}

		}
		cout << A << "  " << B << "  " << C << "  " << result << endl;
	}
	cout << _input;


}


int main(int argc, const char * argv[]) {

	SIGN current_sign[3];
	getline(cin, Input);

	//cout<<endl<<endl<<Input<<endl<<endl;
	if (!check_input_abc(Input))
	{
		cout << "ERROR NOT A,B,C";
		exit(3);
	}
	if (!check_input(Input))
	{
		cout << "ERROR wrong expression";
		exit(2);
	}
	if (!find_symbol(Input, current_sign))
	{
		cout << "ERROR Symbol";
		exit(1);
	}
	int variant = check_variant(Input);
	draw(Input, current_sign, variant);
	system("pause");
	return 0;
}

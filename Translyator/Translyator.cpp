﻿#include <fstream>
#include <string>
#include <iostream>
#include <string>
#include <cstring>  
#include <vector>
#include <map>

using namespace std;
#define NLeck 30

int mVar;
map < string, int > Init_int;
map < string, int*> Init_int1;
map < string, float > Init_float;


// -1 - не зарезервированные, 0 - число, 1 - лексема(зарезервированная)

struct ops {
	float val;
	int num;
	string s;
	ops* next;
	ops* prv;

	ops() {
		val = 0;
		s = "";
		next = NULL;
		prv = NULL;
	}
};


struct bib {
	float val;
	string s;
	int i;
	int j;
	int type;
	bib* next;

	bib() {
		val = 0;
		s = "";
		i = 0;
		j = 0;
		next = NULL;
	}
};


void proc(int v) {
	switch (v) {
	case 1:
		mVar = 1;
		break;
	case 2:
		mVar = 2;
		break;
	case 3:
		mVar = 3;
		break;
	case 4:
		mVar = -1;
		break;
	case 5:
		break;
	}
	
}


int Variable(string s = "", int k = 0) {
	if (Init_int[s] || Init_int1[s] || Init_float[s]) { cout << "Переменная уже объявлена"; return -1; }
	switch (mVar) {
	case 1:

		Init_int[s] = 0;
		break;

	case 2:
		Init_int1[s] = new int[k];
		break;
	case 3:
		Init_float[s] = 0;
		break;
	}
}


int add(ops*& P, int v = 0, string s = "", float f = 0) {
	if (s != "") {
		if (v == 1)
		{
			ops* a = new ops;
			a->s = s;
			a->next = NULL;
			a->prv = P;
			P->next = a;
		}
		else if (Init_int[s] || Init_int1[s] || Init_float[s]) {
			ops* a = new ops;
			a->s = s;
			a->next = NULL;
			a->prv = P;
			P->next = a;
		}
		else return -1;
	}
	else {
		ops* a = new ops;
		a->val = f;
		a->next = NULL;
		a->prv = P;
		P->next = a;
	}
	P = P->next;
}





bool p(bib*& C, ops*& P);
bool r(bib*& C, ops*& P);
bool m(bib*& C, ops*& P);
bool b(bib*& C, ops*& P);
bool w(bib*& C, ops*& P);
bool a(bib*& C, ops*& P);
bool e(bib*& C, ops*& P);
bool j(bib*& C, ops*& P);
bool q(bib*& C, ops*& P);
bool c(bib*& C, ops*& P);
bool d(bib*& C, ops*& P);
bool s(bib*& C, ops*& P);
bool u(bib*& C, ops*& P);
bool t(bib*& C, ops*& P);
bool v(bib*& C, ops*& P);
bool f(bib*& C, ops*& P);
bool g(bib*& C, ops*& P);
bool h(bib*& C, ops*& P);
bool z(bib*& C, ops*& P);


/*bool s0(bib*& C, ops*& P) {
	if (p(C, P)) {
		if (C->s == "┴") {
			C = C->next;
			return true;
		}
		else return false;
	}
	else return false;
}*/


bool p(bib*& C, ops*& P) {
	bool boo;
	if (C->s == "int") {
		add(P, 1);
		C = C->next;
		if (r(C, P) && p(C, P)) {
			boo = true;
		}
		else boo = false;
	}
	else if (C->s == "float") {
		add(P, 3);
		C = C->next;
		if (r(C, P) && p(C, P)) {
			boo = true;
		}
		else boo = false;
	}
	else if (C->s == "int1") {
		add(P, 2);
		C = C->next;
		if (b(C, P) && p(C, P)) {
			boo = true;
		}
		else boo = false;
	}
	else if (C->s == "{") {
		add(P, 4);
		C = C->next;
		if (a(C, P) && q(C, P) && (C->s == "}")) {
			add(P, 5);
			/*if (C->next) {
				C = C->next; p(C, P);
			}*/
			boo = true;
		}
		else boo = false;
	}
	else boo = false;

	return boo;
}


bool r(bib*& C, ops*& P) {
	if (C->type == -1) {
		add(P, 6, C->s);
		C = C->next;

		if (m(C, P)) {
			return true;
		}
		else return false;
	}
	else return false;
}


bool m(bib*& C, ops*& P) {
	if (C->s == ",") {
		C = C->next;
		if (C->type == -1) {
			add(P, 6, C->s);
			C = C->next;
			if (m(C, P)) {
				return true;
			}
			else return false;
		}
		else return false;
	}
	else if (C->s == ";") {
		C = C->next;
		return true;
	}
	else return false;
}


bool b(bib*& C, ops*& P) {
	if (C->type == -1) {
		string a = C->s;
		C = C->next;
		if (C->s == "[") {
			C = C->next;
			if (C->type == 0) {
				add(P, 6, a, C->val);
				C = C->next;
				if (C->s == "]") {
					C = C->next;
					if (w(C, P)) {
						return true;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}


bool w(bib*& C, ops*& P) {
	if (C->s == ",") {
		C = C->next;
		if (C->type == -1) {
			string a = C->s;
			C = C->next;
			if (C->s == "[") {
				C = C->next;
				if (C->type == 0) {
					add(P, 6, a, C->val);
					C = C->next;
					if (C->s == "]") {
						C = C->next;
						if (w(C, P)) {
							return true;
						}
						else return false;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if (C->s == ";") {
		C = C->next;
		return true;
	}
	else return false;
}


bool a(bib*& C, ops*& P) {
	bool boo = false;
	if (C->type == -1) {
		C = C->next; if (h(C, P) && C->s == "=") {
			add(P, 0, C->s);
			C = C->next;
			boo = s(C, P);
			if (boo) boo = q(C, P);
		}
		else  boo = false;
	}
	else if (C->s == "scan") {
		C = C->next;
		if (C->s == "(") {
			C = C->next;
			if (C->type == -1) {
				C = C->next;
				if (h(C, P) && C->s == ")") {
					C = C->next;
					boo = q(C, P);
				}
			}
		}
	}
	else if (C->s == "print") {
		C = C->next;
		if (C->s == "(") {
			C = C->next;
			if (s(C, P) && C->s == ")") {
				C = C->next;
				boo = q(C, P);
			}
		}
	}
	else if (C->s == "if") {
		C = C->next;
		if (c(C, P) && C->s == ":") {
			C = C->next;
			if (j(C, P) && e(C, P) && q(C, P)) boo = true;
		}
	}
	else if (C->s == "while") {
		C = C->next;
		if (c(C, P) && C->s == ":") {
			C = C->next;
			if (j(C, P) && z(C, P) && q(C, P)) boo = true;
		}
	}
	else if (C->s == "{") {
		C = C->next;
		if (a(C, P) && q(C, P) && C->s == "}") {
			C = C->next;
			boo = true;
		}
	}
	else return true;
	return boo;
}


bool e(bib*& C, ops*& P) {
	bool boo = true;
	if (C->s == "else") {
		C = C->next;
		if (j(C, P)) {
			boo = true;
		}
		else boo = false;
	}
	return boo;
}


bool j(bib*& C, ops*& P) {
	bool boo = false;
	if (C->type == -1) {
		C = C->next; if (h(C, P) && C->s == "=") {
			C = C->next;
			boo = s(C, P);
			if (boo) boo = z(C, P);
		}
		else  boo = false;
	}
	else if (C->s == "scan") {
		C = C->next;
		if (C->s == "(") {
			C = C->next;
			if (C->type == -1) {
				C = C->next;
				if (h(C, P) && C->s == ")") {
					C = C->next;
					boo = true;
				}
			}
		}
	}
	else if (C->s == "print") {
		C = C->next;
		if (C->s == "(") {
			C = C->next;
			if (s(C, P) && C->s == ")") {
				C = C->next;
				boo = true;
			}
		}
	}
	else if (C->s == "if") {
		C = C->next;
		if (c(C, P) && C->s == ":") {
			C = C->next;
			if (j(C, P) && e(C, P) && z(C, P)) boo = true;
		}
	}
	else if (C->s == "while") {
		C = C->next;
		if (c(C, P) && C->s == ":") {
			C = C->next;
			if (j(C, P) && z(C, P)) boo = true;
		}
	}
	else if (C->s == "{") {
		C = C->next;
		if (a(C, P) && q(C, P) && C->s == "}") {
			C = C->next;
			boo = true;
		}
	}
	else return true;
	return boo;
}


bool q(bib*& C, ops*& P) {
	bool boo = true;
	if (C->s == ";") {
		C = C->next;
		if (a(C, P) && q(C, P)) {
			boo = true;
		}
		else boo = false;
	}
	return boo;
}


bool c(bib*& C, ops*& P) {
	bool b = false;
	if (C->s == "(") {
		C = C->next; if (s(C, P) && C->s == ")") { C = C->next; b = true; }
	}
	else if (C->type == -1) { C = C->next;  if (h(C, P)) b = true; }
	else if (C->type == 0) { C = C->next; b = true; }
	else if (C->s == "-") { C = C->next;  if (g(C, P)) b = true; }
	else if (C->s == "+") {
		C = C->next;  if (g(C, P)) b = true;
	}
	if (b) b = v(C, P);
	if (b) b = u(C, P);
	if (b) b = d(C, P);
	return b;
}


bool d(bib*& C, ops*& P) {
	bool b = false;
	if (C->s == "<") { C = C->next; b = true; }
	else if (C->s == ">") { C = C->next; b = true; }
	else if (C->s == "<=") { C = C->next; b = true; }
	else if (C->s == ">=") { C = C->next; b = true; }
	else if (C->s == "!=") { C = C->next; b = true; }
	else if (C->s == "==") { C = C->next; b = true; }
	else if (C->s == "and") { C = C->next; b = true; }
	else if (C->s == "or") { C = C->next; b = true; }
	else { return true; }
	if (b) b = s(C, P);
	if (b) b = z(C, P);
	return b;
}


bool s(bib*& C, ops*& P) {
	bool b = false;
	if (C->s == "(") {
		C = C->next; if (s(C, P) && C->s == ")") { C = C->next; b = true; }
	}
	else if (C->type == -1) { C = C->next;  if (h(C, P)) b = true; }
	else if (C->type == 0) { C = C->next; b = true; }
	else if (C->s == "-") { C = C->next;  if (g(C, P)) b = true; }
	else if (C->s == "+") {
		C = C->next;  if (g(C, P)) b = true;
	}
	if (b) b = v(C, P);
	if (b) b = u(C, P);
	return b;
}


bool u(bib*& C, ops*& P) {
	if (C->s == "+") C = C->next;
	else if (C->s == "-")  C = C->next;
	else return true;
	bool b;
	b = t(C, P);
	if (b) b = u(C, P);
	return b;
}


bool t(bib*& C, ops*& P) {
	bool b = false;
	if (C->s == "(") {
		C = C->next; if (s(C, P) && C->s == ")") { C = C->next; b = true; }
	}
	else if (C->type == -1) { C = C->next;  if (h(C, P)) b = true; }
	else if (C->type == 0) { C = C->next; b = true; }
	else if (C->s == "-") { C = C->next;  if (g(C, P)) b = true; }
	else if (C->s == "+") {
		C = C->next;  if (g(C, P)) b = true;
	}
	if (b) b = v(C, P);
	return b;
}


bool v(bib*& C, ops*& P) {
	if (C->s == "*")  C = C->next;
	else if (C->s == "/")  C = C->next;
	else return true;
	bool boo = f(C, P);
	if (boo) boo = v(C, P);
	return boo;
}


bool f(bib*& C, ops*& P) {
	bool boo = false;
	if (C->s == "(") {
		C = C->next; if (s(C, P) && C->s == ")") { C = C->next; boo = true; }
	}
	else if (C->type == -1) { C = C->next;  if (h(C, P)) boo = true; }
	else if (C->type == 0) { C = C->next; boo = true; }
	else if (C->s == "-") { C = C->next;  if (g(C, P)) boo = true; }
	else if (C->s == "+") {
		C = C->next;  if (g(C, P)) boo = true;
	}
	return boo;
}


bool g(bib*& C, ops*& P) {
	bool boo = false;
	if (C->s == "(") {
		C = C->next; if (s(C, P) && C->s == ")") { C = C->next; boo = true; }
	}
	else if (C->type == -1) { C = C->next;  if (h(C, P)) boo = true; }
	else if (C->type == 0) { C = C->next; boo = true; }
	return boo;
}


bool h(bib*& C, ops*& P) {
	bool boo = true;
	if (C->s == "[") C = C->next; if (s(C, P) && C->s == "]") { C = C->next; boo = true; }
	return boo;
}


bool z(bib*& C, ops*& P) {
	return true;
}




int find(string leck, string mas_leksem[NLeck]) {
	for (int i = 0; i < NLeck; i++) {
		if (leck == mas_leksem[i]) {
			return i;
		}
	}
	return -1;
}


int int_(char ch) {
	if (ch >= 65 && ch <= 90 || ch >= 97 && ch <= 122) {
		return 0;
	}
	else if ((ch >= 48) && (ch <= 57)) {
		return 1;
	}
	else if ((ch) == 46) {
		return 2;
	}
	else if ((ch) == 32 || (ch) == '\t') {
		return 3;
	}
	else if ((ch) == 33) {
		return 4;
	}
	else if ((ch) == 60 || (ch) == 62) {
		return 5;
	}
	else if ((ch) == 61) {
		return 6;
	}
	else if ((ch) == 47) {
		return 7;
	}
	else if ((ch) == 42) {
		return 8;
	}
	else if (ch == '\n') {
		return 9;
	}
	else if ((ch) == 40 || (ch) == 41 || ((ch) >= 43 && (ch) <= 45) ||
		(ch) == 58 || (ch) == 59 || (ch) == 91 || (ch) == 93 ||
		(ch) == 123 || (ch) == 125) {
		return 10;
	}
	else if (ch == '┴') {
		return 12;
	}
	else return 11;
}


void find_new_leksem(int& i, int jj, string line, int M[10][13], int M_sem[10][13], string mas_leksem[NLeck], bib* p) {
	int k = 10;
	int s = 0;
	string name;
	int n;
	int FLAJOK_n = 0;
	float d, x;
	int FLAJOK_x = 0;
	int num_leks = -1;

	bib* a = new bib;

	while (s < k && i < line.length()) {
		int j = int_(line[i]);

		switch (M_sem[s][j])
		{
		case 1:
			name = line[i];
			break;
		case 2:
			n = line[i] - '0';
			FLAJOK_n = 1;
			break;
		case 3:
			name += line[i];
			break;
		case 4:
			n = n * 10 + line[i] - '0';
			break;
		case 5:
			d = 1;
			x = n;
			FLAJOK_x = 1;
			break;
		case 6:
			d *= 0.1;
			x += (line[i] - '0') * d;
			break;
		case 8:
			name = "";
			break;
		case 9:
			i--;
		case 7:
			num_leks = find(name, mas_leksem);
			break;
		case 10:
			i--;
			break;
		case 11:
			name += line[i];
			num_leks = find(name, mas_leksem);
			break;
		case 12:
			name = line[i];
			num_leks = find(name, mas_leksem);
			break;
		}

		s = M[s][j];
		i++;
	}

	if (s > k) {
		cout << "error in " << jj << ' ' << i << endl;
	}
	else if (name.length()) {
		a->s = name;
		a->i = i - name.length();
		a->j = jj;
		if (num_leks > -1) a->type = 1;
		else a->type = -1;
		p->next = a;
	}
	else if (FLAJOK_x) {
		a->val = x;
		a->j = jj;
		float numb = x;
		int count = 0;
		for (; numb != int(numb);)
			numb *= 10;
		while (numb) {
			numb /= 10;
			count++;
		}
		a->i = i - count;
		a->type = 0;
		p->next = a;
	}
	else if (FLAJOK_n) {
		a->val = n;
		a->j = jj;

		float numb = n;
		int count = 0;
		while (numb) {
			numb /= 10;
			count++;
		}
		a->i = i - count;
		a->type = 0;
		p->next = a;
	}
}


int main() {
	setlocale(LC_ALL, "russian");

	string mas_leksem[NLeck] = { "int", "float", "int1", "if", "while", ":", ".", ";",
		",", "+", "-", "/", "*", "(", ")", "[", "]", "{", "}", "print",
		 "scan", ">=", "<=", "==", "<", ">", "=", "!=", "and", "or" };


	int M[10][13] = { 1, 2, 11, 0, 4, 6, 6, 7, 10, 0, 10, 11, 10,
					  1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10,
					  11, 2, 3, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10,
					  11, 5, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
					  11, 11, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 11,
					  11, 5, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10,
					  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10,
					  10, 10, 10, 10, 10, 10, 10, 10, 8, 10, 10, 11, 10,
					  8, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8, 8,
					  8, 8, 8, 8, 8, 8, 8, 0, 9, 8, 8, 8, 8 };

	/*int M_sem[10][13] = { 1, 2, -1, 8, 1, 1, 1, 1, 12, 8, 12, -1, -1,
						  3, 3, 9, 7, 9, 9, 9, 9, 9, 9, 9, -1, 9,
						  -1, 4, 5, 8, 10, 10, 10, 10, 10, 10, 10, -1, 10,
						  -1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
						  -1, -1, -1, -1, -1, -1, 11, -1, -1, -1, -1, -1, -1,
						  -1, 6, 10, 8, 10, 10, 10, 10, 10, 10, 10, -1, 10,
						  9, 9, 9, 7, 9, 9, 11, 9, 9, 9, 9, -1, 9,
						  9, 9, 9, 7, 9, 9, 9, 9, 8, 9, 9, -1, 9,
						  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
						  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 };*/

	int M_sem[10][13] = { 1, 2, -1, 8, 1, 1, 1, 1, 12, 8, 12, -1, -1,
						  3, 3, 9, 7, 9, 9, 9, 9, 9, 9, 9, -1, 9,
						  -1, 4, 5, 8, 10, 10, 10, 10, 10, 10, 10, -1, 10,
						  10, 6, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
						  10, 10, 10, 10, 10, 10, 11, 10, 10, 10, 10, 10, 10,
						  -1, 6, 10, 8, 10, 10, 10, 10, 10, 10, 10, -1, 10,
						  9, 9, 9, 7, 9, 9, 11, 9, 9, 9, 9, -1, 9,
						  9, 9, 9, 7, 9, 9, 9, 9, 8, 9, 9, -1, 9,
						  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
						  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 };

	bib C;
	bib* C_temp = &C;

	ops PS;
	ops* PS_temp = &PS;

	string line;
	int i;
	int jj = 0;
	ifstream file("text.txt");
	if (file.is_open())
	{
		while (!file.eof())
		{
			jj++;
			getline(file, line);
			line = line + '\n';
			i = 0;

			while (i < line.length()) {
				find_new_leksem(i, jj, line, M, M_sem, mas_leksem, C_temp);
				if (C_temp->next) C_temp = C_temp->next;
			}
		}
		file.close();
	}
	else cout << "Unable to open file";

	C_temp = &C;
	C_temp = C_temp->next;
	cout << p(C_temp, PS_temp) << endl;

	/*C_temp = &C;
	C_temp = C_temp->next;
	while (C_temp) {
		if (C_temp->s != "") cout << C_temp->s << endl;
		else cout << C_temp->val  << endl;
		cout << " --- ---" << endl;
		C_temp = C_temp->next;
	}*/

	return 0;
}



/*programm
int i;
int  range;
float f, h, g;
int1 a[5];
{
	i = 0;
	while i < range:
	{
		scan(f);
		a[i] = f;
		print(a[i]);
		i = i + 1;
	}
}*/
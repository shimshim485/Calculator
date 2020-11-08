#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <vector>

using namespace std;

char atOper[3][3] = { {}, {}, {} };
char sharpOper[3][3] = { {}, {}, {} };
char andOper[3][3] = { {}, {}, {} };

//Operation
void Operations() {
	ifstream readf("operations.txt");
	char buf;

	readf >> buf;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			readf >> buf;
			atOper[i][j] = buf;
		}
	}
	// Set #
	readf >> buf;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			readf >> buf;
			sharpOper[i][j] = buf;
		}
	}
	// Set &
	readf >> buf;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			readf >> buf;
			andOper[i][j] = buf;
		}
	}

}
char atOperations(char a, char b) {
	for (int i = 0; i < 3; i++) {
		if ((a == atOper[i][0] && b == atOper[i][1]) || (b == atOper[i][0] && a == atOper[i][1])) return atOper[i][2];
	}
	return -1;
}
char sharpOperations(char a, char b) {
	for (int i = 0; i < 3; i++) {
		if ((a == sharpOper[i][0] && b == sharpOper[i][1]) || (b == sharpOper[i][0] && a == sharpOper[i][1])) return sharpOper[i][2];
	}
	return -1;
}
char andOperations(char a, char b) {
	for (int i = 0; i < 3; i++) {
		if ((a == andOper[i][0] && b == andOper[i][1]) || (b == andOper[i][0] && a == andOper[i][1])) return andOper[i][2];
	}
	return -1;
}
/*
char read_and_evaluate(istream& ins)
{
	stack<char> characters;
	stack<char> operations;
	stack<char> parentheses;

	char chars;
	char opers;
	char paren;

	while (ins && ins.peek() != '\n') {
		if (strchr("abc", ins.peek()) != NULL) {
			ins >> chars;
			characters.push(chars);
		}
		else if (strchr("@#&", ins.peek()) != NULL) {
			ins >> opers;
			characters.push(opers);
		}
		else if (strchr("([{", ins.peek()) != NULL)
	   {
			ins>>paren;
			parentheses.push(paren);
			
		}
		else if (strchr(")]}", ins.peek()) != NULL) {
			if (ins.peek() == ')' && parentheses.top() == '(') {
				evaluate_stack(characters, operations);
			}else if (ins.peek() == ']' && parentheses.top() == '[') {
				evaluate_stack(characters, operations);
			}else if(ins.peek() == '}' && parentheses.top() == '{ ') {
				evaluate_stack(characters, operations);
			}
		}
		else {
			ins.ignore();
		}

	}
}

void evaluate_stack(stack<char>& characters,stack<char>& operations) {
	char operand1, operand2;
	operand2 = characters.top();
	characters.pop();
	operand1 = characters.top();
	characters.pop();

	switch (operations.top()) {
	case '@': characters.push(atOperations(operand1, operand2)); break;
	case '#': characters.push(sharpOperations(operand1, operand2)); break;
	case '&': characters.push(andOperations(operand1, operand2)); break;
	}

	operations.pop();
	
}
*/
void calc() {

}

string toPostfix(istream& ins) {
	stack<char> operstack;

	char chars;

	string output;

	while (ins && ins.peek() != '\n') {
		if (strchr("([{", ins.peek()) != NULL)
		{
			ins >> chars;
			operstack.push(chars);
		}
		else if (strchr("abc", ins.peek()) != NULL) {
			ins >> chars;
			output += chars;
		}
		else if (strchr("@#&", ins.peek()) != NULL) {
			ins >> chars;
			if ((operstack.top()!='@')|| (operstack.top() != '#')|| (operstack.top() != '&')) {
				operstack.push(chars);
			}
			else {
				if (((operstack.top() == '#') || (operstack.top() == '@')) && (chars == '&')) {
					output += '&';
				}
				else {
					output += operstack.top();
					operstack.pop();
					operstack.push(chars);
				}
			}
		}
		else if (strchr(")]}", ins.peek()) != NULL) {
			ins >> chars;
			char parentheses[3][2] = { {'(', ')'}, {'[', ']'}, {'{', '}'} };
			for (int i = 0; i < 3; i++) {
				if (parentheses[i][0] == chars) {
					while (1) {
						if (operstack.top() == parentheses[i][1]) {
							operstack.pop();
							break;
						}
						output += operstack.top();
						operstack.pop();
					}
				}
			}
			output = "Error!";
		}
	}

	return output;
}

string hh(istream& ins) {
	return "dfgs";
}

int main(int argc, char const* argv[]) {
	vector<string> ans;
	string input;
	Operations();
	while(1) {
		string output = toPostfix(cin>> input);
		if (input == "EOI") break;
		ans.push_back(output);
	}
	for(int i=0;i< ans.size();i++)
	cout << ans[i]<<endl;



	return 0; 
}
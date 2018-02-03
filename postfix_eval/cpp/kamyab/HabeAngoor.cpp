#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int weight(char ch){

	int w = -1;
	switch(ch)
	{
		case '+':
			w = 1;
			break;
		case '-':
			w = 2;
			break;
		case '*':
			w = 3;
			break;
		case '/':
			w = 4;
			break;
		case '^':
			w = 5;
			break;
	}
	return w;

}

class obj{

public:
	obj(int xx=0, bool op= false){
		isOperator = op;
		x= xx;
	}
	int x;
	bool isOperator;
};

int main(){
	vector<obj> infix;
	vector<char> stack;
	vector<obj> postfix;

	string s;
	getline(cin,s);
	int ii=0;
	while( ii< s.size() ){

		if(s[ii]==' '){
			ii++;
			continue;
		}
		if(s[ii]<= '9' and s[ii]>='0'){
			if(infix.size()>0 and infix[infix.size()-1].isOperator and (char)infix[infix.size()-1].x == ')'){
				infix.push_back(obj('*',1));
			}
			int result = s[ii] - '0';
			while(ii<s.size()-1 and s[ii+1] != ' ' and s[ii+1]!=')' and s[ii+1]!='('){
				ii++;
				result = result*10 + s[ii]-'0';
			}
			infix.push_back(obj(result,false));

		}else if(s[ii]=='(' and infix.size()>0 and (
						(infix[infix.size()-1].isOperator and (char)infix[infix.size()-1].x==')')
				  or
								!infix[infix.size()-1].isOperator)){
			infix.push_back(obj('*',1));
			infix.push_back(obj(s[ii],1));
		}
		else
		   infix.push_back(obj(s[ii],true));
		ii++;

	}

	for(int i=0;i<infix.size();i++){
		if(!infix[i].isOperator){
			postfix.push_back(infix[i]);
		} else if( (char)infix[i].x==')' ){
			char tmp;
			while(!stack.empty() and stack[stack.size()-1]!='('){
				tmp = stack[stack.size()-1];
				stack.pop_back();
				postfix.push_back(obj((int)tmp,true));
			}
			stack.pop_back();
		} else if(infix[i].x=='('){
			stack.push_back((char)infix[i].x);
		} else {
			while( !stack.empty() and stack[stack.size()-1]!='(' and weight((char)infix[i].x) < weight(stack[stack.size()-1])){
				char tmp =  stack[stack.size()-1];
				stack.pop_back();
				postfix.push_back(obj((int)tmp,true));

			}
			stack.push_back((char)infix[i].x);
		}
	}
	while(!stack.empty()){
		char tmp = stack[stack.size()-1];
		postfix.push_back(obj(tmp,true));
		stack.pop_back();
	}


	while(postfix.size()>1){
		int index=2;
		while(index<postfix.size()){
			if(postfix[index].isOperator and !postfix[index-1].isOperator and !postfix[index-2].isOperator){
				int tmp;
				if(postfix[index].x == '*')
					tmp = postfix[index-2].x * postfix[index-1].x;
				if(postfix[index].x == '/')
					tmp = postfix[index-2].x / postfix[index-1].x;
				if(postfix[index].x == '+')
					tmp = postfix[index-2].x + postfix[index-1].x;
				if(postfix[index].x == '-')
					tmp = postfix[index-2].x - postfix[index-1].x;
				if(postfix[index].x == '*')
					tmp = postfix[index-2].x * postfix[index-1].x;
				if(postfix[index].x == '^')
					tmp = (int)pow(postfix[index-2].x , postfix[index-1].x);
				obj tmp2(tmp,false);
				 postfix.erase(postfix.begin()+index-2,postfix.begin()+index+1);
				postfix.insert(postfix.begin()+index-2,tmp2);

				break;
			}
			index++;
		}
	}
	if(postfix.size()==1)
		cout <<  endl << postfix[0].x << endl;
}
#include <iostream>
#include <stack>
#include <stdio.h>  
#include <algorithm>
#include <string>
using namespace std;


class operation {
    public:
    operation(){}
    virtual void print(ostream& stream)=0;
    virtual float exec()=0;
    virtual ~operation(){}; 
} ;
class nr: public operation {
  public:
  int n;
  nr(int n){this->n=n;}
  void print(ostream& stream) {
    stream << ' ' << this->n << ' ';
  }
  float exec(){
    return n;
  }
  ~nr(){/*cout<<"delete nr "<<n<<endl;*/}
} ;
class op: public operation {
  public:
  operation *left;
  operation *right;
  char sign;
  op(){}
  op(operation *l, operation *r, char s){
    this->left=l;
    this->right=r;
    this->sign=s;
  }

  void print(ostream& stream) {
    stream << '('; 
    this->left->print(stream);
    stream << ' ' << this->sign << ' ';
    this->right->print(stream);
    stream << ')';
  }

  float exec(){
    switch(this->sign){
        case '+':
            return this->left->exec()+this->right->exec();
            
        case '-':
            return this->left->exec()-this->right->exec();
            
        case '*':
            return this->left->exec()*this->right->exec();
            
        case '/':
            return this->left->exec()/this->right->exec();
            
        default:
            return 0;
    }
  }
  ~op(){
    /*cout<<"delete op "<<sign<<endl;*/
    delete left;
    delete right;  
  }
};


int findClosingParenthesisIndex(string expression){

	int parenthesisCount=0;
	for(int i=1; i<expression.size(); i++){
		if(parenthesisCount==0 && expression[i]==')')
		{ 
			return i;

		}
		if(expression[i]=='(') parenthesisCount++;
		if(expression[i]==')') parenthesisCount--;
		
	}
	return -1;

}

operation *buildExpressionWithParenthesis(string expression){
	
	//cout<<"expression: "<<expression<<endl;
	if(expression.size()==0) return NULL;	

	
	if(expression.size()==1){
		if('0' > expression[0] || expression[0] > '9')	throw invalid_argument("Expression should be a 0-9 digit!");
    	return new nr(expression[0]-'0');
	}
		
	char firstChar=expression[0];
	int i=1;
	operation *leftOp;
	if(firstChar=='(')
	{
		i = findClosingParenthesisIndex(expression);
		if(i<0) throw invalid_argument("Wrong parenthesis schema!");
		leftOp=buildExpressionWithParenthesis(expression.substr(1, i-1));
		if(i==expression.size())
			return leftOp;
		
		i++;
	} else {
		leftOp=buildExpressionWithParenthesis(expression.substr(0, 1));
	}
		

	//cout<<endl;
	char sign=expression[i];
	if(sign != '-' && sign != '+' && sign != '/' && sign != '*')
         throw invalid_argument("Error: unknown sign!");
	
	//cout<<"sign "<<sign<<endl;
	operation *rightOp;
	for(; sign == '*' || sign == '/';){
		
		//cout<<"iOp "<<i <<endl;		
		//cout<<"signOp "<<expression[i] <<endl;
		int firstIdx = i+1;
		char rightChar=expression[firstIdx];
		if(rightChar=='('){
			int parenthesisExpressionLenght=findClosingParenthesisIndex(expression.substr(firstIdx, expression.size()));
			if(i<0) 
				throw invalid_argument("Wrong parenthesis schema!");
			i = firstIdx+parenthesisExpressionLenght;
			//cout<<"i pranthesis="<<i<<endl;
			//cout<<"expr "<<expression<<endl;
			rightOp=buildExpressionWithParenthesis(expression.substr(firstIdx+1, parenthesisExpressionLenght-1));
			//cout<<"original "<<expression.substr(firstIdx, expression.size())<<endl;
			//cout<<"paranthesis "<<expression.substr(firstIdx+1, parenthesisExpressionLenght)<<endl;
			i++;
			//cout<<"i="<<i<<endl;
		} else {
			int right=rightChar-'0';
			rightOp=buildExpressionWithParenthesis(expression.substr(firstIdx, 1));
			i+=2;
			//cout<<"number "<<right<<endl;
		}
		leftOp=new op(leftOp, rightOp, sign);
	
		if(i>=expression.size())
			return leftOp;
		sign=expression[i];

		if(sign != '-' && sign != '+' && sign != '/' && sign != '*')
            throw invalid_argument("Error: unknown sign!");
		
	}
	//cout<<"end i="<<i<<endl;
	//cout<<"rightOp "<< expression.substr(i+1, expression.size()-1)<<endl;
	rightOp=buildExpressionWithParenthesis(expression.substr(i+1, expression.size()-1));
	//cout <<endl;


	return new op(leftOp, rightOp, sign);
	

}

string removeSpaces(string str){
    string ret="";
    for(int i=0; i< str.size();i++){
        char c = str[i];
        if(!isspace(c))
            ret+=c;    
    }
    return ret;
}

void test(string str){

    cout<<"original expression: "<<str<<endl;    
    string strNoSpc=removeSpaces(str);

    try {
        cout<<"expression without spaces: "<<strNoSpc<<endl;
    	operation *firstOp = buildExpressionWithParenthesis(strNoSpc);

		cout<<"expression with precedence: ";    
		firstOp->print(cout);
		cout << endl;

		cout<<"expression result: " << firstOp->exec() <<endl;
		cout<<endl;

		delete firstOp;
    } catch (std::invalid_argument const& ex) {
        std::cout << "Invalid argument! " << ex.what() << endl << endl;
    }    
}

int main(int argc, char* argv[]) {

   
    cout << "Hello, world!" << endl;
    operation *o = new nr(8);
    o->print(cout);
    cout<<endl;

    test("4");
	test("4 * 3 / 2 + 6+1*5 * 2");
    test("4 * 3 / 2 + 6+1*5 * 2");
    test("4 * 3 / 2 *6 + 6+1*5 * 2");
    test("4 * 3 / 2 + 5 * 2");
    test("((4 + 1) - 3) / 2 + 5 * 2 *9");
    test("4 * (3 + 2) + 5 * 2");
    test("1 * 3 / 2 + 5 * 2");
	test("1 * (3 / (1+2))");
	test(" ((3) / 2 + 5 * 2");
	test("1 a (3 / (1+2))");
	test("a (3 / (1+2))");
   
   return 0;
}


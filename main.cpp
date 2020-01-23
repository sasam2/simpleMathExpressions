#include <iostream>
#include <stack>
#include <stdio.h>  
#include <algorithm>
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
  ~nr(){cout<<"delete nr "<<n<<endl;}
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
    cout<<"delete op "<<sign<<endl;
    delete left;
    delete right;  
  }
};

string getOperation(string expression){
    for(int i=0; i<expression.size(); ){

        char a=0;        
        do{
            a = expression[i++];
        }while(a!=')');

        cout<<"i="<<i<<endl;
        int j=i;
        
        do{
            a = expression[j--];
        }while(a!='(');

        cout<<"j="<<j<<endl;
        string expr=expression.substr(j+2,i-2);
        return expr;
        
        
    }
}



operation *buildExpression(string expression){
    
    if(expression.size()==1 && '0' <= expression[0] && expression[0] <= '9')
        return new nr(expression[0]-'0');
    
        
    op *prevOp=NULL;
    op *currOp=NULL;
    op *firstOp=NULL;
    for(int i=0; i<expression.size(); ){
        
        int a = expression[i++]-'0';
        if(a < 0  || a > 9)
            cerr<<"Error: found non digit"<<endl;

        if(i==expression.size()){ //end
            prevOp->right = new nr(a);
            //cout << a << ')' << endl;
            break;
        }

        char sign = expression[i++];
        if(prevOp!=NULL && (prevOp->sign == '*' || prevOp->sign == '/') && (sign == '-' || sign == '+')){
                        
                //criar nr p/fechar          
                prevOp->right = new nr(a);
    
                //criar firstOp que engloba td em left
                currOp = new op();
                currOp->left = firstOp;
                currOp->sign = sign;
                
                prevOp=currOp;
                firstOp=currOp;

            //cout << a << sign << ' ';
        } else {

            if(sign == '-' || sign == '+' || sign == '/' || sign == '*'){
                currOp = new op();
                currOp->left = new nr(a);
                currOp->sign = sign;
                //cout << "(" << a << sign;
                if(prevOp!=NULL){
                      prevOp->right=currOp;     
                }
            } else {
                cerr << "Error: unknown sign" <<endl;            
            }
        }
        //primeira iteracao
        if(prevOp==NULL){
              firstOp=currOp;        
        }        
        
        prevOp=currOp;

    }
    return firstOp;
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

    cout<<"expression without spaces: "<<strNoSpc<<endl;
    operation *firstOp = buildExpression(strNoSpc);

    cout<<"expression with precedence: ";    
    firstOp->print(cout);
    cout << endl;

    cout<<"expression result: " << firstOp->exec() <<endl;
    cout<<endl;

    cout<<"delete"<<endl;
    delete firstOp;
}

int main(int argc, char* argv[]) {

   
    cout << "Hello, world!" << endl;
    operation *o = new nr(8);
    o->print(cout);
    cout<<endl;

    test("4");
    test("4 * 3 / 2 + 5 * 2");
    test("4 . 3 / 2 + 5 * 2");

    cout << getOperation("(8+9*1)") <<endl;
   
   return 0;
}


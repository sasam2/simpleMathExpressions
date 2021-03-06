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

operation *buildExpression(string expression){
    
    if(expression.size()==1 && '0' <= expression[0] && expression[0] <= '9')
        return new nr(expression[0]-'0');
    
        
    op *prevOp=NULL;
    op *currOp=NULL;
    op *firstOp=NULL;
    for(int i=0; i<expression.size(); ){
        
        int a = expression[i++]-'0';
        if(a < 0  || a > 9){
            cerr<<"Error: found non digit "<< a <<endl;
            if(firstOp!=NULL)
                delete firstOp;
            return NULL;
        }

        if(i==expression.size()){ //expression ended
            prevOp->right = new nr(a);
            //cout << a << ')' << endl;
            break;
        }
        
        char sign = expression[i++];
        if(sign != '-' && sign != '+' && sign != '/' && sign != '*'){
            cerr << "Error: unknown sign " << sign <<endl;
            if(firstOp!=NULL)
                delete firstOp;
            return NULL; 
        }

        if(prevOp!=NULL && (prevOp->sign == '*' || prevOp->sign == '/') && (sign == '-' || sign == '+')){
                        
                //close expression of * or /          
                prevOp->right = new nr(a);
    
                //create new parent node "firstOp" that has current tree on left node
                currOp = new op();
                currOp->left = firstOp;
                currOp->sign = sign;
                
                prevOp=currOp;
                firstOp=currOp;

            //cout << a << sign << ' ';
        } else { //(sign == '-' || sign == '+' || sign == '/' || sign == '*')
    
            //by default rightmost operands are the closest to the leaves of the tree
            currOp = new op();
            currOp->left = new nr(a);
            currOp->sign = sign;
            //cout << "(" << a << sign;
            if(prevOp!=NULL){
                 prevOp->right=currOp;
            }
        }
        //first iteration
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
    if(firstOp==NULL) {
        cout << endl;
        return;
    }

    cout<<"expression with precedence: ";    
    firstOp->print(cout);
    cout << endl;

    cout<<"expression result: " << firstOp->exec() <<endl;
    cout<<endl;

    //cout<<"delete"<<endl;
    delete firstOp;
}

int main(int argc, char* argv[]) {

   
    cout << "Hello, world!" << endl;
    operation *o = new nr(8);
    o->print(cout);
    cout<<endl;

    test("4");
    test("4 * 3 / 2 + 6+1*5 * 2");
    test("4 * 3 / 2 + 5 * 2");
    test("4 + 3 / 2 + 5 * 2 *9");
    test("4 . 3 / 2 + 5 * 2");
    test("a . 3 / 2 + 5 * 2");

   
   return 0;
}


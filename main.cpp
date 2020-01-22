#include <iostream>
#include <stack>
#include <stdio.h>  
using namespace std;


class operation {
    public:
    operation(){}
    virtual void print(ostream& stream)=0;
} ;
class nr: public operation {
  public:
  int n;
  nr(int n){this->n=n;}
  void print(ostream& stream) {
    stream << ' ' << this->n << ' ';
  }
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
};


operation *newExpression(int a, char sign){


}


void buildExpression(string expression){
    
    //stack<operation> ops;
    op *prevOp=NULL;
    op *currOp=NULL;
    op *firstOp=NULL;
    stack<operation> ops;
    for(int i=0; i<expression.size(); ){
        
        int a = expression[i++]-'0';

        if(i==expression.size()){ //end
            prevOp->right = new nr(a);
            cout << a << ')' << endl;
            break;
        }

        char sign = expression[i++];
        if(prevOp!=NULL && (prevOp->sign == '*' || prevOp->sign == '/') && (sign == '-' || sign == '+')){
                        
            //if(sign == '-' || sign == '+'){
                
                //criar nr p/fechar          
                prevOp->right = new nr(a);
    
                //criar firstOp que engloba td em left
                currOp = new op();
                currOp->left = firstOp;
                currOp->sign = sign;
                
                prevOp=currOp;
                firstOp=currOp;
                                
            /*} else {
                
                //cr
                currOp = new op();
                currOp->right = new nr(a);
                currOp->sign = sign;
                prevOp->right = currOp;

                prevOp=currOp;
            }*/

            cout << a << sign << ' ';
        } else {

            currOp = new op();
            currOp->left = new nr(a);
            currOp->sign = sign;
            cout << "(" << a << sign;
            if(prevOp!=NULL){
                  prevOp->right=currOp;     
            }
        }
        if(prevOp==NULL){
              firstOp=currOp;        
        }        
        
        prevOp=currOp;

    }
    firstOp->print(cout);
}



int main(int argc, char* argv[]) {
   
   /*
    if(argc!=2){
        cerr << "No 2nd argument!"<<endl;
        return 1;
   }
   char *expression = argv[1];
    */
   
    cout << "Hello, world!" << endl;
    operation *o = new nr(8);
    o->print(cout);
    cout<<endl;
    buildExpression("9+1*3*2+5*2");
   
   return 0;
}


#include <bits/stdc++.h>
/*
void print_error_msg( const Parser::ResultType & result, const std::string &str ) {
    std::string error_indicator( str.size()+1, ' ');

    // Have we got a parsing error?
    error_indicator[result.at_col] = '^';
    switch ( result.type ) {
        case Parser::ResultType::UNEXPECTED_END_OF_EXPRESSION:
            std::cout << ">>> Unexpected end of input at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::ILL_FORMED_INTEGER:
            std::cout << ">>> Ill formed integer at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::MISSING_TERM:
            std::cout << ">>> Missing <term> at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::EXTRANEOUS_SYMBOL:
            std::cout << ">>> Extraneous symbol after valid expression found at column (" << result.at_col << ")!\n";
            break;
        case Parser::ResultType::INTEGER_OUT_OF_RANGE:
            std::cout << ">>> Integer constant out of range beginning at column (" << result.at_col << ")!\n";
            break;
        default:
            std::cout << ">>> Unhandled error found!\n";
            break;
    }
    std::cout << "\"" << str << "\"\n";
    std::cout << " " << error_indicator << std::endl;
}
*/
bool isOperator(char ch) {
   if(ch == '+'|| ch == '-'|| ch == '*'|| ch == '/' || ch == '^'){
        return true;    
   }
   return false;   
}

int isOperand(char ch) {
   if(ch >= '0' && ch <= '9'){
        return true;   
   }
   return false;   
}

int checkPrec(char c_){
    if(c_ == '^'){
        return 3;
    }else if(c_ == '*' || c_ == '/'){
        return 2;
    }else if(c_ == '+' || c_ == '-'){
        return 1;
    }
    return 0;
}

std::string inToPos(std::string exp){
    std::stack<char> pilha;
    std::string res;
    std::cout << "EXPRESSION → --" << exp << "--\n";
    for(int i{0};i<exp.size();i++){
        if(exp[i]=='0' && exp[i+1]>='0' && exp[i+1]<='9'){
            std::cout << "Error: \'"<<exp[i]<<"\' Não pode iniciar um número\n";
            exit(0);
        }else if((exp[i]>='a' && exp[i]<='z') || (exp[i]>='A' && exp[i]<='Z')){
            std::cout << "Error: \'"<<exp[i]<<"\' Não é um caracter válido\n";
            exit(0);
        }else if(exp[i]==' '){
            continue;
        }else if(exp[i]>='0' && exp[i]<='9'){
            int aux = i+1;
            std::string numCompleto{exp[i]};
            while(exp[aux]>='0' && exp[aux]<='9'){
                numCompleto+=exp[aux];
                aux++;
                i++;
            }
            res+=numCompleto;
            res+='.';
            //std::cout << "Numero: ("<<res<<")\n";
        }else if(exp[i]=='('){
            pilha.push(exp[i]);
        }else if(exp[i]==')'){
            while(!pilha.empty() && pilha.top()!='('){
                res+=pilha.top();
                res+='.';
                pilha.pop();
            }
            if(!pilha.empty()){
                pilha.pop();
            }
        }else{
            while(!pilha.empty() && checkPrec(pilha.top())>checkPrec(exp[i])){
                res+=pilha.top();
                res+='.';
                pilha.pop();
            }
            pilha.push(exp[i]);
        }
    }

    while(!pilha.empty()){
        res+=pilha.top();
        res+='.';
        pilha.pop();
    }
    return res;
}

int result(std::string exp){
    std::stack<int>pilha;

    std::stringstream check1(exp);
    std::string intermediate;
    std::vector<std::string>resp;

    //std::cout << "Recebi →"<<exp<<"→\n";
    
    while(getline(check1, intermediate, '.')){
        resp.push_back(intermediate);
    }

    std::cout << "Elementos: [ ";
    for(int i{0};i<resp.size();i++){
        std::cout << resp[i] << " ";
    }
    std::cout << "]\n";

    for(int i{0};i<resp.size();i++){
        if(resp[i].find_first_not_of("0123456789") == std::string::npos /*resp[i]>='0' && resp[i]<='9'*/){
            pilha.push(std::stoi(resp[i]));
        }else{
            int y = pilha.top();
            pilha.pop();
            int x = pilha.top();
            pilha.pop();
            switch(resp[i][0]){
                case '+':
                    pilha.push(x+y);
                    break;

                case '-':
                    pilha.push(x-y);
                    break;
                
                case '*':
                    pilha.push(x*y);
                    break;
                
                case '/':
                    pilha.push(x/y);
                    break;
                
                case '^':
                    pilha.push(std::pow(x,y));
                    break;
            }
        }
    }
    return pilha.top();
}

int main(){
    std::cout << "Digite a expressão: ";
    std::string expression;
    getline(std::cin,expression);

    std::cout << "PosFixo → " << inToPos(expression) << " Result → " << result(inToPos(expression)) << std::endl; 
    
    //std::cout << "PosFixo → " << inToPos("(2+3)    *    5") << " Result → " << result(inToPos("(2+3)    *    5")) << std::endl; 
    return 0;
}
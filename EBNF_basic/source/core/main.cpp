#include <iostream>
#include <iomanip>
#include <vector>
#include "parser.h"
#include <bits/stdc++.h>

/// List of expressions to evaluate and tokenize.
std::vector<std::string> expressions = {
    "4 + 03",
    "10",
    "    12    +    4   8",
    "32767 - 32768 + 3",
    "5 + -32766",
    "5 + -32769",
    "12 + 3",
    "-3+-5+-6",
    "12 + 3     -3 + -34 ",
    "+12",
    "1.3 * 4",
    "a + 4",
    "       ",
    "  123 *  548",
    "4 + ",
    "32a23",
    "43 + 54 -   "
};

std::vector<std::string> expressions2 = {
    "-3+(-4)",
    "87 + 7 * 85 - 120",
    "5 * ( 64 - 12 / 4 )",
    "((24) / 8 + 5 * 3) / 6",
    "1+2+(5*3)+2^(1+1)",
    "25 / 5 + 4 * 8",
    "(2+3) * 8",
    "(1+2)*3",
    "10",
    "2^2^3",
    "12 + 3 - 3 + -34",
    "12 + 3 - 3 + -2",
    "1+2-3+4-5",
    "2*5*3",
    "(((4+6)/2)*5)+7",
    "2/(1-1)",
    "20*20000",
    "36/6"
};

std::vector<std::string> expressionsProf = {
    "10000000 - 2",
    "2+",
    "3 * d",
    "2 = 3",
    "2.3 + 4",
    "2 * 3 4",
    "2 ** 3",
    "%5 * 10",
    "*5 * 10",
    "(2+3)*/(1-4)",
    "(-3*4)(10*5)",
    "2 - 4)",
    "2) - 4",
    ")2 - 4",
    "((2%3) * 8",
    "3/(1-1)",
    "10/(3*3^-2)",
    "20*20000",
    "25 / 5 + 4 * 8",
    "(5%2)+1*3",
    "(2+3) * 8",
    "-3",
    "5 % 2 ^4",
    "(5 % 3) ^4"
};

/**
 * @brief check if "ch" is an operator like (+,-,*,...)
 * 
 * @param ch Character that will be checked
 * @return true if "ch" is an operator
 * @return false otherwise
 */
bool isOperator(char ch) {
   if(ch == '+'|| ch == '-'|| ch == '*'|| ch == '/' || ch == '^'){
        return true;    
   }
   return false;   
}

/*
void printPilha(std::stack<int> pilha){
    while(!pilha.empty()){
        std::cout << pilha.top() << " ";
        pilha.pop();
    }
}
*/

/**
 * @brief check if "ch" is an operand
 * 
 * @param ch Character that will be checked
 * @return true if "ch" is an operand
 * @return false otherwise
 */
bool isOperand(char ch) {
   if(ch >= '0' && ch <= '9'){
        return true;   
   }
   return false;   
}

/// Send to the standard output the proper error messages.
void print_error_msg( const Parser::ResultType & result, const std::string &str ) {
    //std::string error_indicator( str.size()+1, ' ');

    // Have we got a parsing error?
    //error_indicator[result.at_col] = '^';
    switch ( result.type ) {
        case Parser::ResultType::UNEXPECTED_END_OF_EXPRESSION:
            std::cout << ">>> Unexpected end of input at column (" << result.at_col + 1<< ")!\n";
            break;
        case Parser::ResultType::ILL_FORMED_INTEGER:
            std::cout << ">>> Ill formed integer at column (" << result.at_col + 1<< ")!\n";
            break;
        case Parser::ResultType::MISSING_TERM:
            std::cout << ">>> Missing <term> at column (" << result.at_col + 1<< ")!\n";
            break;
        case Parser::ResultType::EXTRANEOUS_SYMBOL:
            std::cout << ">>> Extraneous symbol after valid expression found at column (" << result.at_col + 1<< ")!\n";
            break;
        case Parser::ResultType::INTEGER_OUT_OF_RANGE:
            std::cout << ">>> Integer constant out of range beginning at column (" << result.at_col + 1<< ")!\n";
            break;
        case Parser::ResultType::MISSING_CLOSING:
            std::cout << ">>> Missing closing \")\" at column (" << result.at_col + 2<< ")!\n";
            break;
        case Parser::ResultType::DIVISION_BY_ZERO:
        std::cout << ">>>  Division by zero!\n";
        break;
        case Parser::ResultType::NUMERIC_OVERFLOW_RESULT:
            std::cout << ">>>  Numeric overflow error!\n";
            break;
        case Parser::ResultType::MISSING_EXP:
            std::cout << ">>> Missing <expr> at column (" << result.at_col + 1<< ")!\n";
            break;
        default:
            std::cout << ">>> Unhandled error found!\n";
            break;
    }
    //std::cout << "\"" << str << "\"\n";
    //std::cout << " " << error_indicator << std::endl;
}

/**
 * @brief Check the precedence of operator
 * 
 * @param c_ Character that will be checked
 * @return int Value that represents the operator's precedence
 */
int checkPrec(char c_){
    if(c_ == '^'){
        return 3;
    }else if(c_ == '*' || c_ == '/' || c_ == '%'){
        return 2;
    }else if(c_ == '+' || c_ == '-'){
        return 1;
    }
    return -1;
}

/**
 * @brief Converts an infixed expression to posfix
 * 
 * @param exp Infix Expression
 * @return std::string Posfix Expression
 */
std::string inToPos(std::vector<std::string> exp){
    std::stack<char> pilha;
    std::string res;

    //std::cout << "Vector Recebido: [ ";
    //for(const auto & i :exp){
    //    std::cout << i << " ";
    //}
    //std::cout << "]\n";

    for(size_t i{0};i<exp.size();i++){
        if(exp[i][0]=='-' && exp[i].size()>1){
            res+=exp[i];
            res+=".";
        }else if(exp[i].find_first_not_of("0123456789") == std::string::npos){
            //std::cout << "Tá Entrando Aqui Mesmo\n";
            res+=exp[i];
            res+=".";
        }else if(exp[i]=="("){
            pilha.push(exp[i][0]);
        }else if(exp[i]==")"){
            while(!pilha.empty() && pilha.top()!='('){
                res+=pilha.top();
                res+=".";
                pilha.pop();
            }
            if(!pilha.empty()){
                pilha.pop();
            }
        }else{
            while(!pilha.empty() && checkPrec(pilha.top())>=checkPrec(exp[i][0])){
                res+=pilha.top();
                res+=".";
                pilha.pop();
            }
            pilha.push(exp[i][0]);
        }
    }

    while(!pilha.empty()){
        res+=pilha.top();
        res+=".";
        pilha.pop();
    }
    return res;
}

/**
 * @brief Check if "x" is out of type range
 * 
 * @param x Value that will be checked
 * @return true 
 * @return false 
 */
bool checkRange(long long int x){
    if(x>=-32768 && x<=32767){
        return true;
    }
    return false;
}

/**
 * @brief Calculates the value of a posfix expression
 * 
 * @param exp Posfix Expression
 * @return int Result of operation
 */
int resultado(std::string exp){
    std::stack<int>pilha;
    //std::cout << "Recebi Para Calcular → "<<exp<<std::endl;
    std::stringstream check1(exp);
    std::string intermediate;
    std::vector<std::string>resp;

    //std::cout << "Recebi →"<<exp<<"→\n";
    
    while(getline(check1, intermediate, '.')){
        resp.push_back(intermediate);
    }

    //std::cout << "PosFix: [ ";
    //for(size_t i{0};i<resp.size();i++){
    //    std::cout << resp[i] << " ";
    //}
    //std::cout << "]\n";

    for(size_t i{0};i<resp.size();i++){
        if(resp[i][0]=='-' && isOperand(resp[i][1])){
            resp[i] = resp[i].substr(1,resp[i].size()-1);
            //std::cout << "APÓS CORTAR O NEGATIVO → " << resp[i] << std::endl;
            if(resp[i].find_first_not_of("0123456789") == std::string::npos){
                pilha.push(std::stoi(resp[i])*-1);
            }
        }
        else if(resp[i].find_first_not_of("0123456789") == std::string::npos /*resp[i]>='0' && resp[i]<='9'*/){
            pilha.push(std::stoi(resp[i]));
        }else{
            
            //printPilha(pilha);
            //std::cout << std::endl;
            int y = pilha.top();
            pilha.pop();
            //std::cout << std::endl;

            //printPilha(pilha);
            int x = pilha.top();
            pilha.pop();
            //printPilha(pilha);
            //std::cout << std::endl;


            switch(resp[i][0]){
                case '+':
                    //std::cout << "X + Y → "<<x<<" + "<<y<<std::endl;
                    if(!checkRange(x+y)){
                        return 'o';
                    }
                    pilha.push(x+y);
                    //printPilha(pilha);
                    //std::cout << std::endl;
                    break;

                case '-':
                    //std::cout << "X - Y → "<<x<<" - "<<y<<std::endl;
                    if(!checkRange(x-y)){
                        return 'o';
                    }
                    pilha.push(x-y);
                    //printPilha(pilha);
                    //std::cout << std::endl;
                    break;
                
                case '*':
                    //std::cout << "X * Y → "<<x<<" * "<<y<<std::endl;
                    if(!checkRange(x*y)){
                        return 'o';
                    }
                    pilha.push(x*y);
                    //printPilha(pilha);
                    //std::cout << std::endl;
                    break;
                
                case '/':
                    //std::cout << "X / Y → "<<x<<" / "<<y<<std::endl;
                    if(y==0){
                        return 'z';
                    }
                    if(!checkRange(x/y)){
                        return 'o';
                    }
                    pilha.push(x/y);
                    //printPilha(pilha);
                    //std::cout << std::endl;
                    break;
                
                case '^':
                    //std::cout << "X ^ Y → "<<x<<" ^ "<<y<<std::endl;
                    if(!checkRange(std::pow(x,y))){
                        return 'o';
                    }
                    pilha.push(std::pow(x,y));
                    //printPilha(pilha);
                    //std::cout << std::endl;
                    break;
                case '%':
                    //std::cout << "X % Y → "<<x<<" % "<<y<<std::endl;
                    if(y==0){
                        return 'z';
                    }
                    if(!checkRange(x%y)){
                        return 'o';
                    }
                    pilha.push(x%y);
                    //printPilha(pilha);
                    //std::cout << std::endl;
                    break;
            }
        }
    }
    //std::cout << "Resultado → ";
    return pilha.top();
}


int main( void ) {
    Parser my_parser; // Instancia um parser.
    // Tentar analisar cada expressão da lista.
    std::string expr;
    while(getline(std::cin,expr)){
        // [I] Fazer o parsing desta expressão.
        auto result = my_parser.parse_and_tokenize( expr );
        // Preparar cabeçalho da saida.
        //std::cout << std::setfill('=') << std::setw(80) << "\n";
        //std::cout << std::setfill(' ') << ">>> Parsing \"" << expr << "\"\n";
        // Se deu pau, imprimir a mensagem adequada.
        if ( result.type != Parser::ResultType::OK ){
            print_error_msg( result, expr );
            //exit(0);
        }
        else{}
            //std::cout << ">>> Expression SUCCESSFULLY parsed!\n";

         // [II] Recuperar a lista de tokens.
        auto lista = my_parser.get_tokens();
        //std::cout << ">>> Tokens: { ";
        //std::copy( lista.begin(), lista.end(),
        //        std::ostream_iterator< Token >(std::cout, " ") );
        //std::cout << "}\n";
        //std::cout << std::endl;

        //std::cout << "EXPRESSÃO → ";
        
        //std::vector<std::string>exp;
        std::vector<std::string>exp;
        for(const auto & i : lista){
            //std::cout << i.value << " ";
            exp.push_back(i.value);
        }
        //std::cout << std::endl;
        //std::cout << "FINAL → " << exp << std::endl;
        //std::cout << "intoPos → " << inToPos(exp) << std::endl;
        if(result.type == Parser::ResultType::OK){
            int resposta = resultado(inToPos(exp));
            if(resposta == 'z'){
                std::cout <<"Division by zero!"<< std::endl;
            }else if(resposta == 'o'){
                std::cout <<"Numeric overflow error!"<< std::endl;
            }else{
                std::cout << resposta << std::endl;
            }
        }
    }
    std::cout << "\n>>> Normal exiting...\n";

    return EXIT_SUCCESS;
}

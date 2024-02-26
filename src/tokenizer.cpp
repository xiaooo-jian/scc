#include <tokenizer.h>


void Tokenizer::token_add(TokenType tok,string val,int line,int col){
    tokens.push_back(Token(tok,val,line,col));
}

bool Tokenizer::is_num(char c){
    if(c >= '0' && c <= '9'){
        return true;
    }
    return false;
}

void Tokenizer::tokenize(string src){
    int cur = 0 ,pre;
    int line = 0;
    int col;
    int size = src.size();
    while(cur < size){
        pre = cur;
        switch(src[cur]){
            case ' ':
                cur++;
                break;
            case '\n':
                line++;
                col = 0;
                cur ++;
                break;
            case '+':
                token_add(Tok_plus,"+",line,col); // 以后需要对token存取的东西进行扩充，还需要保存token的位置
                cur ++;
                break;
            case '-':
                token_add(Tok_minus,"-",line,col);
                cur ++;
                break;
            case '*':
                token_add(Tok_mul,"*",line,col);
                cur ++;
                break;
            case '/':
                token_add(Tok_div,"/",line,col);
                cur ++;
                break;
            case '(':
                token_add(Tok_lbak,"(",line,col);
                cur++;
                break;
            case ')':
                token_add(Tok_rbak,")",line,col);
                cur++;
                break;
            case '=':
                if(src[cur + 1] == '='){
                    token_add(Tok_eq,"==",line,col);
                    cur += 2;
                }
                break;
            case '!':
                if(src[cur + 1] == '='){
                    token_add(Tok_neq,"!=",line,col);
                    cur += 2;
                }
                break;
            default:
                if(is_num(src[cur])){
                    int num = 0;
                    while(cur < size && is_num(src[cur])){
                        num = num * 10 + (src[cur] - '0');
                        cur++;
                    }
                    token_add(Tok_num,to_string(num),line,col);
                    break;
                }
                ERROR("Invalid character: %c" , src[cur]);
        }
        
        col += cur - pre;
    }
}


void Tokenizer::token_display(){
    for(auto &token : tokens){
        cout << token.value << ' ';
    }
    cout <<endl;
}
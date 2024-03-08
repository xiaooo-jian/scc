#include <tokenizer.h>


void Tokenizer::token_add(TokenType tok,string val,int line,int col){
    tokens.push_back(Token(tok,val,line,col));
}

void Tokenizer::keywords_init(){
    keywords = {
                    {"return",Tok_return},
                    {"if",Tok_if},
                    {"else",Tok_else},
                    {"for",Tok_for},
                    {"while",Tok_while}
                };
}

bool Tokenizer::is_num(char c){
    if(c >= '0' && c <= '9'){
        return true;
    }
    return false;
}

bool Tokenizer::is_alpha(char c){
    return isalpha(c);
}
bool Tokenizer::is_alphanum(char c){
    return is_alpha(c) || is_num(c) || c=='_';
}
bool Tokenizer::is_keyword(string str){
    if(keywords.find(str) != keywords.end()){
        return true;
    }
    return false;
}


void Tokenizer::tokenize(string src){
    keywords_init();
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
            case ';':
                token_add(Tok_seg,";",line,col);
                cur++;
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
            case '&':
                token_add(Tok_addr,"&",line,col);
                cur++;
                break;
            case '=':
                if(src[cur + 1] == '='){
                    token_add(Tok_eq,"==",line,col);
                    cur += 2;
                }else{
                    token_add(Tok_assign,"=",line,col);
                    cur ++;
                }
                break;
            case '!':
                if(src[cur + 1] == '='){
                    token_add(Tok_neq,"!=",line,col);
                    cur += 2;
                }
                break;
            case '>':
                if(src[cur + 1] == '='){
                    token_add(Tok_req,">=",line,col);
                    cur += 2;
                }else{
                    token_add(Tok_rt,">",line,col);
                    cur ++;
                }
                break;
            case '<':
                if(src[cur + 1] == '='){
                    token_add(Tok_leq,"<=",line,col);
                    cur += 2;
                }else{
                    token_add(Tok_lt,"<",line,col);
                    cur ++;
                }
                break;
            case '{':
                token_add(Tok_lcul,"{",line,col);
                cur ++;
                break;
            case '}':
                token_add(Tok_rcul,"}",line,col);
                cur ++;
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

                if(is_alpha(src[cur])){
                    string name = string(1,src[cur++]);
                    while(cur < size && is_alphanum(src[cur])){
                        name += src[cur];
                        cur++;
                    }
                    if(is_keyword(name))
                        token_add(keywords[name],name,line,col);
                    else
                        token_add(Tok_ident,name,line,col);
                    break;
                }
                ERROR("Invalid character: %c" , src[cur]);
        }
        
        col += cur - pre;
    }
    token_add(Tok_eof,"",line,col);
}


void Tokenizer::token_display(){
    for(auto &token : tokens){
        cout << token.value << ' ';
    }
    cout <<endl;
}
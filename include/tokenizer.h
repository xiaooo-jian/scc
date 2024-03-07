#include <common.h>

class Tokenizer
{
public:
    Tokenizer(){
        
    };
    ~Tokenizer(){};

    unordered_map<string,TokenType> keywords;
    vector<Token> tokens;
    void tokenize(string str);
    void keywords_init();
    bool is_num(char c);
    bool is_alpha(char c);
    bool is_alphanum(char c);
    bool is_keyword(string str);
    void token_display();
    void token_add(TokenType tok,string val,int line,int col);
    
};
#include <common.h>





class Tokenizer
{
public:
    Tokenizer(){};
    ~Tokenizer(){};

    vector<Token> tokens;
    void tokenize(string str);

    bool is_num(char c);
    bool is_alpha(char c);
    bool is_alphanum(char c);
    void token_display();
    void token_add(TokenType tok,string val,int line,int col);
    
};
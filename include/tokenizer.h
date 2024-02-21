#include <common.h>





class Tokenizer
{
public:
    Tokenizer(){};
    ~Tokenizer(){};

    vector<Token> tokens;
    void tokenize(string str);

    bool is_num(char c);

    void token_display();
    void token_add(TokenType tok,string val,int line,int col);
    
};
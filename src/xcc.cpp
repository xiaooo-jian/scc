#include <common.h>
#include <xcc.h>



void Xcc::load(string file_name){
    ifstream fin;
    fin.open(file_name, ios::in);
    if (!fin.is_open())
    {
        cout << file_name << " open filded. " << fin.bad() <<  endl;
        exit(-1);
    }

    string buf;
    while (getline(fin, buf))
    {
        src += buf;
        src += '\n';
    }

    fin.close();
}

void Xcc::compile(){
    Tokenizer tokenizer;
    tokenizer.tokenize(src);
    
    tokenizer.token_display();

    Parser parser;
    parser.tokens = vector<Token>(tokenizer.tokens);
    // cout << "parser !"  << parser.tokens.size() << endl;
    parser.parse();
    // parser.parserDisplay(parser.root);

    Codegen codegen;
    codegen.root = parser.root;
    codegen.codegen("test.s");
}
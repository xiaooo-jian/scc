#include <common.h>
#include <xcc.h>



void Xcc::load(string file_name){
    if(file_name != "./test/print"){
        src = file_name;
        return;
    }
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
    // cout << "tokenizer success !" << endl;

    Parser parser;
    parser.tokens = vector<Token>(tokenizer.tokens);
    // cout << "parser !"  << parser.tokens.size() << endl;
    Function* func = parser.parse();
    // parser.parserDisplay(func->stmts[0],0);
    cout << "parser success !" << endl;
    Codegen codegen;
    codegen.func = func; 
    codegen.codegen("test.s");

    cout << "codegen success !" << endl;
}
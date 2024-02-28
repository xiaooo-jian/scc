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

    Parser parser;
    parser.tokens = vector<Token>(tokenizer.tokens);
    // cout << "parser !"  << parser.tokens.size() << endl;
    parser.parse();
    // parser.parserDisplay(parser.roots[0]);

    Codegen codegen;
    codegen.roots = vector<AST_node*>(parser.roots); 
    codegen.codegen("test.s");
}
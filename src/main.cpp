#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <cstring>
#include <xcc.h>
using namespace std;

int main(int argc, char *argv[])
{
    Xcc xcc;
    xcc.load(argv[1]);
    xcc.compile();
}
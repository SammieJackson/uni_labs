//#include "copyright.h"
#include "interface.h"
#include "builder.h"
#include <windows.h>
#include "myExceptions.h"
#include <iostream>

int main(int argc, char** argv)
{
//    copyright();
    info();
    bnf();
    string inFileName;
    getInFile(argc, argv, inFileName);

    Championship c;
    Builder b(c);

    try{
    b.build(inFileName);
    //c.print();
    c.findBestAim();
    string outFileName;
    getOutFile(outFileName);
    c.printResults(outFileName);
    }
    catch(builderExcept &e){cout<<"Build failed."<<endl<<e.what()<<endl;}
    catch(containerExcept &e){cout<<"Information container exception caught:"<<endl<<e.what()<<endl;}
    catch(std::exception &e){cout<<"Standard exception caught:"<<endl<<e.what()<<endl;}
    catch(...){cout<<"Unexpected exception caught."<<endl;}

    system("pause");
    return 0;
}

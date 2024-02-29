#include <string>
#include <random>
#include "tree.hpp"
#include "menu.hpp"

using namespace std;

Menu::Menu(){}

void Menu::showMenu(){
    int condition = 0, n;
    cout<<"BIENVENIDO"<<endl;
    do{
        cout<<"Ingrese un valor 'n': ";
        cin>>n;

        int i = 0;
        while(i < n){
            int num = randomNum();
            cout<<i+1<<".Numero: "<<num<<endl;
            tree.insertData(num);
            i++;
            }
        cout<<"PRE ORDER: ";
        tree.parsePreOrder();
        cout<<endl<<endl<<"IN ORDER: ";
        tree.parseInOrder();
        cout<<endl<<endl<<"POST ORDER: ";
        tree.parsePostOrder();
        cout<<endl<<endl<<"Altura del subarbol izquierdo: "<<tree.getLeftHeight()<<endl;
        cout<<"Altura del subarbol derecho: "<<tree.getRightHeight()<<endl;
        cout<<endl<<"Elemento Mayor: "<<tree.retrieve(tree.getHighest())<<endl;
        cout<<"Elemento Menor: "<<tree.retrieve(tree.getLowest())<<endl;

        cout<<endl<<"¿REPETIR"<<endl;
        cout<<"1.Si\n2.No\nOpcion:";

        cin>>condition;
            
        }while(condition != 2);
    cout<<endl<<"ADIOS";
    }

int Menu::randomNum(){
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> distribution(0,100000);

    int num = distribution(gen);
    return num;
    }
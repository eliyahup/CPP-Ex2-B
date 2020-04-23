#pragma once
#include <iostream>
#include <string>


using namespace std;
class node {

public:
    string name;
    node *son = nullptr;
    node *father =nullptr;
    node *mother =nullptr;

    node();

    node(string name);

    friend class Tree;

};
namespace family{

    class Tree{
        node *root = nullptr;
    public:

        Tree(string san){
            root = new node(san);
        }
        void search(node* root, string son);
        Tree& addFather(string son,string father);
        Tree& addMother(string son,string mother);
        string relation(string relation);
        void display();
        string find(string relation);
        void remove(string name);
    };


}









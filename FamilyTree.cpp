#include "FamilyTree.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace family;
#include <algorithm>
#define COUNT 10


node::node(string name1)
{
    name = name1;
    node *son = nullptr;
    node *father = nullptr;
    node *mother= nullptr;

}

void Tree::search(node* root2,string son){
    if (root2 == nullptr) {
        return ;
        }
     else if(son==root2->name) {
        this->root = root2;
    }
     search(root2->father, son);
     search(root2->mother, son);


    }



Tree& Tree::addFather(string son,string father){
    node* root2 = root;
    search(root,son);
       if(root->name != son){
           root=root2;
       throw invalid_argument("name of add not found");
   }
     if(son==(root->name)&&root->father!=nullptr){
         root=root2;
             throw invalid_argument("duplicate father");
        }
    if(root!=nullptr){
        if(son==(root->name)&&root->father==nullptr){
            root->father = new node(father);
            root->father->son = root;
        }
    }
    root=root2;
    return *this;
}
Tree& Tree::addMother(string son,string mother){
    node* root2 = root;
    search(root,son);
    if(root->name != son){
        root=root2;
       throw invalid_argument("name of add not found");
   }
     if(son==(root->name)&&root->mother!=nullptr){
         root=root2;
             throw invalid_argument("duplicate mother");
        }
    if(root!=nullptr){
        if(son==(root->name)&&root->mother==nullptr){
            root->mother = new node(mother);
            root->mother->son = root;
        }
    }
    root=root2;
    return *this;
}
string Tree::relation(string relation) {
    node *root2 = root;
    search(root, relation);
    if (root->name == relation && root->name == root2->name) {
        root = root2;
        return "me";
    } else if (root->name == relation && root->son->name == root2->name && root->son->father->name == root->name) {
        root = root2;
        return "father";
    } else if (root->name == relation && root->son->name == root2->name && root->son->mother->name == root->name) {
        root = root2;
        return "mother";
    } else if (root->name == relation && root->son->son->name == root2->name &&root->son->father!=nullptr &&root->son->father->name == root->name) {
        root = root2;
        return "grandfather";
    } else if (root->name == relation && root->son->son->name == root2->name &&root->son->mother!=nullptr &&root->son->mother->name == root->name) {
        root = root2;
        return "grandmother";
    } else if(root->name == relation ) {
        node *root3 = root;
        string ans = "";
        int count = 0;
        while (root->son != nullptr) {
            count++;
            root = root->son;
        }
        while (count > 2) {
            ans += "great-";
            count--;
        }
        if (root3->son->father!=nullptr&&root3->son->father->name == root3->name) {
            root = root2;
            return ans + "grandfather";
        } else if (root3->son->mother!=nullptr&&root3->son->mother->name == root3->name) {
            root = root2;
            return ans + "grandmother";
        }
    }
        root = root2;
        return "unrelated";

}
     //https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void print2DUtil(node *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->mother, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->name<<"\n";

    // Process left child
    print2DUtil(root->father, space);
}

// Wrapper over print2DUtil()
void print2D(node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}


void Tree::display(){
    cout<<"======================================================="<<endl;
    node* root2 = root;
    print2D(root);
    root=root2;
    cout<<"======================================================="<<endl;

}

string Tree::find(string relation){
    transform(relation.begin(), relation.end(), relation.begin(), ::tolower);
    if(relation=="mother"&&root->mother!=nullptr)
        return root->mother->name;
    else if(relation=="father"&&root->father!=nullptr)
        return root->father->name;
    else if(relation=="grandfather"&&root->mother->father!=nullptr)
        return root->mother->father->name;
    else if(relation=="grandfather"&&root->mother->mother!=nullptr)
        return root->mother->mother->name;
    else if(relation=="grandfather"&&root->father!=nullptr&&root->father->father!=nullptr)
        return root->father->father->name;
    else if(relation=="grandmother"&&root->father->mother!=nullptr)
        return root->father->mother->name;
    else if(relation=="great-grandmother"&&root->mother->father->mother!=nullptr)
        return root->mother->father->mother->name;
    else if(relation=="great-grandfather"&&root->mother->father!=nullptr&&root->mother->father->father!=nullptr)
    return root->mother->father->father->name;

    else {
        
        int count = 0;
        string word = "";
        bool b = true;
        int i = 0;
        for (; i < relation.length(); ++i) {
            for (int j = 0; i + j < relation.length() && relation[i + j] != '-'; ++j) {
                word += relation[i + j];
            }
            if (word == "great") {
                ++count;
                word = "";
            } else{
                while (i < relation.length() && relation[i] != '-') {
                    ++i;
                }
                break;
            }
            while (i < relation.length() && relation[i] != '-') {
                ++i;
            }
        }
        node* root2 = root;

        if (word == "grandfather"&&i>=relation.length()){
          while(count>0){
               if(root2->father==nullptr||root2->father->father==nullptr)
                  throw invalid_argument("The tree cannot handle the "+relation + " relation");
              root2 = root2->father;
              count--;
          }
          if(root2->father->father!=nullptr)
            return root2->father->father->name;
        }

        if (word == "grandmother"&&i>=relation.length()){
            while(count>0){
                if(root2->father==nullptr||root2->father->father==nullptr)
                  throw invalid_argument("The tree cannot handle the "+relation + " relation");
                root2 = root2->father;
                count--;
            }
             if(root2->father->mother!=nullptr)
            return root2->father->mother->name;
        }



        throw invalid_argument("The tree cannot handle the "+relation + " relation");
       

    }
}
void Tree::remove(string name){
    node *root2 = root;
    search(root, name);
   if(root->name==root2->name){
       root=root2;
       throw invalid_argument("can't remove the root of tree");
   }
   if(root->name != name){
       root=root2;
       throw invalid_argument("name of remove not found");
   }
   //cout<< root->name<<endl;
   if(root->son->father!=nullptr&&root->name==root->son->father->name){
    root->son->father = nullptr;
   }
   if(root->son->mother!=nullptr&&root->name==root->son->mother->name){

    root->son->mother = nullptr;
   }
    root=root2;
}





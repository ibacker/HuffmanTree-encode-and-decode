#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
//#program once
#ifndef M_H
#define M_H
//
// Created by ibacker on 12/25/18.
//

#include<string.h>
#include<iostream>
#include<limits>
#include<fstream>
using namespace std;
class HuffmanNode{
public:
    char letter;
    double weight;
    int parent;
    int lchild;
    int rchild;
    HuffmanNode(){
        parent=lchild=rchild=-1;
    }
    HuffmanNode(char nchar,double nweight,int nparent,int nlchild,int nrchild){
        this->letter=nchar;
        this->weight=nweight;
        this->parent=nparent;
        this->lchild=nlchild;
        this->rchild=nrchild;
    }
        HuffmanNode(const char &data, const double &wt, const int &pa=-1, const int &lch=-1, const int &rch=-1) {
        letter=data;
        weight=wt;
        parent=pa;
        lchild=lch;
        rchild=rch;
    }
    ~HuffmanNode(){
        parent=lchild=rchild=-1;
    }
};

class HuffmanTree{
private:
    char *code;
    HuffmanNode *nodeArray;
    int maxSize;
    int currentSize;
public:

    void insert(const char &nletter);//insert nodes to tree

    int Min(int i);//return the min element
    void select(int i,int &,int &);//select two min elements
    void show();//print the
    bool checkReaped(char);
    int findposition(char); //return the position of letter
    void remove(char);

    HuffmanTree(const int &s=100){maxSize=(s>100?s:100);currentSize=0;nodeArray=new HuffmanNode[maxSize];}
    void init();
    //~HuffmanTree(){delete[] nodeArray;}
    void CreateHuffmanTree();
    void creat();//creat  huffman tree
    void CreateHuffmanCode();
    void Ccode();

    void decode(char*);
    int decode_char(char*);

    void writeFile();
    void weight_sort();

    int getLen();
    int* getWei();

    public:
    class Code { //HuffmanTree的私有类，编码类
    public:
        Code():length(10) { ptr=new char[length]; }
        ~Code() { delete[] ptr; }
        char *ptr;
        const int length;
    };
    Code *codeArray; //数组大小为currentSize
    void reverse(char arr[]);
};


//int main(){
//    // char arr[4]={'a','b','c','a'};
//    char buff[1024];
//    cout<<"input string:";
//    cin.getline(buff,1024);
//    int n=0;

//    for(int i=0;i<strlen(buff);i++){
//        if(buff[i]>126 || buff[i]<32)
//        {cout<<"------out of ASCII table--------"<<endl;
//            cout<<"continue or not(Y/N):";
//            char temp;
//            cin>>temp;

//            if (temp=='Y'||temp=='y')
//                break;
//            else
//                return 0;
//        }
//    }
//    HuffmanTree tree;
//    for(int i=0;i<strlen(buff);i++){
//        tree.insert(buff[i]);
//    }
//   // tree.CreateHuffmanTree();
//    tree.creat();  //creat with ccode works well, detecting the warnings
//    tree.Ccode();
// //   tree.CreateHuffmanCode();
//    tree.show();
//    tree.remove('n');
//    cout<<endl;
//    tree.CreateHuffmanTree();tree.CreateHuffmanCode();
//    tree.show();
//    cout<<endl;
//    char s[10];
//    cin.getline(s,10);
//    tree.decode(s);
//}

#endif

#endif // HUFFMANTREE_H

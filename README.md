# 哈夫曼码编/译系统的设计与实现

### 问题描述
在通信联络中传递信息和文件的压缩通常是通过二进制数的编码来实现的。一个对原始信息高效的编码方式可以让信息的传递与文件压缩变得更加的迅速和高效。传统的编码方式，如等长编码，会造成编码位数的浪费。对每一个字符都进行同样长度的编码在数据传输过程中增加了数据丢失的风险，在对文件的压缩过程中更是没有达到精简编码压缩内存的要求。哈夫曼编码是可变长编码(VLC)的一种，通过对不同估算概率字符进行权重不同的编码，能够使得编码位数最短，识别效率更高，信息传送更高效和压缩效率更高。为了实现对字符编码和二进制码的翻译，该系统能够实现对输入字符根据权重不同的自动编码并给出字符对应的二进制编码，对输入的二进制数能够进行对应译码。
### 设计要求
该系统能够实现对用户输入字符的自动获取，并统计不同字符的权重，再根据统计出的源字符估算概率建立一个哈夫曼树。输入的所有不相同字符都包含在哈夫曼树中(最优二叉树)。从建立树的最高位根结点开始，根据”左1右0“的规则，对处于该树中的所有叶子结点进行编码。每一个叶子结点都能够获得一个唯一的二进制编码。在对字符进行哈夫曼编码之后，对输入的二进制数，系统可以自动判别该二进制数是否对应一个字符，并在和字符对应的情况下，输出该字符实现译码。如果该二进制数并不对应编码字符，给出输入的错误。此外，该编码系统实现了下列功能：
1. 初始化（initialization）。对输入的字符读取字符集大小n，以及n个字符所对应权值，建立哈夫曼树。
2. 编码（encode）。利用已建立好的哈夫曼树，对字符进行编码，并将编码及对应字符存放与文件code.txt中。
3. 打印代码文件（prin）。将文件code.txt中的字符和字符编码以紧凑格式输出。
4. 译码（decode）。对已经建立成树并编码的字符，输入二进制编码译出对应的字符，如果输入的二进制编码错误返回出错的位置。将译码存放于文件binary.txt中。
5. 建树过程（chart）。根据字符的不同权重，模拟哈夫曼树的建立过程，将整个最优二叉树的生成过程通过动态过程展现出来。

### 算法思想
哈夫曼编/译码系统是对哈夫曼编码方式的实现。哈夫曼编码通过对每一个源字符出现的估算概率不同，将出现概率大，权重大的字符放在更靠近二叉树根结点的位置，出现概率小，权重小的字符放在更远的位置。这使得编码之后的字符串平均期望长度降低。(出现概率高的字符使用较短编码，反之出现概率低的字符使用较长编码)
##### 编码
哈夫曼的编码过程实际上是一个最优二叉树建立的过程。根据源字符的数量n建立一个具有n个叶子结点的二叉树。其建立是一个自低向上的过程。首先，将n个源字符按照权重从小到大的顺序排列。选取排列中相当最小的两个字符，将其构成一棵二叉树，并将其根结点继续放在排列中。在从接下来的n-1个排列中选取相对最小的两个源字符或根结点，按照左小右大的方式构成一棵二叉树。重复该过程，使的排列中的所有源字符都在一棵二叉树中且都为叶子结点。
对已经建立的二叉树进行编码，从树的根结点开始，按照左1右0的格式，对哈夫曼树中的路径进行表示。将所有的叶结点（源字符）按照路径顺序用01表示。最后得到所有源字符的二进制编码。
    
##### 译码
在已经编码的哈夫曼树中，每一个源字都对应了一个唯一的二进制编码。译码的过程就是通过这个二进制编码找到对应的源字符过程。系统读入用户输入的二进制哈夫曼序列，从哈夫曼树的根结点开始，当读取到0，从根结点的左孩子继续读取过程，当读取到1，从根结点的右孩子继续读取。如果读取到一个结点的左孩子与右孩子都不存在，则说明已经读到一个叶子结点（源字符），将这一串序列和已经编码的序列进行比较，即翻译一个字符成功。把该叶子结点代表的字符存放在一个存储翻译字符的数组中，然后从根结点继续译码过程。

### 模块划分
哈夫曼编/译系统可以分为以下几模块，哈夫曼树建立、哈夫曼编码、二进制译码、文件处理几个模块，每个模块的协同使得系统更加稳固易用。
##### 哈夫曼树的建立
将哈夫曼树中的结点单独处理为一个结点类，该类中包含结点信息所需要的源字符、权值、父结点和左右子结点。
```
class HuffmanNode{
public:
    char letter;  //the source charracter
    double weight;  //the weight of character
    int parent;
    int lchild;
    int rchild;
    HuffmanNode()；
    HuffmanNode(char,double,int,int,int);
    ~HuffmanNode();
};
```
哈夫曼树类中包含一个Node结点数组和一个Code子类，Node数组存储树中的所有结点，Code子类存储叶子结点的哈夫曼编码。
```
class HuffmanTree{
private:
    char *code;  
    HuffmanNode *nodeArray;  //store nodes
    int maxSize;  //maxSize of huffmantree
    int currentSize;  //the currentSize of the tree
public:
    HuffmanTree(const int &s=100){maxSize=(s>100?s:100);currentSize=0;nodeArray=new HuffmanNode[maxSize];}
     void CreateHuffmanTree();  //creat huffman tree
     void CreateHuffmanCode();  //creat huffman code
     ~HuffmanTree(){}
public:
    class Code { //HuffmanTree's private class
    public:
        Code():length(10) { ptr=new char[length]; }
        ~Code() { delete[] ptr; }
        char *ptr;
        const int length;
    };
    void reverse(char arr[]);
};
```
通过一次选择源字符排列中权重相对最小的两个字符构建二叉树，再将二叉树的父结点放入排列中，重复构建过程。最后得到一个只有一个根结点的最优二叉树，即根据源字符构建出的哈夫曼树。
```
void HuffmanTree::CreateHuffmanTree()
{
    int m;
    int i, s1, s2;  //select min node
    if(currentSize<=1) //if only one node return
        return ;
    m=2*currentSize-1; //the total nodes in the tree

    for(i=0; i<m; i++)  //initialize nodes
    {
        nodeArray[i].parent=-1;
        nodeArray[i].lchild=-1;
        nodeArray[i].rchild=-1;
 
    }
    for(i=currentSize; i<m; i++)
    {
        s1=Min(i-1);
        s2=Min(i-1);

        nodeArray[s1].parent=i;
        nodeArray[s2].parent=i;//add to the parent

        nodeArray[i].lchild=s1;
        nodeArray[i].rchild=s2;//set as left and right child
        nodeArray[i].weight=nodeArray[s1].weight+nodeArray[s2].weight;//add the min node and put the new node into the sort
    }
}
```
##### 哈夫曼编码
对已经建立的二叉树进行编码，从树的根结点开始，按照左1右0的格式，对哈夫曼树中的路径进行表示。将所有的叶结点（源字符）按照路径顺序用01表示。最后得到所有源字符的二进制编码。
```
void HuffmanTree::CreateHuffmanCode(){
    codeArray=new Code[currentSize]; //store the huffman code
    int i=0;
    int k, n, m;
    while (i < currentSize) {
        k = nodeArray[i].parent;
        n=0;
        m=i;
        while (k!=-1 && k<currentSize*2-1) {//circulate the progress
            if (m==nodeArray[k].lchild)
                codeArray[i].ptr[n++]='0'; //if the node is leftchild add 0
            else if(nodeArray[k].rchild==m)
                codeArray[i].ptr[n++]='1';  //if the node is rightchild ass 1
            m=k;
            k=nodeArray[m].parent;
        }
        codeArray[i].ptr[n]='\0';
        reverse(codeArray[i].ptr); //reverse the code
        i++;
    }
    weight_sort();  //sort the node into sequence

}
```
其中reverse()反转字符串，使得哈夫曼编码的顺序正确，weight_sort()将已经编码完成的字符按照权重大小重新排序。
##### 二进制译码
将读入的二进制序列，与译码得到的哈夫曼编码对比，找到对应的源字符，并将结果输出。记录每次比较的编码位置，如果没有找到，输出错误位信息。
```
void HuffmanTree::decode(char *arr){
    int len=strlen(arr);  //the lonth of decode array
    char sen[100];
    char temp[50]; //store current binary code input
    char voidstr[]=" ";
    int t=0;   //
    int s=0;  //the decoded char 
    int xx=0;  //position of binary code comparing
    for(int i=0;i<len;i++){
        temp[t++]=arr[i];
        temp[t]='\0';  
        for(int j=0;j<currentSize;j++){
            if(!strcmp(codeArray[j].ptr,temp)){ //not much
                sen[s]=nodeArray[j].letter;
                s++;
                xx+=t;
                strcpy(temp,voidstr);  //empty array temp
                t=0;
                break;
            }
        }
    }
    if(t==0){  //find the charecter 
        sen[s]='\0';
        cout<<"char:"<<sen<<endl;
    }
    else{  //have error binary code
        cout<<"error in "<<xx+1<<endl;
    }
}
```
##### 文件处理
对建立哈夫曼树和编码过程中产生的字符信息和编码信息进行处理，将其保存到文本中。把译码文件存放到本地，并在打印代码文件的过程中，提供数据。
```
void HuffmanTree::FileProcess(string address,string rw){
string process_Read="read";
string process_Write="write";
if(rw == process_Write)  //write file in memory
    fstream file("address",ios::out|ios::trunc);
    for(int k=0;k<currentSize;k++){
        file<<nodeArray[k].letter<<" ("<<nodeArray[k].weight<<"): "<<codeArray[k].ptr<<endl;
    }
if(rw == process_Read){
    fstream file("address",ios::out|ios::trunc);
        for(int i=0;i<strlen(sen);i++){
            file<<sen[i];
        }
}
    file.close();
}
```
### 数据结构
##### 二叉树
二叉树是树的特殊一种，具有如下特点：
1. 每个结点最多有两颗子树，结点的度最大为2。
2. 左子树和右子树是有顺序的，次序不能颠倒。
3. 即使某结点只有一个子树，也要区分左右子树。

所有的分支结点都存在左子树和右子树，并且所有的叶子结点都在同一层上，这样就是满二叉树。能够实现存储更多的结点，其关键在于保证了树的平衡。
根据满二叉树的定义，得到其特点为：
* 叶子只能出现在最下一层。
* 非叶子结点度一定是
* 在同样深度的二叉树中，满二叉树的结点个数最多，叶子树最多。

##### 哈夫曼树
哈夫曼编码是通过构建哈夫曼树来实现的。哈夫曼编码树也被称为最优树，是一种带权路径长度最短的二叉树。所谓树的带权路径长度，就是树中所有的叶结点的权值乘上其到根结点的路径长度（若根结点为0层，叶结点到根结点的路径长度为叶结点的层数）。树的路径长度是从树根到每一结点的路径长度之和，记为WPL=（W1*L1+W2*L2+W3*L3+...+Wn*Ln），N个权值Wi（i=1,2,...n）构成一棵有N个叶结点的二叉树，相应的叶结点的路径长度为Li（i=1,2,...n）。构建的哈夫曼树是一棵满二叉树，其中所有的叶结点都对应一个源字符。在实现树结构的过程中，用以为数组的相对位置来表示存储二叉树。根据叶结点的个树n，可以计算得出整个满二叉树需要2n-1个结点来表示。将根结点存放在0位置，以后假定当前位置为i，那么左子结点在2i+1，右子结点在2i+2。其递归实现为：
```
void btreeArray(node, index)
{ 
    if(node == NULL) 
    array[index] = empty;
    array[index] = node->value;
    btreeArray(node->left, index * 2 + 1);
    btreeArray(node->right, index * 2 + 2);
}  
```
通过调用`
btreeArray(root,0);
`实现初始化。

### 源程序
源程序已打包为附件上传
### 测试数据
输入测试源字符”*THIS PROGRAM IS MY FAVORITE*“，对程序进行测试。对源字符编码得，
````
(4): 100  //spacetab
R (3): 010
I (3): 001
A (2): 1100
S (2): 1010
O (2): 1011
T (2): 0111
M (2): 1101
E (1): 0110
V (1): 0001
F (1): 0000
Y (1): 11111
G (1): 11110
P (1): 11101
H (1): 11100
````
哈夫曼编码按照频率高低排序。
输入二进制数`0101000011100`,选择译码，得到译码结果`R IA`其中第二个字符100为空格。
输入二进制数`01010001`，选择译码，系统提示错误，第7个字符无法对应生成的编码。

### 测试情况
对于输入的测试源字符”*THIS PROGRAM IS MY FAVORITE*“，系统能够高效快速的对字符进行统计编码并生成code文件。在键入二进制编码后，能够准确的识别生成编码中的是否存在对应字符，如果存在能准确输出该字符，如果不存在则输出错误位是多少。







    
  

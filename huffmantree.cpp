#include"1.h"
void HuffmanTree::insert(const char &data) { //插入结点
    if (2*currentSize-1 >= maxSize) //叶子结点为n的哈夫曼树共有2n-1个结点
        return;
    if(checkReaped(data)){
        nodeArray[currentSize].letter=data;
        nodeArray[currentSize].weight=1;
        currentSize++;}
    else{

        nodeArray[findposition(data)].weight++;
    }

}
// void HuffmanTree::insert(const char nletter){
// 	if(2*currentSize-1>maxSize) return;//out of range
// 	nodeArray[currentSize].letter=nletter;
// 	currentSize++;
// }
void HuffmanTree::creat(){
    if(currentSize<=1) return;
    int i=currentSize;
    int k;
    double wt1, wt2;
    int lnode=0;int rnode=0;
    while (i < 2*currentSize-1) {
        wt1=wt2=std::numeric_limits<double>::max();

        k=0;
        while (k < i) {
            if (nodeArray[k].parent==-1) {
                if (nodeArray[k].weight<wt1) {
                    wt2=wt1;
                    rnode=lnode;
                    wt1=nodeArray[k].weight;
                    lnode=k;
                }
                else if (nodeArray[k].weight<wt2) {
                    wt2=nodeArray[k].weight;
                    rnode=k;
                }
            }
            k++;
        }
        nodeArray[i].weight = nodeArray[lnode].weight+nodeArray[rnode].weight;
        nodeArray[i].lchild=lnode;
        nodeArray[i].rchild=rnode;
        nodeArray[lnode].parent=nodeArray[rnode].parent=i;
        i++;
    }

}

int HuffmanTree:: Min(int i)
{
    //unsigned int k = UINT_iMAX;
    double iMax= std::numeric_limits<double>::max();

    int flag=0;
    for(int j = 0; j <= i; ++j)
    {
        if(nodeArray[j].weight < iMax && nodeArray[j].parent == -1)
        {
            iMax = nodeArray[j].weight;
            flag = j;
        }
    }
    nodeArray[flag].parent = 0;
    return flag;
}

void HuffmanTree::select(int i,int &s1,int&s2){
    s1=Min(i);
    s2=Min(i);
}

void HuffmanTree::show() { //打印编码
    int k=0;
    while (k < currentSize) {
        cout<<nodeArray[k].letter<<'('<<nodeArray[k].weight<<"): "<<codeArray[k].ptr<<endl;
        k++;
    }
}

void HuffmanTree::CreateHuffmanTree()
{
    //cout<<"nihao1"<<endl;
    int m;
    int i, s1, s2;
    if(currentSize<=1)//Èç¹ûÖ»ÓÐÒ»¸ö¾Í²»ÓÃ´´½¨
        return ;
    m=2*currentSize-1; //×Ü¹²ÐèÒª2n£­1¸ö½Úµã
  //  HuffmanNode *nod=new HuffmanNode[m+1];//¿ª±Ù¿Õ¼ä
   // nodeArray = new HuffmanNode[m];
    for(i=0; i<currentSize; i++)
    {
       // nod[i].letter='\0';
        nodeArray[i].parent=-1;
        nodeArray[i].lchild=-1;
        nodeArray[i].rchild=-1;
       // nod[i].letter=nodeArray[i].letter;
        //nod[i].weight=nodeArray[i].weight;

    }
    for(i=currentSize; i<=m; i++)
    {
       // nodeArray[i].letter='\0';
        nodeArray[i].parent=-1;
        nodeArray[i].lchild=-1;
        nodeArray[i].rchild=-1;


    }
    cout<<"++++++++++++++"<<endl;
    for(i=currentSize; i<m; i++)
    {
        //select(i-1,s1, s2);//ÔÚn¸öÊýÖÐÕÒ³öÈ¨Öµ×îÐ¡µÄÁ½¸ö
        s1=Min(i-1);
        s2=Min(i-1);
        // cout<<"Min is working"<<endl;
        nodeArray[s1].parent=i;
        nodeArray[s2].parent=i;//½«ËûÃÇÁ½¸öµÄparent½ÚµãÉèÖÃÎªi;

        nodeArray[i].lchild=s1;
        nodeArray[i].rchild=s2;//°ÑÕâÁ½¸ö·Ö±ðµ±×÷×óÓÒ½Úµã
        nodeArray[i].weight=nodeArray[s1].weight+nodeArray[s2].weight;//ËûÃÇÁ½¸öµÄË«Ç×ÎªËûÃÇÁ½¸öµÄºÍ£»
//
    }
    //nodeArray=nod;
}

bool HuffmanTree::checkReaped(char ch){
    for(int i=0;i<currentSize;i++){
        if(ch==nodeArray[i].letter)
            return false;
    }
    return true; //no reaped letter
}

int HuffmanTree::findposition(char ch){
    for(int i=0;i<currentSize;i++){
        if(ch==nodeArray[i].letter)
            return i;
    }
}
void HuffmanTree::CreateHuffmanCode(){
    codeArray=new Code[currentSize];
    int i=0;
    int k, n, m;
    while (i < currentSize) {
        k = nodeArray[i].parent;
        n=0;
        m=i;
        while (k!=-1 && k<currentSize*2-1) {
            if (m==nodeArray[k].lchild)
                codeArray[i].ptr[n++]='0';
            else if(nodeArray[k].rchild==m)
                codeArray[i].ptr[n++]='1';
            m=k;
            k=nodeArray[m].parent;
        }
        codeArray[i].ptr[n]='\0';
        reverse(codeArray[i].ptr); //反转字符串，使之变成正确的编码
        i++;
    }
    weight_sort();

}

void HuffmanTree::reverse(char arr[]) { //反转字符串
    const int len=strlen(arr);
    char *p;
    p=new char[len+1];
    strcpy(p, arr);
    p[len]='\0';
    int k=0;
    for (int i=len-1; i>=0; i--)
        arr[i]=p[k++];
    arr[len]='\0';
    delete[] p;
}
void HuffmanTree::Ccode()
{
    int start, c, f;
    int i;
    codeArray=new Code[currentSize];
    char *cd=new char [currentSize];
    int n=currentSize;
    cd[currentSize-1]='\0';
    HuffmanNode *HT=nodeArray;
    //for(i=0; i<2*n; i++)
    //	cout<<HT[i].letter<<":"<<HT[i].lchild<<":"<<HT[i].rchild<<HT[i].weight<<endl;
    //cout<<"×Ö·û±àÂëÎª£º"<<endl;
    for(i=0; i<n; i++)
    {

        start=n;
        c=i;
        f=HT[i].parent;

        while(f!=-1){
            --start;
            if(HT[f].lchild==c){

                cd[start]='0';
            }
            else{

                cd[start]='1';
            }
            c=f;
            f=HT[f].parent;
        }

        codeArray[i].ptr=new char[n-start];
        strcpy(codeArray[i].ptr,&cd[start]);
        cout<<HT[i].letter<<":"<<codeArray[i].ptr<<endl;
    }

    delete cd;

}

void HuffmanTree::remove(char nchar){
    for(int i=0;i<currentSize;i++){
        if(nchar == nodeArray[i].letter){
            for(int j=i;j<currentSize;j++)
                nodeArray[j]=nodeArray[j+1];
            currentSize--;
        }
        else
            return ;
    }
}

void HuffmanTree::decode(char *arr){
    int len=strlen(arr);
    char sen[100];
    char temp[50];
    char voidstr[]=" ";
    int t=0;
    int s=0;
    int xx=0;
    for(int i=0;i<len;i++){
        temp[t++]=arr[i];
        temp[t]='\0';
        for(int j=0;j<currentSize;j++){
            if(!strcmp(codeArray[j].ptr,temp)){
                sen[s]=nodeArray[j].letter;
                s++;
                xx+=t;
                strcpy(temp,voidstr);
                t=0;
                break;
            }
        }
    }
    if(t==0){
        sen[s]='\0';
        cout<<"char:"<<endl;

        cout<<sen<<endl;
        fstream file("./decode.txt",ios::out|ios::trunc);
        for(int i=0;i<strlen(sen);i++){
            file<<sen[i];
        }
        file.close();
    }
    else{
        cout<<"error in "<<xx+1<<endl;
    }
}

void HuffmanTree::writeFile(){
    fstream file("./code.txt",ios::out|ios::trunc);
    for(int k=0;k<currentSize;k++){
       // file<<endl;
        file<<nodeArray[k].letter<<" ("<<nodeArray[k].weight<<"): "<<codeArray[k].ptr<<endl;
    }
    file.close();
}


int HuffmanTree::decode_char(char *arr){
    int len=strlen(arr);
    char sen[100];
    char temp[50];
    string ring;
    char voidstr[]=" ";
    int t=0;
    int s=0;
    int xx=0;
    for(int i=0;i<len;i++){
        temp[t++]=arr[i];
        temp[t]='\0';
        for(int j=0;j<currentSize;j++){
            if(!strcmp(codeArray[j].ptr,temp)){
                sen[s]=nodeArray[j].letter;
                s++;
                xx+=t;
                strcpy(temp,voidstr);
                t=0;
                break;
            }
        }
    }
    if(t==0){
        sen[s]='\0';
        cout<<"char:"<<endl;
        cout<<sen<<endl;
        fstream file("./decode.txt",ios::out|ios::trunc);
        for(int i=0;i<strlen(sen);i++){
            file<<sen[i];
        }
        file.close();
        cout<<sen<<endl;
        code=sen;
        return -1;
    }
    else{
        cout<<"error in "<<xx+1<<endl;
        return xx+1;
    }
}
void HuffmanTree::init(){
    nodeArray = nullptr;
    //codeArray = nullptr;
    currentSize = 0;
    code = nullptr;
}
void HuffmanTree::weight_sort(){
    for(int i=0;i<currentSize;i++){
        for(int j=i;j>0;j--)
            if(nodeArray[j].weight >=nodeArray[j-1].weight){
                HuffmanNode no_temp;
                char* co_temp;
                no_temp=nodeArray[j];
                co_temp=codeArray[j].ptr;
                nodeArray[j]=nodeArray[j-1];
                codeArray[j].ptr=codeArray[j-1].ptr;
                nodeArray[j-1]=no_temp;
                codeArray[j-1].ptr=co_temp;
            }
    }
}

int HuffmanTree::getLen(){
    return currentSize;
}
int* HuffmanTree::getWei(){
    int* wei= new int[currentSize];
    for(int i=0;i<currentSize;i++){
        wei[i]=nodeArray[i].weight;
    }
    return wei;
}

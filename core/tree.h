#ifndef TREE_H
#define TREE_H

#define MAX_SIZE_OPTIONS 10
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#include <algorithm>
#include <climits>
#include "node.h"
#include <random>
#include <time.h>
#include <string>
//#include <stream>



class Tree {
private:
    Node * root;
    bool shouldPrint;
    string tree;
public:
    Tree() {
        // string str = "";
        // root = new Node(str, false);
        root = 0;
        shouldPrint = false;
    }

    ~Tree(){
      cout << "Tree eliminando\n";
      delete root;
      root=NULL;
      //delete root;
    }
    void printSons (Node * & node) {
        cout << "*** node: " << node << " ***" << endl;
        for (int i = 0; i < ALPHABET_LENGTH; i++) {
            if (node->sons[i]) {
                cout << "i: " << c(i) << " = " << node->sons[i] << endl;
            }
        }
    }

    void printSons() {
        // printSons(root->sons[p('H')]);
        printSons(root);
    }





    void getWords(Node * & node, vector<string> *dictionary){
        if(dictionary->size() < MAX_SIZE_OPTIONS){

            if(node->isWord)
                dictionary->push_back(node->str);

            vector<string> *temp = new vector<string>();

            for (size_t i = 0; i < ALPHABET_LENGTH; i++)
                if (node->sons[i])
                    getWords(node->sons[i], temp);

            int toFill = MAX_SIZE_OPTIONS - dictionary->size();
            int realTemp = temp->size() > MAX_SIZE_OPTIONS ? toFill : (temp->size() > toFill ? toFill : temp->size());

            for (size_t i = 0; i < realTemp; i++)
                dictionary->push_back(node->str+(*temp)[i]);
        }
    }

bool haveson(){
    bool haveson=false;
    for(int i;i<ALPHABET_LENGTH ;i++){
      if(root->sons[i]!=0){
        haveson =true;
        break;
      }
    }
    return haveson;
  }

bool isleaf(Node * node){
    bool isleaf=true;
    for(int i=0;i<ALPHABET_LENGTH ;i++){
      if(node->sons[i]!=0){
        isleaf =false;
        break;
      }
    }
    return isleaf;
  }

string join(Node * node,Node * next){
    string a=node->str;
    string b=next->str;
    cout << "node" <<node->str<<'\n';
    cout << "next" <<next->str<<'\n';
      cout << "next" <<a+b<<'\n';
    return a+b;
  }

   bool iscontain(string & word,Node * node){
    string local= node->str;
    size_t sizeword =word.size();
    size_t sizelocal =local.size();
    size_t len=sizeword-sizelocal;
    for(int i=0;i<len;i++){
      local="-"+local;
    }
    string reverlocal=string(local.rbegin(),local.rend());
    string reverword=string(word.rbegin(),word.rend());
    //cout <<reverlocal << '\n';
    //cout <<local << '\n';
    //cout <<word << '\n';

    for(int i=0;i<sizeword ;i++){
      //cout << reverlocal[i]<<"-"<<reverword[i] << '\n';
      if(reverlocal[i]==reverword[i]){
          if(i<=sizeword){
            //cout << "entro true" <<i<< '\n';
            return true;
          }else
            //cout << "entro false" <<i<< '\n';
            return false;
      }else{
        return false;
      }
    }
    return false;
  }

int nsons(Node * & node){
    int cont=0;
    for(int i=0;i<ALPHABET_LENGTH ;i++){
      if(node->sons[i]!=0){
        cont++;
        //cout << cont << '\n';
      }
    }
    return cont;
  }

 int nsonparents(Node * & node){
    int cont=0;
    Node * parent = node->parent;
    //cout << node << '\n';
    //cout << node->str << '\n';
    if(node->parent!=0){
    for(int i=0;i<ALPHABET_LENGTH ;i++){
      if(parent->sons[i]!=0){
        cont++;
        //cout << cont << '\n';
      }
    }
  }
    return cont;
  }

  //=================================================================
    string dfs(Node * node,string temp,string & tree,int & cont){
      //if(!root->isWord){
        if(!isleaf(node)){
          if(node->isWord || (nsons(node)>=2 && !node->isWord) ){
            string word=node->str;
            temp=temp+word;
            if(node->isWord){
              cont++;
              //cout << "words "<<cont <<temp<<'\n';
              tree=tree+temp+",";
              //cout <<tree<<'\n';
            }
          }
        }

        if(isleaf(node)){
          cont++;
        //  cout << "words " <<cont<<temp+node->str<<'\n';
          string word=node->str;
          tree=tree+temp+word+",";
          //cout  <<tree<<'\n';

        }
      //  cout << "arbol " <<tree<<'\n';
          for (size_t i = 0; i < ALPHABET_LENGTH; i += 1) {
                if(node->sons[i] !=0){
                  dfs(node->sons[i],temp,tree,cont);
                }
              }
        //}
      return "";
    }
    string printdfs(string & tree) {
      string cadena="",result;
      int len=tree.size();
      //cout<<(int)","<<"- "<<(int)tree[1]<<endl;
      for(int i=0;i<len;i++){
          if(tree[i]==','){
            result+="{\"word\":\""+cadena+"\"},";
            cadena="";
            continue;
          }else{
            cadena+=tree[i];
          }
      }
      return result;
    }

    string printdfs(){
      string temp="";
      int cont=0;
      string a =dfs(root,temp,tree,cont);
      //tree.pop_back();
      // cout<<tree<<'\n';
      string str = "{\"list\":[";
      string cadena=printdfs(tree);
      cadena.pop_back();
      str += cadena+ "]}";
      // cout << "str" << '\n';
      tree = "";
      return str;

    }
/*=======================================================================================*/
// void eraser(string str, Node *  node) {
//       if(str==root->str && root->isWord && !haveson()){
//         root=NULL;
//         return;
//       }
//       node = root;//root asigna a la variable node del tipo Node
//       Node * next;//inicializa un puntero next del tipo Node
//       Node * temporal;
//       string prevStr = str;//palabra a buscar
//       size_t result,position = 0;
//       while (node) {
//         //cout<<"____________________________"<<endl;
//         result = node->contains(str, position);
//         //cout<<"position: "<<position<<endl;
//         prevStr = str;
//         str = str.substr(position);
//         //cout<<"str: "<<str<<endl;
//         //cout<<"prevstr: "<<prevStr<<endl;
//         //cout<<"str  node: "<<node->str<<endl;
//         next = node->sons[p(str[0])];
//         //cout << "p" << p(str[0])<< endl;
//         //cout << "node find: " << node<< endl;
//         //cout << "next find: " << next<< endl;
//         if (str.size() && next) {
//             node = next;
//         } else {
//             break;
//         }
//       }
//
//       //cout << "_________________"<< endl;
//       for(int i=0;i<ALPHABET_LENGTH ;i++){
//         if(node->sons[i]!=0){
//           //cout << "node son: " << node->sons[i]<< endl;
//           temporal=node->sons[i];
//         }
//       }
//
//       if ((prevStr == node->str && node->isWord )) {
//         if(isleaf(node)){
//           delete node;
//           node->isWord=false;
//           node->parent->sons[p(node->str[0])]=0;
//         }else if(nsons(node)>1){
//           node->isWord=false;
//         }else{
//           string index=temporal->str;
//           int indice=p(index[0]);
//           string indexactual=node->str;
//           int indiceactual=p(indexactual[0]);
//           node->sons[indice]=0;
//           temporal->parent=node->parent;
//           node->parent->sons[indiceactual]=temporal;
//           temporal->str=join(node,temporal);
//
//         }
//       }
//       //Caso cuando solo tiene un hijo y debe ser raiz una palabra
//       Node * temporal2;
//       if(nsons(root)==1){
//         for(int i=0;i<ALPHABET_LENGTH ;i++){
//           if(root->sons[i]!=0){
//             // cout << "root son: " << root->sons[i]<< endl;
//             temporal2=root->sons[i];
//           }
//         }
//         temporal2->parent=0;
//         //return;
//       }
//
//       // cout << "root " <<nsons(root)<< '\n';
//   }

//==============================================================
void eraser(string str, Node *  node) {
if(find(str)){
  if(str==root->str && root->isWord && !haveson()){
    root=NULL;
    return;
  }
  node = root;//root asigna a la variable node del tipo Node
  Node * next;//inicializa un puntero next del tipo Node
  Node * temporal;
  Node * temp;//se necesita para dos hijos con padre isword=0
  string prevStr = str;//palabra a buscar
  size_t result,position = 0;
  while (node) {
    cout<<"____________________________"<<endl;
    result = node->contains(str, position);
    cout<<"position: "<<position<<endl;
    prevStr = str;
    str = str.substr(position);
    cout<<"str: "<<str<<endl;
    cout<<"prevstr: "<<prevStr<<endl;
    cout<<"str  node: "<<node->str<<endl;
    next = node->sons[p(str[0])];
    cout << "p" << p(str[0])<< endl;
    cout << "node find: " << node<< endl;
    cout << "next find: " << next<< endl;
    if (str.size() && next) {
        node = next;
    } else {
        break;
    }
  }

  cout << "_________________"<< endl;
  for(int i=0;i<ALPHABET_LENGTH ;i++){
    if(node->sons[i]!=0){
      cout << "node son: " << node->sons[i]<< endl;
      temporal=node->sons[i];
    }
  }


  cout << "________bug_________"<< endl;
  cout <<"node parent "<< node->parent<< '\n';
  cout << "Es hoja " <<isleaf(node)<< endl;
  cout << "Es hijos "<<nsons(node)<< endl;
  //cout <<temporal->str << '\n';

  cout<<node->str<<endl;
  if ((prevStr == node->str && node->isWord )) {
    if(isleaf(node)){
      delete node;
      node->isWord=false;
      //eliminar cuando no contiene palabra y tiene un hijo (join)
      if(node->parent->isWord==0 && nsons(node->parent)==1){
        node->parent->isWord=1;
        node->parent->str=join(node->parent,node);
        cout << "NODE ACA " <<node->str<< '\n';
        //______________________________________
        for(int i=0;i<ALPHABET_LENGTH ;i++){
          if(node->parent->sons[i]!=0){
            cout << "node ACA son: "<<node->parent->sons[i]<< endl;
            node->parent->sons[i]=0;
          }
        }
        //______________________________________
      }
      //eliminar cuando no contiene palabra y tiene dos hijos (join)
    /*  if(node->parent->isWord==0 && nsons(node->parent)==2){

        cout << "NODE ACA 2 " <<node->str<< '\n';
        //______________________________________
        for(int i=0;i<ALPHABET_LENGTH ;i++){
          if(node->parent->sons[i]!=0){
            cout << "node ACA son 2: "<<node->parent->sons[i]<< endl;
            temp=node->parent->sons[i];
            break;
            node->parent->sons[i]=0;
          }
        }
        for(int i=0;i<ALPHABET_LENGTH ;i++){
          if(node->parent->sons[i]!=0){
            cout << "node ACA son: "<<node->parent->sons[i]<< endl;
            node->parent->sons[i]=0;
          }
        }
        //______________________________________
        cout << "temp" <<node->parent->parent->str<< '\n';
        node->parent->str=join(temp->parent,temp);
        node->parent->sons[p(node->str[0])]=0;
        node->parent->parent->str=join(node->parent->parent,node->parent);
        for(int i=0;i<ALPHABET_LENGTH ;i++){
          if(node->parent->parent->sons[i]!=0){
            cout << "node ACA son: "<<node->parent->sons[i]<< endl;
            node->parent->parent->sons[i]=0;
          }
        }
      }else
      {
        node->parent->sons[p(node->str[0])]=0;
      }*/
      node->parent->sons[p(node->str[0])]=0;
    }else if(nsons(node)>1){
      node->isWord=false;
    }else{
      string index=temporal->str;
      int indice=p(index[0]);
      string indexactual=node->str;
      int indiceactual=p(indexactual[0]);
      node->sons[indice]=0;
      temporal->parent=node->parent;
      node->parent->sons[indiceactual]=temporal;
      temporal->str=join(node,temporal);

    }
  }
  //Caso cuando solo tiene un hijo y debe ser raiz una palabra

  Node * temporal2;
  if(nsons(root)==1){
    for(int i=0;i<ALPHABET_LENGTH ;i++){
      if(root->sons[i]!=0){
        //cout << "root son: " << root->sons[i]<< endl;
        temporal2=root->sons[i];
      }
    }
    root->str=temporal2->str;
    root->isWord=temporal2->isWord;
    for(int i=0;i<ALPHABET_LENGTH ;i++){
      if(root->sons[i]!=0){
        root->sons[i]=0;
      }
    }
    temporal2=0;
    //temporal2=root;

    //root->str=temporal2->str;
    //root->isWord=temporal2->isWord;
    //cout << "temporal str: " << temporal2->str<< endl;
    //root->isWord=true;
    //root->str=temporal->str;
    //temporal2=0;
    //temporal2=root;
    //cout << "root str: " << root->str<< endl;
    //delete node;
    //return;
  }

  cout << "root " <<nsons(root)<< '\n';
}
}

  void erase(string word,Node * node){
   size_t a,start;
   size_t result;

    // cout << "=====erase========"<< endl;
      if(find(word)){
          if(word==root->str && root->isWord && !haveson()){
            root=NULL;
            }
            else{
              if(!node) return;
              //cout << " prove " <<'\n';
              //cout << node<<'\n';
              //cout <<node->str << '\n';

              if(node->str==word){
                delete node;
                node->parent->sons[p(node->str[0])]=0;
              }

              //cout << " lo contiene: " <<iscontain(word,node) <<'\n';
              //cout << nsonparents(node) << '\n';
              //cout << nsonparents(node) << '\n';
              if(iscontain(word,node) && isleaf(node)){
                //if(nsonparents(node)==2){
                  //string join1=node->str;
                  //string join2=node->parent->str;
                  //string join=join2+join1;
                  //cout << join << '\n';
                  //  node->parent->str=string(join);
                //}
                delete node;
                node->parent->sons[p(node->str[0])]=0;
              }
              // cout << "node parent " <<node->parent <<'\n';
              // cout << "node is word " <<node->isWord <<'\n';
              // cout << "node is *" <<node<<'\n';
              // cout << "node is str " <<node->str<<'\n';
              for (size_t i = 0; i < ALPHABET_LENGTH; i += 1) {
                  if(node->sons[i]!=0) {
                    // cout << "son " <<node->sons[i]<<"i: "<<i<<'\n';
                  }
              }
              // cout << "Es hoja. " <<isleaf(node)<<'\n';

              //cout << "padre parent " <<node->parent->parent <<'\n';
              //cout << "padre is word " <<node->parent->isWord <<'\n';
              // cout << "padre is *" <<node->parent<<'\n';
              //cout << "padre is str " <<node->parent->str<<'\n';
              for (size_t i = 0; i < ALPHABET_LENGTH; i += 1) {
                  if(node->parent->sons[i]!=0) {
                    // cout << "padre son " <<node->parent->sons[i]<<"i: "<<i<<'\n';
                  }
              }
              // cout << "Es hoja. " <<isleaf(node)<<'\n';
              //cout << position << '\n';
              //cout << "hijos " <<node->sons[p(node->str[0])]<<'\n';

              /*if(nsonparents(node)==2 && isleaf(node) && iscontain(word,node)){
              }*/

              //cout << word[0]<<"ok" <<'\n';
              //cout << p(word[0])<<"ok" <<'\n';
              for (size_t i = 0; i < ALPHABET_LENGTH; i += 1) {
                if(node->sons[i] !=0){
                  //cout << node->sons[i]<<"ok son " << '\n';
                  erase(word,node->sons[i]);
                }
              }
            }
      }else{
        cout << "No existe elemento" << '\n';
      }
    }

    void erase(string word){
      string temp="a";int position=0;
      eraser(word,root);
    }


    bool find(string str, Node * & node) {
        node = root;
        Node * next;
        string prevStr = str; //palabra a buscar
        size_t result,position = 0;

        while (node) {
          result = node->contains(str, position); // position of p
          prevStr = str;
          str = str.substr(position);
          next = node->sons[p(str[0])];
          if (str.size() && next) {
              node = next;
          } else {
              break;
          }
        }

        if ((prevStr == node->str && node->isWord )) {
            return true;

        }
        return false;
    }

  bool find(string word){
    Node * node;
    return find(word,node);
  }

    size_t find(
            string & str,
            Node * & node,
            Node * & parent,
            size_t & position
        ) {
        position = 0;
        parent = 0;
        node = root;
        size_t result;
        while (node) {
            result = node->contains(str, position);
            if (shouldPrint) {
                cout << "str: " << str << endl;
                cout << "result: " << result << endl;
                cout << "pos: " << position << endl;
            }
            if (result == SPLIT_1) {
                str = str.substr(position);
                Node * next = node->sons[p(str[0])];

                if (shouldPrint) {
                    printSons(node);
                    cout << "=> node: " << node->str << endl;
                    cout << "next: " << next << " ";
                }

                if (next) {
                    if (shouldPrint) {
                        cout << "[" << next->str << "]";
                    }
                    parent = node;
                    node = next;
                    if (shouldPrint) cout << endl;
                } else {
                    if (shouldPrint) cout << endl;
                    break;
                }
            } else if (result == SPLIT_2) {
                break;
            } else if ( ! result ) {
                break;
            } else if ( result == 3) {
                break;
            } else if ( result == 4 ) {
                break;
            }
        }
        return result;
    }

    void graphviz(Node * & node, string & tree) {
        if ( ! node) {
            return;
        }
        string name;
        char ss[100];
        sprintf(ss, "\"%p\"", node);
        name = ss;
        if (node->parent) {
            string parentStr = "\"\"";

            if (node->parent->str != "") {
                char sp[100];
                sprintf(sp, "\"%p\"", node->parent);
                parentStr = sp;
            }

            tree += parentStr + " -> " + name + "\n";
        }
        if (node->isWord) {
            tree += name + " [" + "color = cyan style = filled label = " + node->str + "]\n";
        } else if(node->str != "") {
            tree += name + " [" + "label = " + node->str + "]\n";
        }

        for (size_t i = 0; i < ALPHABET_LENGTH; i += 1) {
            graphviz(node->sons[i], tree);
        }
    }

    string graphviz(){
        //Node * node;
        string str = "digraph G {\n";
        string tree = "";
        graphviz(root, tree);
        str += tree + "}";
        return str;
    }

    void printjson(Node * & node, string & tree) {
        if ( ! node) {
            return ;
        }
        string name;
        char ss[100];
        sprintf(ss, "\"%p\"", node);
        name = ss;
        string parentStr;

        if (node->parent) {
            parentStr = "\"\"";
            // if (node->parent->str != "") {
                char sp[100];
                sprintf(sp, "\"%p\"", node->parent);
                parentStr = sp;
            // }
        }
        if (node->isWord) {

            if(parentStr == "") parentStr = "\"\""; // << cambio validacion
            tree +="{\"valor\":\"" +node->str + "\",\"id\":"+name +
            ",\"padre\":"+parentStr+",\"isword\":\"1\"},";
        }else{

          if(parentStr == "") parentStr = "\"\""; // << un solo padre root
          tree +="{\"valor\":\"" +node->str + "\",\"id\":"+name +
          ",\"padre\":"+parentStr+",\"isword\":\"0\"},";

        }

        for (size_t i = 0; i < ALPHABET_LENGTH; i += 1) {
            printjson(node->sons[i], tree);
        }
    }

    string printjson(){
      string str = "{";
      string temp = "\"tree\":[";
      printjson(root, temp);
      size_t tam=temp.length();
      temp.pop_back();
      str += temp + "]}";

      return str;
    }

    void print (Node * & node) {
        if ( ! node) {
            return;
        }
        cout << '"' << node->str << '"' << "(" << node->isWord << ")";

        if (node->parent) {
            cout << " >- (" << node->parent->str << ")";
        } else {
            cout <<  " >- root";
        }
        cout << endl;

        for (size_t i = 0; i < ALPHABET_LENGTH; i += 1) {
            print(node->sons[i]);
        }
    }

    void print () {
        print(root);
    }


    /*string wordrandom(){
      rand(NULL);

    }*/

    void add(string str, int & word, int & start) {
        // string str;
        //cout<<"word "<<&word<<endl;
        if ( ! root) {
            root = new Node(word, str, true, start);
            //cout << "root: " << str << endl;
            return;
        }
        Node * node;
        Node * parent;
        size_t position;

        size_t kase = find(str, node, parent, position);
        if (shouldPrint) {
            cout << "+++: " << str << endl;
            cout << "kase: " << kase << endl;
            cout << "node: " << node->str << " - " << node << endl;
            cout << "parent: " << parent << endl;
        }
        if (kase == NOT_FOUND) {
            createEmptyRoot(word, str, start);
        } else if (kase == SPLIT_2) {
            splitNode(word, node, str, position, start);
        } else if (kase == SPLIT_1) {
            // cout << "split 1" << endl;
            createNode(word, node, str, start);
        } else if (kase == INSIDE) {
            createNode(word, node, str, position, start);
        } else if (kase == FOUND) {
            node->isWord = true;
            //node->directory[word].pagerank += 1;
            //if (node->directory[word].start == 0) {
              //  node->directory[word].start = start;
            //}
        }

    }

private:
    void createEmptyRoot(int & word, string & str, int & start) {
        if (root->str != "") {
            Node * tmp = root;
            root = new Node();
            root->sons[p(tmp->str[0])] = tmp;
            tmp->parent = root;
        }

        Node * newNode = new Node(word, str, true, start);
        root->sons[p(str[0])] = newNode;
        newNode->parent = root;
    }
    void createNode(
            int & word,
            Node * & node,
            string & str,
            size_t position,
            int & start
        ) {
        string res = node->reverseCut(position);
        Node * newParent = new Node(word, res, true, start);
        Node * grandparent = node->parent;
        if (node == root) {
            root = newParent;
        } else {
            grandparent->sons[p(node->str[0])] = 0;
            grandparent->sons[p(newParent->str[0])] = newParent;
        }
        newParent->parent = grandparent;
        newParent->sons[p(node->str[0])] = node;
        node->parent = newParent;
    }

    void createNode(int & word, Node * & node, string & str, int & start) {
        Node * newNode = new Node(word, str, true, start);
        node->sons[p(str[0])] = newNode;
        newNode->parent = node;
    }

    void splitNode(
            int & word,
            Node * & node,
            string & str,
            size_t position,
            int & start
        ) {
        if (shouldPrint) cout << "splitting: " << (node == root) << endl;
        if (shouldPrint) cout << "node: " << node->parent->str << endl;
        char nodeIndex = node->str[0];
        string res = node->reverseCut(position);
        Node * newParent = new Node(word, res, false, start);
        Node * parent = node->parent;
        if (node == root) {
            root = newParent;
        } else {
            parent->sons[p(nodeIndex)] = 0;
            parent->sons[p(newParent->str[0])] = newParent;
        }
        newParent->parent = node->parent;

        if (shouldPrint) {
            cout << "node->parent: " << node->parent->str << endl;
            cout << "newParent->parent: " << newParent->parent->str << endl;
        }
        newParent->sons[p(node->str[0])] = node;
        node->parent = newParent;


        string substr = str.substr(position, str.size());
        Node * second = new Node(word, substr, true, start);
        newParent->sons[p(substr[0])] = second;
        second->parent = newParent;

        // node->isWord = false;
    }

};

#endif // TREE_H

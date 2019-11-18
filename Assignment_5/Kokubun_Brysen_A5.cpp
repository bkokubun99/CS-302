// @author Brysen Kokubun
// @date 10/19/2019
// @file Assignment #5 Balance
//       Program given a description of a mobile as input from text file
//       and checks whether the mobile is in equilibrium or not
//       Vasko CS-302-1003

#include <iostream>
#include <fstream>
using namespace std;

//Struct for the binary tree(nodes/items and pointers)
template <class Type>
struct binTreeNode
{
Type wL , dL , wR , dR ;        //Items within Binary Tree
binTreeNode <Type> *left ;      //Binary Tree pointer left
binTreeNode <Type> *right ;     //Binary Tree pointer right
};

/****************************************************************************************************************************
*                                                           Function Prototypes                                                                                    *
******************************************************************************************************************************/
template <class Type>
void buildMobile (binTreeNode <Type> *r , ifstream & infile);

template <class Type>
int getWeight (binTreeNode < Type > * r);

template <class Type>
void destroyTree (binTreeNode <Type> *r);

//Begin Main
int main()
{
/****************************************************************************************************************************
*                                                                   Variables                                                                                             *
******************************************************************************************************************************/
    string Txt_file;        //String Variable for Text File Input
    int Balanced;           //Integer Variable Balanced
    ifstream infile;        //Input stream Variable infile
    
    //Allocate a new node/pointer of type int
    binTreeNode <int> *root = new binTreeNode<int>;
    
/****************************************************************************************************************************
*                                                     Prompt for User Input  txt File                                                                           *
******************************************************************************************************************************/
    cout << "Enter mobile data file: ";
    cin  >> Txt_file;                   //Read User string for txt File name
    infile.open(Txt_file);              //Open  txt File
    buildMobile(root, infile);          //Call buildMobile function
    infile.close();                     //Close txt File
    
    //Balanced variable stores the return value of getWeight fct
    Balanced = getWeight(root);
    
    //Deallocate/Destroys Tree
    destroyTree(root);
    
/****************************************************************************************************************************
*                                                                       Output                                                                                             *
******************************************************************************************************************************/
    if (Balanced >= 0)
    {
        //Output "YES" if Balanced Variable is >= 0
        cout << "\nYES\n" << endl;
    }
    else
    {
        //Output "NO" if Balanced Variable is < 0
        cout << "\nNO\n"  << endl;
    }
    
    return 0;
}//End Main

/****************************************************************************************************************************
*                                                                    Functions                                                                                           *
******************************************************************************************************************************/
//Function will recursively build mobile tree, by pre-order traversal of
//file inputs, will insert into the tree and recursively continue until left
//or right weight is not 0
template <class Type >
void buildMobile (binTreeNode <Type> *r , ifstream & infile)
{
    //Read in from the selected file wL, dL, wR, dR
    infile >> r->wL >> r->dL >> r->wR >> r->dR;
    r->left = r->right = NULL;      //Assign left & right to NULL
    //Control enters if wL == 0
    if(r->wL == 0)
    {
        //Create new node/pointer l_leaf
        binTreeNode<int> *l_leaf = new binTreeNode<int>;
        //Assign l_leaf node to left node of binary tree
        r->left = l_leaf;
        //Recursive Fct call buildMobile w/l_leaf node/pointer
        buildMobile(l_leaf,infile);
    }
    //Control enters if wR == 0
    if(r->wR == 0)
    {
        //Create new node/pointer r_leaf
        binTreeNode<int> *r_leaf = new binTreeNode<int>;
        //Assign r_leaf node to right node of binary tree
        r->right = r_leaf;
        //Recursive Fct call buildMobile w/r_leaf node/pointer
        buildMobile(r_leaf,infile);
    }
}

//Function compares r's left side combined weight X r->dL with r's right side
//combined weight X r->dR, if they are equal returns sum of r's left combined
//weight with r's right side combined weight. Otherwise returns -1 to denote
//that r points to a node that does not form a balanced mobile
template <class Type >
int getWeight (binTreeNode < Type > * r)
{
    //Control enters if wL == 0
    if(r->wL == 0)
    {
        //Recursivly assigns the value of wL
        r->wL = getWeight(r->left);
    }
    //Control enters if wR == 0
    if(r->wR == 0)
    {
        //Recursivly assigns the value of wR
        r->wR = getWeight(r->right);
    }
    //Control enters if LeftWeight*LeftDiameter == RightWeight*RightDiameter
    if((r->wL*r->dL) == (r->wR*r->dR))
    {
        //Returns LeftWeight + RightWeight
        return r->wL+r->wR;
    }
    //Control enters if LeftWeight*LeftDiameter != RightWeight*RightDiameter
    else
    {
        return -1;          //Return -1
    }
}

//Deallocates the binary Tree, uses a postorder traversal
template <class Type >
void destroyTree (binTreeNode <Type> *r)
{
    //Control enters if r is NULL
    if(r==NULL)
    {
        return;
    }
    destroyTree(r->left);   //Recursive Call to delete left node
    destroyTree(r->right);  //Recursive Call to delete right node
    delete r;               //Delete r
}

#include <iostream>
#include <string>
#include "RBTree.cpp"
using namespace std;

//Add these functions to your tree class to show the color and subtree size of each node in order.
//Modify it to fit your class.
//nSize = left subtree size + right subtree size + 1;

// void specialInorder()
// {
//     specialInorderHelper(root);
//     cout << endl;
// };

// void specialInorderHelper(Node *current)
// {
//     if (current == nilNode)
//     {
//         return;
//     }
//     specialInorderHelper(current->left);
//     cout << current->key << "("<<current->color<<")("<<current->nSize<<") ";
//     specialInorderHelper(current->right);
// };

int main()
{
    int int1Key[20];
    int int1Val[20];
    for(int i = 0; i <= 19; i++)
    {
        int1Key[i] = i;
        int1Val[i] = i;
    }

    RBTree<int, int> intTree1(int1Key, int1Val, 20);
    RBTree<int, int> intTree2;

    for(int i = 0; i <= 19; i++)
    {
        intTree2.insert(i, i);
    }

    //Output 1
    cout<<"Correct Output 1: \t0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 "<<endl;
    cout<<"Your Output 1: \t\t";
    intTree1.inorder();

    //Output 2
    cout<<"Correct Output: \t0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19"<<endl;
    cout<<"Your Output: \t\t";
    intTree2.inorder();

    //Output 3
    cout<<"Correct Output: \t9 4 1 0 2 3 6 5 7 8 14 11 10 12 13 17 15 16 18 19"<<endl;
    cout<<"Your Output: \t\t";
    intTree1.preorder();

    //Output 4
    cout<<"Correct Output: \t7 3 1 0 2 5 4 6 11 9 8 10 15 13 12 14 17 16 18 19"<<endl;
    cout<<"Your Output: \t\t";
    intTree2.preorder();

    //Output 5
    cout<<"Correct Output: \t0 3 2 1 5 8 7 6 4 10 13 12 11 16 15 19 18 17 14 9"<<endl;
    cout<<"Your Output: \t\t";
    intTree1.postorder();

    //Output 6
    cout<<"Correct Output: \t0 2 1 4 6 5 3 8 10 9 12 14 13 16 19 18 17 15 11 7"<<endl;
    cout<<"Your Output: \t\t";
    intTree2.postorder();

    //Output 7
    cout<<"Correct Output: \t0(0)(1) 1(0)(4) 2(0)(2) 3(1)(1) 4(0)(9) 5(0)(1) 6(0)(4) 7(0)(2) 8(1)(1) 9(0)(20) 10(0)(1) 11(0)(4) 12(0)(2) 13(1)(1) 14(0)(10) 15(0)(2) 16(1)(1) 17(0)(5) 18(0)(2) 19(1)(1)"<<endl;
    cout<<"Your Output: \t\t";
    intTree1.specialInorder();

    //Output 8
    cout<<"Correct Output: \t0(0)(1) 1(0)(3) 2(0)(1) 3(1)(7) 4(0)(1) 5(0)(3) 6(0)(1) 7(0)(20) 8(0)(1) 9(0)(3) 10(0)(1) 11(1)(12) 12(0)(1) 13(1)(3) 14(0)(1) 15(0)(8) 16(0)(1) 17(1)(4) 18(0)(2) 19(1)(1)"<<endl;
    cout<<"Your Output: \t\t";
    intTree2.specialInorder();

    //Outputs 9-13
    cout<<"Correct output:"<<endl<<"1\n1\n1\n1\n0\n";
    cout<<"Your Output:"<<endl;
    cout<<intTree1.remove(5)<<endl;
    cout<<intTree1.remove(4)<<endl;
    cout<<intTree1.remove(3)<<endl;
    cout<<intTree1.remove(13)<<endl;
    cout<<intTree1.remove(21)<<endl;;

    intTree1.insert(13, 13);

    //Outputs 14-18
    cout<<"Correct output:"<<endl<<"1\n1\n1\n1\n0\n";
    cout<<"Your Output:"<<endl;
    cout<<intTree2.remove(5)<<endl;
    cout<<intTree2.remove(4)<<endl;
    cout<<intTree2.remove(3)<<endl;
    cout<<intTree2.remove(13)<<endl;
    cout<<intTree2.remove(21)<<endl;;

    intTree2.insert(13, 13);

    //Outputs 19-23
    cout<<"Correct Output:"<<endl;
    cout<<"Your Output:"<<endl;
    cout << *(intTree1.search(1)) << endl;
    cout << *(intTree1.search(13)) << endl;
    cout << *(intTree1.search(20)) << endl;


    return 0;
}
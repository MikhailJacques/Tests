////#include <iostream>
////#include <string>
////#include <algorithm>
////
////using namespace std;
////
////int main() {
////    string s = "Hello, world! 123";
////
////    // remove non-alphabetic characters
////    s.erase(remove_if(s.begin(), s.end(), [](char c) {
////        return !isalpha(c);
////        }), s.end());
////
////    cout << s << endl; // Output: Helloworld
////    return 0;
////}
//
//
//#include <algorithm>  
//#include <iostream>  
//#include <vector>  
//
//using namespace std;
//
////bool IsOdd(int i)
////{
////    return ((i % 2) == 1);
////}
////
////int main()
////{
////    vector <int> vec2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
////
////    // Store the position of the last element   
////    vector <int>::iterator pend;
////
////    // Print original vector   
////    cout << "\nOriginal vector : ";
////    for (int i = 0; i < vec2.size(); i++)
////        cout << " " << vec2[i];
////
////    cout << "\n";
////
////    // remove_if function call   
////    // The unary predicate function which accepts an element as an argument that must be satisfied if the value of an element is to be replaced.
////    pend = remove_if(vec2.begin(), vec2.end(), IsOdd);
////
////    // Print the vector   
////    cout << "After remove_if : ";
////    for (vector<int> ::iterator q = vec2.begin(); q != pend; ++q)
////        cout << ' ' << *q;
////
////    cout << '\n';
////
////    return 0;
////}
//
//bool greater6(int value) {
//    return value > 6;
//}
//
//int main() {
//
//    vector <int> v1, v2;
//    vector <int>::iterator Iter1, Iter2, new_end;
//
//    int i;
//    for (i = 0; i <= 9; i++)
//        v1.push_back(i);
//
//    int ii;
//    for (ii = 0; ii <= 3; ii++)
//        v1.push_back(7);
//
//    random_shuffle(v1.begin(), v1.end());
//
//    cout << "Vector v1 is ( ";
//    for (Iter1 = v1.begin(); Iter1 != v1.end(); Iter1++)
//        cout << *Iter1 << " ";
//    cout << ")." << endl;
//
//    // Remove elements satisfying predicate greater6    
//    new_end = remove_if(v1.begin(), v1.end(), greater6);
//
//    cout << "Vector v1 with elements satisfying greater6 removed is\n ( ";
//    for (Iter1 = v1.begin(); Iter1 != v1.end(); Iter1++)
//        cout << *Iter1 << " ";
//    cout << ")." << endl;
//
//    // To change the sequence size, use erase    
//    v1.erase(new_end, v1.end());
//
//    cout << "Vector v1 resized elements satisfying greater6 removed is\n ( ";
//    for (Iter1 = v1.begin(); Iter1 != v1.end(); Iter1++)
//        cout << *Iter1 << " ";
//    cout << ")." << endl;
//
//    return 0;
//}
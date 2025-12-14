//#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {

    LinkedList<int> list;
    
    list.addHead(20);
    list.addHead(30);
    list.addHead(40);
    list.printForward();
    list.printReverse();
    int length = list.getCount();
    std::cout << length << std::endl;
    LinkedList<int>::Node* head = list.getHead();
    std::cout << head->data << std::endl;

    LinkedList<int> list2;
    list2.addHead(25);
    list2 = list;
    list2.printForward();
    return 0;

}


//#endif
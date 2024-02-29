#include <string>

#ifndef MENU_HPP
#define MENU_HPP
class Menu{
    private:
        Tree<int> tree;
    public:
        Menu();
        void showMenu();
        int randomNum();

    };

#endif
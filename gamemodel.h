#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include<vector>
using namespace std;

enum ItemType {
    Empty, Cross, Zero
};


struct GameModel {
    vector<vector<ItemType>> model;

    ItemType player;

    GameModel(int n, int m, ItemType initPlayer = Cross);
    GameModel(vector<vector<ItemType>> model);

    void change_player();
    bool step(int i, int j);

    bool checkHLines(ItemType type);
    bool checkVLines(ItemType type);
    bool checkRDiagonals(ItemType type);
    bool checkLDiagonals(ItemType type);
};

#endif // GAMEMODEL_H

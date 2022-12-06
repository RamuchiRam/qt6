#include "gamemodel.h"

GameModel::GameModel(int n, int m, ItemType initPlayer) {
    player = initPlayer;

    model.resize(n);
    for (int i = 0; i < n; ++i) {
        model[i].resize(m);

        for (int j = 0; j < m; ++j) {
            model[i][j] = Empty;
        }
    }
}

GameModel::GameModel(vector<vector<ItemType>> model) {
    model = model;
}

bool GameModel::checkVLines(ItemType type){
    int count;

    for (int col = 0; col < 10; col++){
        count = 0;

        for (int row = 0; row < 10; row ++){

            (model[row][col] == type) ? count += 1 : count = 0;
            if ((count>=5))  return true;
        }

        if ((count>=5))  return true;
    }

    return false;
}
bool GameModel::checkHLines(ItemType type){
    int count;

    for (int col = 0; col < 10; col++){
        count = 0;

        for (int row = 0; row < 10; row ++){

            (model[col][row] == type) ? count += 1 : count = 0;
            if ((count>=5))  return true;
        }

        if ((count>=5))  return true;
    }

    return false;
}

bool GameModel::checkLDiagonals(ItemType type){
    int count = 0;
    for (int offsetY = 0; offsetY < 10; ++offsetY){
        for (int i = 0; i < 10-offsetY; ++i){
            (model[10-i-1-offsetY][i] == type) ? count += 1 : count = 0;
            if ((count>=5)) return true;
        }
    }
    count = 0;
    for (int offsetY = 0; offsetY < 10; ++offsetY){
        for (int i = 0; i < 10-offsetY; ++i){
            (model[10-i-1][i+offsetY] == type) ? count += 1 : count = 0;
            if ((count>=5)) return true;
        }
    }
    return false;
}

bool GameModel::checkRDiagonals(ItemType type){
    int count = 0;

    for (int offsetY = 0; offsetY < 10; ++offsetY){
    for (int i = 0; i < 10-offsetY; ++i){
        (model[i+offsetY][i] == type) ? count += 1 : count = 0;
        if ((count>=5)) return true;
    }
    }
    count = 0;

    for (int offsetY = 0; offsetY < 10; ++offsetY){
        for (int i = 0; i < 10-offsetY; ++i){
            (model[i][i+offsetY] == type) ? count += 1 : count = 0;
            if ((count>=5)) return true;
        }
    }
    return false;
}

void GameModel::change_player() {
    if (player == Cross) {
        player = Zero;
    }
    else {
        player = Cross;
    }
}

bool GameModel::step(int i, int j) {
    if (model[i][j] != Empty) {
        return false;
    }
    model[i][j] = player;
    change_player();
}

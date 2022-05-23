# About Comment Maker
 Comment Maker auto generates function headers for all your functions, so you don't have to do it! It will save you many annoying hours of work. The program conforms to the function header style required for EGR 103, CS 161 & CS 162. The program is only compatible with C/C++

### [Download Program](https://downgit.github.io/#/home?url=https://github.com/ipoogleduck/Comment-Maker/blob/main/commentMaker.cpp)

# To Use:
1. **Drop the commentMaker.cpp file into the folder that contains your program files (cpp files)**
2. **Add an @ symbol to the beginning of every function in your program you want to add a function header for**

ie:
```
void removeCardsAt() {

}
```

Would become:
```
@void removeCardsAt() {

}
```

3. **Compile this .cpp file with g++.**

Ex: ```g++ commentMaker.cpp -std=c++11 -o commentMaker```

4. **Run commentMaker with the name(s) of your c++ files.**

Ex: ```./commentMaker filename.cpp```

Or for multiple files: ```./commentMaker filename.cpp filename2.cpp filename3.cpp```

## Example:
```
@Hand::Hand(Card* cards) {
    this->cards = cards;
    this->n_cards = 7;
}

@int amountOfWinners(Player players[], int playerCount, int &highScore) {
    int winningPlayerCount = 0;
    return winningPlayerCount;
}
```
Will be converted to:
```
/********************************************************************
** Function: Hand class constructor
** Description: Constructs Hand class with parameters listed below
** Parameters: Card* cards
** Pre-Conditions: cards must be of type Card*
** Post-Conditions: Class is constructed
********************************************************************/
Hand::Hand(Card* cards) {
    this->cards = cards;
    this->n_cards = 7;
}

/********************************************************************
** Function: amountOfWinners
** Parameters: Player players[], int playerCount, int &highScore
** Pre-Conditions: players[] must be of type Player, playerCount must be of type int, &highScore must be of type int
** Post-Conditions: Function returns value of type int
********************************************************************/
int amountOfWinners(Player players[], int playerCount, int &highScore) {
    int winningPlayerCount = 0;
    return winningPlayerCount;
}
```

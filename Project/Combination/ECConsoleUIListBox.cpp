//
//  ECConsoleUIListBox.cpp
//  
//
//  Created by Yufeng Wu on 5/23/23.
//

#include "ECConsoleUIListBox.h"
#include <iostream>

using namespace std;

ECConsoleUIListBox :: ECConsoleUIListBox(int xUL, int yUL, int xLR, int yLR) : ECConsoleUIItem(xUL, yUL, xLR, yLR), indexChoice(0), firstvis(0) {
    visitem = yLR - yUL + 1;
}

void ECConsoleUIListBox :: AddChoice(const string &text) {
    choices.push_back(text);
}

void ECConsoleUIListBox :: Choose(int rIndex) {
    if (rIndex >= 0 && rIndex < choices.size()) {
        indexChoice = rIndex;
    }
}

string ECConsoleUIListBox::GetTextAtRow(int r) const {
    int local = r - GetYUL();

    if (local < 0 || local >= visitem) {
        return "";
    }

    int idx = firstvis + local;

    if (idx >= 0 && idx < choices.size()) {
        return choices[idx];
    }
    return "";
}

int ECConsoleUIListBox :: GetHighlightPosition(int &xLeft, int &xRight) const {
    if (indexChoice >= firstvis && indexChoice < firstvis + visitem) {
        xLeft = GetXUL();
        xRight = GetXLR();

        return GetYUL() + (indexChoice - firstvis);
    }
    
    return -1;
}

void ECConsoleUIListBox :: HdlKeyUp() {
    if (indexChoice > 0) {
        --indexChoice;

        if (indexChoice < firstvis) {
            --firstvis;
        }
    }
}

void ECConsoleUIListBox :: HdlKeyDown() {
    if (indexChoice < choices.size() - 1) {
        ++indexChoice;

        if (indexChoice >= firstvis + visitem) {
            ++firstvis;
        }
    }
}

string ECConsoleUIListBox :: getAirport() const {
        if (indexChoice < choices.size()) {
            return choices[indexChoice];
        }

    return "";
}

void ECConsoleUIListBox :: clear() {
    choices.clear();
    indexChoice = 0;
    firstvis = 0;
}


void ECConsoleUIListBox :: HdlKeyEnter() {}

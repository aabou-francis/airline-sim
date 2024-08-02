//
//  ECConsoleUITextField.cpp
//  
//
//  Created by Yufeng Wu on 5/24/23.
//

#include "ECConsoleUITextField.h"
#include "ECTextViewImp.h"

using namespace std;

ECConsoleUITextField :: ECConsoleUITextField(ECTextViewImp *pTextView, int xpos, int ypos, int len) : ECConsoleUIItem(xpos, ypos, xpos + len - 1, ypos), isActive(false) { this->pTextView = pTextView; }

string ECConsoleUITextField :: GetTextAtRow(int r) const {
    if (r == GetYUL()) {
        return ":" + text;
    }
    
    return "";
}

int ECConsoleUITextField :: GetHighlightPosition(int &xLeft, int &xRight) const {
    if (isActive) {
        xLeft = GetXUL() + 1;
        xRight = GetXLR();
        return GetYUL();
    }

    return -1;
}

void ECConsoleUITextField :: HdlKeyEnter() {
    isActive = true;

    pTextView->SetCursorX(GetXUL() + 1);
    pTextView->SetCursorY(GetYUL());
    pTextView->Refresh(); 
}

void ECConsoleUITextField :: HdlOtherKey(int key) {
    if (!isActive) return;

    switch(key) {
        case CTRL_C:
            isActive = false;
            break;

        case BACKSPACE:
            if (!text.empty()) text.pop_back();

            pTextView->SetCursorX(pTextView->GetCursorX() - 1);
            break;

        default:
            text.push_back(static_cast<char>(key));
        
            pTextView->SetCursorX(pTextView->GetCursorX() + 1);
            break;
    }

    pTextView->Refresh();
}
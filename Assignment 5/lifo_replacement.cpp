/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Andres Hinojosa
 * @brief A class implementing the LIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lifo_replacement.h"

LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    //keeps track of frame count
    frames = num_frames;
}

LIFOReplacement::~LIFOReplacement() {
    //deletes all elements
        while(!lifo.empty())
        lifo.pop_back();
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = count;
    frames--;
    count++;

    lifo.push_back(page_num);
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    int temp = lifo.back();
    lifo.pop_back();
    page_table[temp].valid = false;
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = page_table[temp].frame_num;

    lifo.push_back(page_num);
    
    return 0;
}
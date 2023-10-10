/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Andres Hinojosa
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "fifo_replacement.h"
#include<iostream>

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    //keeps track of frame count
    frames = num_frames;
}

FIFOReplacement::~FIFOReplacement() {
        //deletes all elements
    while(!fifo.empty())
        fifo.pop();
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    //sets page to true and gives it free frame num
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = count;

    //decrement frame num and increment count to keep track
    frames--;
    count++;
//add new node to back
    fifo.push(page_num);
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    //gets oldest page num and deletes it
    int temp = fifo.front();
    fifo.pop();

    //sets old page to false and new one to true
    page_table[temp].valid = false;
    page_table[page_num].valid = true;

    //gives old frame num to new page
    page_table[page_num].frame_num = page_table[temp].frame_num;

//adds new node to back
    fifo.push(page_num);

    return 0;
}
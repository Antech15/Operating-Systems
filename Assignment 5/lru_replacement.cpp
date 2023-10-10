/**
* Assignment 5: Page replacement algorithms
 * @file Andres Hinojosa
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lru_replacement.h"

LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    //keeps track of frame count
    frames = num_frames;
}

LRUReplacement::~LRUReplacement()
{
    //deletes all elements
        while(!lru.empty())
        lru.pop_back();
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
    //deletes node for the pagenum
    lru.erase(map[page_num]);

    //moves it to the front
    lru.push_front(page_num);

    //sets key
    map[page_num] = lru.begin();
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    //sets page to true and gives it the frame num
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = count;

    //decrements frames and increments count to keep track
    frames--;
    count++;

    //adds new node and sets its key in map
    lru.push_front(page_num);
    map[page_num] = lru.begin();
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {

    //gets and deletes last node (lru)
    int temp = lru.back();
    lru.pop_back();
    //sets removed page to false and new one to true
    page_table[temp].valid = false;
    page_table[page_num].valid = true;

    //gives new page old frame num
    page_table[page_num].frame_num = page_table[temp].frame_num;

//erases old node from map
 map.erase(temp);

 //adds new page to front and sets its key
    lru.push_front(page_num);
map[page_num] = lru.begin();

    return 0;
}

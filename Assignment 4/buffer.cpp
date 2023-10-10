/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Andres Hinojosa
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"

/**
 * @brief Construct a new Buffer object
 * @param size the size of the buffer
 */
Buffer::Buffer(int size)
{
  //initializes the buffer size and variables
  bufferSize = size;
  count = 0;
  in = 0;
  out = 0;
  daBuffer.resize(size);
}

/**
 * @brief Destroy the Buffer object
 */
Buffer::~Buffer()
{
  //deletes everything
  daBuffer.clear();
}

/**
 * @brief Insert an item into the buffer
 * @param item the item to insert
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::insert_item(buffer_item item)
{
  if(count < bufferSize)
    {
      //inserts
      daBuffer[in] = item;
      //updates in and counter
      in = (in + 1) % bufferSize;
      count++;
      return true;
    }
  return false;
}

/**
 * @brief Remove an item from the buffer
 * @param item the item to remove
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::remove_item(buffer_item *item)
{
  if(count > 0)
    {
      //gets item number
      *item = daBuffer[out];
      //updates out and decrements counter
      out = (out + 1) % bufferSize;
      count--;
      return true;
    }
  return false;
}

/**
 * @brief Get the size of the buffer
 * @return the size of the buffer
 */
int Buffer::get_size()
{
  return bufferSize;
}

/**
 * @brief Get the number of items in the buffer
 * @return the number of items in the buffer
 */
int Buffer::get_count()
{
  return count;
}

/**
 * @brief Chceck if the buffer is empty
 * @return true if the buffer is empty, else false
 */
bool Buffer::is_empty()
{
  if(count == 0)
    return true;
  return false;
}

/**
 * @brief Check if the buffer is full
 * @return true if the buffer is full, else false
 */
bool Buffer::is_full()
{
  if(count == bufferSize)
    return true;
  return false;
}

/**
 * @brief Print the buffer
 */
void Buffer::print_buffer()
{
  //counter
  int tempC = 0;
  //prints buffer format
  cout << "Buffer: [";
  for(int i = out; tempC < count; i = (i + 1) % bufferSize)
    {
      cout << daBuffer[i];

      //updates counter so it knows when it is done
      tempC++;

      if(tempC < count)
	cout << ", ";
    }
  cout << "]" << endl;
}

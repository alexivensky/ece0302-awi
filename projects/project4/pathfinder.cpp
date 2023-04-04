#include <cstdlib>
#include <iostream>
#include "lib/image.h"
#include "list.hpp"
#include "queue.hpp"


//./pathfinder maze02.png myoutput00.png
struct state {
  int r;
  int c;
};

struct state initial(Image<Pixel>);
bool goal(struct state, Image<Pixel>);
bool breadthFirstSearch(Image<Pixel>&);


int main(int argc, char *argv[])
{
  // get input/output file names from command line arguments
  if (argc != 3) {
    std::cout << "Usage: pathfinder "
              << "<first_input_filename> <second_output_filename>\n"
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string input_file = argv[1];
  std::string output_file = argv[2];

  // Read input image from file
  Image<Pixel> image = readFromFile(input_file);
  bool success = breadthFirstSearch(image);
  

  // Write solution image to file
  writeToFile(image, output_file);
  
}

struct state initial(Image<Pixel> image) {
  struct state temp;
  int numRed = 0; 
  for (int i = 0; i < image.height(); i++) {
    for (int j = 0; j < image.width(); j++) {
      if (image(i,j) != WHITE && image(i,j) != BLACK && image(i,j) != RED) {
        std::cerr << "Invalid color in image.";
        exit(EXIT_FAILURE);
      } else if (image(i,j) == RED) {
        temp.r = i;
        temp.c = j;
        numRed++;
      } else {
        continue;
      }
    }
  }
  if (numRed == 1) {
    return temp;
  } else if (numRed == 0) {
    std::cerr << "No starting point.";
    exit(EXIT_FAILURE);
  } else {
    std::cerr << "More than one red pixel.";
    exit(EXIT_FAILURE);
  }
  
}

bool goal(struct state cand, Image<Pixel> image) {
  return (cand.r == 0 || cand.r == image.height()-1 || cand.c == 0 || cand.c == image.width()-1);
}

bool breadthFirstSearch(Image<Pixel>& image) {
  state curPoint = initial(image); //initial state

  if (goal(curPoint, image)) { //base case -- reached goal state
    image(curPoint.r, curPoint.c) = GREEN;
    return true;
  }
  int imHeight = image.height();
  int imWidth = image.width();
  bool exploredCheck[imHeight][imWidth]; //2D array to keep track of what has been explored
  bool frontierCheck[imHeight][imWidth]; //2D array to keep track of what is currently in the frontier
  for (int i = 0; i < imHeight; i++) { //initializing all elements of both arrays to zero
    for (int j = 0; j < imWidth; j++) { //although this has complexity O(n^2), this will save time later on since array access is O(1)
      exploredCheck[i][j] = 0;
      frontierCheck[i][j] = 0;
    }
  }

  Queue<state, List<state> > frontier; //queue of states (pixels)
  frontier.enqueue(curPoint); //initial state is initial element
  frontierCheck[curPoint.r][curPoint.c] = 1; //adding to the 2D array as well 
  
  while(1) {
    if (frontier.isEmpty()) { //if frontier is empty return failure
      return false;
    }
    curPoint = frontier.peekFront(); //peeking first element
    frontier.dequeue(); //popping!
    frontierCheck[curPoint.r][curPoint.c] = 0; //removing from 2D array
    
    if (goal(curPoint, image)) { //if we have reached the goal, return true
      image(curPoint.r, curPoint.c) = GREEN;
      return true;
    }
    

    state up;
    up.r = curPoint.r - 1;
    up.c = curPoint.c;
    if (image(up.r, up.c) == WHITE && !exploredCheck[up.r][up.c] && !frontierCheck[up.r][up.c] && up.r > -1) {
      frontier.enqueue(up);
      frontierCheck[up.r][up.c] = 1;
    }

    state down;
    down.r = curPoint.r + 1;
    down.c = curPoint.c;
    if (image(down.r, down.c) == WHITE && !exploredCheck[down.r][down.c] && !frontierCheck[down.r][down.c] && down.r < image.height()) {
      frontier.enqueue(down);
      frontierCheck[down.r][down.c] = 1;
    }

    state left;
    left.r = curPoint.r;
    left.c = curPoint.c - 1;
    if (image(left.r, left.c) == WHITE && !exploredCheck[left.r][left.c] && !frontierCheck[left.r][left.c] && left.c > -1) {
      frontier.enqueue(left);
      frontierCheck[left.r][left.c] = 1;
    }

    state right;
    right.r = curPoint.r;
    right.c = curPoint.c + 1;
    if (image(right.r, right.c) == WHITE && !exploredCheck[right.r][right.c] && !frontierCheck[right.r][right.c] && right.c < image.width()) {
      frontier.enqueue(right);
      frontierCheck[right.r][right.c] = 1;
    }
    exploredCheck[curPoint.r][curPoint.c] = 1;

  } 
  
  return true;
}
#include "FloodFill.h"


#include <stdlib.h>
#include <stdio.h>
#include "FLOODFILL.h"


static int debug_on = FALSE;    /* debug flag */

/*** Debug Statement Functions ***/


/* Debug Statements turned on */
void set_debug_on () {
  debug_on = TRUE;
}


/* Debug Statements turned off */
void set_debug_off () {
  debug_on = FALSE;
}

/* returns current debug flag status */
int get_debug_mode () {
  return debug_on;
}

/*** Struct Constructors and Destructors ***/


/* Node Constructor */
Node * new_Node (const short i, const short j) {

  Node * this_node;
  short halfway;

  if (debug_on)
    printf("allocating %hd, %hd\n", i, j);

  this_node = (Node *) malloc(sizeof(Node));
  halfway = SIZE / 2;

  ROW = i;
  COL = j;
  VISITED = FALSE;

  /* Initializing the flood value at this coord
   	   NOTE : Right now this only works when SIZE is even -- which is ok */
  if (i < halfway && j < halfway)
    FLOODVALUE = (halfway - 1 - i) + (halfway - 1 - j) ;


  else if (i >= halfway && j < halfway)
    FLOODVALUE = (i - halfway) + (halfway - 1 - j) ;

  else if (i < halfway && j >= halfway)
    FLOODVALUE = (halfway - 1 - i) + (j - halfway) ;


  else
    FLOODVALUE = (i - halfway) + (j - halfway) ;

  return this_node;
}


/* Maze Constructor */
Maze * newMaze () {

  Maze * maze;
  short i, j;

  maze = (Maze *) malloc(sizeof(Maze));

  /* Allocate a new Node for each coord of maze */
  for (i = 0; i < SIZE; ++i)
    for (j = 0; j < SIZE; ++j)
      MAPCORD = new_Node (i, j);

  /* setting the neighbors ptrs... must be done after all cells allocated */
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++) {
      MAPCORD->left = (j == 0) ? NULL : (maze->map[i][j-1]);
      MAPCORD->right = (j == SIZE-1) ? NULL : (maze->map[i][j+1]);
      MAPCORD->up = (i == 0) ? NULL : (maze->map[i-1][j]);
      MAPCORD->down = (i == SIZE-1) ? NULL : (maze->map[i+1][j]);
    }

  return maze;
}


/* Node Destructor */
void deleteNode (Node ** npp) {

  /* debug statements */
  if (debug_on)
    printf("deallocating %d, %d\n", (*npp)->row, (*npp)->column);

  free (*npp);
  *npp = 0;
}

/* Maze Destructor */
void deleteMaze (Maze ** mpp) {

  short i, j;

  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      deleteNode (&((*mpp)->map[i][j]));

  free(*mpp);
  *mpp = 0;
}



/*** Node Functions ***/

/* function for obtaining this_node's smallest neighbor's floodvalue */
short obtainSmallestNeighbor (Node * this_node) {

  /* debug statements */
  if (debug_on)
    printf("In obtainSmallestNeighbor\n");

  // The Node's floodvalue will be 1 higher than the neigboring cell
  short smallestneighbor = LARGEVAL;

  // NOTE: LEFT, RIGHT, etc, are substituting:
  // this_node->left, this_node->right, etc.

  if (LEFT != NULL && (LEFT->right != NULL) && (LEFT->floodvalue) < smallestneighbor)
    smallestneighbor = LEFT->floodvalue;

  if (RIGHT != NULL && (RIGHT->left != NULL) && (RIGHT->floodvalue) < smallestneighbor)
    smallestneighbor = RIGHT->floodvalue;

  if (UP != NULL && (UP->down != NULL) && (UP->floodvalue) < smallestneighbor)
    smallestneighbor = UP->floodvalue;

  if (DOWN != NULL && (DOWN->up != NULL) && (DOWN->floodvalue) < smallestneighbor)
    smallestneighbor = DOWN->floodvalue;

  return smallestneighbor;
}



/* function for obtaining this nodes's smallest neighbor's direction */
short get_smallest_neighbor_dir (Node * this_node, const short preferred_dir) {

  short smallestValue; 		/* smallest neighbor value */
  short pathcount; 			/* number of available paths */

  /* debug statement */
  if (debug_on)
    printf("In get_smallest_neighbor_dir\n");

  /* get the smallest neighboring flood_val */
  smallestValue = obtainSmallestNeighbor(this_node);

  /* clear pathcount */
  pathcount = 0;

  /* A BUNCH OF DEBUG STATEMENTS! */
  if (debug_on) {
    printf("preferred_dir: %hd\n", preferred_dir);
    printf("smallestValue: %hd\n", smallestValue);
    printf("neighboring floodvals:\n");
    if (UP != NULL) {
      printf("UP: %hd\n", UP->floodvalue);
      if (UP->floodvalue == smallestValue)
        printf("NORTH cell reachable\n");
    }
    if (RIGHT != NULL)
    {
      printf("RIGHT: %hd\n", RIGHT->floodvalue);
      if (RIGHT->floodvalue == smallestValue)
        printf("EAST cell reachable\n");
    }
    if (DOWN != NULL)
    {
      printf("DOWN: %hd\n", DOWN->floodvalue);
      if (DOWN->floodvalue == smallestValue)
        printf("SOUTH cell reachable\n");
    }
    if (LEFT != NULL)
    {
      printf("LEFT: %hd\n", LEFT->floodvalue);
      if (LEFT->floodvalue == smallestValue)
        printf("WEST cell reachable\n");
    }
  }

  /* count the number of available paths */
  if ((UP != NULL) && (UP->floodvalue == smallestValue))
    pathcount++;

  if ((RIGHT != NULL) && (RIGHT->floodvalue == smallestValue))
    pathcount++;

  if ((DOWN != NULL) && (DOWN->floodvalue == smallestValue))
    pathcount++;

  if ((LEFT != NULL) && (LEFT->floodvalue == smallestValue))
    pathcount++;

  /* more debug statments */
  if (debug_on)
    printf("pathcount: %d\n", pathcount);

  switch (preferred_dir){

  case NORTH:
    if ((UP != NULL) && (UP->floodvalue == smallestValue))
      return NORTH;
    break;
  case EAST:
    if ((RIGHT != NULL) && (RIGHT->floodvalue == smallestValue))
      return EAST;
    break;
  case SOUTH:
    if ((DOWN != NULL) && (DOWN->floodvalue == smallestValue))
      return SOUTH;
    break;
  case WEST:
    if ((LEFT != NULL) && (LEFT->floodvalue == smallestValue))
      return WEST;
    break;

  }

  /* if there is only one path, return that direction */
  //if (pathcount > 1)
  //	return preferred_dir;

  /* if there are multiple available paths, choose the favorable path */


  if ((UP != NULL) && (UP->floodvalue == smallestValue) && (UP->visited == FALSE))
    return NORTH;
  else if ((RIGHT != NULL) && (RIGHT->floodvalue == smallestValue) && (RIGHT->visited == FALSE))
    return EAST;
  else if ((DOWN != NULL) && (DOWN->floodvalue == smallestValue) && (DOWN->visited == FALSE))
    return SOUTH;
  else if ((LEFT != NULL) && (LEFT->floodvalue == smallestValue) && (LEFT->visited == FALSE))
    return WEST;

  if ((UP != NULL) && (UP->floodvalue == smallestValue))
    return NORTH;
  else if ((RIGHT != NULL) && (RIGHT->floodvalue == smallestValue))
    return EAST;
  else if ((DOWN != NULL) && (DOWN->floodvalue == smallestValue))
    return SOUTH;
  else //if ((LEFT != NULL) && (LEFT->floodvalue) == smallestValue)
  return WEST;

}


/* helper function for updateFlood
 checks if this node already fulfills flood value requirements*/
short floodval_check(Node * this_node) {

  /* debug statments */
  if (debug_on)
    printf("In floodval_check\n");

  /* return a flag determining wheter this node should be updated
   	   aka, is this Node 1 + min open adj cell? */
  if (obtainSmallestNeighbor (this_node) + 1 == this_node->floodvalue)
    return TRUE;

  return FALSE;
}


/* helper fuction for updateFlood
 updates this node's flood value to 1 greater than the smallest neighbor*/
void updateFloodvalue (Node * this_node) {

  /* debug statements */
  if (debug_on)
    printf("In updateFloodvalue\n");

  /* set this node's value to 1 + min open adjascent cell */
  this_node->floodvalue = obtainSmallestNeighbor (this_node) + 1;

}

/* pushes the open neighboring cells of this node to the stack */
void push_open_neighbors (Node * this_node, Stack * this_stack) {

  /* debug statements */
  if (debug_on)
    printf("In push_open_neighbors\n");

  /* A NULL neighbor represents a wall.
   	   if neighbor is accessible, push it onto stack! */
  if (LEFT != NULL && LEFT->right != NULL)
    push(this_stack, LEFT);

  if (RIGHT != NULL && RIGHT->left != NULL)
    push(this_stack, RIGHT);

  if (UP != NULL && UP->down != NULL)
    push(this_stack, UP);

  if (DOWN != NULL && DOWN->up != NULL)
    push(this_stack, DOWN);

}

/* main function for updating the flood values of this node */
void updateFlood (Node * this_node, Stack * this_stack, const short reflood_flag) {

  short status;  /* Flag for updating the flood value or not */

  /* debug statements */
  if (debug_on)
    printf("In updateFlood (%d, %d) \n", this_node->row, this_node->column);

  /* we want to avoid flooding the goal values - this is for non-reverse */
  if (!reflood_flag)
    if (ROW == SIZE / 2 || ROW == SIZE / 2 - 1)
      if (COL == SIZE / 2 || COL == SIZE / 2 - 1)
        return;

  /* we want to avoid flooding the goal values - this is reverse */
  if (reflood_flag)
    if (ROW == START_X && COL == START_Y)
      return;

  /* is the cell (1 + minumum OPEN adjascent cell) ? */
  status = floodval_check (this_node);

  /* if no, update curent cell's flood values,
   	   then push open adjascent neighbors to stack. */
  if (!status) {
    updateFloodvalue(this_node); /* Update floodvalue to 1 + min open neighbor */
    push_open_neighbors(this_node, this_stack); /* pushed, to be called later */
  }

  /* debug statements */
  if (debug_on)
    printf ("Exiting updateFlood (%d, %d)\n", this_node->row, this_node->column);

}

/* Function for setting this node's floodvalue to a specific value */
void setFloodValue (Node * this_node, const short value) {

  /* debug statements */
  if (debug_on) {
    printf("In setFloodValue\n");
    printf("Floodval set to : %d\n", FLOODVALUE);
  }

  /* set the flood value to specified value */
  FLOODVALUE = value;
}

/* Function for setting this node's floodvalue to a specific value */
void setVisited (Node * this_node) {

  /* debug statements */
  if (debug_on)
    printf("In setVisited\n");

  /* set the flood value to specified value */
  VISITED = TRUE;
}

/* Function for setting the walls of this node */
void setNodeWall (Node * this_node, const short dir) {

  /* set a wall, of this node, of the specified direction  */
  switch (dir) {

  case NORTH :
    if (ROW != 0) {
      UP = NULL;
      if (debug_on)
        printf("NORTH Wall Set\n");
    }
    break;

  case SOUTH :
    if (ROW != SIZE -1) {
      DOWN = NULL;
      if (debug_on)
        printf("SOUTH Wall Set\n");

    }
    break;

  case EAST :
    if (COL != SIZE - 1) {
      RIGHT = NULL;
      if (debug_on)
        printf("EAST Wall Set\n");
    }
    break;

  case WEST :
    if (COL != 0) {
      LEFT = NULL;
      if (debug_on)
        printf("WEST Wall Set\n");
    }
    break;
  }
}

/*** Maze Functions ***/

/* prints the flood values of each cell in the maze */
void printMazeMap (const Maze * maze) {

  short i, j;

  printf("\n%s\n\n", "CURRENT MAP VALUES: ");
  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      printf("%s%3hd", "  ", MAPCORD->floodvalue);
    }
    printf("\n\n");
  }
  printf("\n");
}


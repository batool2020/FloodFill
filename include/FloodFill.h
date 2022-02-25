#ifndef FLOODFILL_H
#define FLOODFILL_H

 // Constants


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define SIZE 16			// Size of one dimention of Map


// Directions
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// Shortcut Constants
#define MAPCORD maze->map[i][j]
#define MAP maze->map
#define FLOODVALUE this_node->floodvalue
#define ROW this_node->row
#define COL this_node->column
#define VISITED this_node->visited
#define LEFT this_node->left
#define RIGHT this_node->right
#define UP this_node->up
#define DOWN this_node->down

// Stack Constants
#define SPI 1			// Stack Pointer Index
#define SSI 0 			// Stack Size Index
#define STACK_OFFSET 2
#define STACKSIZE 80

// Solver Constants - will be used on mouse
#define START_X 15
#define START_Y 0
#define LARGEVAL 301

// Solver Constants - for command line simulation only
#define NEWLINE 13
#define YES 'y'
#define NO 'n'

/* Main template constants */
#define ONECELL 61
#define LEFT_WALL_SENSED 1700
#define FRONT_WALL_SENSED 2200
#define RIGHT_WALL_SENSED 1700
#define LEFT_BASE_SPEED 23000
#define RIGHT_BASE_SPEED 23000
#define P_VAL 7
#define D_VAL 0
#define TURN_LEFT_COUNT 17
#define TURN_RIGHT_COUNT 18
#define ABOUT_FACE_COUNT 39
#define CENTER 2000
#define LEFT_TWO_AWAY 570
#define RIGHT_TWO_AWAY 630


typedef struct Node {

	/* data fields */
	short floodvalue;
	short row;
	short column;
	short visited;

	/* pointers to neighbors */
	struct Node * left;
	struct Node * right;
	struct Node * up;
	struct Node * down;

} Node;

typedef struct Maze {

	Node * map [SIZE][SIZE];

} Maze;

typedef struct Stack {

	short properties [STACK_OFFSET];
	Node * _stack [STACKSIZE];

} Stack;


// Node Functions
Node * newNode (const short i, const short j);
void deleteNode (Node ** npp);
void updateFlood (Node * this_node, Stack * n_stack, const short reflood_flag);
void setNodeWall (Node * this_node, const short dir);
void setFloodValue (Node * this_node, const short value);
void setVisited (Node * this_node);
short get_smallest_neighbor_dir (Node * this_node, const short preferred_dir);

// Floodfill Helper Functions
short obtainSmallestNeighbor (Node * this_node);
short floodval_check(Node * this_node) ;
void updateFloodvalue (Node * this_node);
void push_open_neighbors (Node * this_node, Stack * n_stack);


// Maze Functions
Maze * newMaze ();
void deleteMaze (Maze ** mpp);
void printMazeMap (const Maze * this_maze);


// Stack Functions
Stack * create_Stack();
void delete_Stack (Stack ** spp);
int is_empty_Stack (Stack * n_stack);
void pop (Stack * n_stack, Node ** npp);
void push (Stack * n_stack, Node * this_node);

// Debug On, Off
void set_debug_on ();
void set_debug_off ();
int get_debug_mode ();


#endif // FLOODFILL_H

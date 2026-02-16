#include <string.h>
#include <stdlib.h> // ต้องมีเพื่อใช้ malloc, free

// structure definition
struct Node {
   int id; 
   char name[50]; 
   struct Node *nextPtr; // pointer to next node
   struct Node *pPtr;    // pointer to previous node
};

typedef struct Node LLnode; 
typedef LLnode *LLPtr; 

// prototypes
int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int value, char *n );
void printList( LLPtr currentPtr );
void instructions( void );
void clearList( LLPtr *sPtr );

// display program instructions to user
void instructions( void )
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
}

// insert a new value into the list in sorted order
void insert( LLPtr *sPtr, int value, char *n )
{
   LLPtr newPtr; 
   LLPtr previousPtr; 
   LLPtr currentPtr; 

   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); 

   if ( newPtr != NULL ) { 
      newPtr->id = value; 
      strcpy(newPtr->name, n);
      newPtr->nextPtr = NULL; 
      newPtr->pPtr = NULL;
    
      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && value > currentPtr->id ) {
         previousPtr = currentPtr; 
         currentPtr = currentPtr->nextPtr; 
      } 

      // insert new node at beginning of list
      if ( previousPtr == NULL ) {
         newPtr->nextPtr = *sPtr;
         if(*sPtr) (*sPtr)->pPtr = newPtr;
         *sPtr = newPtr;
      } 
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->pPtr = previousPtr;
   
         newPtr->nextPtr = currentPtr;
         if(currentPtr) currentPtr->pPtr = newPtr;
      } 
   } 
   else {
      printf( "%d not inserted. No memory available.\n", value );
   } 
} 

// delete a list element
int deletes( LLPtr *sPtr, int value )
{
   LLPtr previousPtr; 
   LLPtr currentPtr; 
   LLPtr tempPtr; 

   // delete first node
   if ( value == ( *sPtr )->id ) {
      tempPtr = *sPtr; 
      *sPtr = ( *sPtr )->nextPtr; 
      if(*sPtr) (*sPtr)->pPtr = NULL;
      free( tempPtr ); 
      return value;
   } 
   else {
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      while ( currentPtr != NULL && currentPtr->id != value ) {
         previousPtr = currentPtr; 
         currentPtr = currentPtr->nextPtr; 
      } 

      if ( currentPtr != NULL ) {
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         if(currentPtr->nextPtr) currentPtr->nextPtr->pPtr = previousPtr;
         free( tempPtr );
         return value;
      } 
   } 

   return '\0';
} 

int isEmpty( LLPtr sPtr )
{
   return sPtr == NULL;
} 

// print the list (ปรับรูปแบบตามรูปภาพตัวอย่าง)
void printList( LLPtr currentPtr )
{
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } 
   else {
      puts( "The list is:" );

      LLPtr lastPtr = NULL; // เก็บตัวสุดท้ายไว้ print ย้อนกลับ

      // Forward Loop
      while ( currentPtr != NULL ) {
         printf( "%d %s --> ", currentPtr->id, currentPtr->name );
         if (currentPtr->nextPtr == NULL) lastPtr = currentPtr; // หาหาง
         currentPtr = currentPtr->nextPtr;
      } 
      puts( "NULL" );
       
      // Backward Loop
      while ( lastPtr != NULL ) {
         printf( "%d %s --> ", lastPtr->id, lastPtr->name );
         lastPtr = lastPtr->pPtr;
      } 
      puts( "NULL\n" );
   } 
} // วงเล็บปิดที่เคยหายไป ใส่ครบแล้วครับ

void clearList( LLPtr *sPtr )
{
    LLPtr tempPtr;
    while (*sPtr != NULL) {
        tempPtr = *sPtr;
        *sPtr = (*sPtr)->nextPtr;
        printf("delete %d\n", tempPtr->id); 
        free(tempPtr);
    }
}
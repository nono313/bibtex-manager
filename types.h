/* 
Bibtex Project - types.h
Maxime B. & Nathan O. (TC03)
maxime.bourgeois@utbm.fr nathan.olff@utbm.fr

types.h : cointains declarations of our constants, of our data structures (Linked List and others) and the prototypes of our fonctions.
*/

#ifndef __TYPES__
#define __TYPES__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>


/* == Constantes == */
/* Constantes for defining the BOOL type */
#define BOOL int
#define TRUE 1
#define FALSE 0


/* == Structures == */
/* AbstractList : may also be used as Library */
typedef struct elemAbstract {
	void* value;					
	struct elemAbstract* next;
	struct elemAbstract* prev;
} AbstractElement;

typedef struct {
	AbstractElement* head;
	AbstractElement* tail;
	int count;
	size_t size;
} AbstractList;

/* EntryField */
typedef struct {
	char* name;					
	void* value;					/* If name="author" => abstractList of authors, else => char* */
} EntryField;

/* Entry */
typedef struct {
	char* key;					
	char* type;					
	AbstractList requiredFieldList; 	/* List of entryField */
	AbstractList optionalFieldList; 	/* List of entryField */
} Entry;

/* Author */
typedef struct {
	char* lastName;					/* Example : GAUD */ 
	char* firstName;				/* Example : Nicolas */
} Author;

/* AuthorPublications */
typedef struct {
	Author author;					
	AbstractList publicationsList; 	/* List of Entry */
} AuthorPublications;

/* DataPublications : List of publications */
typedef struct {
	char* year;								
	AbstractList publicationsList;	/* List of entry */
} DatePublications;

typedef AbstractList Library;
typedef AbstractList ListAuthorPublications;
typedef AbstractList AuthorList;
typedef AbstractList ListDatePublications;

/* == Functions' prototypes == */
int testRegex(char* line, char* regexString, char*** regexArray, int sizeMax);
/*
* isContained : replace all the special characters in a string
* 
* value : a string we want to search in the variable string
* string : the given string in which we want to search value
* 
* return a boolean : TRUE if value is contained in string, FALSE if not
*/
BOOL isContained(char* value, char* string);
/*
* isEmpty : indicates if the list is empty or not
* 
* list : a generic list
* 
* return a boolean : TRUE if the list is empty, FALSE if the list isnt
*/
BOOL isEmpty(AbstractList list);
/*
* replaceSpecialChars : replace all the special characters in a string
* 
* string : the given string in which we want to replace special characters
* 
* return the string special characters replaced
*/
char* replaceSpecialChars(char* string);

/*
* initEntry : initialize an entry
* 
* typeEntry : the entry's type
* key : the entry's key
* 
* return an Entry initialized
*/
Entry* initEntry(char* typeEntry, char* key);
/*
* initList : initialize a list (which is returned) setting his head/tail equal to NULL, his count equal to 0 and his size equal to the given size (function's argument)
* 
* size : since the list is a abstract list (including void*) we must have a list.size which contains the size of the list's element,
         for Example : if it's a list of entryField then we'll have size=sizeof(entryField), if it's a list of publications for then we'll have size=sizeof(Entry)
* 
* return an AbstractList initialized
*/
AbstractList initList(int size);

/*
* insertHead : insert an element or a pointer at the beginning of the list
* 
* list : the list in which we have to put the element/pointer
* element : a pointer on a given element we want to put in the beginning of list
* allocMemory : if allocMemory is equal to TRUE (1) then we create a new element at the beginning of the list and we will copy the value of element into the new created element
                else then we just copy the pointer at the end of the list (which means element is not a temporary element so we can just copy his adress)
*
* return the list with the new element
*/
AbstractList insertHead(AbstractList list, void* element, BOOL allocMemory);
/*
* removeHead : remove the first element of the list
* 
* list : the list in which we have to remove the first element
* 
* return the list without the first element
*/
AbstractList removeHead(AbstractList list);
/*
* insertTail : insert an element or a pointer at the end of the list
* 
* list : the list in which we have to put the element/pointer
* element : a pointer on a given element we want to put in the end of list
* allocMemory : if allocMemory is equal to TRUE (1) then we create a new element at the beginning of the list and we will copy the value of element into the new created element
                else then we just copy the pointer at the end of the list (which means element is not a temporary element so we can just copy his adress)
*
* return the list with the new element
*/
AbstractList insertTail(AbstractList list, void* element, BOOL allocMemory);
/*
* removeTail : remove the first element of the list
* 
* list : the list in which we have to remove the first element
* 
* return the list without the last element
*/
AbstractList removeTail(AbstractList list);
/*
 * clean_stdin : clean the keyboard buffer
 */
void clean_stdin(void);

#endif

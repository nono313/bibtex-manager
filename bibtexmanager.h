/* 
Bibtex Project - bibtexmanager.h
Maxime B. & Nathan O. (TC03)
maxime.bourgeois@utbm.fr nathan.olff@utbm.fr

bibtexmanager.h : cointains the prototypes of our fonctions which manage the bibtex.
*/

#ifndef __SORT_H__
#define __SORT_H__
#include <printLibrary.h>

/*
* longestLine : search the lengh of the longuest line of a file
* 
* fileName : the file's name
* 
* return the lengh of the longuest line of the file
*/
int longestLine(char* fileName);
/*
* parseBibtexFile : parse a bibtex file
* 
* fileName : the file's name
* 
* return a library from the parsing of the file
*/
AbstractList parseBibtexFile(char* fileName);

/*
* stringToUpper : upper a string
* 
* string : a given string
* 
* return the string uppered
*/
char* stringToUpper(char* string);
/*
* stringToLower : lower a string
* 
* string : a given string
* 
* return the string lowered
*/
char* stringToLower(char* string);

/*
* findEntryYear : find the entry's year
* 
* entry : a given entry
* 
* return a string corresponding to the entry's year
*/
char* findEntryYear(void* entry);

/*
* compareYear : compare two years (string)
* 
* year1, year2 : two given years
* 
* - return an integer < 0 if year1 < year2
* - return 0 if year1 = year2
* - return an integer > 0 if year1 > year2
*/
int compareYear(void* year1, void* year2);
/*
* compareEntryByYear : compare two entries by years (string)
* 
* year1, year2 : two given entries
* 
* - return an integer < 0 if year1 < year2
* - return 0 if year1 = year2
* - return an integer > 0 if year1 > year2
*/
int compareEntryByYear(void* entry1, void* entry2);
/*
* compareAuthor : compare two authors
* 
* author1, author2 : two given authors
* 
* - return an integer < 0 if author1 < author2
* - return 0 if author1 = author2
* - return an integer > 0 if author1 > author2
*/
int compareAuthor(void* author1, void* author2);
/*
* compareEntryByAuthor : compare two entries by author
* 
* entry1, entry2 : two given entries
* 
* - return an integer < 0 if author1 < author2
* - return 0 if author1 = author2
* - return an integer > 0 if author1 > author2
*/
int compareEntryByAuthor(void* entry1, void* entry2);

/*
* randomIndex : compute a random integer with min <= int < max
* 
* min, max : two given integers witch are the limit of the random generation
* 
* return an integer with min <= int < max
*/
int randomIndex(int min, int max);
/*
* swapValues : swap the values of two elements
* 
* Elem1, Elem2 : the generic element
* 
* return nothing
*/
void swapValues(AbstractElement* Elem1, AbstractElement* Elem2);
/*
* partition : put the elements lesser than an index at his left, and the greater ones at his right
* 
* list : a generic list
* left : the "left" border of the partionning
* right : the "right" border of the partionning
* pivotIndex : the initial index of the pivot
* storeIndex : the final index of the pivot
* 
* return the list partionned
*/
int partition(AbstractList list, int left, int right, int pivotIndex, int(*ptrFCompare)(void*,void*));
/*
* quicksort : quicksort a list 
* 
* list : a generic list
* left : the "left" border of the partionning
* right : the "right" border of the partionning
* ptrFCompare : a pointer of a comparison function
* 
* return nothing
*/
void quicksort(AbstractList list, int left, int right, int(*ptrFCompare)(void*,void*));

/*
* sortLibraryAuthorDate : sort a library by author and sort each author's publication by date
* 
* library : the library we want to sort
* 
* return the library sorted
*/
AbstractList sortLibraryAuthorDate(AbstractList library);
/*
* sortLibraryDateAuthor : sort a library by date and sort each date's publications by author
* 
* library : the library we want to sort
* 
* return the library sorted
*/
AbstractList sortLibraryDateAuthor(AbstractList library);

/*
* exportAuthorListToHtml : export a list of author
* 
* authorList : a list of author
* filePtr : a file's pointer
* 
* return nothing
*/
void exportAuthorListToHtml(AbstractList *authorList, FILE* filePtr);

/*
* exportEntryToHtml : export an entry
* 
* entry : a given entry
* filePtr : a file's pointer
* 
* return nothing
*/
void exportEntryToHtml(Entry* entry, FILE* filePtr);
/*
* exportAuthorsPublications : export the list of all author's publication from a library
* 
* libraryAuthorDate : the list of all author's publication
* fileName : the name of the file that will be created by the export
* 
* return nothing
*/
void exportAuthorsPublications(ListAuthorPublications libraryAuthorDate, char* fileName);
/*
* exportDatePublications : export the list of all date's publication from a library
* 
* libraryDateAuthor : the list of all date's publication
* fileName : the name of the file that will be created by the export
* 
* return nothing
*/
void exportDatePublications(ListDatePublications libraryDateAuthor, char* fileName);
/*
* exportDatePublications : export a library
* 
* library : the library we want to export
* fileName : the name of the file that will be created by the export
* 
* return nothing
*/
void exportToHTML(AbstractList library, char* fileName);

/*
* freeAuthorList : free a list of authors
* 
* authorList : the list of authors we want to free
* 
* return nothing
*/
void freeAuthorList(AbstractList *authorlist);
/*
* freeEntry : free a entry
* 
* entry : the entry we want to free
* 
* return nothing
*/
void freeEntry(Entry *entry);
/*
* removeEntry : remove a entry in the library
* 
* library : the library in which we remove the entry
* keyToBeRemoved : the key of the entry we want to free
* 
* return nothing
*/
AbstractList removeEntry(AbstractList library, char* keyToBeRemoved);
/*
* freeLibrary : free a entry
* 
* library : the library we want to free
* freeValue : a boolean which indicate if we need to free the value of the entries 
* 
* return nothing
*/
void freeLibrary(AbstractList library, BOOL freeValue);

/*
* freeAuthorsPublications : free the list of all AuthorsPublications
* 
* libraryDateAuthor : the list of all author's publication
* 
* return nothing
*/
void freeAuthorsPublications(ListAuthorPublications libraryAuthorDate);
/*
* freeDatePublications : free the list of all DatePublications
* 
* libraryDateAuthor : the list of all date's publication
* 
* return nothing
*/
void freeDatePublications(ListDatePublications libraryDateAuthor);
/*
* freeSimpleList : free a list
* 
* list : the list we want to free
* 
* return nothing
*/
void freeSimpleList(AbstractList list);
/*
* deleteList : delete a list
* 
* list : the list we want to delete
* 
* return nothing
*/
void deleteList(AbstractList list);


#endif

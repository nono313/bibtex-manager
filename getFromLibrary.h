/* 
Bibtex Project - getFromLibrary.h
Maxime B. & Nathan O. (TC03)
maxime.bourgeois@utbm.fr nathan.olff@utbm.fr

getFromLibrary.h : cointains the prototypes of our fonctions which get things from the library.
*/

#ifndef __GET_FROM_LIBRARY_H__
#define __GET_FROM_LIBRARY_H__
#include <types.h>

/*
 * checkEntry : check if an entry exists in the library
 * 
 * library : list of entries
 * key : the key of the entry to check
 */
BOOL checkEntry(AbstractList library, char* key);
/*
* getEntry : get an entry from a library
* 
* library : the library from which we want to get the entry
* key : the key of the entry we want to get
* 
* return the entry found
*/
Entry* getEntry(AbstractList library, char* key);
/*
* getListAuthor : make the library's list of authors
* 
* library : the library from which we want to make the author list
* 
* return the library's list of authors
*/
AbstractList getListAuthor(AbstractList* library);
/*
* getListAuthorFromEntry : make the entry's list of authors
* 
* entry : the entry from which we want to make the author list
* 
* return the entry's list of authors
*/
AbstractList* getListAuthorFromEntry(Entry* entry);
/*
* getListDate : make the library's list of date
* 
* library : the library from which we want to make the list date
* 
* return the library's list of date
*/
AbstractList getListDate(AbstractList* library);

/*
* getYearFromEntry : get the entry's year
* 
* entry : a given entry
* 
* return a string corresponding to the entry's year
*/
char* getYearFromEntry(Entry *entry);

/*
* addAuthor : add an author to the library's list of authors
* 
* listAuthor : the library's list of authors
* firstName : the first name of the author
* lastName : the last name of the author
* 
* return the library's list of authors with the new author
*/
AbstractList addAuthor(AbstractList listAuthor, char* firstName, char* lastName);
/*
* addEntryField : add an entryField to the entry
* 
* name : the name of the entryField
* value : the value of the entryField
* entry : the entry in which we want to add the new entryField
* requiredFieldArray : the array of required field by the entry
* boolRequiredArray : an array of boolean which indicates if the entry already contains a requiredField or not
* sizeofRequiredArray : the requiredFieldArray's size
* 
* return the entry with the new entryField
*/
Entry* addEntryField(char* name, void* value, Entry* entry, char* requiredFieldArray[15], BOOL *boolRequiredArray, int sizeofRequiredArray);

/*
* isAuthorInEntry : check if an author is in the entry
* 
* entry : the entry in which we want to search the author
* author : the author we want to search in the entry
* 
* return a boolean : TRUE if the author is one of the entry's authors, 0 if not
*/
BOOL isAuthorInEntry(Entry *entry, Author author);
/*
* isEntryFromThisYear : check if a year is the entry's year
* 
* entry : a given entry
* year : a given year (string)
* 
* return a boolean : TRUE if year is the entry's year, 0 if not
*/
BOOL isEntryFromThisYear(Entry *entry, char* year);

/*
* getAuthorPublications : build the list of the author's publications from the library
* 
* library : the library from which we want to take the author's publications
* author : a given author
* 
* return the author's publications from the library
*/
AuthorPublications getAuthorPublications(AbstractList library, Author author);
/*
* getListAuthorPublications : build the list of the all author's publications from the library
* 
* library : the library from which we want to take the list of all the author's publications
* authorList : a list of all the authors contained in the library
* 
* return the list of all the author's publications from the library
*/
AbstractList getListAuthorPublications(AbstractList library, AbstractList authorList);
/*
* getDatePublications : build the list of the date's publications from the library
* 
* library : the library from which we want to take the date's publications
* year : a given year (string)
* 
* return the date's publications from the library
*/
DatePublications getDatePublications(AbstractList library, char* year);
/*
* getListDatePublications : build the list of the all date's publications from the library
* 
* library : the library from which we want to take the list of all the date's publications
* dateList : a list of all the date contained in the library
* 
* return the list of all the date's publications from the library
*/
AbstractList getListDatePublications(AbstractList library, AbstractList dateList);


#endif

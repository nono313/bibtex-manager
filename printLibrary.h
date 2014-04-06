/* 
Bibtex Project - printLibrary.h
Maxime B. & Nathan O. (TC03)
maxime.bourgeois@utbm.fr nathan.olff@utbm.fr

printLibrary.h : cointains the prototypes of our fonctions which print library or lists.
*/

#ifndef __PRINT_LIB_H__
#define __PRINT_LIB_H__
#include <types.h>
#include <getFromLibrary.h>

/*
* printAuthorList : print a list of authors
* 
* authorList : a list of authors
* 
* return nothing
*/
void printAuthorList(AbstractList authorList);
/*
* printAuthorListFromEntry : print a list of authors from a given entry
* 
* entry : a given entry
* 
* return nothing
*/
void printAuthorListFromEntry(Entry* entry);

/*
* printEntry : print an entry
* 
* entry : a given entry
* 
* return nothing
*/
void printEntry(Entry* entry);
/*
* printEntryField : print an entryField
* 
* entryField : a given entryField
* 
* return nothing
*/
void printEntryField(EntryField* entryField);

/*
* printLibrary : print a library
* 
* list : a given library (list)
* 
* return nothing
*/
void printLibrary(AbstractList list);

/*
* printAuthorPublications : print the list of author's publications
* 
* authorPublications : the list of author's publications
* 
* return nothing
*/
void printAuthorPublications(AuthorPublications authorPublications);
/*
* printDatePublications : print the list of date's publications
* 
* datePublications : the list of author's publications
* 
* return nothing
*/
void printDatePublications(DatePublications datePublications);
/*
* printListAuthorPublications : print all the authors's publications
* 
* listAuthorPublications : a list of all the authors' publications
* 
* return nothing
*/
void printListAuthorPublications(ListAuthorPublications listAuthorPublications);
/*
* printListDatePublications : print all the dates's publications
* 
* listAuthorPublications : a list of all the dates' publications
* 
* return nothing
*/
void printListDatePublications(ListDatePublications listDatePublications);
/*
* printKeyLibraryEntry : print only the entries' key of a library
* 
* list : a given library (list)
* 
* return nothing
*/
void printKeyLibraryEntry(AbstractList list);

#endif

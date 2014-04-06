/* 
Bibtex Project - printLibrary.c
Maxime B. & Nathan O. (TC03)
maxime.bourgeois@utbm.fr nathan.olff@utbm.fr

printLibrary.c : cointains the code of our fonctions which print library or lists.
*/

#include <printLibrary.h>

/*
* printAuthorList : print a list of authors
* 
* authorList : a list of authors
* 
* return nothing
*/
void printAuthorList(AbstractList authorList)
{
	AbstractElement* tmpElem;	
	
	tmpElem = authorList.head;	
	while(tmpElem != NULL)
	{
		printf("%s %s", ((Author*) tmpElem->value)->firstName, ((Author*) tmpElem->value)->lastName);
		if(tmpElem->next != NULL)
		{
			if(tmpElem->next->next == NULL)
				printf(" and ");
			else
				printf(", ");
		}
		else
			printf("\n");
		
		tmpElem = tmpElem->next;
	}
}
/*
* printAuthorListFromEntry : print a list of authors from a given entry
* 
* entry : a given entry
* 
* return nothing
*/
void printAuthorListFromEntry(Entry* entry)
{
	AbstractList *listAuthor;
	listAuthor = getListAuthorFromEntry(entry);
	if(listAuthor == NULL)
		printf("NULL");
	else
		printAuthorList(*listAuthor);
}

/*
* printEntry : print an entry
* 
* entry : a given entry
* 
* return nothing
*/
void printEntry(Entry* entry)
{
	AbstractElement* tmpElem;
	tmpElem = entry->requiredFieldList.head;	
	if(tmpElem != NULL)
	{
		puts(entry->key);
		while(tmpElem != NULL)
		{
			if(strcmp((char*)((EntryField*) tmpElem->value)->name, "author") == 0 && ((EntryField*) tmpElem->value)->value != NULL)
			{
				/*printAuthorList(*(AbstractList*)((EntryField*) tmpElem->value));*/
				printAuthorList(*(AbstractList*)((EntryField*) tmpElem->value)->value);
			}
			else if(((EntryField*) tmpElem->value)->value != NULL)
			{
				printEntryField((EntryField*) tmpElem->value);
			}
			tmpElem = tmpElem->next;
		}
	}
	
	tmpElem = entry->optionalFieldList.head;
	if(tmpElem != NULL)
	{
		while(tmpElem != NULL)
		{
			if(strcmp((char*)((EntryField*) tmpElem->value)->name, "author") == 0 && ((EntryField*) tmpElem->value)->value != NULL)
			{
				/*printAuthorList(*(AbstractList*)((EntryField*) tmpElem->value));*/
				printAuthorList(*(AbstractList*)((EntryField*) tmpElem->value)->value);
			}
			else if(((EntryField*) tmpElem->value)->value != NULL)
			{
				printEntryField((EntryField*) tmpElem->value);
			}
			
			tmpElem = tmpElem->next;
		}
	}
	printf("\n\n");
}
/*
* printEntryField : print an entryField
* 
* entryField : a given entryField
* 
* return nothing
*/
void printEntryField(EntryField* entryField)
{
	if(strcmp((char*)entryField->value, "-") != 0)
	{
		printf("%s,", (char*)entryField->value);
	}
	if(strcmp(entryField->name, "title") == 0 || strcmp(entryField->name, "booktitle") == 0)
	{
		printf("\n");
	}
}

/*
* printLibrary : print a library
* 
* list : a given library (list)
* 
* return nothing
*/
void printLibrary(AbstractList list)
{
	AbstractElement* tmpElem;
	tmpElem = list.head;	
	
	while(tmpElem != NULL)
	{
		printEntry((Entry*) (tmpElem->value));
		tmpElem = tmpElem->next;
	}
}

/*
* printAuthorPublications : print the list of author's publications
* 
* authorPublications : the list of author's publications
* 
* return nothing
*/
void printAuthorPublications(AuthorPublications authorPublications)
{	
	printf("\n\t\t%s %s\n", authorPublications.author.firstName, authorPublications.author.lastName);
	printLibrary(authorPublications.publicationsList);
}
/*
* printDatePublications : print the list of date's publications
* 
* datePublications : the list of author's publications
* 
* return nothing
*/
void printDatePublications(DatePublications datePublications)
{	
	printf("\n\t\t%s\n\n", datePublications.year);
	printLibrary(datePublications.publicationsList);
}
/*
* printListAuthorPublications : print all the authors's publications
* 
* listAuthorPublications : a list of all the authors' publications
* 
* return nothing
*/
void printListAuthorPublications(ListAuthorPublications listAuthorPublications)
{	
	AbstractElement* tmpAuthorPublication;
	tmpAuthorPublication = listAuthorPublications.head;	
	
	while(tmpAuthorPublication != NULL)
	{
		printAuthorPublications(*(AuthorPublications*) (tmpAuthorPublication->value));
		tmpAuthorPublication = tmpAuthorPublication->next;
	}
}
/*
* printListDatePublications : print all the dates's publications
* 
* listAuthorPublications : a list of all the dates' publications
* 
* return nothing
*/
void printListDatePublications(ListDatePublications listDatePublications)
{	
	AbstractElement* tmpDatePublications;
	tmpDatePublications = listDatePublications.head;	
	
	while(tmpDatePublications != NULL)
	{
		printf("\n\t%s\n\n", ((DatePublications*)(tmpDatePublications->value))->year);
		printLibrary(((DatePublications*)(tmpDatePublications->value))->publicationsList);
		tmpDatePublications = tmpDatePublications->next;
	}
}
/*
* printKeyLibraryEntry : print only the entries' key of a library
* 
* list : a given library (list)
* 
* return nothing
*/
void printKeyLibraryEntry(AbstractList list)
{	
	AbstractElement* tmpElem;
	tmpElem = list.head;	
	
	while(tmpElem != NULL)
	{
		printf("\n%s :\n\t", ((Entry*)(tmpElem->value))->key);
		printAuthorListFromEntry((Entry*)(tmpElem->value));
		tmpElem = tmpElem->next;
	}
}

/* 
Bibtex Project - getFromLibrary.c
Maxime B. & Nathan O. (TC03)
maxime.bourgeois@utbm.fr nathan.olff@utbm.fr

getFromLibrary.c : cointains the code of our fonctions which get things from the library.
*/

#include <bibtexmanager.h>
#include <getFromLibrary.h>

/*
 * checkEntry : check if an entry exists in the library
 * 
 * library : list of entries
 * key : the key of the entry to check
 */
BOOL checkEntry(AbstractList library, char* key)
{
	AbstractElement* tmpElem = NULL;
	tmpElem = library.head;
	while(tmpElem != NULL && strcmp(((Entry*)(tmpElem->value))->key, key) != 0)
	{
		tmpElem = tmpElem->next;
	}
	if(tmpElem == NULL)
	{
		return FALSE;
	}
	else
		return TRUE;
}
/*
* getEntry : get an entry from a library
* 
* library : the library from which we want to get the entry
* key : the key of the entry we want to get
* 
* return the entry found
*/
Entry* getEntry(AbstractList library, char* key)
{
	AbstractElement* tmpElem = NULL;
	tmpElem = library.head;
	while(tmpElem != NULL && strcmp(((Entry*)(tmpElem->value))->key, key) != 0)
	{
		tmpElem = tmpElem->next;
	}
	if(tmpElem == NULL)
	{
		return NULL;
	}
	else
		return (Entry*)(tmpElem->value);
}
/*
* getListAuthor : make the library's list of authors
* 
* library : the library from which we want to make the author list
* 
* return the library's list of authors
*/
AbstractList getListAuthor(AbstractList* library)
{
	AbstractElement *tmpAbstrEntry, *tmpAbstrEntryField, *tmpAbstrAuthor,  *tmpAbstrListAuthor;
	AbstractList listAuthor;
	Entry* tmpEntry;
	tmpAbstrEntry = library->head;
	listAuthor = initList(sizeof(Author));
	while(tmpAbstrEntry != NULL)
	{
		tmpEntry = (Entry*)tmpAbstrEntry->value;
		tmpAbstrEntryField = tmpEntry->requiredFieldList.head;
		while(tmpAbstrEntryField != NULL && strcmp(((EntryField*)tmpAbstrEntryField->value)->name, "author") != 0)
		{
			tmpAbstrEntryField = tmpAbstrEntryField->next;
		}
		if(tmpAbstrEntryField != NULL && strcmp(((EntryField*)tmpAbstrEntryField->value)->name, "author") == 0)
		{
			tmpAbstrAuthor = ((AbstractList*)((EntryField*)tmpAbstrEntryField->value)->value)->head;
			while(tmpAbstrAuthor != NULL)
			{
				tmpAbstrListAuthor = listAuthor.head;
				if(isEmpty(listAuthor))
					listAuthor = addAuthor(listAuthor, ((Author*)(tmpAbstrAuthor->value))->firstName, ((Author*)(tmpAbstrAuthor->value))->lastName);
				else
				{
					/*printf("%p\n", (void*)((Author*)(tmpAbstrListAuthor->value))->lastName);
					tmpAuthor.firstName = (char*) malloc(sizeof(char)*(strlen(((Author*)(tmpAbstrAuthor->value))->firstName)+1);
					tmpAuthor.lastName = (char*) malloc(sizeof(char)*(strlen(((Author*)(tmpAbstrAuthor->value))->lastName)+1);
					strcpy(tmpAuthor.firstName, ((Author*)(tmpAbstrAuthor->value))->firstName);
					strcpy(tmpAuthor.lastName, ((Author*)(tmpAbstrAuthor->value))->lastName);
					puts(((Author*)(tmpAbstrListAuthor->value))->lastName);*/
					
					
					while(tmpAbstrListAuthor != NULL && strcmp(((Author*)(tmpAbstrListAuthor->value))->lastName, ((Author*)(tmpAbstrAuthor->value))->lastName) != 0)
					{				
						tmpAbstrListAuthor = tmpAbstrListAuthor->next;
					}
					if(tmpAbstrListAuthor == NULL || strcmp(((Author*)(tmpAbstrListAuthor->value))->lastName, ((Author*)(tmpAbstrAuthor->value))->lastName) != 0)
					{
						listAuthor = addAuthor(listAuthor, ((Author*)(tmpAbstrAuthor->value))->firstName, ((Author*)(tmpAbstrAuthor->value))->lastName);
					}
				}
				tmpAbstrAuthor = tmpAbstrAuthor->next;
			}
		}
		tmpAbstrEntry = tmpAbstrEntry->next;
	}
	return listAuthor;
}
/*
* getListAuthorFromEntry : make the entry's list of authors
* 
* entry : the entry from which we want to make the author list
* 
* return the entry's list of authors
*/
AbstractList* getListAuthorFromEntry(Entry* entry)
{
	AbstractList *listAuthor = NULL;
	AbstractElement *tmpElem;
	tmpElem = entry->requiredFieldList.head;
	while(tmpElem != NULL && strcmp(((EntryField*)(tmpElem->value))->name, "author") != 0)
	{
		tmpElem = tmpElem->next;
	}
	if(tmpElem == NULL)
	{
		listAuthor = NULL;
	}
	else
	{
		listAuthor = (AbstractList*)((EntryField*)(tmpElem->value))->value;
	}
	return listAuthor;
}
/*
* getListDate : make the library's list of date
* 
* library : the library from which we want to make the list date
* 
* return the library's list of date
*/
AbstractList getListDate(AbstractList* library)
{
	/* AbtractList -> AbstractElement -> Entry -> EntryField -> Year */
	/* AbtractList -> AbstractElement -> Year (char*) */
	AbstractList listYear;
	AbstractElement *tmpAbstrElem, *tmpAbstrEntryField, *tmpListYear;
	Entry* tmpEntry;

	listYear = initList(sizeof(char)*5);
	
	tmpAbstrElem = library->head;
	while(tmpAbstrElem != NULL)
	{		
		tmpEntry = (Entry*)tmpAbstrElem->value;
		tmpAbstrEntryField = tmpEntry->requiredFieldList.head;
		while(tmpAbstrEntryField != NULL && strcmp(((EntryField*)tmpAbstrEntryField->value)->name, "year") != 0)
		{
			tmpAbstrEntryField = tmpAbstrEntryField->next;
		}
		if(tmpAbstrEntryField != NULL && strcmp(((EntryField*)tmpAbstrEntryField->value)->name, "year") == 0)
		{
			tmpListYear = listYear.head;
			while(tmpListYear != NULL && strcmp((char*)(((EntryField*)tmpAbstrEntryField->value)->value), (char*)(tmpListYear->value)) != 0)
			{
				tmpListYear = tmpListYear->next;
			}
			if(tmpListYear == NULL)
			{
				listYear = insertTail(listYear, (char*)(((EntryField*)tmpAbstrEntryField->value)->value), 1);
			}
		}
		else
		{
			tmpAbstrEntryField = tmpEntry->optionalFieldList.head;
			while(tmpAbstrEntryField != NULL && strcmp(((EntryField*)tmpAbstrEntryField->value)->name, "year") != 0)
			{
				tmpAbstrEntryField = tmpAbstrEntryField->next;
			}
			if(tmpAbstrEntryField != NULL && strcmp(((EntryField*)tmpAbstrEntryField->value)->name, "year") == 0)
			{
				tmpListYear = listYear.head;
				while(tmpListYear != NULL && strcmp((char*)(((EntryField*)tmpAbstrEntryField->value)->value), (char*)(tmpListYear->value)) != 0)
				{
					tmpListYear = tmpListYear->next;
				}
				if(tmpListYear == NULL /*&& strcmp((char*)(((EntryField*)tmpAbstrEntryField->value)->value), (char*)(tmpListYear->value)) != 0 */)
				{
					listYear = insertTail(listYear, (char*)(((EntryField*)tmpAbstrEntryField->value)->value), 1);
				}
			}
		}
		
		tmpAbstrElem = tmpAbstrElem->next;
	}

	return listYear;
}

/*
* getYearFromEntry : get the entry's year
* 
* entry : a given entry
* 
* return a string corresponding to the entry's year
*/
char* getYearFromEntry(Entry *entry)
{
	AbstractElement *tmpElem;
	char* year = NULL;
	year = (char*)malloc(sizeof(char)*5);
	
	tmpElem = entry->requiredFieldList.head;
	while(tmpElem != NULL && strcmp(((EntryField*)(tmpElem->value))->name, "year") != 0)
		tmpElem = tmpElem->next;
	if(tmpElem != NULL)
	{
		strcpy(year, (char*)((EntryField*)(tmpElem->value))->value);
	}
	else
	{
		tmpElem = ((Entry*)(tmpElem->value))->optionalFieldList.head;
		while(tmpElem != NULL && strcmp(((EntryField*)(tmpElem->value))->name, "year") != 0)
			tmpElem = tmpElem->next;
		if(tmpElem != NULL)
		{
			strcpy(year, (char*)((EntryField*)(tmpElem->value))->value);
		}
	}
	return year;
}

/*
* addAuthor : add an author to the library's list of authors
* 
* listAuthor : the library's list of authors
* firstName : the first name of the author
* lastName : the last name of the author
* 
* return the library's list of authors with the new author
*/
AbstractList addAuthor(AbstractList listAuthor, char* firstName, char* lastName)
{
	Author* tmpAuthor;
	
	tmpAuthor = (Author*) malloc(sizeof(Author));
	tmpAuthor->lastName = (char*) malloc(sizeof(char)*(strlen(lastName)+1));
	tmpAuthor->firstName = (char*) malloc(sizeof(char)*(strlen(firstName)+1));
	
	strcpy(tmpAuthor->lastName, lastName);
	strcpy(tmpAuthor->firstName, firstName);	
	
	listAuthor = insertTail(listAuthor, (void*) tmpAuthor, 0);
	
	return listAuthor;
}
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
Entry* addEntryField(char* name, void* value, Entry* entry, char* requiredFieldArray[15], BOOL *boolRequiredArray, int sizeofRequiredArray)
{
	EntryField* tmpEntryField;
	char *firstName, *lastName, *prevValue, *string;
	BOOL contained = FALSE;
	int i = -1;
	tmpEntryField = (EntryField*) malloc(sizeof(EntryField));
	tmpEntryField->name = (char*) malloc(sizeof(char)*(strlen(name)+1));
	strcpy(tmpEntryField->name, name);
	/*tmpEntryField->value = (void*) malloc(sizeof(char)*(strlen(value)+1));*/
	
	while(i < sizeofRequiredArray-1 && contained == FALSE)
	{
		i++;
		contained = isContained(name, requiredFieldArray[i]);
	}

	
	if(strcmp(name, "author") == 0)
	{
		tmpEntryField->value = (AbstractList*) malloc(sizeof(AbstractList));
		*(AbstractList*)(tmpEntryField->value) = initList(sizeof(Author));
		while(value != NULL)
		{
			firstName = NULL;
			string = (char*) malloc(sizeof(char)*500);
			firstName = (char*) malloc(sizeof(char)*100);
			lastName = (char*) malloc(sizeof(char)*100);
			prevValue = (char*)value;
			value = strstr(value, " and ");
			if(value == NULL)
				strcpy(string, prevValue);
			else
			{
				strncpy(string, prevValue, (int)((char*)value-prevValue));
				string[(int)((char*)value-prevValue)] = '\0';
			}
			sscanf(string, "%[^,], %[^\t\n]", lastName, firstName);
			free(string);
			lastName = replaceSpecialChars(lastName);
			firstName = replaceSpecialChars(firstName);
			
			*((AbstractList*)(tmpEntryField->value)) = addAuthor(*((AbstractList*)(tmpEntryField->value)), firstName, lastName);
			free(firstName);
			free(lastName);

			if(value != NULL)
				value = (char*)value+5;
			
		}
		
	}
	else
	{
		value = (void*)replaceSpecialChars(value);
		tmpEntryField->value = (void*) malloc(sizeof(char)*(strlen(value)+1));
		strcpy((char*)(tmpEntryField->value), value);	
		
	}


	

	
	
	if(contained == TRUE && boolRequiredArray[i] == FALSE)
	{
		boolRequiredArray[i] = TRUE;
		entry->requiredFieldList = insertTail(entry->requiredFieldList, (void*) tmpEntryField, FALSE);
	}
	else
		entry->optionalFieldList = insertTail(entry->optionalFieldList, (void*) tmpEntryField, FALSE);
	free(value);
	
	return entry;
}

/*
* isAuthorInEntry : check if an author is in the entry
* 
* entry : the entry in which we want to search the author
* author : the author we want to search in the entry
* 
* return a boolean : TRUE if the author is one of the entry's authors, 0 if not
*/
BOOL isAuthorInEntry(Entry *entry, Author author)
{
        AbstractElement *tmpElem;
        AbstractList *authorList; 
        AbstractElement *tmpElemAuthor;
        BOOL toBeReturned;
        toBeReturned = FALSE;
        tmpElem = NULL;
        tmpElem = entry->requiredFieldList.head;
        while(tmpElem != NULL && strcmp(((EntryField*)(tmpElem->value))->name, "author") != 0)
                tmpElem = tmpElem->next;
        if(tmpElem != NULL)
        {
                authorList = (AbstractList*)(((EntryField*)(tmpElem->value))->value);
                tmpElemAuthor = authorList->head;
                while(tmpElemAuthor != NULL && !( strcmp(((Author*)(tmpElemAuthor->value))->lastName, author.lastName) == 0 && strcmp(((Author*)(tmpElemAuthor->value))->firstName, author.firstName) == 0) )
                        tmpElemAuthor = tmpElemAuthor->next;
                if(tmpElemAuthor != NULL)
                {
                        toBeReturned = TRUE;
                }
        }
        else
        {
                tmpElem = entry->optionalFieldList.head;
                while(tmpElem != NULL && strcmp(((EntryField*)(tmpElem->value))->name, "author") != 0)
                        tmpElem = tmpElem->next;
                if(tmpElem != NULL)
                {
		               authorList = (AbstractList*)(((EntryField*)(tmpElem->value))->value);
		                tmpElemAuthor = authorList->head;
		                while(tmpElemAuthor != NULL && !( strcmp(((Author*)(tmpElemAuthor->value))->lastName, author.lastName) == 0 && strcmp(((Author*)(tmpElemAuthor->value))->firstName, author.firstName) == 0) )
		                        tmpElemAuthor = tmpElemAuthor->next;
		                if(tmpElemAuthor != NULL)
		                {
		                        toBeReturned = TRUE;
		                }
                }
        }
        return toBeReturned;
}
/*
* isEntryFromThisYear : check if a year is the entry's year
* 
* entry : a given entry
* year : a given year (string)
* 
* return a boolean : TRUE if year is the entry's year, 0 if not
*/
BOOL isEntryFromThisYear(Entry *entry, char* year)
{
	BOOL toBeReturned;
	char* yearFromEntry;
	toBeReturned = FALSE;
	yearFromEntry = getYearFromEntry(entry);
	if(strcmp(yearFromEntry, year) == 0)
	{
		toBeReturned = TRUE;
	}
	free(yearFromEntry);
	return toBeReturned;
}

/*
* getAuthorPublications : build the list of the author's publications from the library
* 
* library : the library from which we want to take the author's publications
* author : a given author
* 
* return the author's publications from the library
*/
AuthorPublications getAuthorPublications(AbstractList library, Author author)
{
	AuthorPublications tmpPubli;
	AbstractElement *tmpElem;
	
	tmpPubli.author = author;
	tmpPubli.publicationsList = initList(sizeof(Entry));
	tmpElem = library.head;
	while(tmpElem != NULL)
	{
		if(isAuthorInEntry((Entry*)(tmpElem->value), author) == TRUE)
		{
			tmpPubli.publicationsList = insertTail(tmpPubli.publicationsList, tmpElem->value, 0);
		}
		tmpElem = tmpElem->next;
	}
	return tmpPubli;
	
}
/* 
* getListAuthorPublications : build the list of the all author's publications from the library
* 
* library : the library from which we want to take the list of all the author's publications
* authorList : a list of all the authors contained in the library
* 
* return the list of all the author's publications from the library
*/
AbstractList getListAuthorPublications(AbstractList library, AbstractList authorList)
{
	AbstractList listAuthorPub;
	AbstractElement *tmpElem;
	AuthorPublications tmpAuthorPub;
	listAuthorPub = initList(sizeof(AuthorPublications));
	
	tmpElem = authorList.head;
	while(tmpElem != NULL)
	{
		tmpAuthorPub = getAuthorPublications(library, (*(Author*)(tmpElem->value)));
		listAuthorPub = insertTail(listAuthorPub, (void*)(&tmpAuthorPub), 1);
		tmpElem = tmpElem->next;
	}
	return listAuthorPub;	
}
/*
* getDatePublications : build the list of the date's publications from the library
* 
* library : the library from which we want to take the date's publications
* year : a given year (string)
* 
* return the date's publications from the library
*/
DatePublications getDatePublications(AbstractList library, char* year)
{
	DatePublications tmpPubli;
	AbstractElement *tmpElem;
	
	tmpPubli.year = (char*) malloc(sizeof(char)*5);
	
	strcpy(tmpPubli.year, year);
	tmpPubli.publicationsList = initList(sizeof(Entry));
	tmpElem = library.head;
	while(tmpElem != NULL)
	{
		if(isEntryFromThisYear((Entry*)(tmpElem->value), year) == TRUE)
		{
			tmpPubli.publicationsList = insertTail(tmpPubli.publicationsList, tmpElem->value, 0);
		}
		tmpElem = tmpElem->next;
	}
	return tmpPubli;
}
/*
* getListDatePublications : build the list of the all date's publications from the library
* 
* library : the library from which we want to take the list of all the date's publications
* dateList : a list of all the date contained in the library
* 
* return the list of all the date's publications from the library
*/
AbstractList getListDatePublications(AbstractList library, AbstractList dateList)
{
	AbstractList listDatePub;
	AbstractElement *tmpElem;
	DatePublications tmpDatePub;
	
	listDatePub = initList(sizeof(DatePublications));
	
	tmpElem = dateList.head;
	while(tmpElem != NULL)
	{
		tmpDatePub = getDatePublications(library, (char*)(tmpElem->value));
		listDatePub = insertTail(listDatePub, (void*)(&tmpDatePub), 1);
		tmpElem = tmpElem->next;
	}
	
	return listDatePub;	
}

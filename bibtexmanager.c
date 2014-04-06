/* 
Bibtex Project - bibtexmanager.c
Maxime B. & Nathan O. (TC03)
maxime.bourgeois@utbm.fr nathan.olff@utbm.fr

bibtexmanager.c : cointains the code of our fonctions which manage the bibtex.
*/

#include <bibtexmanager.h>

/*
* longestLine : search the lengh of the longuest line of a file
* 
* fileName : the file's name
* 
* return the lengh of the longuest line of the file
*/
int longestLine(char* fileName)
{
	int sizeMax, i;
	char c;
	FILE *file;
	file = fopen(fileName, "r");
	c = (char)fgetc(file);
	sizeMax = 0;
	do{
		c = (char)fgetc(file);
		i = 0;
		while(c != '\n' && c != EOF)
		{
			i++;
			c = (char)fgetc(file);
		}
		if(i > sizeMax)
			sizeMax = i;
	}while(c != EOF);
	fclose(file);
	return sizeMax;
}
/*
* parseBibtexFile : parse a bibtex file
* 
* fileName : the file's name
* 
* return a library from the parsing of the file
*/
AbstractList parseBibtexFile(char* fileName)
{
	int nMatch, sizeMaxOfALine;
	FILE* file = NULL;
	AbstractList* library;
	Entry* tmpEntry = NULL;
	char *line;
	char **arrayRegex/*, **nextLine*/;
	int i, sizeOfRequiredArray, sizeOfLine;
	BOOL *boolRequiredArray;
	
	char** requiredFieldArray = NULL;
	/*Declaration of every arrays or requiredFields for each type of entry*/
	char* requiredFieldArrayArticle[15] = {"author", "title", "journal", "year", ""};
	char* requiredFieldArrayBook[15] = {"author/editor", "title", "publisher", "year", ""};
	char* requiredFieldArrayBooklet[15] = {"title", ""};
	char* requiredFieldArrayInbook[15] = {"author/editor", "title", "chapter/pages", "publisher", "year", ""};
	char* requiredFieldArrayIncollection[15] = {"author", "title", "booktitle", "publisher", "year", ""};
	char* requiredFieldArrayInproceedings[15] = {"author", "title", "booktitle", "year", ""};
	char* requiredFieldArrayConference[15] = {"author", "title", "booktitle", "year", ""};
	char* requiredFieldArrayManual[15] = {"title", ""};
	char* requiredFieldArrayMastersthesis[15] = {"author", "title", "school", "year", ""};
	char* requiredFieldArrayMisc[15] = {""};
	char* requiredFieldArrayPhdthesis[15] = {"author", "title", "school", "year", ""};
	char* requiredFieldArrayProceedings[15] = {"title", "year", ""};
	char* requiredFieldArrayTechreport[15] = {"author", "title", "institution", "year", ""};
	char* requiredFieldArrayUnpublished[15] = {"author", "title", "note", ""};
	arrayRegex = NULL;
	arrayRegex = (char**) malloc(sizeof(char*)*2);
	arrayRegex[0] = NULL;
	arrayRegex[1] = NULL;
	tmpEntry = NULL;
	
	file = fopen(fileName, "r");	/*Open the file in read-only mode*/
	library = (AbstractList*) malloc(sizeof(AbstractList));
	*library = initList(sizeof(Entry));
	if(file == NULL)
	{
		printf("The file %s doesn't exist !\n", fileName);
		return *library;
	}
	
	sizeMaxOfALine = longestLine(fileName);
	line = (char*) malloc(sizeof(char)*(sizeMaxOfALine+1));

	while(fgets(line, sizeMaxOfALine, file) != NULL)
	{
		nMatch = 0;
		/*Read the next line untill it reaches the end of the file or the beginning of an entry*/
		while(line != NULL && line[0] != '@')
		{
			fgets(line, sizeMaxOfALine, file);
		}
		nMatch = testRegex(line, "@([a-zA-Z]+)\\{(.+),", &arrayRegex, sizeMaxOfALine);
		if(nMatch != 0)		/* Beginning of an entry */
		{
			tmpEntry = initEntry(arrayRegex[0], arrayRegex[1]);
			/* Choice of the requiredFieldArray */
			if(strcmp(arrayRegex[0], "Article") == 0)
				requiredFieldArray = requiredFieldArrayArticle;
			else if(strcmp(arrayRegex[0], "Book") == 0)
				requiredFieldArray = requiredFieldArrayBook;
			else if(strcmp(arrayRegex[0], "Booklet") == 0)
				requiredFieldArray = requiredFieldArrayBooklet;
			else if(strcmp(arrayRegex[0], "Inbook") == 0)
				requiredFieldArray = requiredFieldArrayInbook;
			else if(strcmp(arrayRegex[0], "Incollection") == 0)
				requiredFieldArray = requiredFieldArrayIncollection;
			else if(strcmp(arrayRegex[0], "Inproceedings") == 0)
				requiredFieldArray = requiredFieldArrayInproceedings;
			else if(strcmp(arrayRegex[0], "Conference") == 0)
				requiredFieldArray = requiredFieldArrayConference;
			else if(strcmp(arrayRegex[0], "Manual") == 0)
				requiredFieldArray = requiredFieldArrayManual;
			else if(strcmp(arrayRegex[0], "Mastersthesis") == 0)
				requiredFieldArray = requiredFieldArrayMastersthesis;
			else if(strcmp(arrayRegex[0], "Misc") == 0)
				requiredFieldArray = requiredFieldArrayMisc;
			else if(strcmp(arrayRegex[0], "Phdthesis") == 0)
				requiredFieldArray = requiredFieldArrayPhdthesis;
			else if(strcmp(arrayRegex[0], "Proceedings") == 0)
				requiredFieldArray = requiredFieldArrayProceedings;
			else if(strcmp(arrayRegex[0], "Techreport") == 0)
				requiredFieldArray = requiredFieldArrayTechreport;
			else if(strcmp(arrayRegex[0], "Unpublished") == 0)
				requiredFieldArray = requiredFieldArrayUnpublished;
			else
				requiredFieldArray = requiredFieldArrayMisc;

			/* Filling of the requiredFieldList with EntryField [name={"author", "title", ...} & value=NULL] */
			sizeOfRequiredArray=0;
			
			while(strcmp(requiredFieldArray[sizeOfRequiredArray],"") != 0)
			{
				sizeOfRequiredArray++;
			}
			/* boolRequiredArray : array of sizeOfRequiredArray booleans. 
			 * Each element corresponds to a required field.*/
			boolRequiredArray = (BOOL*) malloc(sizeof(BOOL)*sizeOfRequiredArray);
			/* Initialize boolRequiredArray */
			for(i = 0 ; i < sizeOfRequiredArray; i++)
				boolRequiredArray[i] = FALSE;
			do
			{
				fgets(line, sizeMaxOfALine, file);
				/* Quit the loop when arrive at an empty line or a simple '}' */
				if(line[0] == '}' || line[0] == '\0' || line[0] == '\n')
				{
					nMatch = 0;
				}
				else
				{
					sizeOfLine = strlen(line);
					line = realloc(line, sizeof(char)*(sizeMaxOfALine+1));
					/* Loop untill we reach the end of the field value (used for multi-line fields */
					while(line[sizeOfLine-2] != ',')
					{
						line = realloc(line, sizeof(char)*(sizeOfLine+sizeMaxOfALine+1));
						fgets(&line[sizeOfLine], sizeMaxOfALine+1, file);
						sizeOfLine = strlen(line);
					}
					
					nMatch = testRegex(line, "([a-z]+) = [\\{\"](.+)[\\}\"],[\n]$", &arrayRegex, sizeOfLine);
					if(nMatch == 0)
					{
						
						nMatch = testRegex(line, "([a-z]+) = (.+),[\n]$", &arrayRegex, sizeOfLine);
					}
					
					if(nMatch > 0)
					{
						tmpEntry = addEntryField(arrayRegex[0], arrayRegex[1], tmpEntry, requiredFieldArray, boolRequiredArray, sizeOfRequiredArray);
						/*printEntry(tmpEntry);*/
						
					}
				}
			}while(nMatch > 0);
			
			if(tmpEntry != NULL)
			{
				i = 0;
				while(i < sizeOfRequiredArray-1 && boolRequiredArray[i] == TRUE)
				{
					i++;
				}
				if(boolRequiredArray[i] == FALSE)	
				{
					printf("Error, the field \"%s\" is missing !\n", requiredFieldArray[i]);
				}
				else
					*library = insertTail(*library, (void*)tmpEntry, 1);
				
				free(tmpEntry);
				tmpEntry = NULL;
				free(boolRequiredArray);
			}
		}
	}
	free(line);
	free(arrayRegex[0]);
	free(arrayRegex[1]);
	free(arrayRegex);
	fclose(file);
	return *library;
}

/*
* stringToUpper : upper a string
* 
* string : a given string
* 
* return the string uppered
*/
char* stringToUpper(char* string)
{
	int i = 0;
	char* newString;
	newString = (char*) malloc(sizeof(char) * (strlen(string)+1));
	while(string[i] != '\0')
	{
		newString[i] = toupper(string[i]);
		i++;
	}
	newString[i] = '\0';
	return newString;
}
/*
* stringToLower : lower a string
* 
* string : a given string
* 
* return the string lowered
*/
char* stringToLower(char* string)
{
	int i = 0;
	char *newString;
	newString = (char*) malloc(sizeof(char) * (strlen(string)+1));
	while(string[i] != '\0')
	{
		newString[i] = tolower(string[i]);
		i++;
	}
	newString[i] = '\0';
	return newString;
}

/*
* findEntryYear : find the entry's year
* 
* entry : a given entry
* 
* return a string corresponding to the entry's year
*/
char* findEntryYear(void* entry)
{
	AbstractElement* tmpElem;
	char* year = "0000";
	
	tmpElem = ((Entry*) entry)->requiredFieldList.head;
	while(tmpElem != NULL && strcmp(((EntryField*) tmpElem->value)->name, "year") != 0)
	{
		tmpElem = tmpElem->next;
	}
	
	if(tmpElem != NULL)
		year = (char*)((EntryField*) tmpElem->value)->value;
	else
	{
		tmpElem = ((Entry*) entry)->optionalFieldList.head;
		while(tmpElem != NULL && strcmp(((EntryField*) tmpElem->value)->name, "year") != 0)
		{
			tmpElem = tmpElem->next;
		}
		if(tmpElem != NULL)
			year = (char*)((EntryField*) tmpElem->value)->value;
	}
	
	return year;
}

/*
* compareYear : compare two years (string)
* 
* year1, year2 : two given years
* 
* - return an integer < 0 if year1 < year2
* - return 0 if year1 = year2
* - return an integer > 0 if year1 > year2
*/
int compareYear(void* year1, void* year2)
{
	return(-1*strcmp((char*)year1, (char*)year2));
}
/*
* compareEntryByYear : compare two entries by year (string)
* 
* entry1, entry2 : two given entries
* 
* - return an integer < 0 if year1 < year2
* - return 0 if year1 = year2
* - return an integer > 0 if year1 > year2
*/
int compareEntryByYear(void* entry1, void* entry2)
{
	char *year1 = "0000", *year2 = "0000";
	
	year1 = findEntryYear(entry1);
	year2 = findEntryYear(entry2);
	
	return(-1*strcmp(year1, year2));
}
/*
* compareAuthor : compare two authors
* 
* author1, author2 : two given authors
* 
* - return an integer < 0 if author1 < author2
* - return 0 if author1 = author2
* - return an integer > 0 if author1 > author2
*/
int compareAuthor(void* author1, void* author2)
{
	int toBeReturned;
	char *lastName1, *lastName2, *firstName1, *firstName2;
	if(author1 == NULL && author2 == NULL)
		toBeReturned = 0;
	else if(author1 == NULL)
		toBeReturned = -1;
	else if(author2 == NULL)
		toBeReturned = 1;
	else
	{
		lastName1 = stringToUpper(((Author*)author1)->lastName);
		lastName2 = stringToUpper(((Author*)author2)->lastName);
		toBeReturned = strcmp(lastName1, lastName2);
		if(toBeReturned == 0)
		{
			firstName1 = stringToLower(((Author*)author1)->firstName);
			firstName2 = stringToLower(((Author*)author2)->firstName);
			toBeReturned = strcmp(firstName1, firstName2);
			free(firstName1);
			free(firstName2);
		}
		free(lastName1);
		free(lastName2);
	}
	return toBeReturned;
}
/*
* compareEntryByAuthor : compare two entries by author
* 
* entry1, entry2 : two given entries
* 
* - return an integer < 0 if author1 < author2
* - return 0 if author1 = author2
* - return an integer > 0 if author1 > author2
*/
int compareEntryByAuthor(void* entry1, void* entry2)
{
	int toBeReturned;
	AbstractList *listAuthor1 = NULL, *listAuthor2 = NULL;
	AbstractElement *tmpAuth1, *tmpAuth2;
	
	listAuthor1 = getListAuthorFromEntry(entry1);
	listAuthor2 = getListAuthorFromEntry(entry2);

	if(listAuthor1 == NULL && listAuthor2 == NULL)
		toBeReturned = 0;
	else if(listAuthor1 == NULL)
		toBeReturned = -1;
	else if(listAuthor2 == NULL)
		toBeReturned = 1;
	else
	{
		tmpAuth1 = listAuthor1->head;
		tmpAuth2 = listAuthor2->head;
		
		toBeReturned = 0;
		while(tmpAuth1 != NULL && tmpAuth2 != NULL && toBeReturned == 0)
		{
			toBeReturned = compareAuthor((Author*)(tmpAuth1->value), (Author*)(tmpAuth2->value));
			tmpAuth1 = tmpAuth1->next;
			tmpAuth2 = tmpAuth2->next;
			/*toBeReturned = strcmp((*(Author*)(listAuthor1->head->value)).lastName, (*(Author*)(listAuthor2->head->value)).lastName);
			if(toBeReturned == 0)
			{
				toBeReturned = strcmp((*(Author*)(listAuthor1->head->value)).firstName, (*(Author*)(listAuthor2->head->value)).firstName);
			}*/
		}
		/*toBeReturned = compareAuthor((Author*)(listAuthor1.head->value), (Author*)(listAuthor2.head->value));*/
	}
	
	return toBeReturned;
}

/*
* randomIndex : compute a random integer with min <= int < max
* 
* min, max : two given integers witch are the limit of the random generation
* 
* return an integer with min <= int < max
*/
int randomIndex(int min, int max)
{
	int index;
	
	/* min <= index < max */
	index = rand()%(max-min) + min;
	
	return index;
}
/*
* swapValues : swap the values of two elements
* 
* Elem1, Elem2 : the generic element
* 
* return nothing
*/
void swapValues(AbstractElement* Elem1, AbstractElement* Elem2)
{
	void* tmpValue;
	if(Elem1 != NULL && Elem2 != NULL)
	{
		tmpValue = Elem1->value;
		Elem1->value = Elem2->value;
		Elem2->value = tmpValue;
	}
}
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
int partition(AbstractList list, int left, int right, int pivotIndex, int(*ptrFCompare)(void*,void*))
{
	AbstractElement* tmpElem;
	AbstractElement* storeIndexElem; 
	AbstractElement* tmpRight;
	void* pivotValue;
	int i, j, storeIndex;
	
	
	/* Find the pivotElem */
	tmpElem = list.head;
	for(i=0; i<pivotIndex; i++)
	{
		tmpElem = tmpElem->next;
	}
	pivotValue = tmpElem->value;
	
	
	/* Find the rightElem*/
	tmpRight = list.tail;
	for(i=(list.count-1); i>right; i--)
	{
		tmpRight = tmpRight->prev;
	}
	
	/* Move the pivot to the end */		
	swapValues(tmpElem, tmpRight);	
	
	/* Swapping ... */
	storeIndex = left;
	tmpElem = list.head;
	for(i=0; i<right; i++) 
	{
	    if(i>=left)
	    {			
			if((*ptrFCompare)(tmpElem->value, pivotValue) < 0)
			{
				storeIndexElem = list.head;
				for(j=0; j<storeIndex; j++)
				{
					storeIndexElem = storeIndexElem->next;
				}
				swapValues(tmpElem, storeIndexElem);
				storeIndex = storeIndex + 1;
			}
		}
		tmpElem = tmpElem->next;
	}
		
	/* Find the storeIndexElem */
	storeIndexElem = list.head;
	for(i=0; i<storeIndex; i++)
	{
		storeIndexElem = storeIndexElem->next;
	}
	
	/* Find the rightElem*/
	tmpRight = list.tail;
	for(i=(list.count-1); i>right; i--)
	{
		tmpRight = tmpRight->prev;
	}
	
	/* Move the pivot to its final place */
	swapValues(storeIndexElem, tmpRight);
	
	return storeIndex;
}
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
void quicksort(AbstractList list, int left, int right, int(*ptrFCompare)(void*,void*))
{	
	int pivotIndex, pivotNewIndex;
	
	/* If the list has 2 or more items */
	if(left < right)
	{ 

		/* Choose a random index with left <= pivotIndex < right */
		pivotIndex = randomIndex(left, right);
 
		/* Get lists of bigger and smaller items and final position of pivot */
		pivotNewIndex = partition(list, left, right, pivotIndex, ptrFCompare);
		/* Recursively sort elements smaller than the pivot */
		quicksort(list, left, pivotNewIndex-1, ptrFCompare);
 
		/* Recursively sort elements at least as big as the pivot */
		quicksort(list, pivotNewIndex+1, right, ptrFCompare);

	}  
}        

/*
* sortLibraryAuthorDate : sort a library by author and sort each author's publications by date
* 
* library : the library we want to sort
* 
* return the library sorted
*/
AbstractList sortLibraryAuthorDate(AbstractList library)
{
	AbstractList listAuthorPublications, authorList;
	AbstractElement *tmpAuthorPublic;
	int (*compare)(void*,void*);
	listAuthorPublications = initList(sizeof(AuthorPublications));
	
	authorList = getListAuthor(&library);
	compare = &compareAuthor;
	quicksort(authorList, 0, authorList.count-1, compare);
	listAuthorPublications = getListAuthorPublications(library, authorList);
	
	tmpAuthorPublic = listAuthorPublications.head;
	compare = &compareEntryByYear;
	while(tmpAuthorPublic != NULL)
	{
		quicksort(((AuthorPublications*)(tmpAuthorPublic->value))->publicationsList, 0, (((AuthorPublications*)(tmpAuthorPublic->value))->publicationsList).count-1, compare);
		tmpAuthorPublic = tmpAuthorPublic->next;
	}
	deleteList(authorList);
	return listAuthorPublications;
}
/*
* sortLibraryDateAuthor : sort a library by date and sort each date's publications by author
* 
* library : the library we want to sort
* 
* return the library sorted
*/
AbstractList sortLibraryDateAuthor(AbstractList library)
{
	AbstractList listDatePublications, dateList;
	AbstractElement *tmpDatePublic;
	int (*compare)(void*,void*);
	listDatePublications = initList(sizeof(DatePublications));
	
	dateList = getListDate(&library);
	compare = &compareYear;
	quicksort(dateList, 0, dateList.count-1, compare);

	listDatePublications = getListDatePublications(library, dateList);
	tmpDatePublic = listDatePublications.head;
	compare = &compareEntryByAuthor;
	while(tmpDatePublic != NULL)
	{
		quicksort(((DatePublications*)(tmpDatePublic->value))->publicationsList, 0, (((DatePublications*)(tmpDatePublic->value))->publicationsList).count-1, compare);
		tmpDatePublic = tmpDatePublic->next;
	}
	
	freeSimpleList(dateList);
	return listDatePublications;
}


/*
* exportAuthorListToHtml : export a list of author
* 
* authorList : a list of author
* filePtr : a file's pointer
* 
* return nothing
*/
void exportAuthorListToHtml(AbstractList *authorList, FILE* filePtr)
{
	AbstractElement* tmpElem;
	if(authorList != NULL)
	{
		tmpElem = authorList->head;	
		while(tmpElem != NULL)
		{
			fprintf(filePtr, "%s %s", ((Author*) tmpElem->value)->firstName, ((Author*) tmpElem->value)->lastName);
			if(tmpElem->next != NULL)
			{
				if(tmpElem->next->next == NULL)
					fprintf(filePtr, " and ");
				else
					fprintf(filePtr, ", ");
			}		
			tmpElem = tmpElem->next;
		}
		fprintf(filePtr, ".<br>\n");
	}
}

/*
* exportEntryToHtml : export an entry
* 
* entry : a given entry
* fileName : the name of the file that will be created by the export
* 
* return nothing
*/
void exportEntryToHtml(Entry* entry, FILE* filePtr)
{
	AbstractList* listAuthor = NULL;
	AbstractElement *tmpElem;
	EntryField *tmpEntryField;
	char *yearField, *titleField, *otherFields, *singleLines, *tmpFieldName;
	otherFields = (char*) malloc(sizeof(char));
	*otherFields = '\0';
	singleLines = (char*) malloc(sizeof(char));
	*singleLines = '\0';
	tmpElem = entry->requiredFieldList.head;
	while(tmpElem != NULL)
	{
		tmpEntryField = (EntryField*)(tmpElem->value);
		if(strcmp(tmpEntryField->name, "title") == 0)
		{
			titleField = (char*) tmpEntryField->value;
		}
		else if(strcmp(tmpEntryField->name, "author") == 0)
		{
			listAuthor = tmpEntryField->value;
		}
		else if(strcmp(tmpEntryField->name, "year") == 0)
		{
			yearField = (char*)tmpEntryField->value;
		}
		else if(strcmp(tmpEntryField->name, "journal") == 0)
		{
			otherFields = realloc(otherFields, sizeof(char)*(strlen(otherFields)+strlen((char*)tmpEntryField->value)+6));
			otherFields = strcat(otherFields, "In ");
			otherFields = strcat(otherFields, (char*)tmpEntryField->value);
			otherFields = strcat(otherFields, ", ");
		}
		else if(strcmp(tmpEntryField->name, "booktitle") == 0)
		{
			if(strcmp(entry->type, "Inproceedings") == 0)
			{
				otherFields = realloc(otherFields, sizeof(char)*(strlen(otherFields)+strlen((char*)tmpEntryField->value)+3+strlen("In Proc. of ")));
				otherFields = strcat(otherFields, "In Proc. of ");
			}
			else
			{
				otherFields = realloc(otherFields, sizeof(char)*(strlen(otherFields)+strlen((char*)tmpEntryField->value)+3));
			}
			otherFields = strcat(otherFields, (char*)tmpEntryField->value);
			otherFields = strcat(otherFields, ", ");
		}
		else if(strcmp(tmpEntryField->name, "doi") == 0 || strcmp(tmpEntryField->name, "isbn") == 0 || strcmp(tmpEntryField->name, "issn") == 0)
		{
			singleLines = realloc(singleLines, sizeof(char)*(strlen(singleLines)+strlen((char*)tmpEntryField->value)+11+strlen(tmpEntryField->name)));
			tmpFieldName = stringToUpper(tmpEntryField->name);
			singleLines = strcat(singleLines, tmpFieldName);
			free(tmpFieldName);
			singleLines = strcat(singleLines, " : ");
			singleLines = strcat(singleLines, (char*)tmpEntryField->value);
			singleLines = strcat(singleLines, ".<br/>\n");
		}
		else if(strcmp(tmpEntryField->name, "abstract") != 0 && strcmp(tmpEntryField->name, "pdf") != 0 && strcmp(tmpEntryField->name, "url") != 0)
		{
			otherFields = realloc(otherFields, sizeof(char)*(strlen(otherFields)+strlen((char*)tmpEntryField->value)+3));
			otherFields = strcat(otherFields, (char*)tmpEntryField->value);
			otherFields = strcat(otherFields, ", ");
		}
		if(tmpElem == entry->requiredFieldList.tail)
			tmpElem = entry->optionalFieldList.head;
		else
			tmpElem = tmpElem->next;
	}
	otherFields = realloc(otherFields, sizeof(char)*(strlen(otherFields)+7));
	otherFields = strcat(otherFields, yearField);
	strcpy(&otherFields[strlen(otherFields)], ".");
	fprintf(filePtr, "\t<p class=\"authorPublication\">\n");
	fprintf(filePtr, "%s<br />\n", titleField);
	exportAuthorListToHtml(listAuthor, filePtr);
	fprintf(filePtr, "%s<br />\n%s</p>\n\n", otherFields, singleLines);
	free(otherFields);
	free(singleLines);
}
/*
* exportAuthorsPublications : export the list of all author's publication from a library
* 
* libraryAuthorDate : the list of all author's publication
* fileName : the name of the file that will be created by the export
* 
* return nothing
*/
void exportAuthorsPublications(ListAuthorPublications libraryAuthorDate, char* fileName)
{
	AbstractElement *tmpElem, *tmpEntry;
	AuthorPublications *authPub;
	char* lastDate, *date;
	FILE* html = NULL;
	lastDate = (char*)malloc(sizeof(char)*5);
	tmpElem = libraryAuthorDate.head;
	html = fopen(fileName, "w+");
	fputs("<html>\n<head>\n\t<title>Bibtex File</title>\n<link rel=\"stylesheet\" href=\"style.css\" />\n</head>\n<body>\n\t<h1>Bibtex file</h1><h2>AuthorsPublications</h2>\n", html);
	
	while(tmpElem != NULL)
	{
		authPub = (AuthorPublications*)(tmpElem->value);
		fprintf(html, "<h3>%s %s</h3>\n", (char*)(authPub->author.firstName), (char*)(authPub->author.lastName));
		tmpEntry = authPub->publicationsList.head;
		strcpy(lastDate, "0000");

		while(tmpEntry != NULL)
		{
			date = getYearFromEntry((Entry*)(tmpEntry->value));
			if(strcmp(date, lastDate) != 0)
			{
				fprintf(html, "<h4>%s</h4>\n", date);
				strcpy(lastDate, date);
			}
			free(date);
			exportEntryToHtml((Entry*)(tmpEntry->value), html);
			
			tmpEntry = tmpEntry->next;
		}
		tmpElem = tmpElem->next;
		if(tmpElem != NULL)
			free(tmpElem->prev);
	}
	fprintf(html, "\n</body></html>");
	fclose(html);
	free(lastDate);
}

/*
* exportDatePublications : export the list of all date's publication from a library
* 
* libraryDateAuthor : the list of all date's publication
* fileName : the name of the file that will be created by the export
* 
* return nothing
*/
void exportDatePublications(ListDatePublications libraryDateAuthor, char* fileName)
{
	AbstractElement *tmpElem, *tmpEntry;
	DatePublications *datePub;
	FILE* html = NULL;

	tmpElem = libraryDateAuthor.head;
	html = fopen(fileName, "w+");
	fputs("<html>\n<head>\n\t<title>Bibtex File</title>\n<link rel=\"stylesheet\" href=\"style.css\" />\n</head>\n<body>\n\t<h1>Bibtex file</h1><h2>DatePublications</h2>\n", html);
	
	while(tmpElem != NULL)
	{
		datePub = (DatePublications*)(tmpElem->value);
		fprintf(html, "<h3>%s</h3>\n", (char*)(datePub->year));
		tmpEntry = datePub->publicationsList.head;
		while(tmpEntry != NULL)
		{
			exportEntryToHtml((Entry*)(tmpEntry->value), html);
			tmpEntry = tmpEntry->next;
		}
		tmpElem = tmpElem->next;
	}
	fprintf(html, "\n</body></html>");
	fclose(html);
}

/*
* exportDatePublications : export a library
* 
* library : the library we want to export
* fileName : the name of the file that will be created by the export
* 
* return nothing
*/
void exportToHTML(AbstractList library, char* fileName)
{
	AbstractElement* tmpElemEntry = NULL;
	FILE* html = NULL;
	
	tmpElemEntry = library.head;
	
	html = fopen(fileName, "w+");
	fputs("<html>\n<head>\n\t<title>Bibtex File</title>\n<link rel=\"stylesheet\" href=\"style.css\" />\n</head>\n<body>\n\t<h1>Bibtex file</h1>\n", html);
	while(tmpElemEntry != NULL)
	{
		fprintf(html, "<h3>%s</h3>\n", ((Entry*)(tmpElemEntry->value))->key);
		exportEntryToHtml(tmpElemEntry->value, html);
		tmpElemEntry = tmpElemEntry->next;
	}
	fprintf(html, "\n</body></html>");
	fclose(html);
}


/*
* freeAuthorList : free a list of authors
* 
* authorList : the list of authors we want to free
* 
* return nothing
*/
void freeAuthorList(AbstractList *authorList)
{
	AbstractElement *tmpElem;
	tmpElem = authorList->head;
	while(tmpElem != NULL)
	{
		free(tmpElem->prev);
		tmpElem->prev = NULL;
			free(((Author*)(tmpElem->value))->firstName);
			free(((Author*)(tmpElem->value))->lastName);
		tmpElem->value = NULL;
		tmpElem=tmpElem->next;
	}
	free(authorList->tail);
	authorList->tail = NULL;
}
/*
* freeEntry : free a entry
* 
* entry : the entry we want to free
* 
* return nothing
*/
void freeEntry(Entry *entry)
{
	AbstractElement *tmpElem;
	free(entry->key);
	entry->key = NULL;
	free(entry->type);
	tmpElem = entry->requiredFieldList.head;
	free(((EntryField*)(tmpElem->value))->name);
	free(((EntryField*)(tmpElem->value))->value);
	((EntryField*)(tmpElem->value))->name = NULL;
	((EntryField*)(tmpElem->value))->value = NULL;
	free(tmpElem->value);
	tmpElem = tmpElem->next;
	while(tmpElem != NULL)
	{
		free(tmpElem->prev);
		tmpElem->prev = NULL;
		if(strcmp((char*)(((EntryField*)(tmpElem->value))->name), "author") == 0)
		{
			freeAuthorList((AbstractList*)((EntryField*)(tmpElem->value))->value);
		}
		free(((EntryField*)(tmpElem->value))->name);
		free(((EntryField*)(tmpElem->value))->value);
		((EntryField*)(tmpElem->value))->name = NULL;
		((EntryField*)(tmpElem->value))->value = NULL;
		free(tmpElem->value);
		tmpElem = tmpElem->next;
	}
	free(entry->requiredFieldList.tail);
	entry->requiredFieldList.tail = NULL;
	tmpElem = entry->optionalFieldList.head;
	free(((EntryField*)(tmpElem->value))->name);
	free(((EntryField*)(tmpElem->value))->value);
	((EntryField*)(tmpElem->value))->name = NULL;
	((EntryField*)(tmpElem->value))->value = NULL;
	free(tmpElem->value);
	tmpElem = tmpElem->next;
	while(tmpElem != NULL)
	{
		free(tmpElem->prev);
		tmpElem->prev = NULL;
		if(strcmp((char*)(((EntryField*)(tmpElem->value))->name), "author") == 0)
		{
			freeAuthorList((AbstractList*)((EntryField*)(tmpElem->value))->value);
		}
		free(((EntryField*)(tmpElem->value))->name);
		free(((EntryField*)(tmpElem->value))->value);
		((EntryField*)(tmpElem->value))->name = NULL;
		((EntryField*)(tmpElem->value))->value = NULL;
		free(tmpElem->value);
		tmpElem = tmpElem->next;
	}
	free(entry->optionalFieldList.tail);
	entry->optionalFieldList.tail = NULL;
	free(entry);
	entry = NULL;
}
/*
* removeEntry : remove a entry in the library
* 
* library : the library in which we remove the entry
* keyToBeRemoved : the key of the entry we want to free
* 
* return nothing
*/
AbstractList removeEntry(AbstractList library, char* keyToBeRemoved)
{
	AbstractElement *tmpEntry;

	tmpEntry = library.head;
	while(tmpEntry != NULL && strcmp(((Entry*)(tmpEntry->value))->key, keyToBeRemoved) != 0)
	{
		tmpEntry=tmpEntry->next;
	}
	if(tmpEntry != NULL)
	{
		if(tmpEntry->prev != NULL)
			tmpEntry->prev->next = tmpEntry->next;
		if(tmpEntry->next != NULL)
			tmpEntry->next->prev = tmpEntry->prev;
		freeEntry(((Entry*)(tmpEntry->value)));
	}
	return library;
}
/*
* freeLibrary : free a entry
* 
* library : the library we want to free
* freeValue : a boolean which indicate if we need to free the value of the entries 
* 
* return nothing
*/
void freeLibrary(AbstractList library, BOOL freeValue)
{
	AbstractElement *tmpEntry;
	tmpEntry = library.head;
	library.head = NULL;
	while(tmpEntry != NULL)
	{
		free(tmpEntry->prev);
		tmpEntry->prev = NULL;
		if(freeValue)
			freeEntry((Entry*)(tmpEntry->value));
		tmpEntry->value = NULL;
		tmpEntry=tmpEntry->next;
	}
	free(library.tail);
	library.tail = NULL;
}

/*
* freeAuthorsPublications : free the list of all AuthorsPublications
* 
* libraryDateAuthor : the list of all author's publication
* 
* return nothing
*/
void freeAuthorsPublications(ListAuthorPublications libraryAuthorDate)
{
	AbstractElement *tmpElem;
	AuthorPublications *authPub;
	if(!isEmpty(libraryAuthorDate))
	{
		tmpElem = libraryAuthorDate.head;
		
		while(tmpElem != NULL)
		{
			authPub = (AuthorPublications*)(tmpElem->value);
			free(authPub->author.firstName);
			free(authPub->author.lastName);
			freeLibrary(authPub->publicationsList, 0);
			tmpElem = tmpElem->next;
			if(tmpElem != NULL)
				free(tmpElem->prev);
		}
		free(libraryAuthorDate.tail);
	}
}
/*
* freeDatePublications : free the list of all DatePublications
* 
* libraryDateAuthor : the list of all date's publication
* 
* return nothing
*/
void freeDatePublications(ListDatePublications libraryDateAuthor)
{
	AbstractElement *tmpElem;
	DatePublications *datePub;
	if(!isEmpty(libraryDateAuthor))
	{
		tmpElem = libraryDateAuthor.head;
		
		while(tmpElem != NULL)
		{
			datePub = (DatePublications*)(tmpElem->value);
			free(datePub->year);
			freeLibrary(datePub->publicationsList, 0);
			free(datePub);
			tmpElem = tmpElem->next;
			if(tmpElem != NULL)
				free(tmpElem->prev);
		}
		free(libraryDateAuthor.tail);	
	}
}



/*
* freeSimpleList : free a list
* 
* list : the list we want to free
* 
* return nothing
*/
void freeSimpleList(AbstractList list)
{
	AbstractElement *tmpElem;
	tmpElem = list.head;
	list.head = NULL;
	while(tmpElem != NULL)
	{
		free(tmpElem->prev);
		tmpElem->prev = NULL;
		free(tmpElem->value);
		tmpElem->value = NULL;
		tmpElem=tmpElem->next;
	}
	free(list.tail);
	list.tail = NULL;
}
/*
* deleteList : delete a list
* 
* list : the list we want to delete
* 
* return nothing
*/
void deleteList(AbstractList list)
{
	AbstractElement *tmpElem;
	tmpElem = list.head;
	list.head = NULL;
	while(tmpElem != NULL)
	{
		free(tmpElem->prev);
		tmpElem->prev = NULL;
		free(tmpElem->value);
		tmpElem->value = NULL;
		tmpElem=tmpElem->next;
	}
	free(list.tail);
	list.tail = NULL;
}

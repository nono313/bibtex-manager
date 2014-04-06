/* 
Bibtex Project - types.c
Maxime B. & Nathan O. (TC03)
maxime.bourgeois@utbm.fr nathan.olff@utbm.fr

types.h : cointains the code of our basic fonctions.
*/

#include <types.h>

int testRegex(char* line, char* regexString, char*** regexArray, int sizeMax)
{
  /*char * regexString = "[\t ]+([a-z]+) = \\{(.+)\n\0";*/

	int nMatch;
/*	regexArray = (char***) malloc(sizeof(char**));*/
	unsigned int m;
	char *cursor, *cursorCopy;
	size_t maxMatches;
	size_t maxGroups;
	regex_t regexCompiled;
	regmatch_t groupArray[3];	/*maxGroups*/
	unsigned int g;
	unsigned int offset;
	if((*regexArray)[0] != NULL)
	{
		free((*regexArray)[0]);
		free((*regexArray)[1]);
	}
	maxMatches = 2;
	maxGroups = 3;
	nMatch = 0;

	if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
	{
		printf("Could not compile regular expression.\n");
		return 0;
	}
	m = 0;
	cursor = line;
	for (m = 0; m < maxMatches; m ++)
	{
		if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
			break;  /* No more matches*/
			
		g = 0;
		offset = 0;
		for (g = 0; g < maxGroups; g++)
		{
			if (groupArray[g].rm_so == (size_t)-1)
				break;  /* No more groups*/

			if (g == 0)
				offset = groupArray[g].rm_eo;

			cursorCopy = (char*) malloc(sizeof(char*)*(strlen(cursor) + 1));
			strcpy(cursorCopy, cursor);
			cursorCopy[groupArray[g].rm_eo] = 0;
			if(g > 0)
			{
				(*regexArray)[g-1] = (char*) malloc(sizeof(char)*(sizeMax+1));
				nMatch = nMatch+1;
				strcpy((*regexArray)[g-1], cursorCopy + groupArray[g].rm_so);
			}
			free(cursorCopy);
		}
		cursor += offset;
	}
	regfree(&regexCompiled);
	return nMatch;
}
/*
* isContained : replace all the special characters in a string
* 
* value : a string we want to search in the variable string
* string : the given string in which we want to search value
* 
* return a boolean : TRUE if value is contained in string, FALSE if not
*/
BOOL isContained(char* value, char* string)
{
	char* pattern = NULL;
	char* cursor;
	BOOL contained = FALSE;
	size_t maxGroups;
	regex_t regexCompiled;
	regmatch_t groupArray[3];	/*maxGroups*/
	
	pattern = (char*) malloc(sizeof(char)*(strlen(value)*3+25));
	strcpy(pattern, "^(");
	strcat(pattern, value);
	strcat(pattern, ")$|^(.+)(/");
	strcat(pattern, value);
	strcat(pattern,	")$|^(");
	strcat(pattern, value);
	strcat(pattern, "/)(.+)$");
	/*puts(pattern);*/
/*	regexArray = (char***) malloc(sizeof(char**));*/

  maxGroups = 3;
  if (regcomp(&regexCompiled, pattern, REG_EXTENDED))
    {
      printf("Could not compile regular expression.\n");
      return 0;
    };

	
    cursor = string;

  
      if (!regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
        contained = TRUE;
    
	free(pattern);
	regfree(&regexCompiled);
	return contained;
}

/*
* isEmpty : indicates if the list is empty or not
* 
* list : a generic list
* 
* return a boolean : TRUE if the list is empty, FALSE if the list isnt
*/
BOOL isEmpty(AbstractList list)
{
	if(list.head == NULL)
		return TRUE;
	else
		return FALSE;
}
/*
* replaceSpecialChars : replace all the special characters in a string
* 
* string : the given string in which we want to replace special characters
* 
* return the string special characters replaced
*/
char* replaceSpecialChars(char* string)
{
	char *beforeFound, *afterFound, *cFound, *newString, *cursorString;
	char replace[][2][10] = {{"{\\\'e}", "é"}, {"{\\`e}", "è"}, {"{\\c{c}}", "ç"}, {"{\"}", "\""} , {"{\\cc}", "ç"}, {"{\\^e}", "ê"}, {"{\\\"e}", "ë"}, {"{\\\'a}", "á"},{"{\\\'{\\i}}", "í"}, {"\\^{i}", "î"}, {"{\\\"{\\i}}", "ï"}, {"\\~{n}", "ñ"},  {"{\\‘o}", "ò"}, {"{\\^o}", "ô"}, {"{\\\'o}", "ó"}, {"{\\\"o}", "ö"} };
	int sizeOfOldString, sizeOfNewString = 0, i;
	newString = (char*)malloc(sizeof(char)*(strlen(string)+1));
	strcpy(newString, string);
	beforeFound = strchr(newString, '{');
	/*beforeFound = newString;*/
	cursorString = beforeFound;
	while(beforeFound != NULL)
	{
		i = -1;
		cFound = NULL;
		while(i < 15 && cFound == NULL)
		{
			i++;
			cFound = strstr(beforeFound, replace[i][0]);
		}
		if(cFound != NULL)
		{
			sizeOfOldString = (int)strlen(replace[i][0]);
			sizeOfNewString = (int)strlen(replace[i][1]);
			afterFound = cFound + sizeOfOldString;
			strncpy(cFound, replace[i][1], sizeOfNewString);
			i = 0;
			cFound = cFound+sizeOfNewString;
			while(afterFound[i] != '\0')
			{
				cFound[i] = afterFound[i];
				i++;
			}
			cFound[i] = '\0';
		/*printf("\t%s : %d / %d\n", replace[i][0], sizeOfOldString, sizeOfNewString);*/
		}
		else
		{
			cursorString = strchr(cursorString, '}');
		}
		beforeFound = strchr(cursorString, '{');
		/*beforeFound++;*/
		
	}
	return newString;
}


/*
* initEntry : initialize an entry
* 
* typeEntry : the entry's type
* key : the entry's key
* 
* return an Entry initialized
*/
Entry* initEntry(char* typeEntry, char* key)
{
	/* Declarations */	
	Entry* entry = NULL;

	/* Mallocs */
	entry = (Entry*) malloc(sizeof(Entry));
	entry->key = (char*) malloc(sizeof(char)*100);
	entry->type = (char*) malloc(sizeof(char)*20);
	
	/* Initialisations */
	strcpy(entry->key, key);
	entry->requiredFieldList = initList(sizeof(EntryField));
	entry->optionalFieldList = initList(sizeof(EntryField));
	
	/* Filling of the Entry */
	strcpy(entry->type, typeEntry);	
	return entry;
}
/*
* initList : initialize a list (which is returned) setting his head/tail equal to NULL, his count equal to 0 and his size equal to the given size (function's argument)
* 
* size : since the list is a abstract list (including void*) we must have a list.size which contains the size of the list's element,
         for Example : if it's a list of entryField then we'll have size=sizeof(entryField), if it's a list of publications for then we'll have size=sizeof(Entry)
* 
* return an AbstractList initialized
*/
AbstractList initList(int size)
{
	AbstractList l;
	
	l.head = NULL;
	l.tail = NULL;
	l.count = 0;
	l.size = size;
	
	return l;
}



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
AbstractList insertHead(AbstractList list, void* element, BOOL allocMemory)
{
	AbstractElement* newEl;
	newEl = (AbstractElement*) malloc(sizeof(AbstractElement));
	
	if(allocMemory == TRUE)
	{
		newEl->value = (void*) malloc(list.size);
		memcpy(newEl->value, element, list.size);
	}
	else		newEl->value = element;
	
	newEl->prev = NULL;
	list.count++;
	
	if(isEmpty(list))
	{
		newEl->next = NULL;
		list.head = newEl;
		list.tail = newEl;
	}
	else
	{
		list.head->prev = newEl;
		newEl->next = list.head;
		list.head = newEl;
	}
	
	return list;
}
/*
* removeHead : remove the first element of the list
* 
* list : the list in which we have to remove the first element
* 
* return the list without the first element
*/
AbstractList removeHead(AbstractList list)
{
	if(!isEmpty(list))	/* If the list is empty, do nothing and return the list */
	{
		if(list.head->next == NULL)	/* The list has only one element */
		{
			free(list.head);
			list.head = NULL;
			list.tail = NULL;
		}
		else
		{
			list.head = list.head->next;
			free(list.head->prev);
			list.head->prev = NULL;
		}
	}
	
	return list;
}
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
AbstractList insertTail(AbstractList list, void* element, BOOL allocMemory)
{
	
	AbstractElement* newEl;
	if(element != NULL)
	{
		newEl = (AbstractElement*) malloc(sizeof(AbstractElement));
		
		if(allocMemory == TRUE)
		{
			newEl->value = (void*) malloc(list.size);
			memcpy(newEl->value, element, list.size);
			
		}
		else		
			newEl->value = element;
		
		newEl->next = NULL;
		list.count++;
		
		if(isEmpty(list))
		{
			newEl->prev = NULL;
			list.head = newEl;
			list.tail = newEl;
		}
		else
		{
			list.tail->next = newEl;
			newEl->prev = list.tail;
			list.tail = newEl;
		}
	}
	return list;
}
/*
* removeTail : remove the first element of the list
* 
* list : the list in which we have to remove the first element
* 
* return the list without the last element
*/
AbstractList removeTail(AbstractList list)
{
	if(!isEmpty(list))	/* If the list is empty, do nothing and return the list */
	{
		if(list.tail->prev == NULL)	/* If the list has only one element */
		{
			free(list.tail);
			list.tail = NULL;
			list.head = NULL;
		}
		else
		{
			list.tail = list.tail->prev;
			free(list.tail->next);
			list.tail->next = NULL;
		}
	}
	
	return list;
}

/*
 * clean_stdin : clean the keyboard buffer
 */
void clean_stdin(void)
{
    int c;
    
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
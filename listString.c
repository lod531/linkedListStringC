#include <stdio.h>
#include <stdlib.h>

struct charNode
{
	char data;
	struct charNode * next;
};

struct charNode * mystring_new()
{
	struct charNode * result = malloc(sizeof(struct charNode));
	return result;
}

struct charNode * mystring_new_from_array(char * array)
{
	if(array[0] == '\0')
	{
		return mystring_new();
	}
	else
	{
		struct charNode * result = malloc(sizeof(struct charNode));
		struct charNode * currentNode = result;
		int i;
		for(i = 0; array[i+1] != '\0'; i++)
		{
			currentNode->data = array[i];
			currentNode->next = malloc(sizeof(struct charNode));
			currentNode = currentNode->next;
		}
		currentNode->data = array[i];
		currentNode->next = NULL;
		return result;
	}
}

int mystring_compare(struct charNode * zero, struct charNode * one)
{
	while(zero != NULL && one != NULL && zero->data == one->data)
	{
		zero = zero->next;
		one = one->next;
	}
	if(zero == NULL && one == NULL)
	{
		return 0;
	}
	else if( ((zero != NULL) && (one != NULL) && (zero->data < one->data)) ||
				 zero == NULL )
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

void mystring_print(struct charNode * this)
{
	while(this != NULL)
	{
		printf("%c", this->data);
		this = this->next;
	}
	printf("\n");
}

//replaces string contained within start and end, inclusive of start, exclusive of end
void mystring_replace_helper(struct charNode * start, struct charNode * end, struct charNode * newText)
{
	struct charNode * temp = start->next;
	struct charNode * tempTemp;
	while(temp != end)
	{
		tempTemp = temp->next;
		free(temp);
		temp = tempTemp;
	}

	while(newText != NULL)
	{
		start->data = newText->data;
		start->next = malloc(sizeof(struct charNode));
		temp = start;
		start = start->next;
		newText = newText->next;
	}
	free(temp->next);
	temp->next = end;
}

struct charNode * mystring_replace(struct charNode * text, struct charNode * search, struct charNode * replacement)
{
	//this could be optimized A LOT.
	while(text != NULL)
	{
		if(text->data == search->data)
		{
			struct charNode * tempText = text;
			struct charNode * tempSearch = search;
			while(tempText != NULL && tempSearch != NULL && tempText->data == tempSearch->data)
			{
				tempText = tempText->next;
				tempSearch = tempSearch->next;
			}
			if(tempSearch == NULL)
			{
				mystring_replace_helper(text, tempText, replacement);
			}
			tempSearch = replacement;
			while(tempSearch != NULL)
			{
				text = text->next;
				tempSearch = tempSearch->next;
			}
		}
		text = text->next;
	}
}


int main()
{
	char * testArray = "I cosmos therefore cosm I am";
	struct charNode * test = mystring_new_from_array(testArray);
	char * testArrayOne = "cosmos";
	struct charNode * testOne = mystring_new_from_array(testArrayOne);
	char * testArrayTwo = "think";
	struct charNode * testTwo = mystring_new_from_array(testArrayTwo);
	mystring_replace(test, testOne, testTwo);
	mystring_print(test);
	
	return 0;
}
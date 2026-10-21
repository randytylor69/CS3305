#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_WORD_LENGTH 100
#define ARR_LENGTH 10

typedef struct Dict{
    char name[MAX_WORD_LENGTH];
    int count;
} Dict;

void processList(char arr[ARR_LENGTH][MAX_WORD_LENGTH]){
    Dict list[ARR_LENGTH]; // a list that holds tuple {name, count}
    int listIndex = 0;

    for (size_t i = 0; i < ARR_LENGTH; i++){

	if (arr[i][0] == '\0') continue; // skip empty
				       //
	int isExists = 0;
	/* check if word exists in list */
	for (size_t j = 0; j < listIndex; j++){
	    if (strcmp(list[j].name, arr[i])==0) {
		isExists = 1;
		list[j].count++;
		break;
	    }
	}

	if (isExists == 0) {
	    Dict d = {"NULL", 1};
	    strcpy(d.name, arr[i]);
	    list[listIndex] = d;
	    listIndex++;
	} else continue;

    }

    /* print the list */
    for (size_t i = 0; i < listIndex; i++){
	printf("%s: %d\n", list[i].name, list[i].count);
    }
}

int main(){
    /* lists of words */
    char arr0[ARR_LENGTH][MAX_WORD_LENGTH] = {"apple", "apple", "orange", "banana", "banana", "banana"};
    char arr1[ARR_LENGTH][MAX_WORD_LENGTH] = {"apple", "grape", "grape"};
    char arr2[ARR_LENGTH][MAX_WORD_LENGTH] = {"orange", "banana", "banana", "orange"};

    /* create an array to contain all child processes */
    pid_t pids[3]; // p0, p1, p2
    
    for (size_t i=0; i < 3; i++){

	pids[i] = fork();
	if (pids[i] < 0) {
	    /* error */
	    printf("FORK FAILED!\n");
	    return 1;
	} else if (pids[i]==0) {
	    /* child process code */
	    int childCount = i + 1;

	    printf("Child %d (PID %d):\n", childCount, getpid());
	    
	    switch (childCount) {
		case 1 : processList(arr0); break;
		case 2 : processList(arr1); break;
		case 3 : processList(arr2); break;
	    }
	    printf("\n"); // line break between children

	    return 0;
	    
	}
    }

    for (size_t i=0; i<3; i++){
	waitpid(pids[i], NULL, 0);
    }

    return 0;
}

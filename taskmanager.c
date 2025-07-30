#define FILENAME "tasks.dat"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

    int id ;
    char title[100];
    char description[1000];
    char deadline[20]; // DD-MM-YYYY format 
    int priority ; // Priority of each task 
    int check ; // Task completed or not
}Task ; 

Task List[100] ; 
int count = 0; // To keep track of number of tasks

void AddTask(){

    Task newtask;
    newtask.id = count + 1; 

    printf("\nEnter the task title  ");
    while ((getchar()) != '\n');
    fgets(newtask.title , 100 , stdin); // we set limit to 100 because thats maximum characters in the title variable

    printf("Enter Task Description  ");
    fgets(newtask.description , 1000 , stdin);

    printf("Enter Task Deadline (DD-MM-YYYY)  ");
    fgets(newtask.deadline , 20 , stdin);

    printf("Enter Task Priority (1 = High , 2 = Medium , 3 = Low)  ");
    scanf("%d" , &newtask.priority);

    newtask.check = 0;  // task is not completed obviously

    List[count] = newtask; 
    count++ ;

    printf("Task Added Succesfully \n");

    Save();

}

void Save(){

    FILE *fp = fopen("tasks.dat" , "wb");

    if(fp == NULL){

        printf("Error opening file for writing\n");
        return ;

    }

    fwrite(&count , sizeof(int) , 1 ,fp); // Save count
    fwrite(List , sizeof(Task) , count , fp); // Save count list    
    fclose(fp);

}

void Load(){

    FILE *fp = fopen("tasks.dat" , "rb");

    if(fp == NULL){

        // FIle doesnt exist yet
        return ;

    }

    fread(&count , sizeof(int) , 1 , fp); //Load count
    fread(List , sizeof(Task) , count , fp); // Load Task list
    fclose(fp);

}

void ViewTask(){

    if(count == 0){

        printf("There is no task to display");
        return;
    }
    
    printf("---------------Task List---------------\n");
    for(int i = 0 ; i < count ; i++){

        printf("Task ID : %d \n" , List[i].id );
        printf("Task Title : %s \n", List[i].title );
        printf("Task Description : %s \n" , List[i].description);
        printf("Task Deadline : %s \n" , List[i].deadline);
        printf("Task Priority : %d \n" , List[i].priority);
        printf("Task Status : %s\n\n" , List[i].check? "Completed" : "Pending");

    }

}

void DeleteTask(){

    int del , found = 0 ;

    printf("Enter the Task ID to be deleted");
    scanf("%d" , &del);

    for(int i = 0 ; i < count ; i++){

        if(List[i].id == del){

            found = 1;

            for(int j = i ; j < count-1 ; j++){

                List[j] = List[j+1];

            }

            count-- ;
            printf("Task %d deleted succesfully\n" , del);
            return ;

        }

    }

    if(!found)
    printf("Task ID %d not found \n" , del);

}

void EditTask(){

    int edit , found = 0 ;

    printf("Enter the Task ID to be editted");
    scanf("%d" , &edit);

    for(int i = 0 ; i < count ; i++){

        if(List[i].id == edit){

            found = 1 ;
            getchar();
            
            char choice; 

            printf("Current title : %s" , List[i].title);
            printf("Edit Title? (y/n)");
            scanf("%c" , &choice);
            getchar();

            if(choice == 'y' || choice == 'Y'){

                printf("Enter new title : ");
                fgets(List[i].title , 100 , stdin);

            }

            printf("Current description : %s" , List[i].description);
            printf("Edit Description? (y/n)");
            scanf("%c" , &choice);
            getchar();

            if(choice == 'y' || choice == 'Y'){

                printf("Enter new description : ");
                fgets(List[i].description , 1000 , stdin);

            }

            printf("Current deadline : %s" , List[i].deadline);
            printf("Edit Deadline? (y/n)");
            scanf("%c" , &choice);
            getchar();

            if(choice == 'y' || choice == 'Y'){

                printf("Enter new deadline : ");
                fgets(List[i].deadline , 20 , stdin);

            }

            printf("Current Priority : %d" , List[i].priority);
            printf("Edit Priority? (y/n)");
            scanf("%c" , &choice);
            getchar();

            if(choice == 'y' || choice == 'Y'){

                printf("Enter new priority (1 = High, 2 = Medium, 3 = Low) : ");
                scanf("%d" , &List[i].priority);

            }

            printf("Task updated successfully!\n");
            return;
        }
    }

    if(!found)
    printf("Task ID %d not found" , edit);

}

void SortByPriority(){

    for(int i = 0 ; i < count -1 ; i++){
        for(int j = i ; j < count -1 ; j++){

            if(List[j].priority > List[j+1].priority){ // if the number is smaller it has higher priority according to our code

                Task temp = List[j]; // thats why , if the priority of next task is lesser , we will swap it
                List[j] = List[j+1];
                List[j+1] = temp;

            }
        }
    }

    printf("Tasks sorted by priority (High to Low)\n");

}

void Search(){

    int choice ;
    char s_title[100];
    char s_deadline[20];
    int s_status ;
    int found = 0 ;

    printf("------Search Menu------\n\n");
    printf("Enter 1 to search by Title\n");
    printf("Enter 2 to search by Deadline\n");
    printf("Enter 3 to search by Status (0 for Pending 1 for Completed)\n");

    printf("Enter your choice");
    scanf("%d" , &choice);
    getchar();

    switch(choice){

        case 1 : printf("Enter the title"); 
                 fgets(s_title , 100 , stdin);

                 for(int i = 0 ; i < count ; i++){

                    if(strstr(List[i].title , s_title)){

                        printf("\n Task ID : %d" , List[i].id);
                        printf("\n Title : %s " , List[i].title);
                        printf(" \n Description : %s " , List[i].description);
                        printf("\n Deadline : %s " , List[i].deadline);
                        printf("\n Priority : %d " , List[i].priority);
                        printf("\n Status : %s " , List[i].check?"Completed":"Pending");
                        found = 1;

                    }

                 }

                 break;

        case 2 : printf("Enter the deadline");
                 fgets(s_deadline , 20 , stdin);

                 for(int i = 0 ; i < count ; i++){

                    if(strstr(List[i].deadline , s_deadline)){

                        printf("\n Task ID : %d" , List[i].id);
                        printf("\n Title : %s " , List[i].title);
                        printf(" \n Description : %s " , List[i].description);
                        printf("\n Deadline : %s " , List[i].deadline);
                        printf("\n Priority : %d " , List[i].priority);
                        printf("\n Status : %s " , List[i].check?"Completed":"Pending");
                        found = 1;

                    }

                 }

                 break;

        case 3 : printf("Enter the status (0 for Pending 1 for Completed)");
                 scanf("%d" , &s_status);

                 for(int i = 0 ; i < count ; i++){

                    if(List[i].check == s_status){

                        printf("\n Task ID : %d" , List[i].id);
                        printf("\n Title : %s " , List[i].title);
                        printf(" \n Description : %s " , List[i].description);
                        printf("\n Deadline : %s " , List[i].deadline);
                        printf("\n Priority : %d " , List[i].priority);
                        printf("\n Status : %s " , List[i].check?"Completed":"Pending");
                        found = 1;

                    }

                 }

                 break;

            default : printf("Invalid Choice !! \n");

    }

    if(!found){

        printf("No matching tasks found !");
    }
}

void StatusUpdate(){

    int status , update;

    printf("Enter the task ID of the task whose status you want to update. ");
    scanf("%d" , &update);

    printf("Enter 1 if the task is completed , 0 if the task is pending");
    scanf("%d" , &status);

    int found = 0;

    for (int i = 0; i < count; i++) {

        if (List[i].id == update) {
            List[i].check = status;
            found = 1;
            printf("Status updated successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("No task with given ID found.\n");
    }

    Save();
}

void Menu(){

    int choice;

    do{

        printf("------Task Manager------\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Change status of task\n");
        printf("4. Delete Task \n");
        printf("5. Edit Task\n");
        printf("6. Sort Tasks by Priority \n");
        printf("7. Search Tasks\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){

            case 1: AddTask();
                    break;
                   
            case 2 : ViewTask();
                     break;

            case 3 : StatusUpdate();
                     break;
                     
            case 4 : DeleteTask();
                     break;

            case 5 : EditTask();
                     break;

            case 6 : SortByPriority();
                     break;

            case 7 : Search();
                     break;

            case 8 : printf("Exitting.... Goodbye!");
                     break;
                     
            default : printf("Invalid choice ! Try again") ;
            
        }

    }while(choice != 8);

}

int main(){

    Load();
    Menu();

    return 0;
}
#include <stdio.h>
#include <string.h>

typedef struct Expense
{
    int id;
    char name[75];
    int cost;
    char category[50];
}exp;

exp addexpense(int);

exp addexpense(int count)
{

    exp e1;

    printf("write the details for item no.%d\n", count + 1);

    e1.id = count + 1;
    printf("\n");
    while (getchar() != '\n');
    printf("Enter your expense name: ");
    fgets(e1.name, sizeof(e1.name), stdin);
    e1.name[strcspn(e1.name, "\n")] = '\0';
    printf("\n");
    printf("Enter your expense cost: ");
    scanf("%d", &e1.cost);
    printf("\n");
    while (getchar() != '\n');
    printf("Enter your expense category: ");
    fgets(e1.category, sizeof(e1.category), stdin);
    e1.category[strcspn(e1.category, "\n")] = '\0';
    printf("\n");

    return e1;
}
void viewexpense(exp *, int);

void viewexpense(exp *e, int count)
{
    printf("Item no.%d and its related info is displayed below\n", count + 1);
    printf("Expense id: %d\n", e->id);
    printf("Expense name: %s\n", e->name);
    printf("Expense cost: %d\n", e->cost);
    printf("Expense category: %s\n", e->category);
    printf("\n");
}

void totalcost(exp e[], int count)
{
    int sum_cost = 0;
    for (int i = 0; i < count; i++)
    {
        sum_cost += e[i].cost;
    }
    printf("The total cost is: %d\n", sum_cost);
}

int searchid_found(int, exp *, int);

int searchid_found(int count, exp *e, int s_id)
{
    for (int i = 0; i < count; i++)
    {
        if (e[i].id == s_id)
        {
            return i;
        }
    }
    return -1;
}

int searchname_found(int, exp *);

int searchname_found(int count, exp *e)
{
    char s_name[75];
    printf("Enter name: ");

    fgets(s_name, sizeof(s_name), stdin);
    s_name[strcspn(s_name, "\n")] = '\0';
    printf("\n");

    for (int a = 0; a < count; a++)
    {
        if (strcmp(e[a].name, s_name) == 0)
        {
            return a;
        }
    }

    return -1;
}

int find_cat(char *s_cat, int unique, char (*arr)[50]);

int find_cat(char *s_cat, int unique, char (*arr)[50])
{
    for (int c = 0; c < unique; c++)
    {
        int cat_found = 0;
        if (strcmp(s_cat, arr[c]) == 0)
        {
            cat_found = 1;
            return cat_found;
        }
    }
    return -1;
}

void delete_exp(int, exp *, int);

void delete_exp(int count, exp *e, int found_name){
    for(int a = found_name; a < (count - 1); a++){
        e[a] = e[a + 1];
    }
   
}

void fixid(int *e){
    *e -= 1;
    
}

void edit_name(char *e, char *new_name){
    
    
    strcpy(e, new_name);
}

void edit_cat(char *e, char *x ){
   strcpy(e, x);
}

void edit_cost(int *cost, int new_cost){
    
    *cost = new_cost;
}

int main(void)
{
    FILE *fptr;
    FILE *fptr_load = fopen("storage.dat", "rb");

    exp e[100];

    int count;
    if(fptr_load != NULL){
        count = fread(e, sizeof(exp), 100, fptr_load);
        fclose(fptr_load);
    }
    else{
        printf("No data loaded as the file doesn't exist.\n");
    }
    if(count != 0){
        printf("Data loaded successfully\n");
    }
    else{
        count = 0;
    }
    

    int choice;

    int choose_id;

    int count_proof;

    int edit_on;



    do
    {

        printf("Choose an option from the following\n");
        printf("1. add an expense.\n");
        printf("2. View an expense.\n");
        printf("3. View all your expenses.\n");
        printf("4. Calculate total cost.\n");
        printf("5. Search an expense.\n");
        printf("6. Edit an expense.\n");
        printf("7. Delete an expense.\n");
        printf("8. Summarize all expenses.\n");
        printf("9. Save and exit.\n");
        printf("Enter your choice by entering the number: ");
        scanf("%d", &choice);
        printf("\n");

        while (choice < 1 || choice > 9)
        {
            printf("Choose a correct option: ");
            scanf("%d", &choice);
            printf("\n");
        }

        char cat_arr[75][50];
        int uniqueid = 0;

        switch (choice)
        {

        case (1):
            if (count >= 100)
            {
                printf("You have already reached your sheet limit...\n");
                break;
            }
            e[count] = addexpense(count);
            count++;

            break;
        case (2):
            if (count < 1)
            {
                printf("Add an expense item first.\n");
                break;
            }
            else
            {
                printf("Choose an expense you want to view by enterng its ID\n");
                printf("Choose from the following IDs:\n");
                for (int i = 1; i <= count; i++)
                {
                    printf("ID.%d\n", i);
                }
            }
            printf("Choose an ID: ");
            scanf("%d", &choose_id);
            printf("\n");
            while (choose_id < 1 || choose_id > count)
            {
                printf("Please enter a valid ID: ");
                scanf("%d", &choose_id);
                printf("\n");
            }
            viewexpense(&e[choose_id - 1], choose_id - 1);
            printf("\n");
            break;
        case (3):
            if (count < 1)
            {
                printf("Add an expense item first.\n");
                break;
            }

            printf("Your expense are shown as follows: \n");
            for (int a = 0; a < count; a++)
            {
                viewexpense(&e[a], a);
            }
            printf("\n");
            break;
        case (4):
            if (count < 1)
            {
                printf("Add an expense item first.\n");
                break;
            }

            totalcost(e, count);
            printf("\n");
            break;
        case (5):
            if (count < 1)
            {
                printf("Add an expense first.\n");
                break;
            }
            printf("Choose with what you want to search an expense from below:\n");
            printf("1. With ID\n");
            printf("2. With name\n");
            printf("3. With category\n");

            int select_num;
            printf("Enter your choice by entering the number: ");
            scanf("%d", &select_num);
            printf("\n");
            while (select_num < 1 || select_num > 3)
            {
                printf("Please select a valid option: ");
                scanf("%d", &select_num);
                printf("\n");
            }
            int s_id;
            int return_id;

            char s_name[75];
            int found_name = 0;

            char arr[75][50];
            int unique = 0;
            char s_cat[50];
            int arr_idx[75];
            int unique_idx = 0;
            int cat_found;

            switch (select_num)
            {
            case (1):
                printf("Choose an ID from the following: \n");
                for (int a = 1; a <= count; a++)
                {
                    printf("ID.%d\n", a);
                }
                printf("Enter ID: ");
                scanf("%d", &s_id);
                printf("\n");

                while (s_id < 1 || s_id > count)
                {
                    printf("Choose a valid ID: ");
                    scanf("%d", &s_id);
                    printf("\n");
                }
                return_id = searchid_found(count, e, s_id);
                viewexpense(&e[return_id], return_id);
                break;
            case (2):
                printf("Choose a name from the following:\n");
                for (int i = 0; i < count; i++)
                {
                    printf("%s\n", e[i].name);
                }

                while (getchar() != '\n')
                    ;

                found_name = searchname_found(count, e);

                while (found_name == -1)
                {
                    printf("Name not found, enter again.\n");
                    found_name = searchname_found(count, e);
                }

                viewexpense(&e[found_name], found_name);

                break;
            case (3):
                for (int a = 0; a < count; a++)
                {
                    int exists = 0;
                    for (int i = 0; i < unique; i++)
                    {
                        if (strcmp(e[a].category, arr[i]) == 0)
                        {
                            exists = 1;
                            break;
                        }
                    }
                    if (exists == 0)
                    {
                        strcpy(arr[unique], e[a].category);
                        unique++;
                    }
                }
                printf("Choose a category from the following:\n");
                for (int i = 0; i < unique; i++)
                {
                    printf("%s\n", arr[i]);
                }

                printf("Enter Category: ");
                while (getchar() != '\n')
                    ;
                fgets(s_cat, sizeof(s_cat), stdin);
                s_cat[strcspn(s_cat, "\n")] = '\0';
                printf("\n");

                cat_found = find_cat(s_cat, unique, arr);

                while (cat_found == -1)
                {
                    printf("Enter a valid category:\n");

                    printf("Enter Category: ");
                    fgets(s_cat, sizeof(s_cat), stdin);
                    s_cat[strcspn(s_cat, "\n")] = '\0';
                    printf("\n");

                    cat_found = find_cat(s_cat, unique, arr);
                }

                if (cat_found == 1)
                {
                    for (int i = 0; i < count; i++)
                    {
                        if (strcmp(s_cat, e[i].category) == 0)
                        {
                            arr_idx[unique_idx] = i;
                            unique_idx++;
                        }
                    }
                    for (int b = 0; b < unique_idx; b++)
                    {
                        viewexpense(&e[arr_idx[b]], arr_idx[b]);
                    }
                }
            }

            break;
        case(6):
            if (count < 1)
            {
                printf("Add an expense item first.\n");
                break;
            }

            printf("Choose an ID from the following:\n");
            for(int a = 0; a < count; a++){
                printf("ID.%d\n", e[a].id);
            }

            printf("Enter ID: ");
            scanf("%d", &edit_on);\
            printf("\n");

            while(edit_on < 1 || edit_on > count){
                printf("Enter a valid ID: ");
                scanf("%d", &edit_on);
                printf("\n");
            }
            printf("How would you like to edit this expense:\n");
            printf("1. Edit its Name\n");
            printf("2. Edit its Category\n");
            printf("3. Edit its Cost\n");
            printf("4. Edit the entre expense\n");

            int edit_choice;
            printf("Enter your choice by entering the number: ");
            scanf("%d", &edit_choice);
            printf("\n");
            while (edit_choice < 1 || edit_choice > 4)
            {
                printf("Please select a valid option: ");
                scanf("%d", &edit_choice);
                printf("\n");
            }
            char cat_arr[75][50];
            char s_cat2[50];
            char new_cat[50];
            char new_name[50];
            int new_cost;

            switch(edit_choice){
                case(1):
                    printf("Enter new name: ");
                    while(getchar() != '\n');
                    fgets(new_name, 50, stdin);
                    new_name[strcspn(new_name, "\n")] = '\0';
                    printf("\n");

                    edit_name(e[edit_on - 1].name, new_name);
                    break;
                case(2):
                    printf("Enter your new category name: ");
                    while(getchar() != '\n');
                    fgets(new_cat, 50, stdin);
                    new_cat[strcspn(new_cat, "\n")] = '\0';
                    printf("\n");

                    edit_cat(e[edit_on - 1].category, new_cat);
                    break;
                
                case(3):
                    printf("Enter new cost: ");
                    scanf("%d", &new_cost);
                    printf("\n");

                    edit_cost(&e[edit_on - 1].cost, new_cost);
                    break;
                case(4):
                    printf("Enter new name: ");
                    while(getchar() != '\n');
                    fgets(new_name, 50, stdin);
                    new_name[strcspn(new_name, "\n")] = '\0';
                    printf("\n");

                    edit_name(e[edit_on - 1].name, new_name); 

                    printf("Enter your new category name: ");
                    fgets(new_cat, 50, stdin);
                    new_cat[strcspn(new_cat, "\n")] = '\0';
                    printf("\n");

                    edit_cat(e[edit_on - 1].category, new_cat);

                    printf("Enter new cost: ");
                    scanf("%d", &new_cost);
                    printf("\n");

                    edit_cost(&e[edit_on - 1].cost, new_cost);

                    break;

            }
            break;

            
        case(7):
            printf("Enter a name from the followig:\n");
            for(int a = 0; a < count; a++){
                printf("%d. %s\n", a + 1, e[a].name);
            }
            while(getchar() != '\n');
            found_name = searchname_found(count, e);

            while(found_name == -1){
                printf("Enter a valid name: ");
                found_name = searchname_found(count, e);
            }

            delete_exp(count, e, found_name);
            count--;
            
            for(int a = found_name; a < count; a++){
                fixid(&e[a].id);
            }
            break;

        case(8):
            if (count < 1)
            {
                printf("Add an expense item first.\n");
                break;
            }
            printf("The summarization of all the expenses is shown below:\n");
            printf("\n");
            printf("Total nubner of expenses: %d\n", count);
            totalcost(e, count);
            printf("All the names of the expenses are:\n");
            for(int a = 0; a < count; a++){
                printf("%d. %s\n", a + 1, e[a].name);
            }
            printf("All the categories of the expenses are:\n");
            for(int i = 0; i < count; i++){
                int exists = 0;
                for(int z = 0; z < uniqueid; z++){
                    if(strcmp(e[i].category, cat_arr[z]) == 0){
                        exists = 1;
                        break;
                    }
                }
                if(exists == 0){
                    strcpy(cat_arr[uniqueid], e[i].category);
                    uniqueid++;
                }
            }
            for(int b = 0; b < uniqueid; b++){
                printf("%d. %s\n", b + 1, cat_arr[b]);
            }
            break;

        case (9):
            fptr = fopen("storage.dat", "wb");
            if(fptr == NULL){
                printf("File couldn't be accessed.");
                fclose(fptr);
                printf("Goodbye");  
                break;
            }
             
            count_proof = fwrite(e, sizeof(exp), count, fptr);
            if(count_proof == 0){
                printf("Error data not found.\n");
            }
            else{
                printf("Data saved successfully.\n");
            }
            fclose(fptr);
            printf("Goodbye\n");  
            break;
        }

    } while (choice != 9);

    return 0;
}
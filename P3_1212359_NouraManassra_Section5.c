#include <stdio.h>
#include <stdlib.h>//for the order of the words
#include <string.h>

/// Name : Noura Awni Jaber Manassra
/// ID   : 1212359
/// Instructor : Dr. Anas Arram
/// Section : 5

// Structure for the
//-----------> I have used this way since it's easier to deal with, and it take me less time instead of writing each type alone
typedef struct
{
    int studentID;
    char studentName[50];
    char city[50];
    int classID;
    char EDate[20];//ENROLMENT DATE
} Student;
typedef struct tnode
{
    Student data;        //held the data in it
    struct tnode *right;   // pointer that point to left sub nodes(children nodes).
    struct tnode *left;   //pointer that point to right sub nodes(children nodes).

} tnode;
tnode* createTnode(Student student)
{
    tnode* newNode = (tnode*)malloc(sizeof(tnode)); //<-- will search about a space in the memo
    if (newNode == NULL)
    {
        printf("memory allocation failed");
        return NULL;
    }
    newNode->data = student;     // set the data inside the node.
    //--------->> note that at the previous line, it showed the importance of adding it at a struct instead of writing all of them
    newNode->left = NULL;    //set the lift pointer to null temprorey.
    newNode->right = NULL;  //set the right pointer to null temprorey.
    return(newNode);
}
tnode* insertTnode(tnode* node, Student student)
{
//------->> note also that here it's obvious that the binary tree is used
//------->> note that the parameter i used student, so all the dara will be inserted once
    // if the root is null then we will create a tree :
    if(node == NULL)
    {
        return createTnode(student);
    }
    else
    {
        // if the node is not null then insert the data by recursion
        // resurion will used to reach the leafs (most left or right node ) to insert the data:
        if (student.studentID < node->data.studentID)
        {
            //if the data is less than the node data -> insert into the left subtree:
            node->left = insertTnode(node->left,student);
        }
        else if (student.studentID > node->data.studentID)
        {
            ///if the data is bigger than the node data -> insert into the right subtree:
            node->right = insertTnode(node->right,student);
        }
        else node->data = student;
    }
    return node;
}
tnode* find(tnode* root, int studentID)
{
//------->> Note that this function is using the ID as key for the search, and here the search is BST
    if(root ==  NULL || root->data.studentID == studentID)
    {
        return root; // actually here is the best case which has the less time comp.
    }
    else if (studentID < root->data.studentID)
    {
        return find(root->left, studentID);//note here that i used the left, since the ID is less
    }
    else
    {
        return find(root->right, studentID);//since the ID is greater, so we have to search at the right side of the tree
    }
}
void printStudentData(Student* student)
{
    //--------->> I put this function to print each data for each student at the tree
    printf("Student ID: %d\n", student->studentID);
    printf("Student Name: %s\n", student->studentName);
    printf("City: %s\n", student->city);
    printf("Class ID: %d\n", student->classID);
    printf("Enrollment Date: %s\n\n", student->EDate);
}
void sortStudentsByName(Student students[], int counter)
{
    //---------->> To make the order true, i have used the bubble sort :)
    int i, j;
    for (i = 0; i < counter-1; i++)
    {
        for (j = 0; j < counter- i - 1; j++)
        {
            if (strcmp(students[j].studentName, students[j+1].studentName)> 0)
            {
                Student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }

    }
}
void listStudentss(Student students[], int counter)
{
    sortStudentsByName(students, counter);
    for (int i = 0; i < counter; i++)
    {
        printStudentData(&students[i]);
    }
}
void findCity(tnode* root, char cityy[], Student students[], int* counter)
{
    //------------------>> The idea of this function is to check each node if it has the same city as the inserted one
    if (root == NULL)
    {
        return ;
    }
//------------------->> To do this we used the strcmp function to check if it's the same or not
    findCity(root->left, cityy, students, counter);

    if (strcmp(root->data.city, cityy) == 0)
    {
        students[*counter] = root->data;
        (*counter)++;
    }

    findCity(root->right, cityy, students, counter);
    //--------->> this function supposed to fill the array of the cities needed by the used ;)
}
void findClassID(tnode* root, int classID,  Student students[], int* counter)
{
    //-------->> The idea here is to check each node if it has the classID, if yes print it, that is why it's void function :)
    if (root == NULL) return ;
    else  //    findCity(root->left, cityy, students, counter);
    {
        findClassID(root->left, classID,students, counter);
        if (root->data.classID == classID)
        {
            students[*counter] = root->data;
            (*counter)++;
        }
        findClassID(root->right, classID,students, counter);
    }
}
tnode* deleteNode(tnode* root, int studentID)
{
    if (root == NULL)
    {
        return root;
    }
    else if (studentID < root->data.studentID)     // since it's less so we have to return the left root
    {
        root->left = deleteNode(root->left, studentID);
    }
    else if (studentID > root->data.studentID)     // since it's greater so we have to return the right root
    {
        root->right = deleteNode(root->right, studentID);
    }
    else
    {
        // Node to be deleted found
        if (root->left == NULL)   //here is the easier part, when the node does not has a left node, we just delete it's right
        {
            tnode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)    //when the node does not has a right node, we just delete it's left
        {
            tnode* temp = root->left;
            free(root);
            return temp;
        }
        tnode* temp = root->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.studentID);
    }
    return root;
}
void printToFile(tnode* root, FILE* file)
{
    if (root == NULL)   // it means that there is nothing to print :)
    {
        return;
    }
    printToFile(root->left, file);
    fprintf(file, "%d %s %s %d %s\n", root->data.studentID, root->data.studentName,
            root->data.city, root->data.classID, root->data.EDate);// here is the actual printing to the file
    printToFile(root->right, file);
}
void listStudents(tnode* root)
{
    if (root != NULL)
    {
        listStudents(root->left);
        printf("ID: %d, Name: %s, Address: %s, Class: %d, Enrollment Date: %s\n",
               root->data.studentID, root->data.studentName, root->data.city,
               root->data.classID, root->data.EDate);
        listStudents(root->right);
    }
}

int main()
{
    tnode* root = NULL; //this one will be used to represnt the tree
    tnode* news = NULL;
    int choice=0, studentID=0, classID=0; // gonna be used as user input
    char studentName[50]="", city[50]="", EDate[20]="";// gonna be used as user input
    //----------------->> These two counters gonna be used as parameters fot sorting
    int cityCounter = 0;
    int classCounter = 0;
    char line[256];
    FILE* file2 = fopen("studentData.txt","r+");
    if (file2 == NULL)
    {
        printf("Failed to open the file.\n");
        exit(0);
    }
    int counter = 0;
    //here is used to just count the lines :)
    while (fgets(line, sizeof(line), file2) != NULL)
    {
        counter++;
    }
    Student newStudent;
    rewind(file2);//this is important to let the same file read and write
    Student students[counter];//here is we gonna store the data of the student inside
//----------->> actual reading for the data from the file, note that i saved them inside the structure student
    for (int i = 0; i < counter; i++)
    {
        fgets(line, sizeof(line), file2);
        sscanf(line, "%d%s%s%d%s",
               &students[i].studentID,
               students[i].studentName,
               students[i].city,
               &students[i].classID,
               students[i].EDate);
//----------->> after reading them from file and sorting them inside structure, insert them inside file
        root = insertTnode(root, students[i]);
    }
    Student cityStudents[counter];//to make an order for the cities
    Student classStudents[counter];//to make an order for the cities
    while (1)
    {
        printf("Selam, Welcome to the Students System. Choose what you want to do:\n");
        printf("1. Insert a student\n");
        printf("2. Find a student by student ID\n");
        printf("3. List all students in lexicographic order of their names\n");
        printf("4. Search for a city and list all students from that city\n");
        printf("5. List all students by their class\n");
        printf("6. Delete a student by student ID\n");
        printf("7. Save all students to file\n");
        printf("8. Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter student ID: ");
            scanf("%d", &studentID);
            students[counter - 1].studentID = studentID;

            printf("Enter student name: ");
            scanf("%s", studentName);
            strcpy(students[counter - 1].studentName, studentName);

            printf("Enter home address: ");
            scanf("%s", city);
            strcpy(students[counter - 1].city, city);

            printf("Enter class ID: ");
            scanf("%d", &classID);
            students[counter - 1].classID = classID;

            printf("Enter enrollment date: ");
            scanf("%s", EDate);
            strcpy(students[counter - 1].EDate, EDate);
            // Insert the student into the BST
            root = insertTnode(root, students[counter - 1]);
            //counter++;
            printf("The new data:\n");
            printStudentData(&students[counter - 1]);
            printf("Student inserted successfully. %d\n",counter);
            break;
        case 2:
            printf("Please enter the student's ID you want to find:\n");
            scanf("%d", &studentID);
            // Logic to find the student with the given ID
            tnode* updateStudent = find(root, studentID);
            if (updateStudent != NULL)
            {
                printf("Well, we found the student with the given ID. Here is the data:\n");
                printStudentData(&updateStudent->data);
                printf("If you want to update it, please press 1. Otherwise, press 0:\n");
                int flag;
                scanf("%d", &flag);
                if (flag == 1)
                {
                    printf("Please enter the updated student's ID, name, city, class ID, and enrollment date respectively:\n");
                    scanf("%d", &studentID);
                    scanf("%s", studentName);
                    scanf("%s", city);
                    scanf("%d", &classID);
                    scanf("%s", EDate);
                    updateStudent->data.studentID = studentID;
                    strcpy(updateStudent->data.studentName, studentName);
                    strcpy(updateStudent->data.city, city);
                    updateStudent->data.classID = classID;
                    strcpy(updateStudent->data.EDate, EDate);
                    printf("Student updated successfully. Here is the updated data:\n");
                    printStudentData(&updateStudent->data);
                }
            }
            else
            {
                printf("There is no student with the given ID.\n");
            }
            break;
        case 3:
            printf("Here is the List all students in lexicographic order of their names:\n");
            listStudentss(students,counter);
            break;
        case 4:
            printf("Please enter the name of the city:) \n");
            scanf("%s", city);
            findCity(root, city, cityStudents, &cityCounter);
            if (findCity == NULL)  break;
            // Sort the cityStudents array by name
            listStudentss(students,counter);

            // Print the sorted list of students from the specified city
            printf("List of students from the city you have entered in lexicographic order of their names:) \n") ;
            for (int i = 0; i < cityCounter; i++)
            {
                printf("Student %d:\n", i + 1);
                printStudentData(&cityStudents[i]);
            }
            break;

        case 5:
            printf("Please enter the classID :) \n");
            scanf("%d",&classID);
            findClassID(root, classID,classStudents,&classCounter );
            if (findClassID==NULL ) break;
            sortStudentsByName(classStudents, classCounter);
            printf("Here is a List all students by their class in lexicographic order of their names:) \n ");
            for (int i = 0; i < classCounter; i++)
            {
                printf("Student %d:\n", i + 1);
                printStudentData(&classStudents[i]);
            }
            break;
        case 6 :
            printf("Well, please enter the student's ID you need to remove :) \n");
            scanf("%d", &studentID);
            --counter;
            root = deleteNode(root, studentID);
            printf("Student deleted successfully.\n");
            break;
        case 7 :
            fclose(file2);
            file2 = fopen("studentData.txt", "wb");
            if (file2 == NULL)
            {
                printf("Failed to open the file for writing.\n");
                exit(0);
            }
            printToFile(root, file2);
            printf("Students saved to file successfully.\n");
            fclose(file2);
            break;
        case 8:
            exit(0);
        }
    }
}

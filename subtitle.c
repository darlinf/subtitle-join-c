#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>

void create_2d_array(int rows, int cols, char ***arr) {
    *arr = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        (*arr)[i] = (char *)malloc((cols + 1) * sizeof(char));
    }
}

 void free_2d_array(int rows, char ***arr) {
    for (int i = 0; i < rows; i++) {
        free((*arr)[i]);
    }
    free(*arr);
    *arr = NULL; // Set the pointer to NULL to avoid dangling pointers
}

void write_to_file(char** strings, int num_strings, const char* filename) {
    FILE* fp;
    fp = fopen(filename, "w"); // open file in write mode

    if (fp == NULL) { // check for errors opening the file
        printf("Error opening file!\n");
        return;
    } 

    // write each string to the file
    for (int i = 0; i < num_strings; i++) {
      fputs(strings[i], fp); 
    }

    fclose(fp); // close the file
}
 
size_t get_array_length(char** array) {
    size_t length = 0;
    while (*array != NULL) {
        length++;
        array++;
    }
    return length;
} 

size_t get_array_length_2(char** array) {
    size_t length = 0;
    while (*array != NULL) {
        length++;
        array++;
    }
    return length;
}  

int i = 0;
char** read_file(char* filename, int* num_lines) {
    FILE* fp;
    char *buffer ;
    i = 0;
    long size;

    // Open the file in read mode
    fp = fopen(filename, "r");

    // Get the size of the file
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);    
    char** lines = malloc(size * sizeof(char*));

    // Allocate memory for the buffer to hold the file contents
    buffer = (char*) malloc(size + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for buffer\n");
        return NULL;
    }

    // Check if file exists
    if (fp == NULL) {
        printf("File not found.\n");
        *num_lines = 0;
        return NULL;
    }

    // Read the contents of the file and store them in the lines array
    while (fgets(buffer, size, fp) != NULL && i < size) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
        lines[i] = malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(lines[i], buffer);
        i++;


       // printf("%s", buffer);
    }

    // Close the file
    fclose(fp);

    // Set the number of lines and return the lines array
    *num_lines = i;
    return lines;
}

int removeArrow(){   
    printf("%s\n", "start");

    char** lines_english;
    int num_lines_english; 
    lines_english = read_file("files_en_es/english.txt", &num_lines_english);
    if (lines_english == NULL) {
        return 1; 
    }  

    size_t array_size_english  = i;
    char** lines_spanish;
    int num_lines_spanish; 
    lines_spanish = read_file("files_en_es/spanish.txt", &num_lines_spanish);
    if (lines_spanish == NULL) {
        return 1; 
    }   
 
    char arrayLines[array_size_english][200];
    for (size_t i = 0; i < array_size_english; i++)
    { 
        strcpy(arrayLines[i], lines_spanish[i]);  
    }
 
    char **array_lines_result;
    int rows = (array_size_english * 4) + 1;
    int cols = 200; 
    create_2d_array(rows, cols, &array_lines_result);
    size_t i_j = 0; 

    for (size_t i = 0; i < array_size_english; i++)
    {  
        if(strstr(lines_spanish[i] , "-->") == NULL){ 
           strcpy(array_lines_result[i_j], lines_english[i]); 
           i_j++; 
           strcpy(array_lines_result[i_j], "\n");  
           i_j++;
        }  
        if(atoi(lines_spanish[i]) == 0){ 
            strcpy(array_lines_result[i_j], lines_spanish[i]);  
            i_j++;
            strcpy(array_lines_result[i_j], "\n");  
            i_j++;
        }  
    }   
     
    write_to_file(array_lines_result, i_j,"subtitle join/subtitle.txt"); 

    printf("%s\n", "done!");
} 

int main() {
    removeArrow();
    return 0;
}
 

 
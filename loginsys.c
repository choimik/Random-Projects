
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int lines_count(FILE *fPtr);
char* get_str(const char* text);
char* get_fchar(FILE* fPtr);
char* parse(char* str, int i);
char *user(char *user_data[], int i);
int get_int(char* text);
int counter(char* str);
//char *password_gen(int len);

int main(void) {
    FILE* fPtr = NULL;
    fPtr = fopen("user-data.txt", "a+");

    if (fPtr == NULL) {
        return 1;
    }

    // Read lines from the file and store them in an array
    int lines = 0;
    int size = lines_count(fPtr);
    char* user_data[size];
    char* temp_ptr;

    while ((temp_ptr = get_fchar(fPtr)) != NULL) {
        user_data[lines] = temp_ptr;
        printf("%s\n", user_data[lines]);
        lines++;
    }
    
    fclose(fPtr);

    char* user_type = get_str("User: ");

    // HAVE TO MAKE WAY TO PLUG IN USER and VERIFY, FIND USER's USERNAME AND PASSWORDS
    char *users[lines];
    for (int i = 0; i < lines; i++){
        users[i] = user(user_data, i);
    }

    bool is_user = false;
    int user_line;
    for (int i = 0; i < lines; i++){
        if(strcmp(users[i], user_type) == 0){
            is_user = true;
            user_line = i;
            break;
        } else{
            is_user = false;
        }
    }


    if (is_user == true && strcmp(user_type, users[lines - 1]) != 0)  {
        char* u_entry = get_str("Username: ");
        char* p_entry = get_str("Password: ");

        char* u_user;
        char* p_user;
        bool u_valid = false;
        bool p_valid = false;

        //creation of max var to be used in for loop and index_u to check if username corresponds with its password
        int max = counter(user_data[user_line]);
        int index_u;
        // Username iteration through and compare
        for(int i = 1; i < max; i+=2){
            u_user = parse(user_data[user_line], i);
            if(strcmp(u_user, u_entry) == 0){
                index_u = i;
                u_valid = true;
            }
        }   

        //Password iteration and compare
        for(int i = 2; i < max; i+=2){
            p_user = parse(user_data[user_line], i);
            if(strcmp(p_user, p_entry) == 0 && (index_u + 1 == i)){
                p_valid = true;
            }
        }   

        if(u_valid == true && p_valid == true){
            printf("\nCorrect");
        }else {
            printf("\nIncorrect");
            return 3;
        }
        
    }

    char* mu_entry = NULL;
    char* mp_entry = NULL;

    if (is_user == true && strcmp(user_type, users[lines - 1]) == 0) {
        mu_entry = get_str("Master Username: ");
        mp_entry = get_str("Master Password: ");
    } else if (is_user == false){
        printf("User Not Found");
        return 2;
    }

    bool master_true = false;

    // have to fix without m_pass and m_user
    // to find a user i need the array user_data[lines] and which line the user is on

    char* mu_user;
    char* mp_user;

    if (mu_entry != NULL && mp_entry != NULL) {
        bool mu_valid = false;
        bool mp_valid = false;

        //creation of max var to be used in for loop and index_u to check if username corresponds with its password
        int max = counter(user_data[user_line]);
        int index_u;
        // Username iteration through and compare
        for(int i = 1; i < max; i+=2){
            mu_user = parse(user_data[lines-1], i);
            if(strcmp(mu_user, mu_entry) == 0){
                index_u = i;
                mu_valid = true;
            }
        }   

        //Password iteration and compare
        for(int i = 2; i < max; i+=2){
            mp_user = parse(user_data[lines-1], i);
            if(strcmp(mp_user, mp_entry) == 0 && (index_u + 1 == i)){
                mp_valid = true;
            }
        }   

        if(mu_valid == true && mp_valid == true){
            master_true = true;
        }else {
            printf("\n Incorrect");
            return 3;
        }
    }

/*   int action;
    if (master_true == true) {
        action = get_int("\n\n Would you like to... \n\n 1.) View all the stored Username-Password combinations for a particular user. \n 2.) Generate a random password of a given length. \n 3.) Store a Username-Password combination for a site. \n 4.) Modify a previously stored Username-Password combination. \n 5.) Delete a record. \n 6.) Modify master username and password. \n\n Answer with a number: ");

    }


    if(master_true == true && action == 1){

        printf("What user's login credentials would you like to see?\n\n");

        char* user_1 = get_str("User: ");
        for (int i = 0; i < lines; i++){
            printf("%s",users[i]);
        }


    }
    else if(master_true == true && action == 2){

    //Generate a random password of a given length.
        int len = get_int("How long would you like your new password to be?");
        //printf("%s",password_gen(len));
    }
    else if(master_true == true && action == 3){
    
    char* wsp = get_str("wsp");
    printf("%s", wsp);

        printf("1");
    }
    else if(master_true == true && action == 4){

    //Modify a previously stored Username-Password combination.

        printf("1");
    }
    else if(master_true == true && action == 5){
    
    //Delete a record

        printf("1");
    }
    else if(master_true == true && action == 6){

    //Modify master username and password.

        printf("1");
    } else if (master_true){
        printf("\n Not an option \n\n Exiting...");
        return 4;
    }
*/
    return 0;

}


int get_int(char* text){
    printf("%s", text);
    char* str_ptr = NULL;
    int counter = 0;
    char c;

    while ((c = getchar()) != EOF && c != '\n' && c != '\r') {
        counter++;
        if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7'|| c == '8' || c == '9'){
            str_ptr = (char*)realloc(str_ptr, counter + 1);
        } else{
            return 5;
        }
        
        if (str_ptr == NULL) {
            free(str_ptr);
            return 5;
        }
        str_ptr[counter - 1] = c;
    }

    if (str_ptr == NULL) {
        free(str_ptr);
        return 5;
    }

    str_ptr[counter] = '\0';

    return atoi(str_ptr);
}

char* get_str(const char* text) {
    printf("%s", text);
    char* str_ptr = NULL;
    int counter = 0;
    char c;

    while ((c = getchar()) != EOF && c != '\n' && c != '\r') {
        counter++;
        str_ptr = (char*)realloc(str_ptr, counter + 1);

        
        if (str_ptr == NULL) {
            free(str_ptr);
            return NULL;
        }
        str_ptr[counter - 1] = c;
    }

    if (str_ptr == NULL) {
        free(str_ptr);
        return NULL;
    }

    str_ptr[counter] = '\0';

    return str_ptr;
}


char* get_fchar(FILE* fPtr) {
    char c;
    int counter = 0;
    char* str_ptr = NULL;

    while ((c = fgetc(fPtr)) != EOF && c != '\n') {
        counter++;
        str_ptr = (char*)realloc(str_ptr, counter + 1);
        if (str_ptr == NULL) {
            free(str_ptr);
            return NULL;
        }
        str_ptr[counter - 1] = c;
    }

    if (str_ptr == NULL) {
        free(str_ptr);
        return NULL;
    }

    str_ptr[counter] = '\0';
    return str_ptr;

}

int lines_count(FILE *fPtr){
    char c;
    int lines = 0;
    while((c = fgetc(fPtr)) != EOF){
        if (c == '\n'){
            lines++;
        }
    }
    fseek(fPtr, 0, SEEK_SET);
    return lines;
}


char* parse(char* str, int i) {
    int index = 0;
    char c;
    int size = 0;

    while ((c = *(str + index)) != '\0') {
        if (c == ' ') {
            size++;
        }
        index++;
    }

    index = 0;
    int counter = 0;
    char** array = (char**)malloc((size + 1) * sizeof(char*)); // Allocate an array of pointers

    for (int i = 0; i < size + 1; i++) { // Add one more iteration for the last word
        while ((c = *(str + index)) != '\0' && c == ' ') {
            index++; // Skip leading spaces
        }

        int word_length = 0;
        while ((c = *(str + index)) != '\0' && c != ' ') {
            word_length++;
            index++;
        }

        if (word_length > 0) {
            array[counter] = (char*)malloc((word_length + 1) * sizeof(char)); // Allocate space for the word
            strncpy(array[counter], str + index - word_length, word_length);
            array[counter][word_length] = '\0'; // Null-terminate the word
            counter++;
        }
    }

    return array[i];
}

int counter(char* str){
    int index = 0;
    char c;
    int size = 0;

    while ((c = *(str + index)) != '\0') {
        if (c == ' ') {
            size++;
        }
        index++;
    }

    return size + 1;
}

char *user(char *user_data[], int i){
    int counter = 0;
    char c;
    char* ptr = NULL;


    while ((c = user_data[i][counter]) != ' '){
        ptr = (char*)realloc(ptr, counter + 1);
        *(ptr + counter) = c;
        counter++;
    }
    *(ptr + counter) = '\0';


    return ptr;
 
}

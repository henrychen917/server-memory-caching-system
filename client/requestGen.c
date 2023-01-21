#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 32
#define MAX_VAL_LEN 64

int main() {
    FILE *file = fopen("requests.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(0)); // seed the random number generator
    int num_requests = 250000; // change this to the number of requests you want to generate
    char requests[3][MAX_LEN] = {"SET", "GET", "DEL"};
    char keys[num_requests][MAX_LEN];
    int keys_count = 0;

    for (int i = 0; i < num_requests; i++) {
        int request_index = rand() % 3; // choose a random request
        char key[MAX_LEN], val[MAX_VAL_LEN];

        switch (request_index) {
            case 0: // SET
                sprintf(key, "key_%d", i);
                sprintf(val, "val_%d", i);
                strcpy(keys[keys_count], key);
                keys_count++;
                fprintf(file, "%s %s %s\n", requests[request_index], key, val);
                break;
            case 1: // GET
            case 2: // DEL
                if(keys_count > 0){
                    int key_index = rand() % keys_count;
                    strcpy(key, keys[key_index]);
                    if(request_index == 2){
                      // remove key from list
                      for (int j = key_index; j < keys_count - 1; j++) {
                        strcpy(keys[j], keys[j+1]);
                      }
                      keys_count--;
                    }
                    fprintf(file, "%s %s\n", requests[request_index], key);
                }
                break;
            default:
                printf("Invalid request type!\n");
                break;
        }
    }

    fclose(file);
    return 0;
}

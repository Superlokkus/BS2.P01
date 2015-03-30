//
//  main.c
//  BS2.P01
//
//  Created by Markus Klemm on 25.03.15.
//  Copyright (c) 2015 net.markusklemm. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_semaphore.h"

int child_main(const char *file_name);

int main(int argc, const char * argv[]) {
    
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file_name>\n",argv[0]);
        return EXIT_FAILURE;
    }
    
    my_sem_id file_sem = create_sem(1);
    const uint_fast8_t child_count = 5;
    pid_t childs[child_count];
    
    int i;
    for(i = 0; i < child_count; i++)
    {
        childs[i] = fork();
        if (childs[i] == 0)
        {
            //Child
            return child_main(argv[1]);
        } else if(childs[i] == -1)
        {
            perror("Fork of child failed");
            return EXIT_FAILURE;
        }
    }
    
    for (i = 0; i < child_count; i++) {
        int return_value;
        waitpid(childs[i], &return_value,0);
        if (WIFEXITED(return_value)) {
            printf("Child Nr. %d exited with %d\n",i+1,WEXITSTATUS(return_value));
            //while( (wpid = wait(&exitStatus)) > 0)
        }
        delete_sem(file_sem);
    }
    
    return EXIT_SUCCESS;
}

int child_main(const char *file_name)
{
    FILE *f = fopen(file_name, "r+");
    if (!f)
    {
        perror("Can not open zahl.dat");
        return EXIT_FAILURE;
    }
    
    char buffer[512];
    if(!fgets(buffer, 512, f))
    {
        perror("Failed to read file content");
        return EXIT_FAILURE;
    }
    long number = strtol(buffer, NULL, 10);
    printf("Read %ld from file\n",number);
    
    number++;
    rewind(f);
    fprintf(f, "%ld",number);
    
    
    fclose(f);
    
    return EXIT_SUCCESS;
}
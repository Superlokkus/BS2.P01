//
//  my_semaphore.c
//  BS2.P01
//
//  Created by Markus Klemm on 30.03.15.
//  Copyright (c) 2015 net.markusklemm. All rights reserved.
//

#include "my_semaphore.h"

my_sem_id create_sem(const int sem_init)
{
    int semid = semget(IPC_PRIVATE,1,SEM_R);
    if (semid == -1) {
        perror("Semget() failed");
        exit(EXIT_FAILURE);
    }
    
    
    return semid;
}
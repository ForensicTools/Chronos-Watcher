//
//  Chronos_Watcher.c
//  Chronos Watcher
//
//  Created by Vlad Ionescu, Joe Messinger on 11/3/13.
//  Copyright (c) 2013 Vlad Ionescu. All rights reserved.
//
//  vlad@vladionescu.com    / https://github.com/vladionescu
//  joem3921@gmail.com      / https://github.com/joem3921
//

#include <mach/mach_types.h>
#include <string.h>

// thanks to: gdbinit a/k/a fractalG!
// this is for dev right now - will make leaner soon
#include "bruteforcesysent/sysent.h"
#include "bruteforcesysent/idt.h"

kern_return_t Chronos_Watcher_start(kmod_info_t * ki, void *d);
kern_return_t Chronos_Watcher_stop(kmod_info_t *ki, void *d);

// all the syscalls we care about
char *syscalls[12][10];

// here we will have either:
// - a variable to hold a copy of the entire original syscall table
// - variables for every original pointer for every sysent[SYSCALL].sy_call we modify

kern_return_t Chronos_Watcher_start(kmod_info_t * ki, void *d)
{
    // define those syscalls we will intercept!
    strcpy(syscalls[0], "read");
    strcpy(syscalls[1], "write");
    strcpy(syscalls[2], "link");
    strcpy(syscalls[3], "unlink");
    strcpy(syscalls[4], "mknod");
    strcpy(syscalls[5], "chmod");
    strcpy(syscalls[6], "chown");
    strcpy(syscalls[7], "utimes");
    strcpy(syscalls[8], "rename");
    strcpy(syscalls[9], "execve");
    strcpy(syscalls[10], "pipe");
    strcpy(syscalls[11], "truncate");
    
    // search for sysent pointer in kernel memory (/dev/kmem)
    uint64_t sysent = get_sysent_address();
    
    // search for pointers to every SYSCALL we want to modify (foreach SYSCALL)
    for (int i=0;i<sizeof(*syscalls);i++) {
        uint64_t syscall_ptr = sysent[*syscalls[i]].sy_call;
        uint64_t syscall_ptr_o = syscall_ptr;
        
        // save the original sysent[SYSCALL].sy_call contents in one of the global variables above
        // OR
        // save the entire sysent contents (if this, put this earlier in the code, before the foreach)
        
        // overwrite sysent[SYSCALL].sy_call
    }
    
    return KERN_SUCCESS; // return KERN_FAILURE if we want to hide this from showing up in `kextstat`
}

kern_return_t Chronos_Watcher_stop(kmod_info_t *ki, void *d)
{
    // cleanup all the things we did, otherwise we guarantee a kernel panic
    // revert sysent (the syscall table) to its original state from global variables above
    
    // offer an option to revert MAC times
    
    return KERN_SUCCESS;
}

// write a function to copy the existing MAC times and pass them to a store function

// write a store function to store the given MAC times in a database of some sort (probably flatfile/csv)
// then call log function

// write a log function to generate times.log and append to it anything going to store function

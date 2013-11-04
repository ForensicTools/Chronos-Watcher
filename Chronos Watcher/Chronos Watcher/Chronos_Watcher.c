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

kern_return_t Chronos_Watcher_start(kmod_info_t * ki, void *d);
kern_return_t Chronos_Watcher_stop(kmod_info_t *ki, void *d);

// here we will have either:
// - a variable to hold a copy of the entire original syscall table
// - variables for every original pointer for every sysent[SYSCALL].sy_call we modify

kern_return_t Chronos_Watcher_start(kmod_info_t * ki, void *d)
{
    // search for sysent pointer in kernel memory
    
    // search for pointers to every SYSCALL we want to modify (foreach SYSCALL)
    
    // save the original sysent[SYSCALL].sy_call contents in one of the global variables above
    // OR
    // save the entire sysent contents (if this, put this earlier in the code, before the foreach)
    
    // overwrite sysent[SYSCALL].sy_call
    
    // endforeach
    
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
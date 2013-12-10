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

struct sysent {		/* system call table */
	int16_t		sy_narg;	/* number of args */
	int8_t		sy_resv;	/* reserved  */
	int8_t		sy_flags;	/* flags */
	uint32_t	sy_call;	/* implementing function */
	uint32_t	sy_arg_munge32; /* system call arguments munger for 32-bit process */
	uint32_t	sy_arg_munge64; /* system call arguments munger for 64-bit process */
	int32_t		sy_return_type; /* system call return types */
	uint16_t	sy_arg_bytes;	/* Total size of arguments in bytes for
								 * 32-bit system calls
								 */
};
struct sysent64 {		/* system call table */
	int16_t		sy_narg;	/* number of args */
	int8_t		sy_resv;	/* reserved  */
	int8_t		sy_flags;	/* flags */
    uint32_t    padding;        /* padding, x86 binary against 64bits kernel would fail */
	uint64_t	sy_call;	/* implementing function */
	uint64_t	sy_arg_munge32; /* system call arguments munger for 32-bit process */
	uint64_t	sy_arg_munge64; /* system call arguments munger for 64-bit process */
	int32_t		sy_return_type; /* system call return types */
	uint16_t	sy_arg_bytes;	/* Total size of arguments in bytes for
								 * 32-bit system calls
								 */
};

// 16 bytes IDT descriptor, used for 32 and 64 bits kernels (64 bit capable cpus!)
struct descriptor_idt
{
	uint16_t offset_low;
	uint16_t seg_selector;
	uint8_t reserved;
	uint8_t flag;
	uint16_t offset_middle;
	uint32_t offset_high;
	uint32_t reserved2;
};

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
    
    // sysent pointer in kernel memory (/dev/kmem)
    // get by running ./bruteforcesysent
    struct sysent64 *sysent = (struct sysent64 *)0xffffff802f85d7f0;
    
    // search for pointers to every SYSCALL we want to modify (foreach SYSCALL)
    for (int i=0;i<sizeof(*syscalls);i++) {
        uint64_t syscall_ptr = sysent[(int)*syscalls[i]].sy_call;
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

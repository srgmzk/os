> Paging allows us to remap memory address to point to other memory address
> Can be used to provide the illusion we have the maximum amount of ram installed
> Can be used to hide memory from other processes

Remapping Memory
----------------

o Paging allows us to remap one memory address to another, so 0x100000 could point to 0x200000
o Paging works in 4096 byte block size by default. The blocks are called pages.
o When paging is enabled the MMU will look at your allocated page tables to resolve virtual addresses into
    physical addresses
o Paging allows us to pretend memory exists  when it does not

o num of page directories (tables) * num of entries in each table * byte block memory (page) = full addressable mem
            1024 * 1024 * 4096 = 4 294 967 296 Bytes / 4GB of addressable memory

o Page directory structure holds:
'''''''''''''''''''''''''''''''''
    - a pointer to a page table
    - attributes

    Page table directory structure:
    -------------------------------    

    31               11        9                                   0
    | page table 4-KB | Avail. | G | S | 0 | A | D | W | U | R | P |
    | Aligned address |        |   |   |   |   |   |   |   |   |   |

|         Name                    | Description
+---------------------------------+---------------------------------------------------------------------
| Page table 4-K aligned address  | The Physical 4096 byte aligned address to the start of a page table
+--------------------------------+----------------------------------------------------------------------
|            S                    | Set to 0 for 4KB pages, set to 1 for 4MB pages.
+--------------------------------+----------------------------------------------------------------------
|            A                    | Set to 1 by the CPU if this page is accessed
+--------------------------------+----------------------------------------------------------------------
|            D                    | Cache Disable Bit. Set to 1 to disable page caching  
+--------------------------------+----------------------------------------------------------------------
|            W                    | If this bit is set then write throught caching is enabled if no then
|                                 | write back is enabled instead
+---------------------------------+---------------------------------------------------------------------
|    U(User Supervisor Bit)       | If this is set then this  page can be accessed be all privelege ring
|                                 | levels. If it is not set then only supervisor ring levels can access
|                                 | this page.
+---------------------------------+-------------------------------------------------------------------- 
|            R                    | If this bit is set the page is readable and writeble if its not set 
|                                 | then this page is only readable. Note the WP bit in the CR0 register
|                                 | cal allow writting in all cases for supervisor.
+---------------------------------+-------------------------------------------------------------------- 
|            P                    | This bit is set if the page exists in real memory, if this page isn't
|                                 | actually available then we the kernel developer should set this bit
|                                 | to zero. If someone accesses this memory a "Page fault" will occur
|                                 | and we are expected to resolve it.
+---------------------------------+---------------------------------------------------------------------- 

o Page Fault Exception
''''''''''''''''''''''
The CPU will call the page fault interrupt ox14 when their was a problem with paging
The exception is invoked:
    - if you access a page in memory that does not have its "P(Present)" bit set.
    - invoked if you access a page that is for supervisor but you are not supervisor
    - invoked if you write to a page that is rad only and you are not supervisor.

o Hiding memory from process
''''''''''''''''''''''''''''
- If we give each process its own page directory table then we can map the memory for the process
    however we want it to be. We can make it so the process can only see its self.
- Hiding memory can be achieved be switching the page directories when moving between processes.
- All processes can access the same virtual memory addresses but they will point to different physical
    addresses

o Illusion of more memory
'''''''''''''''''''''''''
- We can pretend we have the maximum amount of memory even if we do not
- This is achieved be creating page tables that are not presented. Once a process access this non-presented
    adress a page fault will occur. We can then load the page back into memory and the process had no
    idea.
- 100MB system can act as if it access to the full 4GB on a 32 bit arch.

o Enabling Paging
'''''''''''''''''

paging_load_directory:  ; need before enable (instead kernel panic) 
         ...
         mov cr3, eax
         ...

enable_paging:
    
        ...
        mov eax, cr0
        or eax, 0x80000000
        mov cr0, eax
        ...


> The Heap is a giant memory region that can be shared in a controlled manner
> You can ask the heap for memomry and tell the heap when your done with that memory
> Heap inplementations are essentially system memory managers

Memory of an uninitialized system
---------------------------------

> Video memory takes up portions of RAM
> Hardware memory takes up portions of RAM
> Unused parts of RAM are available for user
> An array of uninitialized memory is available to us from address 0x01000000 (can be able a lot of RAM or
    very little depending on the installed memory)

Note address: 0xc0000000 is reserved this means the memory array we have at address 0x01000000 can give us
a maximum of 3.22GB for a machine with 4GB or higher installed

Simple possible heap implementation
-----------------------------------

> Start with a start address and call it a "current address" point it somewhere free i.e. (0x01000000)
> Any call to malloc gets the current address stores it in a temporary variable called "tmp"
> Now the current address is incremented by the size provided to "malloc"
> Temporary variable called "tmp" that contains the allocated address is returned
> Current_address now contains the next address for "malloc" to return when "malloc" is called again

Benefits: Easy to implementation
Negatives: Memory can never be released which may eventually lead to the system being unusable and 
requiring a reset.

Our implementation
------------------

> Will consist of a giant table which describes a giant piece of free memory in the system. This table will
describe which memory is taken, which memory is free and so on. We will call this the "entry table".

> Will have another pointer to a giant piece of free memory, this will be the actual heap data its self 
that users of "malloc" can use. We will call this the "data pool". If our heap can allocate 100 MB of ram
then the heap data pool will be 100MB in size.

> Our heap implementation will be block based, each address returned from "malloc" will be aligned to 
4096 and will at least 4096 in size.

> If you request to hace "50" bytes 4096 bytes of memory will be returned to you.

The entry table
---------------

> Composes of an array of 1 byte values that represent an entry in our heap data pool.
> Array size is calculated by taking the heap data pool size and dividing it by our block size of 4096bytes
  We are left with the total number of entries we need in our array.

    We want a 100MB heap then the math is 100MB/4096 = 25600 entries in our entry table
    ( 1 enty is 1 bytes => 25600 bytes )

    If our heap data pool is at address 0x01000000 then entry zero in out table will represent 
    addresss 0x01000000

    Entry one will represent address 0x01001000
    Entry two will represent address 0x01002000

    0x1000 = 4096 bytes

Entry structure
---------------

                        Bit structure of 8 bit entry in out table

        Upper 4 bits flags                      Lower 4 bits are the entry type
    7 [  HAS_N  ][ IS_FIRST ][   0   ][   0   ][  ET_3  ][  ET_3  ][  ET_1  ][  ET_0  ] 0

    HAS_N = Set if the entry to the right of us is part of our allocation
    IS_FIRST = Set if this is the first entry of our allocation

    *Each entry byte describes 4096 bytes of data in the heap data pool*

Entry types
-----------
> HEAP_BLOCK_TABLE_ENTRY_TAKEN - The entry is taken and the address connot be used
> HEAP_BLOCK_TABLE_ENTRY_FREE - The entry is free and may be used

The data pool
-------------

> Simply a raw flat array of thousands or millions of bytes that our heap imlementation can give to people
who need memory.

Malloc example - Memory allocataion process
-------------------------------------------

> Take the size from malloc and calculate how many blocks we need to allocate for this size. If the user
asks for 5000 bytes we weill needto allocate 8192 bytes (2 blocks)
> Check the entry table for the forst entry we can find that has a type of HEAP_BLOCK_TABLE_ENTRY_FREE,
meaning that the 4096 block that this entry represented is free for use.
> Since we require two blocks we also need to ensure the next entry is free otherwise we will need to 
discard the first block we found and look further in our table untill we find at least two free blocks 
that are next to each other.
> Once we have two blocks we mark those blocks as taken.
> We now return the absolute address that the starting block represent. Calculation

    (heap_data_pool_start_address + (block_number * block_size)


    example: we need 5000
        
    if ((5000 % 4096) == 0 )
    {
        return 5000
    }
    uint32_t new_val = 5000-(5000 % 4096);
    new_val += 4096;
    return new_val;


Step 2: Find two free blocks in the table:

    Table:
    [0xC1][0x81][0x01][0xC1]... [0x41]
    [0x01][0x00] ...            [0x00]
    [0x00][0x00][0x00]...       [0x00]

    0xC1: 0b11000001 
          - has more blocks. is first. entry taken

    0x41: ...
    0x01 - Block taken. Not first. no more blocks for this alloc.
    0x00 - Block free

Step 3: Calculate the absolute address the programmer can use

    We find free bytes in pool-arrray, for example this is index 22
 
        22 * block_size(4096) = 90122 dec. - This is our offset.    
        
    Our heap data pool starts at address 0x01000000 so we just add the 
    offset 0x01000000 + 90122  = 0x101600A - our absolute address our "malloc".

Now we can safely write our 5000 bytes to address 0x101600A

Free
----

o Calculate the block num
o Go to index and set each entry 0x00
o We know how many blocks (bit HAS_N)


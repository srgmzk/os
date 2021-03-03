o The Virtual Filesystem Layer allowa a kernel to support an infinite amount of filesystems
o The VFS allows us to abstract out low-level filesystem code
o Allows filesystem functionality to be load or unloaded to the kernel at any time

Unlimited Filesystems
''''''''''''''''''''''

o Filesystem drivers can be loaded or unloaded demand
o The programming interface to the filesystem remains the same for all filesystems

What happens when a disk get inserted?
''''''''''''''''''''''''''''''''''''''

o We poll each filesystem and ask if the disk holds a filesystem it can manage 
o We call this resolving the filesystem
o When a filesystem that can be used with the disk is found then the disk binds its self to its implementation
o All the filesystem functionality uses the same interface
o The caller of file routines does not have to care about which filesystem to use

   *Fopen communication*
   
                     fopem("0:/test.txt", "r") ->
   [ user program ] <---------------------------> [ kernel ] <------> [ path parser ] ---+ 
                     <- File Descriptor: 1             A                                 |
                                                       |        Path Root: Disk 0        |
                                                       +------- Path part test.txt <-----+
   *Fread communication*
   
                  fread(buf, 10, 1, file_desc) ->
   [ user program ] <---------------------------> [ kernel ] <------> [ FAT16 ] 
                     <- Data to buf                                                     
                                                      
                                                   

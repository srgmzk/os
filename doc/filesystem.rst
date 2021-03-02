> A fs is a structure that describes how information is laid on a disk
> Disk are not aware of files
> The OS knows the fs structure so knows how to read files from the disk

Disks
'''''

> Hard disk can be though of as just a giant array of information split into sector
> Each sector can be read into memory and is given a LBA (Logical Block Address) number
> Files do not exist on the disk
> Disks have no concept of files

Filesytem Structure
'''''''''''''''''''

> Contains raw data for files (remember the disk isn't aeare of this)
> Contains the filesystem structure header which can explain things such as how many files are on the disk,
    where the root directory is located and so on...
> The way files are laid out on disk  is different depending on the filesystem you are using for example
"FAT16", "FAT32", "NTFS", and more...
> Without filesystems we would be forced to read and write data through the use of sector numbers, 
structure woul not exist and corruption would be likely.

FAT16
'''''
> first sector in this filesystem format is the boot sector on a disk. Fields also exist in this sector that
describe the filesystem such as how many reserved sector follow this sector.

> The follows the reserved sectors these are sectors ignored be the filesystem. There is a field in the boot 
sector that specifies how many reserved sectors there are. ( Remember the operating system must ignore these
its not automatic! The disk has no idea.

> Now we hove our first file allocation table, this table contains values represent which clusters on the
disk are taken and which are free. ( A cluster is just a certain number of sectors joined together to 
represent one cluster)

> Next comes our second file allocation table it's optional though and depends on the FAT16 header in the 
boot sector.

> Now comes our root directory this explains what files/directories are in the root directory of the fs. 
Each entry a relative name that represents the file or directory name, attributes such as read only, the 
address of the first cluster representing the data on the disk. And more...

> Filanlly we have our data region, all the data is her

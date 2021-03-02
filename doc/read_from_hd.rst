
1. PCI IDE Controller

> IDE ref connect spec ATA
> IDE allows:
    1. ATA serial
    2. ATA parallel
    3. ATAPI serial
    4. ATAPI parallel
> kernel programmers don't care if the drive is serial or parallel

2. Possible Drive Types

    > Primary master
    > Primary slave
    > Secondary master
    > Secondary slave

3. ATA read example

..code ::

    int disk_read_sector(int lba, int total, void *buf)
    {
        outb(0x1F6, (lba >> 24) | 0xE0);            // Select master drive and pass pasrt of the LBA
        outb(0x1F2, total);                         // Send the total number of sectors we want to read

        outb(0x1F3, (unsigned char)(lba & 0xff));   // 
        outb(0x1F4, (unsigned char)(lba >> 8));     //  Send more of the LBA
        outb(0x1F5, (unsigned char)(lba >> 16));    //

        outb(0x1F7, 0x20);                          // 0x20 = Read command

        unsigned short *ptr = (unsigned short *)buf;
        for (int b = 0; b < total; b++)
        {
            // Wait until buffer is ready
            char c = insb(0x1F7);                   //  
            while (!(c & 0x08))                     // Poll until we are ready to read.
            {                                       // You can also use interrupts if you perfer
                c = insb(0x1F7);                    //
            }

            // Copy from hard disk to memory two bytes at a time
            for (int i = 0; i < 256; i++)           // Read two bytes at a time
            {                                       // into the buffer from the 
                *ptr = insw(0x1F0);                 // ATA controller.
                ptr++;
            }

        }
        return 0;
    }
    

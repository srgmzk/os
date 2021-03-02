Text mode
=========

- Text mode allows you to write ascii to video memory
    o You write ascii characters into memory starting at address 0xB8000 for cloured display
    o Or for monochrome display address 0xB0000
    o Each ascii character written to this memory has its pixels quivalent outputted to the monitor

- Text mode supports 16 unique colours
    #   colour    RGB         HEX
    --------------------------------
    0   Black   0 0 0       00 00 00 
    1   Blue    0 0 170     00 00 AA
    2   Green   0 170 0     00 AA 00
    ...

- No need to set individual screen pixels for printing characters
    o While in text mode the video card will take your ascii value and automatically reference it in a font
    table to output the correct pixels for the letter 'A' for example.

Each character takes up two bytes
    o Byte 0 = ascii character e.g. 'A'
    o Byte 1 = Colour code

    Example: We want to set row 0 column 0 to a black 'A'
    
    0xb8000 = 'A'
    0xb8001 = 0x00

    Example: row 0 clumn 1 to blak 'B'
    0xb8002 = 'B'
    0xb8003 = 0x00


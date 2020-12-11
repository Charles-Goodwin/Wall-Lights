#ifndef FONT_H
#define FONT_H

//const unsigned int symbol[] = PROGMEM {0xFF1F, 0x0324 0xFF31}; 
const unsigned int font_10[][3] = {0x3FF, 0x301, 0x3FF, //0
                                   0x3FF, 0x000, 0x000, //1
                                   0x3F1, 0x311, 0x31F, //2
                                   0x311, 0x311, 0x3FF, //3 
                                   0x0FF, 0x080, 0x380, //4
                                   0x31F, 0x311, 0x3F1, //5
                                   0x3FF, 0x211, 0x3F0, //6
                                   0x001, 0x001, 0x3FF, //7
                                   0x3FF, 0x311, 0x3FF, //8
                                   0x01F, 0x311, 0x3FF, //9
                                   0x300, 0x000, 0x000, //10 .
                                   0x033, 0x000, 0x000, //11 :
                                   0x3C2, 0x077, 0x10F, //12 %
                                   0x000, 0x000, 0x003, //13 '
                                   0x3FF, 0x300, 0x3FF, // Undefined
                                   0x000, 0x3FF, 0x000, // North/South
                                   0x3C0, 0x078, 0x00F, // NE/SW
                                   0x030, 0x030, 0x030, // East/West
                                   0x00F, 0x078, 0x3C0  // NW/SE
                                   }; 

const int asciiMap[] = {12, // %
                        14, // Undefined
                        13, // '
                        15, // North/South
                        16, // NE/SW  
                        17, // East/West  
                        18, // NW/SE
                        14, // Undefined
                        14, // Undefined
                        14, // Undefined
                        10, // .
                        0,  // 0
                        1,  // 1
                        2,  // 2
                        3,  // 3
                        4,  // 4
                        5,  // 5 
                        6,  // 6  
                        7,  // 7  
                        8,  // 8
                        9,  // 9
                        11  // :
                            };
                            


 #endif


#ifndef BIT_MATH
#define BIT_MATH

#define SET_BIT(REG,BIT)    (  REG |=  (1<<(BIT) ) )
#define CLR_BIT(REG,BIT)    (  REG &= ~(1<<(BIT) ) )
#define TOGGLE_BIT(REG,BIT) (  REG ^=  (1<<(BIT) ) )
#define GET_BIT(REG,BIT)    ( (REG>>(BIT) ) & 1    )

#define BYTE_CONC2(B0,B1,B2,B3,B4,B5,B6,B7)    0b##B0##B1##B2##B3##B4##B5##B6##B7
#define BYTE_CONC(B0,B1,B2,B3,B4,B5,B6,B7)     BYTE_CONC2(B0,B1,B2,B3,B4,B5,B6,B7)

#define NIBBLE_CONC2(B_0,B_1,B_2,B_3)          B_0##B_1##B_2##B_3
#define NIBBLE_CONC(B_0,B_1,B_2,B_3)           NIBBLE_CONC2(B_0,B_1,B_2,B_3)

#define NIBBLES_MERGE2(NIBBLE1,NIBBLE0)        0b##NIBBLE1##NIBBLE0
#define NIBBLES_MERGE(NIBBLE1,NIBBLE0)         NIBBLES_MERGE2(NIBBLE1,NIBBLE0)

#endif

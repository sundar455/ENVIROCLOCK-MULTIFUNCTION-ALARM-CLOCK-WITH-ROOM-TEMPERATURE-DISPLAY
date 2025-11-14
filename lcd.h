//types.h
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;
typedef unsigned long int u32;
typedef signed long int s32;
typedef float f32;
typedef double f64;

void Init_LCD(void);
void WriteLCD(u8 byte);
void cmdLCD(u8 cmd);
void charLCD(u8 asciival);
void strLCD(s8*);
void U32LCD(u32);
void S32LCD(s32);
void F32LCD(f32,u32);
void BUILDCGRAM(u8 *,u8);

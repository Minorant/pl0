#include <stdio.h>
#include <stdint.h>
#define norw       15             // 保留字数
#define txmax      100            // 标识符表项数
#define nmax       14             // max. no. of digits in numbers
#define al         10             // 标识符长度
#define amax       2047           // INT_MAX
#define levmax     3              // 嵌套最大深度
#define cxmax      2000           // 指令项数

#define nul	   0x1
#define ident      0x2
#define number     0x4
#define plus       0x8
#define minus      0x10
#define times      0x20
#define slash      0x40  // /
#define oddsym     0x80  // 奇数
#define eql        0x100 // =
#define neq        0x200 // <>
#define lss        0x400
#define leq        0x800
#define gtr        0x1000
#define geq        0x2000
#define lparen     0x4000
#define rparen     0x8000
#define comma      0x10000 // ,
#define semicolon  0x20000 // ;
#define period     0x40000 // .
#define becomes    0x80000 // :=
#define beginsym   0x100000
#define endsym     0x200000
#define ifsym      0x400000
#define thensym    0x800000
#define whilesym   0x1000000
#define dosym      0x2000000
#define callsym    0x4000000
#define constsym   0x8000000
#define varsym     0x10000000
#define procsym    0x20000000
#define elsesym    0x40000000
#define exitsym    0x80000000
#define readsym    0x100000000
#define writesym   0x200000000


enum object {
    constant, variable, proc
};

enum fct {
    lit, opr, lod, sto, cal, Int, jmp, jpc         // functions
};

typedef struct{
    enum fct f;		// function code
    long l; 		// level
    long a; 		// displacement address
} instruction;// 汇编指令
/*  lit 0, a : load constant a
    opr 0, a : execute operation a
    lod l, a : load variable l, a
    sto l, a : store variable l, a
    cal l, a : call procedure a at level l
    Int 0, a : increment t-register by a
    jmp 0, a : jump to a
    jpc 0, a : jump conditional to a       */

/* 最后读入字符 */
char ch;      
/* 最后读入单词 */         
unsigned long sym;    
/* 最后读入标识符 */ 
char id[al+1];         // 最后读入标识符
/* 最后读入数字 */ 
long num;              // 最后读入数字
/* 列计数 */
long cc;               
/* 行计数 */
long ll;               // line length
long kk, err;
/* code表idx */
long cx;               // code allocation index

char line[81];
char a[al+1];
instruction code[cxmax+1];
// 相当于建个map
char word[norw][al+1];
unsigned long wsym[norw];
unsigned long ssym[256];
/* 汇编指令 */
char mnemonic[8][3+1];
unsigned long declbegsys, statbegsys, facbegsys;
/* 标识符表 */
struct{
    char name[al+1];
    enum object kind;
    long val;
    long level;
    long addr;
}table[txmax+1];

char infilename[80];
FILE* infile;

// the following variables for block
/* 数据分配idx */
long dx;		// data allocation index
long lev;		// current depth of block nesting
/* 当前符号表idx */
long tx;		// current table index

// the following array space for interpreter
#define stacksize 50000
/* 数据栈 */
long s[stacksize];	// datastore

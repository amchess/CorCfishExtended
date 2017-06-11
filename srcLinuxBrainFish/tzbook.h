#ifndef TZBOOK_H_INCLUDED
#define TZBOOK_H_INCLUDED

#include "bitboard.h"
#include "position.h"
#include <string.h> //to control

struct TZHash2
{
    uint32_t key1;
    uint16_t key2;
    unsigned char move_number;
    unsigned char move_number2;
};
typedef struct TZHash2 TZHash2;

Bitboard last_position;
Bitboard akt_position;
int last_anz_pieces;
int akt_anz_pieces;
int search_counter;

int enabled, do_search;
int  book_move2_probability;

int keycount;
TZHash2 *tzhash2;
	

 
void initBook(char *path);
void set_book_move2_probability(int book_move2_prob);
Move probe2Move(Pos *pos);
TZHash2 *probe2(Key key);
int check_draw(Move m, Pos *pos);
Move get_move_from_draw_position(Pos *pos, TZHash2 *tz);
Move get_move(Pos *pos, TZHash2 *tz);
Move movenumber_to_move(Pos *pos, int n);	
#endif // #ifndef TZBOOK_H_INCLUDED

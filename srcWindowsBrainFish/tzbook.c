#include "tzbook.h"
#include "uci.h"
#include "movegen.h"
#include "thread.h"
#include <stdio.h>
#include "misc.h"
#include <sys/timeb.h> //?

int qsort_compare_int(const void* a, const void* b)
{
    const int int_a = *((const int*)a);
    const int int_b = *((const int*)b);

    if (int_a == int_b) return 0;
    else if (int_a < int_b) return -1;
    else return 1;
}
int keycount = 0;  
int book_move2_probability = 0;
Bitboard last_position = 0;
Bitboard akt_position = 0;
int last_anz_pieces = 0;
int akt_anz_pieces = 0;
int search_counter = 0;
int do_search = 1;  
int enabled = 0;



void initBook(char *path)
{   
    if (sizeof(path) == 0) return;

    const char *p = path;
    if (strcmp(p, "<empty>") == 0)
        return;

    FILE *fpt = fopen(p, "rb");
    if (fpt == NULL)
    {
        fprintf(stderr, "info string Could not open ", path);
        return;
    }

    if (tzhash2 != NULL)
    {
        free(tzhash2);
        tzhash2 = NULL;
    }

    fseek(fpt, 0L, SEEK_END);
    int filesize = ftell(fpt);
    fseek(fpt, 0L, SEEK_SET);

    keycount = filesize / 8;
	tzhash2 = malloc(sizeof(int)*keycount);
    
    fread(tzhash2, 1, filesize, fpt);
    fclose(fpt);

	fprintf(stderr, "info string Book loaded: ", path);

    srand((int)time(NULL));
    enabled = 1;
}


void set_book_move2_probability(int book_move2_prob)
{
    book_move2_probability = book_move2_prob;
}


Move probe2Move(Pos *pos)
{
    Move m = 0;
    if (!enabled) return m;

    akt_position = pieces();
    akt_anz_pieces = popcount(akt_position);

    if (do_search == 0)
    {
        Bitboard b = akt_position ^ last_position;
        int n2 = popcount(b);

        if (n2 > 4) do_search = 1;
        if (akt_anz_pieces > last_anz_pieces) do_search = 1;
        if (akt_anz_pieces < last_anz_pieces - 2) do_search = 1;
    }

    last_position = akt_position;
    last_anz_pieces = akt_anz_pieces;

    if (do_search)
    {
        TZHash2 *tz = probe2(pos_key());
        if (tz == NULL)
        {
            search_counter++;
            if (search_counter > 2)
            {
                do_search = 0;
                search_counter = 0;
            }
        }
        else
        {
            if (is_draw(pos))
                m = get_move_from_draw_position(pos, tz);
            else
                m = get_move(pos, tz);
        }
    }

    return m;
}


TZHash2 *probe2(Key key)
{
    uint32_t key1 = key >> 32;
    unsigned short key2 = key >> 16 & 0xFFFF;

    int start = 0;
    int end = keycount;

    for (;;)
    {
        int mid = (end + start) / 2;

        if (tzhash2[mid].key1 < key1)
            start = mid;
        else
        {
            if (tzhash2[mid].key1 > key1)
                end = mid;
            else
            {
                start = max(mid - 4, 0);
                end = min(mid + 4, keycount);
            }
        }

        if (end - start < 9)
            break;
    }

    for (int i = start; i < end; i++)
        if ((key1 == tzhash2[i].key1) && (key2 == tzhash2[i].key2))
            return &(tzhash2[i]);

    return NULL;
}

Move movenumber_to_move(Pos *pos, int n)
{
	INLINE ExtMove list[MAX_MOVES];	
	ExtMove *last = generate_legal(pos, list);
	int size=sizeof(last);
	Move mv[size];
	for(int i=0;i<size;i++){
		mv[i] = last[i].move;
	}
    qsort(mv, size, sizeof(mv[0]), qsort_compare_int);
    return mv[n];
}

int check_draw(Move m, Pos *pos)
{
	int givesCheck = gives_check(pos, pos->st, m);
    do_move(pos,m,givesCheck);   
    int draw = is_draw(pos);
    undo_move(pos,m);

    return draw;
}


Move get_move_from_draw_position(Pos *pos, TZHash2 *tz)
{
    Move m = movenumber_to_move(pos, tz->move_number);
    if (!check_draw(m, pos))
        return m;

    if (tz->move_number2 == 255)
        return m;

    m = movenumber_to_move(pos, tz->move_number2);
    if (!check_draw(m, pos))
        return m;
       
    return 0;
}


Move get_move(Pos *pos, TZHash2 *tz)
{
    Move m1 = movenumber_to_move(pos, tz->move_number);
    if ((book_move2_probability == 0) || (tz->move_number2 == 255))
        return m1;

    Move m2 = movenumber_to_move(pos, tz->move_number2);
    if ((book_move2_probability == 100) || (rand() % 100 < book_move2_probability))
        return m2;

    return m1;
}
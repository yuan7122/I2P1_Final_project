#include "scene.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_COUNTOF_FOUNDGROUND     ( 40 )
#define DEBUGPRINT_SCENE            ( false )
#define COUNOF_BACKGROUND           ( 4 )
#define MAX_COUNTOF_GROUND          ( 600 )

ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *g_background[ COUNOF_BACKGROUND ] = { NULL };
ALLEGRO_BITMAP *Ground[ MAX_COUNTOF_GROUND ] = { NULL };
ALLEGRO_BITMAP *Ground2[ MAX_COUNTOF_GROUND ] = { NULL };

int g_nBackgroundWidth = 0;
Pos g_Ground[ MAX_COUNTOF_GROUND ];
int g_nGroundCount = 0;

int FindClosestGround( int *pGroundIdx, int nGroundCount, const int x, const int nToe ) {
    int nMinY = INT_MAX;
    int nClosestGroundIdx = -1;
    for( int i = 0; i < nGroundCount; i++ ) {
        if( ( g_Ground[ pGroundIdx[ i ] ].x <= x ) && ( x <= ( g_Ground[ pGroundIdx[ i ] ].x + g_Ground[ pGroundIdx[ i ] ].nWidth ) ) ) {
            if( g_Ground[ pGroundIdx[ i ] ].y >= nToe && g_Ground[ pGroundIdx[ i ] ].y < nMinY ) {
                nMinY = g_Ground[ pGroundIdx[ i ] ].y;
                nClosestGroundIdx = pGroundIdx[ i ];
            }
        }
    }
    return nClosestGroundIdx;
}

bool IsInGroundRange( int nGroundIdx, const int x ) {
    if( ( g_Ground[ nGroundIdx ].x <= x ) && ( x <= ( g_Ground[ nGroundIdx ].x + g_Ground[ nGroundIdx ].nWidth ) ) ) {
        return true;
    }
    return false;
}

void FindGround( int *pnFoundGroundIdx, int *pnFoundCount, int x ) {
    int j = 0;
    for( int i = 0; i < g_nGroundCount; i++ ) {
        if( IsInGroundRange( i, x ) == true ) {
            pnFoundGroundIdx[ j++ ] = i;
            *pnFoundCount = j;
        }
    }
}

int CompareGround( const void *plhs, const void *prhs ) {
    Pos *pLHS = ( Pos * )plhs;
    Pos *pRHS = ( Pos * )prhs;
    if( pLHS->x < pRHS->x ) {
        return -1;
    }
    else if( pLHS->x > pRHS->x ) {
        return 1;
    }
    // pLHS->x == pRHS->x
    else {
        if( pLHS->y < pRHS->y ) {
            return -1;
        }
        else if( pLHS->y > pRHS->y ) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

void GroundSetup( void ) {

    FILE* fp = fopen( "./res/ground.txt", "r" );
    int nType = 0;
    int nPosX = 0;
    int nPosY = 0;
    while( fscanf( fp, "%d%d%d", &nType, &nPosX, &nPosY ) != EOF && g_nGroundCount <= MAX_COUNTOF_GROUND ) {
        g_Ground[ g_nGroundCount ].type = nType;
        g_Ground[ g_nGroundCount ].x = nPosX;
        g_Ground[ g_nGroundCount ].y = nPosY;
        g_nGroundCount++;
    }

    // sort ground
    qsort( g_Ground, g_nGroundCount, sizeof( Pos ), CompareGround );

    for( int i = 0; i < g_nGroundCount; i++ ) {
        if( g_Ground[ i ].type == 1 ) {
            Ground[ i ] = al_load_bitmap("./image/ground100_10.png");
            Ground2[ i ] = al_load_bitmap("./image/ground_red_100_10.png");
        }
        else if( g_Ground[ i ].type == 2 ) {
            Ground[ i ] = al_load_bitmap("./image/ground50_10.png");
            Ground2[ i ] = al_load_bitmap("./image/ground_red_50_10.png");
        }

        g_Ground[ i ].nWidth = al_get_bitmap_width( Ground[ i ] );
        g_Ground[ i ].nHeight = al_get_bitmap_height( Ground[ i ] );
    }
}


// function of menu
void menu_init(){
    font = al_load_ttf_font("./font/pirulen.ttf",12,0);
}
void menu_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = true;
}
void menu_draw(){
    al_clear_to_color(al_map_rgb(100,100,100));
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+120 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_rectangle(WIDTH/2-150, 310, WIDTH/2+150, 350, al_map_rgb(255, 255, 255), 0);
}
void menu_destroy(){
    al_destroy_font(font);
}

// function of game_scene
void game_scene_init(){
    for( int i = 0; i < COUNOF_BACKGROUND; i++ ) {
        g_background[ i ] = al_load_bitmap("./image/test3.png");
    }
    g_nBackgroundWidth = al_get_bitmap_width( g_background[ 0 ] );

    character_init( COUNOF_BACKGROUND * g_nBackgroundWidth - ( g_nBackgroundWidth ) );

    GroundSetup();
}

void game_scene_draw( void ){
    // plot background
    for( int i = 0; i < COUNOF_BACKGROUND; i++ ) {
       al_draw_bitmap( g_background[ i ], i * g_nBackgroundWidth, 0, 0 );
    }

    // plot ground
    for( int i = 0; i < g_nGroundCount; i++ ) {
       al_draw_bitmap( Ground[ i ], g_Ground[ i ].x, g_Ground[ i ].y, 0 );
    }

    // ²¾°Ê¤p©Ç
    // ..

    // find closest lower ground
    int nFoundGroundIdx[ MAX_COUNTOF_FOUNDGROUND ] = { 0 };
    int nFoundGroundCount = 0;
    FindGround( nFoundGroundIdx, &nFoundGroundCount, pchara->x );

    int nClosestGroundIdx = -1;
    int nGroundY = -1;
    nClosestGroundIdx = FindClosestGround( nFoundGroundIdx, nFoundGroundCount, pchara->x, pchara->y + pchara->height );
    if( nClosestGroundIdx != -1 ) {
        nGroundY = g_Ground[ nClosestGroundIdx ].y;
        // draw the closest lower ground
        al_draw_bitmap( Ground2[ nClosestGroundIdx ], g_Ground[ nClosestGroundIdx ].x, g_Ground[ nClosestGroundIdx ].y, 0 );
    }

    if( DEBUGPRINT_SCENE ) {
        printf( "chara x = %d, y = %d\n", pchara->x, pchara->y );
        for( int i = 0; i < nFoundGroundCount; i++ ) {
            printf( "*************************************Ground %d: x = %d, y = %d, width = %d, height = %d\n",
                    i, g_Ground[ nFoundGroundIdx[ i ] ].x, g_Ground[ nFoundGroundIdx[ i ] ].y,
                    g_Ground[ nFoundGroundIdx[ i ] ].nWidth, g_Ground[ nFoundGroundIdx[ i ] ].nHeight );
        }
    }

    // draw character
    character_draw( nGroundY );
}

/*
0         255|256          511|          |          |
  v  ++++++                       +++
++++++                    +++
                v      ++
         ++++++++++++++
 */

void game_scene_destroy(){
    // background
    for( int i = 0; i < COUNOF_BACKGROUND; i++ ) {
        al_destroy_bitmap( g_background[ i ] );
    }

    // ground
    for( int i = 0; i < g_nGroundCount; i++ ) {
        al_destroy_bitmap( Ground[ i ] );
        al_destroy_bitmap( Ground2[ i ] );
    }

    character_destory();
}

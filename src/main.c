
#include <genesis.h>
#include <resources.h>

u16 ind = TILE_USER_INDEX;
float hscroll_offset = 0;
int hscroll_offset_fore = 0;

#define ANIM_STILL 0
#define ANIM_IDLE 1
#define ANIM_WALK 2
#define ANIM_UPPER 3

Sprite* player;
int player_x = 100;
int player_y = 85;

static void handleInput(){
    u16 value = JOY_readJoypad(JOY_1);
    if (value & BUTTON_RIGHT){
        player_x += 1;
        SPR_setAnim(player, ANIM_WALK);
        SPR_setHFlip(player, TRUE);
    }
    else if (value & BUTTON_LEFT){
        player_x -= 1;
        SPR_setAnim(player, ANIM_WALK);
        SPR_setHFlip(player, FALSE);
    }
    
    if (value & BUTTON_UP){
        player_y -= 1;
        SPR_setAnim(player, ANIM_WALK);
    }
    else if (value & BUTTON_DOWN){
        player_y += 1;
        SPR_setAnim(player, ANIM_WALK);
    }

    if ( !(value & BUTTON_RIGHT) && !(value & BUTTON_LEFT) && !(value & BUTTON_UP) && !(value & BUTTON_DOWN) ) {
        SPR_setAnim(player, ANIM_IDLE);
    }

    SPR_setPosition(player, player_x, player_y);
}

int main()
{
    SPR_init();
    PAL_setPalette(PAL2, our_sprite.palette->data, DMA);
    player = SPR_addSprite(&our_sprite, player_x, player_y, TILE_ATTR(PAL2, FALSE, FALSE, TRUE));
    // SPR_setAnim(player, ANIM_UPPER);

    PAL_setPalette(PAL0, bg1.palette->data, DMA);
    VDP_drawImageEx(BG_B, &bg1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, -2, FALSE, TRUE);
    ind += bg1.tileset->numTile;

    PAL_setPalette(PAL1, fg1.palette->data, DMA);
    VDP_drawImageEx(BG_A, &fg1, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, ind), 0, -2, FALSE, TRUE);
    ind += fg1.tileset->numTile;

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    
    while(1)
    {
        VDP_setHorizontalScroll(BG_B, hscroll_offset);
        // hscroll_offset -= .5;

        VDP_setHorizontalScroll(BG_A, hscroll_offset_fore);
        // hscroll_offset_fore -= 2;

        handleInput();
        SPR_update();
        
        SYS_doVBlankProcess();
    }
    return (0);
}

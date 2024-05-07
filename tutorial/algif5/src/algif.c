#include "algif.h"
#include <allegro5/allegro_primitives.h>
#include <math.h>

/* Renders the next frame in a GIF animation to the given position.
 * You need to call this in order on the same destination for frames
 * [0..gif->frames_count - 1] to properly render all the frames in the GIF.
 * The current target bitmap should have the same height as the animation,
 * and blending should be set to fully copy RGBA.
 */
void algif_render_frame(ALGIF_ANIMATION *gif, int frame, int xpos, int ypos) {
    int x, y, w, h;
    ALGIF_FRAME *f = &gif->frames[frame];
    ALGIF_PALETTE *pal;
    if (frame == 0) {
        al_draw_filled_rectangle(xpos, ypos, xpos + gif->width,
              ypos + gif->height, al_map_rgba_f(0, 0, 0, 0));
    }
    else {
        ALGIF_FRAME *p = &gif->frames[frame - 1];
        if (p->disposal_method == 2) {
            al_draw_filled_rectangle(xpos + p->xoff, ypos + p->yoff,
                xpos + p->xoff + p->bitmap_8_bit->w,
                ypos + p->yoff + p->bitmap_8_bit->h,
                al_map_rgba_f(0, 0, 0, 0));
        }
        else if (p->disposal_method == 3 && gif->store) {
            al_draw_bitmap_region(gif->store, xpos + p->xoff, ypos + p->yoff,
                p->bitmap_8_bit->w,
                p->bitmap_8_bit->h,
                xpos + p->xoff, ypos + p->yoff, 0);
            al_destroy_bitmap(gif->store);
            gif->store = NULL;
        }
    }
    w = f->bitmap_8_bit->w;
    h = f->bitmap_8_bit->h;
    if (f->disposal_method == 3) {
        if (gif->store)
            al_destroy_bitmap(gif->store);
        gif->store = al_clone_bitmap(al_get_target_bitmap());
    }
    pal = &gif->frames[frame].palette;
    if (pal->colors_count == 0)
        pal = &gif->palette;

    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            int c = f->bitmap_8_bit->data[x + y * f->bitmap_8_bit->w];
            if (c != f->transparent_index) {
                al_draw_pixel(xpos + f->xoff + x, ypos + f->yoff + y,
                    al_map_rgb(pal->colors[c].r, pal->colors[c].g,
                        pal->colors[c].b));
            }
        }
    }
}

ALGIF_ANIMATION *algif_load_animation_f(ALLEGRO_FILE *file) {
    ALGIF_ANIMATION *gif = algif_load_raw(file);

    if (!gif)
        return gif;

    al_init_primitives_addon();

    gif->duration = 0;
    ALLEGRO_STATE s;
    al_store_state(&s, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER);
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);
    int n = gif->frames_count;
    int i;
    for (i = 0; i < n; i++) {
        ALGIF_FRAME *f = &gif->frames[i];
        f->rendered = al_create_bitmap(gif->width, gif->height);
        al_set_target_bitmap(f->rendered);
        algif_render_frame(gif, i, 0, 0);
        gif->duration += f->duration;
    }

    al_restore_state(&s);
    return gif;
}

ALGIF_ANIMATION *algif_load_animation(char const *filename) {
    ALLEGRO_FILE *file = al_fopen(filename, "rb");
    return algif_load_animation_f(file);
}
ALGIF_ANIMATION *algif_new_gif(char const *filename, int loop) {
    ALGIF_ANIMATION *gif = algif_load_animation(filename);
    gif->loop = loop;
    gif->start_time = 0;
    gif->display_index = 0;
    gif->done = false;
    return gif;
}
ALLEGRO_BITMAP *algif_get_bitmap(ALGIF_ANIMATION *gif, double seconds) {
    if(gif->done || gif->start_time == 0) {
        gif->start_time = seconds;
        gif->display_index = 0;
        gif->done = false;
    }
    seconds -= gif->start_time;
    double gif_duration = gif->duration / 100.0;
    // no loop
    if(gif->loop == -1 && seconds > gif_duration ){
        gif->done = true;
        gif->start_time = 0;
        gif->display_index = 0;
        return gif->frames[0].rendered;
    }
    // loop n times
    if(gif->loop > 0 && seconds > gif_duration * gif->loop){
        gif->done = true;
        gif->start_time = 0;
        gif->display_index = 0;
        return gif->frames[0].rendered;
    }
    seconds = fmod(seconds, gif_duration);
    int n = gif->frames_count;
    double d = 0;
    int i;
    for (i = 0; i < n; i++) {
        d += gif->frames[i].duration / 100.0;
        if (seconds < d){
            gif->display_index = i;
            return gif->frames[i].rendered;
        }

    }
    return gif->frames[0].rendered;
}

ALLEGRO_BITMAP *algif_get_frame_bitmap(ALGIF_ANIMATION *gif, int i) {
    return gif->frames[i].rendered;
}

double algif_get_frame_duration(ALGIF_ANIMATION *gif, int i) {
    return gif->frames[i].duration / 100.0;
}

#include "header/threat.h"

threat::threat() {
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    come_back_time = 0;
    on_ground = true;
    frame = 0;

    animation_a = 0;
    animation_b = 0;
    input_type.left = 1;
    type_move = STATIC_THREAT;

    object_name = "threat";
}

threat::~threat() {
//    Free();
}

bool threat::LoadImg(string path, SDL_Renderer* screen) {
    bool ret = gameObject::LoadImg(path, screen);
    if (ret) {
        width_frame = rect.w / THREAT_FRAME_NUMBER;
        height_frame = rect.h;
    }
    return ret;
}

void threat::set_clips() {
    if (width_frame > 0 && height_frame > 0) {
        for (int i = 0; i < THREAT_FRAME_NUMBER; i++) {
            frame_clip[i].x = i * width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void threat::Render(SDL_Renderer *screen) {
    if (come_back_time == 0) {
        rect.x = x_pos - map_x;
        rect.y = y_pos - map_y;
        frame++;
        if (frame >= THREAT_FRAME_NUMBER) frame = 0;


        SDL_Rect* currentClip = &frame_clip[frame];
        SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};
        SDL_RenderCopy(screen, object, currentClip, &renderQuad);
    }
}

void threat::DoThreat(Map &map_data) {
    if (come_back_time == 0) {
        x_val = 0;
        y_val += GRAVITY_SPEED;
        if (y_val >= MAX_FALL_SPEED) y_val = MAX_FALL_SPEED;

        if (input_type.left == 1) {
            x_val -= PLAYER_SPEED;
        } else if (input_type.right == 1) {
            x_val += PLAYER_SPEED;
        }

        CheckToMap(map_data);
    } else if (come_back_time > 0) {
        come_back_time--;
        if (come_back_time == 0) {
            InitThreat();
        }
    }
}

void threat::CheckToMap(Map &map_data) {

        int x1 = 0;
        int x2 = 0;
        int y1 = 0;
        int y2 = 0;

        // Check horizontal
        int height_min = min(height_frame, TILE_SIZE);
        x1 = (x_pos + x_val) / TILE_SIZE;
        x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;

        y1 = y_pos / TILE_SIZE;
        y2 = (y_pos + height_min - 1) / TILE_SIZE;

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
            if (x_val > 0) {
                if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
                    x_pos = x2 * TILE_SIZE;
                    x_pos -= width_frame + 1;
                    x_val = 0;
                }
            } else if (x_val < 0) {
                if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE) {
                    x_pos = (x1 + 1) * TILE_SIZE;
                    x_val = 0;
                }
            }
        }

        // Check vertical
        int width_min = min(width_frame, TILE_SIZE);
        x1 = x_pos / TILE_SIZE;
        x2 = (x_pos + width_min) / TILE_SIZE;

        y1 = (y_pos + y_val) / TILE_SIZE;
        y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
            if (y_val > 0) {
                if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
                    y_pos = y2 * TILE_SIZE;
                    y_pos -= (height_frame + 1);
                    y_val = 0;
                    on_ground = true;
                }
            } else if (y_val < 0) {
                if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
                    y_pos = (y1 + 1) * TILE_SIZE;
                    y_val = 0;
                }
            }
        }

        x_pos += x_val;
        y_pos += y_val;

        if (x_pos < 0) {
            x_pos = 0;
        } else if (x_pos + width_frame > MAX_MAP_X * TILE_SIZE) {
            x_pos = MAX_MAP_X * TILE_SIZE - width_frame;
        }

}

void threat::InitThreat() {
    x_val = 0;
    y_val = 0;

    if (x_pos > 4 * TILE_SIZE) {
        x_pos -= 4 * TILE_SIZE;
        animation_a -= 4 * TILE_SIZE;
        animation_b -= 4 * TILE_SIZE;
    } else {
        x_pos = 0;
    }
    y_pos = 0;
    come_back_time = 0;
    input_type.left = 1;
}

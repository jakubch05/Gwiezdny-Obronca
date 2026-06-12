#pragma once

struct GameConfig {
    static constexpr int WINDOW_WIDTH = 1280;
    static constexpr int WINDOW_HEIGHT = 720;

    static constexpr int ENEMY_ROWS = 4;
    static constexpr int ENEMY_COLS = 12;
    static constexpr float ENEMY_BASE_SPEED = 100.0f;

    static constexpr int PLAYER_LIVES = 3;
    static constexpr float PLAYER_SPEED = 400.0f;

    static constexpr int SCORE_PER_ENEMY = 100;
    static constexpr int SCORE_PER_BONUS = 50;
};

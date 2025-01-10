#include "splashkit.h"
#include "particle_system.h"
#include <vector>
#include <cmath>

// Player structure
struct Player
{
    float x, y;
    float dx, dy;
    float radius;
    bool is_jumping;
};

struct Lightning
{
    bool active = false;
    double start_time = 0;
    std::vector<std::pair<double, double>> segments;
};

std::vector<ParticleSystem> snow_systems;
std::vector<ParticleSystem> rain_systems;
Lightning lightning;
double next_lightning_time = 0;

// Initialize player
void initialize_player(Player &player)
{
    player.x = 400;
    player.y = 500;
    player.dx = 0;
    player.dy = 0;
    player.radius = 20;
    player.is_jumping = false;
}

// Update player movement
void update_player(Player &player, float delta_time)
{
    // Apply gravity
    player.dy += 0.5f * delta_time * 60;

    // Horizontal movement
    if (key_down(LEFT_KEY))
        player.dx = -5;
    else if (key_down(RIGHT_KEY))
        player.dx = 5;
    else
        player.dx = 0;

    // Jumping
    if (key_typed(SPACE_KEY) && !player.is_jumping)
    {
        player.dy = -10;
        player.is_jumping = true;
    }

    // Update position
    player.x += player.dx * delta_time * 60;
    player.y += player.dy * delta_time * 60;

    // Check for ground collision
    if (player.y >= 500)
    {
        player.y = 500;
        player.dy = 0;
        player.is_jumping = false;
    }

    // Keep player within window bounds
    if (player.x < player.radius)
        player.x = player.radius;
    else if (player.x > 800 - player.radius)
        player.x = 800 - player.radius;
}

// Render player
void render_player(const Player &player)
{
    fill_circle(COLOR_RED, player.x, player.y, player.radius);
}

// Initialize snow particle systems
void initialize_snow()
{
    for (int i = 0; i < 800; i += 100)
    {
        ParticleSystem snow_system;
        initialize_particle_system(snow_system, i, 0);
        set_max_particles(snow_system,1000);
        set_emission_rate(snow_system, 30);
        set_particle_lifespan(snow_system, 135);
        set_particle_size(snow_system, 2);
        set_particle_color(snow_system, COLOR_WHITE);
        set_emission_angle(snow_system, 90, 100);
        set_emission_speed(snow_system, 1);
        set_gravity(snow_system,0.04f);
        snow_systems.push_back(snow_system);
    }
}

// Initialize rain particle systems
void initialize_rain()
{
    for (int i = 0; i < 800; i += 100)
    {
        ParticleSystem rain_system;
        initialize_particle_system(rain_system, i, 0);
        set_max_particles(rain_system,1000);
        set_emission_rate(rain_system, 50);
        set_particle_lifespan(rain_system, 80);
        set_particle_size(rain_system, 2);
        set_particle_color(rain_system, COLOR_BLUE);
        set_emission_angle(rain_system, 90, 150);
        set_emission_speed(rain_system, 3);
        set_gravity(rain_system,0.1f);
        rain_systems.push_back(rain_system);
    }
}

// Generate random lightning segments
void generate_lightning()
{
    lightning.active = true;
    lightning.start_time = timer_ticks("lightning_timer");
    lightning.segments.clear();

    double x = rnd(800);
    double y = 0; // Start at the top of the screen
    lightning.segments.push_back({x, y});

    for (int i = 0; i < 10; i++)
    {
        double next_x = x + rnd() * 50 - 25; // Random horizontal movement
        double next_y = y + rnd() * 50;      // Downward movement

        if (next_y > 500) break; // Stop if it reaches the ground

        lightning.segments.push_back({next_x, next_y});
        x = next_x;
        y = next_y;
    }
}

// Render lightning
void render_lightning()
{
    if (!lightning.active) return;

    if (timer_ticks("lightning_timer") - lightning.start_time > 500)
    {
        lightning.active = false;
        return;
    }

    for (size_t i = 0; i < lightning.segments.size() - 1; i++)
    {
        double x1 = lightning.segments[i].first;
        double y1 = lightning.segments[i].second;
        double x2 = lightning.segments[i + 1].first;
        double y2 = lightning.segments[i + 1].second;

        draw_line(rgba_color(255, 255, 255, 200), x1, y1, x2, y2);
    }

    // Glow effect
    fill_rectangle(rgba_color(255, 255, 255, 50), 0, 0, 800, 600);
}

// Render environment with gradient, mountains, trees, and bushes
void render_environment()
{
    // Draw gradient sky
    for (int i = 0; i < 600; i++)
    {
        int intensity = 25 + static_cast<int>((112 - 25) * (i / 600.0));
        draw_line(rgb_color(intensity, intensity, 112), 0, i, 800, i);
    }

    // Draw ground
    draw_rectangle(COLOR_BROWN, 0, 500, 800, 100);

    // Draw mountains
    for (int i = -400; i < 1200; i += 600)
    {
        fill_triangle(COLOR_GRAY, i, 500, i + 300, 200, i + 600, 500);
    }

    // Draw trees
    for (int i = 0; i < 800; i += 150)
    {
        fill_rectangle(COLOR_DARK_GREEN, i + 50, 450, 20, 50); 
        fill_circle(COLOR_GREEN, i + 60, 440, 30);            
        fill_circle(COLOR_DARK_GREEN, i + 100, 480, 15);      
    }
}

int main()
{
    // Open a new window for rendering
    open_window("Seasons", 800, 600);

    // Create player
    Player player;
    initialize_player(player);

    // Initialize particle systems
    initialize_snow();
    initialize_rain();

    // Initialize timer for lightning
    create_timer("lightning_timer");
    start_timer("lightning_timer");

    int level = 1; 

    // Game loop
    while (!window_close_requested("Seasons"))
    {
        process_events();

        // Render environment
        render_environment();

        // Generate lightning every 3-8 seconds
        if (timer_ticks("lightning_timer") > next_lightning_time)
        {
            next_lightning_time = timer_ticks("lightning_timer") + (3 + rnd() * 5) * 1000;
            generate_lightning();
        }

        // Render lightning
        render_lightning();

        // Update player
        update_player(player, 1.0f / 60.0f);

        if (level == 1) 
        {
            for (auto &system : snow_systems)
            {
                update_particle_system(system, 1.0f / 60.0f);
                spawn_particle(system);
                render_particle_system(system);
            }
        }
        else if (level == 2) // Rain Season
        {
            for (auto &system : rain_systems)
            {
                update_particle_system(system, 1.0f / 60.0f);
                spawn_particle(system);
                render_particle_system(system);
            }
        }

        // Render player
        render_player(player);

        // Check for level progression or regression
        if (player.x >= 780 && level < 2)
        {
            level++;
            player.x = 20; // Reset player position for next level
        }
        else if (player.x <= 20 && level > 1)
        {
            level--;
            player.x = 780; // Reset player position for previous level
        }

        // Refresh the screen
        refresh_screen(60); // 60 FPS
    }

    // Close the window
    close_window("Seasons");

    return 0;
}

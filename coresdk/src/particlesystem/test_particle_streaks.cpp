#include "splashkit.h"
#include "particle_system.h"

int main()
{
    // Open a new window for rendering
    open_window("Particle System Test", 1000, 800);

    // Create multiple particle systems for demonstration
    ParticleSystem system1, system2, system3, system4, system5, system6;

    // Initialize particle systems at different positions
    initialize_particle_system(system1, 100, 100); // Top-left corner
    initialize_particle_system(system2, 300, 100); // Top-center
    initialize_particle_system(system3, 500, 100); // Top-right corner
    initialize_particle_system(system4, 100, 400); // Bottom-left corner
    initialize_particle_system(system5, 300, 400); // Bottom-center
    initialize_particle_system(system6, 500, 400); // Bottom-right corner

    // Configure particle systems
    // System 1: Basic particles
    set_emission_rate(system1, 5);
    set_particle_lifespan(system1, 100);
    set_particle_size(system1, 5);
    set_particle_color(system1, COLOR_GREEN);
    set_emission_angle(system1, 0, 180); // Half-circle emission
    set_emission_speed(system1, 3);

    // System 2: Fast particles with a wide spread
    set_emission_rate(system2, 10);
    set_particle_lifespan(system2, 50);
    set_particle_size(system2, 8);
    set_particle_color(system2, COLOR_BLUE);
    set_emission_angle(system2, 90, 90); // Narrow spread upwards
    set_emission_speed(system2, 6);

    // System 3: Large slow particles
    set_emission_rate(system3, 3);
    set_particle_lifespan(system3, 200);
    set_particle_size(system3, 15);
    set_particle_color(system3, COLOR_YELLOW);
    set_emission_angle(system3, 270, 30); // Downward emission
    set_emission_speed(system3, 2);

    // System 4: Rotating emitter
    set_emission_rate(system4, 5);
    set_particle_lifespan(system4, 120);
    set_particle_size(system4, 6);
    set_particle_color(system4, COLOR_RED);
    set_emission_angle(system4, 0, 360); // Full-circle emission
    set_emission_speed(system4, 4);

    // System 5: Particles with decay
    set_emission_rate(system5, 8);
    set_particle_lifespan(system5, 150);
    set_particle_size(system5, 10);
    set_particle_color(system5, COLOR_PURPLE);
    set_emission_angle(system5, 45, 45); // Diagonal spread
    set_emission_speed(system5, 5);
    set_decay_velocity(system5, 0.02f);

    // System 6: Gravity-enabled particles
    set_emission_rate(system6, 6);
    set_particle_lifespan(system6, 100);
    set_particle_size(system6, 7);
    set_particle_color(system6, COLOR_ORANGE);
    set_emission_angle(system6, 90, 60); // Upwards with spread
    set_emission_speed(system6, 4);
    set_gravity(system6, 0.1f);

    // Game loop
    while (!window_close_requested("Particle System Test"))
    {
        process_events();

        // Clear the screen
        clear_screen(COLOR_BLACK);

        // Update all particle systems
        update_particle_system(system1, 1.0f / 60.0f);
        update_particle_system(system2, 1.0f / 60.0f);
        update_particle_system(system3, 1.0f / 60.0f);
        update_particle_system(system4, 1.0f / 60.0f);
        update_particle_system(system5, 1.0f / 60.0f);
        update_particle_system(system6, 1.0f / 60.0f);

        // Spawn particles for all systems
        spawn_particle(system1);
        spawn_particle(system2);
        spawn_particle(system3);
        spawn_particle(system4);
        spawn_particle(system5);
        spawn_particle(system6);

        // Render all particle systems
        render_particle_system(system1);
        render_particle_system(system2);
        render_particle_system(system3);
        render_particle_system(system4);
        render_particle_system(system5);
        render_particle_system(system6);

        // Refresh the screen
        refresh_screen(60); // 60 FPS
    }

    // Close the window
    close_window("Particle System Test");

    return 0;
}

/*
This is the test for the particle system.
*/

#include "particle_system.h"
#include "splashkit.h"

int main(){
    open_window("Particle System Test",600,500);

     // Declare and initialize the particle system
    ParticleSystem ps;
    initialize_particle_system(ps, 400, 300); // Initial position of the emitter


    enable_streaks(ps,true,COLOR_ORANGE_RED,40);
    
    // Set the default particle size
    set_particle_size(ps, 1.5f); // Set particle size 
    set_particle_lifespan(ps,500); // set the lifespan of a particle
    set_max_particles(ps,10000);
    set_emission_angle(ps,90.0f,180.0f);  // set the emission angle and spread
    set_decay_velocity(ps, 3.0f); // Adjust this value for faster or slower decay

    set_gravity(ps, 0.1f); // Adjust gravity force as needed


    set_particle_color(ps,COLOR_ORANGE_RED);
    set_emission_speed(ps,8);
    //enable_particle_glow(ps,true);

    while (!window_close_requested("Particle System Demo"))
    {
        process_events();
        // Update last position before moving the emitter
        ps.last_x = ps.emitter_x;
        ps.last_y = ps.emitter_y;

        // Update streak history based on movement
        update_streak_history(ps);

        // Spawn particles continuously
        spawn_particle(ps);

        // Update the particle system
        update_particle_system(ps, 1.0f / 60.0f);
        // Render the particle system
        clear_screen(COLOR_BLACK);
        
        render_particle_system(ps);
        refresh_screen(60);
    }

    close_window("Particle System Demo");
    return 0;
}
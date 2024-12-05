#include "particle_system.h"
#include <cmath>

// Initialize the particle system
void initialize_particle_system(ParticleSystem &system, double x, double y)
{
    system.emitter_x = x;
    system.emitter_y = y;
    
    system.default_particle_size = 5.0f; // Default size for particles
    system.emission_angle = 0.0f;       // Default angle (0 degrees, pointing right)

    system.last_x = x; // Initialize last position 
    system.last_y = y; // Initialize last position
    system.add_streaks=false;
    system.streak_color=COLOR_WHITE;
    system.streak_index = 0;
    system.max_active_particles = 100;       // Default to 100 particles
    system.decay_velocity = 0.01f;             // Default decay rate
    system.gravity = 0.0f;                     // Default gravity force
    system.gravity_enabled = false;           // Gravity disabled by default


    for (int i = 0; i < STREAK_HISTORY; ++i)
    {
        system.streak_positions[i][0] = x;
        system.streak_positions[i][1] = y;
    }

    // Initialize all particles as inactive
    for (int i = 0; i < MAX_PARTICLES; ++i)
    {
        system.particles[i].is_active = false;
    }
}

// Spawn a new particle
void spawn_particle(ParticleSystem &system)
{
    int active_count = 0;

    // Count the number of currently active particles
    for (int i = 0; i < MAX_PARTICLES; ++i)
    {
        if (system.particles[i].is_active)
        {
            active_count++;
        }
    }

    // Spawn new particles only if the active count is less than the user-defined maximum
    if (active_count < system.max_active_particles)
    {
        int particles_to_spawn = system.emission_rate;

        for (int i = 0; i < MAX_PARTICLES && particles_to_spawn; ++i)
        {
            if (!system.particles[i].is_active)
            {
                // Activate and initialize the particle
                system.particles[i].is_active = true;
                system.particles[i].x = system.emitter_x;
                system.particles[i].y = system.emitter_y;


                // Randomize angle within spread
                float random_offset = rnd() * system.spread - (system.spread / 2.0f); // ±spread/2
                float angle_in_radians = (system.emission_angle + random_offset) * (PI / 180.0f);

                // Calculate velocity using the randomized angle
                float speed = system.speed;
                system.particles[i].dx = cos(angle_in_radians) * speed;
                system.particles[i].dy = sin(angle_in_radians) * speed;

                system.particles[i].lifespan = system.default_particle_lifespan;
                system.particles[i].size = system.default_particle_size; // Set the size to the user-defined value
                system.particles[i].particle_color = system.default_particle_color;
                break;
            }
        }
    }
}


// Update the particle system
void update_particle_system(ParticleSystem &system, float delta_time)
{
    for (int i = 0; i < MAX_PARTICLES; ++i)
    {
        if (system.particles[i].is_active)
        {
            // Update particle position
            system.particles[i].x += system.particles[i].dx * delta_time * 60; // Normalize for frame rate
            system.particles[i].y += system.particles[i].dy * delta_time * 60;

            // Apply decay to velocity
            if (system.decay_velocity > 0.0f)
            {
                system.particles[i].dx *= (1.0f - system.decay_velocity * delta_time);
                system.particles[i].dy *= (1.0f - system.decay_velocity * delta_time);
            }

            // Apply gravity
            if (system.gravity_enabled)
            {
                system.particles[i].dy += system.gravity * delta_time * 60;
            }

            // Decrease lifespan
            system.particles[i].lifespan -= delta_time * 60;

            // Deactivate particle if its lifespan is over
            if (system.particles[i].lifespan <= 0)
            {
                system.particles[i].is_active = false;
            }
        }
    }
}


// Render the particle system
void render_particle_system(const ParticleSystem &system)
{
    // to add streaks if streaks are enabled
     if (system.add_streaks)
    {
        for (int i = 0; i < STREAK_HISTORY - 1; ++i)
        {
            // Get the current and next positions from history
            int current_index = (system.streak_index - i + STREAK_HISTORY) % STREAK_HISTORY;
            int next_index = (system.streak_index - i - 1 + STREAK_HISTORY) % STREAK_HISTORY;

            float x1 = system.streak_positions[current_index][0];
            float y1 = system.streak_positions[current_index][1];
            float x2 = system.streak_positions[next_index][0];
            float y2 = system.streak_positions[next_index][1];

            // Calculate the distance between the points
            float dx = x2 - x1;
            float dy = y2 - y1;
            float distance = sqrt(dx * dx + dy * dy);

            // Skip segments with large distances (to prevent the straight line artifact)
            if (distance > 50.0f) // Threshold for skipping outliers
            {
                continue;
            }

            // Determine the number of intermediate circles
            int steps = static_cast<int>(distance / 2.0f); // Smaller value for tighter spacing
            float step_x = dx / (steps > 0 ? steps : 1);
            float step_y = dy / (steps > 0 ? steps : 1);

            for (int j = 0; j <= steps; ++j)
            {
                float segment_x = x1 + step_x * j;
                float segment_y = y1 + step_y * j;

                // Calculate thickness and transparency (thicker and more opaque near the emitter)
                float thickness = 8.0f * (1.0f - static_cast<float>(i) / STREAK_HISTORY);
                int alpha = static_cast<int>(system.set_streak_transparency * (1.0f - static_cast<float>(i) / STREAK_HISTORY));

                color faded_color = rgba_color(
                    red_of(system.streak_color),
                    green_of(system.streak_color),
                    blue_of(system.streak_color),
                    alpha);

                // Render the circle
                fill_circle(faded_color, segment_x, segment_y, thickness);
            }
        }
    }

    // Rendering the particles
    for (int i = 0; i < MAX_PARTICLES; ++i)
    {
    if (system.particles[i].is_active)
    {
        // Add Godot-like glow rendering for particles with glow_enabled = true
        if (system.particles[i].glow_enabled)
        {
            // Create multiple layers of glow to simulate Godot-style glow
            for (int glow_layer = 0; glow_layer < 3; ++glow_layer) // More layers for a smoother gradient
            {
                float glow_size = system.particles[i].size * (1.5f + glow_layer * 0.8f); // Gradually increase size
                int glow_alpha = static_cast<int>(200 / (glow_layer + 1)); // Stronger inner glow, softer outer layers

                color glow_color = rgba_color(
                    (red_of(system.particles[i].particle_color) + 255) / 2, // Blend with white
                    (green_of(system.particles[i].particle_color) + 255) / 2,
                    (blue_of(system.particles[i].particle_color) + 255) / 2,
                    glow_alpha);

                // Draw the glow layer
                fill_circle(glow_color, system.particles[i].x, system.particles[i].y, glow_size);
            }
        }

        // Draw the actual particle
        fill_circle(system.particles[i].particle_color, system.particles[i].x, system.particles[i].y, system.particles[i].size);
    }
}

}

// for enabling streaks and to set color
void enable_streaks(ParticleSystem &system, bool add_streaks = false, color streak_color = COLOR_WHITE, int transparency)
{
    system.add_streaks = add_streaks;
    system.streak_color = streak_color;
    system.set_streak_transparency=transparency;
}

void update_streak_history(ParticleSystem &system)
{
    // Calculate distance between the current emitter position and the last history entry
    float dx = system.emitter_x - system.streak_positions[system.streak_index][0];
    float dy = system.emitter_y - system.streak_positions[system.streak_index][1];
    float distance = sqrt(dx * dx + dy * dy);

    // Update history only if the distance exceeds the threshold
    if (distance > 5.0f) // Threshold for significant movement
    {
        system.streak_positions[system.streak_index][0] = system.emitter_x;
        system.streak_positions[system.streak_index][1] = system.emitter_y;
        system.streak_index = (system.streak_index + 1) % STREAK_HISTORY;
    }
}

// helper function to enable glow to individual particles
void enable_particle_glow(ParticleSystem &system, bool enable = false)
{
    for (int i = 0; i < MAX_PARTICLES; ++i)
    {
        system.particles[i].glow_enabled = enable;
    }
}

// setter function for setting the particle size
void set_particle_size(ParticleSystem &system, float size)
{
    system.default_particle_size = size;
}

// setter function for setting the particle lifespan
void set_particle_lifespan(ParticleSystem &system, int lifespan){
    system.default_particle_lifespan=lifespan;
}

// setter function for setting the particle emission angle
void set_particle_color(ParticleSystem &system, color set_color){
    system.default_particle_color=set_color;
}

// setter function for setting the particle emission angle
void set_emission_angle(ParticleSystem &system, float angle, float spread=0.0f)
{
    system.emission_angle = angle; 
    system.spread=spread; 
}

// setter function for setting the particle emission speed
void set_emission_speed(ParticleSystem &system, int speed=4){
    system.speed=speed;
}

// function to set the maximum particles 
void set_max_particles(ParticleSystem &system, int max_particles)
{
    system.max_active_particles = max_particles; 
}

// function to set the decay velocity
void set_decay_velocity(ParticleSystem &system, float decay_rate)
{
    system.decay_velocity = decay_rate; 
}

// set the gravity
void set_gravity(ParticleSystem &system, float gravity_force)
{
    system.gravity = gravity_force;
    system.gravity_enabled = true; 
}

// function to turn off the gravity 
void disable_gravity(ParticleSystem &system)
{
    system.gravity_enabled = false; 
}

// set the emission rate
void set_emission_rate(ParticleSystem &system, int rate)
{
    system.emission_rate = rate; // Set the number of particles emitted per frame
}
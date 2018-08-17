/**
 * @header  animations
 * @author  Andrew Cain
 * @brief   Animations in SplashKit can be used to move between cells in
 *          bitmaps and sprites. Each animation generates a number sequence
 *          that can then be used when drawing bitmaps.
 *
 * @attribute group  animations
 * @attribute static animation
 */

#ifndef animations_h
#define animations_h

#include "types.h"
#include "drawing_options.h"

#include <string>
using std::string;

namespace splashkit_lib
{
    /**
     * Load animation details from an animation frames file.
     *
     * @param name          The name of the `animation_script`.
     * @param filename      The file to load the `animation_script` from.
     *
     * @returns Returns the newly loaded `animation_script`.
     *
     * @attribute class animation_script
     * @attribute constructor true
     */
    animation_script load_animation_script(const string &name, const string &filename);

    /**
     * Frees loaded animation frames data. Use this when you will no
     * longer be using the animation for any purpose, including within
     * sprite.
     *
     * @param script_to_free The `animation_script` to be freed.
     *
     * @attribute class     animation_script
     * @attribute self      script_to_free
     * @attribute destructor true
     */
    void free_animation_script(animation_script script_to_free);

    /**
     * Frees loaded `animation_script` data. Use this when you will no
     * longer be using the animation for any purpose, including within
     * sprite.
     *
     * @param name          The name of the `animation_script` to be freed.
     *
     * @attribute suffix    with_name
     *
     * @attribute static  animation_script
     */

    void free_animation_script(const string &name);

    /**
     * Frees all loaded `animation_script`s.
     *
     * @attribute static    animation_script
     * @attribute method    free_all
     */
    void free_all_animation_scripts();

    /**
     * Loads and returns a `animation_script`. The supplied filename is
     * used to locate the `animation_script` to load. The supplied name
     * indicates the name to use to refer to this in SplashKit. The
     * `animation_script` can then be retrieved by passing this name to
     * the animation_script_named method.
     *
     * @param name          Indicates the name used to locate the animation_script to load
     *
     * @returns Returns the newly loaded `animation_script`.
     *
     * @attribute static  animation_script
     */
    animation_script animation_script_named(const string &name);

    /**
     * Determines if SplashKit has animation frames loaded for the
     * supplied name. This checks against all loaded animation frames,
     * those loaded without a name are assigned the filename as a default.
     *
     * @param name          The name of the animation script to look for.
     * @returns Returns the `bool` that denotes if the animation has the `animation_script`
     *
     * @attribute static  animation_script
     */
    bool has_animation_script(const string &name);

    /**
     * Retuns the name of an `animation_script`.
     *
     * @param script        The `animation_script` to return the name of.
     * @returns Returns a `string` that is the name of the animation script passed to the method.
     *
     * @attribute class  animation_script
     * @attribute getter name
     * @attribute self   script
     */
    string animation_script_name(animation_script script);

    /**
     * Returns whether an `animation_script` has been loaded with the
     * given name.
     *
     * @param script        The `animation_script` to check.
     * @param name          The name of the `animation_script` to look for.
     * @returns Returns a `bool` that denotes whether the `animation_script` has been loaded.
     *
     * @attribute class  animation_script
     * @attribute self   script
     */
    bool has_animation_named(animation_script script, const string &name);

    /**
     * Returns the number of `animation`s within an `animation_script`.
     *
     * @param script        The `animation_script` to count the animations in.
     *
     * @returns Returns an `int` equal to the total number of animations in the script.
     *
     * @attribute class     animation_script
     * @attribute getter    animation_count
     * @attribute self      script
     */
    int animation_count(animation_script script);


    /**
     * Creates an animation from a `animation_script`. This may play a
     * sound effect if the animation is set to play a sound effect on
     * its first frame.
     *
     * @param script        The `animation_script` to create the `animation` from
     * @param name          The name for the new `animation`
     * @param with_sound    Denotes whether the `animation` should play audio.
     * @returns Returns the newly created `animation`.
     *
     * @attribute class     animation_script
     * @attribute self      script
     * @attribute method    create_animation
     *
     * @attribute suffix    with_sound
     */
    animation create_animation(animation_script script, const string &name, bool with_sound);

    /**
     * Creates an animation from an `animation_script`'s name. This may
     * play a sound effect if the animation is set to play a sound effect
     * on its first frame.
     *
     * @param script_name   The name of the `animation_script` to create the `animation` from
     * @param name          The name for the new `animation`
     * @param with_sound    Denotes whether the `animation` should play audio.
     * @returns Returns the newly created `animation`
     *
     * @attribute suffix    from_script_named_with_sound
     */
    animation create_animation(const string &script_name, const string &name, bool with_sound);

    /**
     * Creates an animation from an `animation_script`.
     *
     * @param script        The `animation_script` to create the `animation` from
     * @param name          The name for the new `animation`
     * @returns Returns the newly created `animation`
     *
     * @attribute class     animation_script
     * @attribute method    create_animation
     * @attribute self      script
     */
    animation create_animation(animation_script script, const string &name);

    /**
     * Creates an animation from an `animation_script`'s name. This may
     * play a sound effect if the animation is set to play a sound effect
     * on its first frame.
     *
     * @param script_name   The name of the `animation_script` to create the `animation` from
     * @param name          The name for the new `animation`
     * @returns Returns the newly created `animation`
     *
     * @attribute suffix    from_script_named
     */
    animation create_animation(const string &script_name, const string &name);

    /**
     * Creates an animation from an `animation_script`. This may play a
     * sound effect if the animation is set to play a sound effect on its
     * first frame.
     *
     * @param script        The `animation_script` to create the `animation` from.
     * @param idx           The index of the `animation` to create.
     * @param with_sound    Denotes whether the `animation` should play audio.
     * @returns Returns the newly created `animation_script`.
     *
     * @attribute suffix    from_index_with_sound
     */
    animation create_animation(animation_script script, int idx, bool with_sound);


    /**
     * Disposes of the resources used in the animation.
     *
     * @param ani           The `animation` to be disposed of.
     *
     * @attribute class       animation
     * @attribute destructor  true
     * @attribute self        ani
     */
    void free_animation(animation ani);

    /**
     * Setup an `animation` to follow the script from an indicated index.
     * This uses the index from the current animation script and
     * sets the supplied animation to start at that point in the script.
     *
     * @param anim          The `animation` to be assigned.
     * @param idx           The index of the animation to use from its current script.
     * @param with_sound    Denotes whether the `animation` should play audio.
     *
     * @attribute class     animation
     * @attribute method    assign
     *
     * @attribute suffix    index_with_sound
     */
    void assign_animation(animation anim, int idx, bool with_sound);
    
    /**
     * Setup an `animation` to follow the script from an indicated name.
     * This locates the name of the animation from the current animation script and
     * sets the supplied animation to start at that point in the script.
     *
     * @param anim          The `animation` to be assigned.
     * @param name          The name of the animation to use from its current script.
     * @param with_sound    Denotes whether the `animation` should play audio.
     *
     * @attribute class     animation
     * @attribute method    assign
     *
     * @attribute suffix    with_sound
     */
    void assign_animation(animation anim, string name, bool with_sound);
    
    /**
     * Setup an `animation` to follow the script from an indicated index.
     * This uses the index from the current animation script and
     * sets the supplied animation to start at that point in the script.
     *
     * @param anim          The `animation` to be assigned.
     * @param idx           The index of the animation to use from its current script.
     *
     * @attribute class     animation
     * @attribute method    assign
     *
     * @attribute suffix    index
     */
    void assign_animation(animation anim, int idx);
    
    /**
     * Setup an `animation` to follow the script from an indicated name.
     * This locates the name of the animation from the current animation script and
     * sets the supplied animation to start at that point in the script.
     *
     * @param anim          The `animation` to be assigned.
     * @param name          The name of the animation to use from its current script.
     *
     * @attribute class     animation
     * @attribute method    assign
     */
    void assign_animation(animation anim, string name);
    
    /**
     * Setup an `animation` to follow the script from an indicated name.
     * This will switch the animation to use the supplied script.
     * It locates the name of the animation with the animation script and
     * sets the `anim` to start at that point in the script.
     *
     * @param anim          The `animation` to be assigned.
     * @param script        The `animation_script` to assign the `animation` to.
     * @param name          The name of the `animation` to be assigned.
     *
     * @attribute class     animation
     * @attribute method    assign
     * @attribute self      anim
     *
     * @attribute suffix    with_script
     */
    void assign_animation(animation anim, animation_script script, const string &name);

    /**
     * Assigns an `animation` to an `animation_script`. This may play a
     * sound effect if the animation is set to play a sound effect on its
     * first frame.
     *
     * @param anim          The `animation` to be assigned.
     * @param script        The `animation_script` to assign the `animation` to.
     * @param name          The name of the `animation` to be assigned.
     * @param with_sound    Denotes whether the `animation` should play audio.
     *
     * @attribute class     animation
     * @attribute method    assign
     * @attribute self      anim
     *
     * @attribute suffix    with_script_and_sound
     */
    void assign_animation(animation anim, animation_script script, const string &name, bool with_sound);

    /**
     * Assigns an `animation` to an `animation_script`.
     *
     * @param anim          The `animation` to be assigned.
     * @param script_name   The name of the `animation_script` to assign the `animation` to.
     * @param name          The name of the `animation` to be assigned.
     *
     * @attribute class     animation
     * @attribute method    assign
     * @attribute self      anim
     *
     * @attribute suffix    with_script_named
     */
    void assign_animation(animation anim, const string &script_name, const string &name);

    /**
     * Assigns an `animation` to an `animation_script`. This may play a
     * sound effect if the animation is set to play a sound effect on its
     * first frame.
     *
     * @param anim          The `animation` to be assigned.
     * @param script_name   The name of the `animation_script` to assign the `animation` to.
     * @param name          The name of the `animation` to be assigned
     * @param with_sound    Denotes whether the `animation` should play audio.
     *
     * @attribute class     animation
     * @attribute method    assign
     * @attribute self      anim
     *
     * @attribute suffix    with_script_named_and_sound
     */
    void assign_animation(animation anim, const string &script_name, const string &name, bool with_sound);

    /**
     * Assigns an `animation` to an `animation_script`.
     *
     * @param anim          The `animation` to be assigned.
     * @param script        The `animation_script` to assign the `animation` to.
     * @param idx           The index of the `animation` to create.
     *
     * @attribute class     animation
     * @attribute method    assign
     * @attribute self      anim
     *
     * @attribute suffix    index_with_script
     */
    void assign_animation(animation anim, animation_script script, int idx);

    /**
     * Assigns an `animation` to an `animation_script`. This may play a
     * sound effect if the animation is set to play a sound effect on its
     * first frame.
     *
     * @param anim          The `animation` to be assigned.
     * @param script        The `animation_script` to assign the `animation` to.
     * @param idx           The index of the `animation` to create.
     * @param with_sound    Denotes whether the `animation` should play audio.
     *
     * @attribute class     animation
     * @attribute method    assign
     * @attribute self      anim
     *
     * @attribute suffix    index_with_script_and_sound
     */
    void assign_animation(animation anim, animation_script script, int idx, bool with_sound);

    /**
     * Searches an `animation_script` for an `animation` and returns its
     * index.
     *
     * @param script        The `animation_script` to look for the `animation` in.
     * @param name          The name of the `animation` to look for.
     *
     * @attribute class     animation_script
     * @attribute method    animation_index
     * @attribute self      script
     *
     * @returns Returns the index of the `animation` in the `animation_script`
     */
    int animation_index(animation_script script, const string &name);

    /**
     * Searches an `animation_script` for an animation and returns its name.
     *
     * @param temp          The `animation` to search for.
     *
     * @attribute class     animation
     * @attribute getter    name
     * @attribute self      temp
     *
     * @returns Returns the name of the `animation` in the `animation_script`.
     */
    string animation_name(animation temp);

    /**
     * Returns the current cell (the part of the image or sprite) of this
     * animation. This can be used to animate an image or sprite.
     *
     * @param anim          The `animation` to return the cell of.
     *
     * @attribute class     animation
     * @attribute getter    current_cell
     * @attribute self      anim
     *
     * @returns Returns the current cell of the animation passed to the method.
     */
    int animation_current_cell(animation anim);

    /**
     * Checks if an `animation` has ended.
     *
     * @param anim          The animation to check.
     *
     * @attribute class     animation
     * @attribute getter    ended
     *
     * @returns Returns a `bool` denoting whether the `animation` has ended.
     */
    bool animation_ended(animation anim);

    /**
     * Returns true if the `animation` entered a new frame on its last update.
     * This can be used to trigger actions on frames within an animation.
     *
     * @param anim          The animation to check.
     *
     * @attribute class     animation
     * @attribute getter    entered_frame
     *
     * @returns Returns a `bool` denoting whether the `animation` has ended.
     */
    bool animation_entered_frame(animation anim);

    /**
     * Returns the amount of time spent in the current frame. When this
     * exceeds the frames duration the animation moves to the next frame.
     *
     * @param anim          The animation to check.
     *
     * @attribute class     animation
     * @attribute getter    frame_time
     *
     * @returns Returns the amount of time spent in the current frame as a `float`.
     */
    float animation_frame_time(animation anim);

    /**
     * Returns the `vector_2d` assigned to the current frame in the animation.
     *
     * @param anim          The animation to check the vector of.
     *
     * @attribute class     animation
     * @attribute getter    current_vector
     *
     * @returns Returns the `vector_2d` assigned to the current frame in the animation.
     */
    vector_2d animation_current_vector(animation anim);

    /**
     * Restarts an `animation`.
     *
     * @param anim          The `animation` to restart.
     *
     * @attribute class     animation
     * @attribute method    restart
     * @attribute self      anim
     */
    void restart_animation(animation anim);

    /**
     * Restarts an `animation`. This may play a sound effect if the first
     * frame triggers a sound.
     *
     * @param anim          The `animation` to restart.
     * @param with_sound    Denotes whether the `animation` should play audio.
     *
     * @attribute class     animation
     * @attribute method    restart
     * @attribute self      anim
     *
     * @attribute suffix    with_sound
     */
    void restart_animation(animation anim, bool with_sound);

    /**
     * Updates the animation, updating the time spent and possibly moving to
     * a new frame in the animation. This may play a sound effect if the new
     * frame triggers a sound.
     *
     * @param anim          The `animation` to update.
     *
     * @attribute class     animation
     * @attribute method    update
     * @attribute self      anim
     */
    void update_animation(animation anim);

    /**
     * Updates the animation, updating the time spent and possibly moving to
     * a new frame in the animation. This may play a sound effect if the new
     * frame triggers a sound.
     *
     * @param anim          The `animation` to update.
     * @param pct           The amount that the frame time will be incremented
     *
     * @attribute class     animation
     * @attribute method    update
     * @attribute self      anim
     *
     * @attribute suffix    percent
     */
    void update_animation(animation anim, float pct);

    /**
     * Updates the animation, updating the time spent and possibly moving to
     * a new frame in the animation. This may play a sound effect if the new
     * frame triggers a sound.
     *
     * @param anim          The `animation` to update.
     * @param pct           The amount that the frame time will be incremented
     * @param with_sound    Denotes whether the `animation` should play audio.
     *
     * @attribute suffix    percent_with_sound
     */
    void update_animation(animation anim, float pct, bool with_sound);
}

#endif /* animations_h */

//
//  animations.cpp
//  splashkit
//
//  Created by Andrew Cain on 10/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "animations.h"
#include "types.h"
#include "audio.h"
#include "resources.h"
#include "vector_2d.h"

#include "utility_functions.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;
using std::ifstream;
using std::to_string;

namespace splashkit_lib
{
    static map<string, animation_script> _animation_scripts;

    struct row_data
    {
        int id,cell,dur,next;
        sound_effect snd;
        vector_2d mvmt;
    };

    struct id_data
    {
        string name;
        int start_id;
    };

    int animation_index(animation_script temp, const string &name);

    animation_script load_animation_script(const string &name, const string &filename)
    {
        animation_script result;
        vector<row_data> rows;
        vector<id_data> ids;

        string line, line_id, data;
        int line_no, max_id;

        string path = path_to_resource(filename, ANIMATION_RESOURCE);

        if ( ! file_exists(path) )
        {
            LOG(WARNING) << cat({ "Unable to locate animation file for ", name, " (", path, ")"});
            return nullptr;
        }

        ifstream input(path);

        //
        // Declare lambdas that access above data
        //

        auto add_row = [&](row_data my_row)
        {
            int j;

            // Check if beyond current range
            if (my_row.id > max_id)
            {
                rows.resize(my_row.id + 1);

                // Mark new rows as "empty"
                for (j = max_id + 1; j < rows.size(); j++)
                {
                    rows[j].id   = -1;
                    rows[j].snd  = nullptr;
                    rows[j].cell = -1;
                    rows[j].next = -1;
                    rows[j].mvmt = vector_to(0,0);
                }

                max_id = my_row.id;
            }

            if (rows[my_row.id].id != -1)
            {
                LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". A frame with id " + to_string(my_row.id) + " already exists.";
                return false;
            }
            else
            {
                // Success add the row.
                rows[my_row.id] = my_row;
                return true;
            }
        }; // end add_row

        auto add_id = [&](id_data my_id)
        {
            int j;

            // Check if name is already in ids
            for (j = 0; j < ids.size(); j++)
            {
                if (ids[j].name == my_id.name)
                {
                    LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". The id " + my_id.name + " already exists.";
                    return false;
                }
            }

            ids.push_back(my_id);
            return true;
        };

    //    auto process_frame = [&]()
    //    {
    //        row_data my_row;
    //
    //        if (count_delimiter(data, ',') != 3)
    //        {
    //            LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". A frame must have 4 values separated as id,cell,dur,next");
    //            return false;
    //        }
    //
    //        my_row.id    = str_to_int(extract_delimited(1,data,','), false);
    //        my_row.cell  = str_to_int(extract_delimited(2,data,','), false);
    //        my_row.dur   = str_to_int(extract_delimited(3,data,','), false);
    //        my_row.next  = str_to_int(extract_delimited(4,data,','), true, -1);
    //        my_row.snd   = nullptr;
    //        my_row.mvmt  = vector_to(0, 0);
    //
    //        return add_row(my_row);
    //    };

        auto process_multi_frame = [&]()
        {
            vector<int> id_range, cell_range;
            int dur, next, j;
            row_data my_row;

            if ( count_delimiter_with_ranges(data, ',') != 3 )
            {
                LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". A multi-frame must have 4 values separated as id-range,cell-range,dur,next";
                return false;
            }

            process_range(extract_delimited_with_ranges(1, data), id_range);
            process_range(extract_delimited_with_ranges(2, data), cell_range);

            if (id_range.size() != cell_range.size())
            {
                LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". The range of cells and ids is not the same length.";
                return false;
            }

            dur = str_to_int(extract_delimited_with_ranges(3,data), false);
            next = str_to_int(extract_delimited_with_ranges(4,data), true, -1);

            for ( j = 0; j < id_range.size(); j++)
            {
                my_row.id        = id_range[j];
                my_row.cell      = cell_range[j];
                my_row.dur       = dur;
                my_row.snd       = nullptr;
                my_row.mvmt      = vector_to(0,0);

                if ( j < id_range.size() - 1 )
                    my_row.next = id_range[j + 1];
                else
                    my_row.next = next;

                if (not add_row(my_row)) return false;
            }

            return true;
        };

        auto process_id = [&]()
        {
            id_data my_id_data;

            if (count_delimiter_with_ranges(data, ',') != 1)
            {
                LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". An id must have 2 values separated as name,start-id";
                return false;
            }

            my_id_data.name = to_lower(extract_delimited(1, data, ','));
            my_id_data.start_id = str_to_int(extract_delimited(2,data,','), false);

            return add_id(my_id_data);
        };

        auto process_sound = [&]()
        {
            int id;
            string snd_id, snd_file;

            if (count_delimiter(data, ',') != 2)
            {
                LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". A sound must have three parts frame #,sound name,sound file.";
                return;
            }

            id = str_to_int(extract_delimited(1, data, ','), true);
            snd_id = extract_delimited(2,data,',');
            snd_file = extract_delimited(3,data,',');

            if (not has_sound_effect(snd_id))
            {
                if(load_sound_effect(snd_id, snd_file) == nullptr)
                {
                    LOG(WARNING) << "At line " + to_string(line_no) + " in animation " + filename + ": Cannot find " + snd_id + " sound file " + snd_file;
                    return;
                }
            }

            if (id >= 0 && id < rows.size())
                rows[id].snd = sound_effect_named(snd_id);
            else
                LOG(WARNING) << "At line " + to_string(line_no) + " in animation " + filename + ": No frame with id " + to_string(id) + " for sound file " + snd_file;
        };

        auto process_vector = [&]()
        {
            vector<int> id_range;
            string x_val, y_val;
            double x, y;
            vector_2d v;

            if (count_delimiter(data, ',') != 2)
            {
                LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". A vector must have three parts frame #s, x value, y value.";
                return;
            }

            process_range(extract_delimited_with_ranges(1, data), id_range);
            x_val = extract_delimited_with_ranges(2,data);
            y_val = extract_delimited_with_ranges(3,data);

            if (not try_str_to_double(x_val, x))
            {
                LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". X value must be a number.";
                return;
            }

            if (not try_str_to_double(y_val, y))
            {
                LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". Y value must be a number.";
                return;
            }

            v = vector_to(x, y);

            // WriteLn('Vector ', PointToString(v) );
            //
            for (int id : id_range)
            {
                if (id >= 0 && id < rows.size())
                {
                    rows[id].mvmt = v;
                }
            }
        };

        auto process_line = [&]()
        {
            // Split line into id and data
            line_id = extract_delimited(1, line, ':');
            data = extract_delimited(2, line, ':');

            // Verify that id is a single char
            if (line_id.length() != 1)
            {
                LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". Error with frame #: " + line_id + ". This should be a single character.";
                return;
            }

            // Process based on id
            switch (tolower(line_id[0])) // in all cases the data variable is read
            {
                case 'f':
                    process_multi_frame(); //test... or ProcessFrame();
                    break;
                case 'm':
                    process_multi_frame();
                    break;
                case 'i':
                    process_id();
                    break;
                case 's':
                    process_sound();
                    break;
                case 'v':
                    process_vector();
                    break;
                default:
                    LOG(WARNING) << "Error at line " + to_string(line_no) + " in animation " + filename + ". Error with id: " + line_id + ". This should be one of f,m,i, s, or v.";
                    return;
            }
        };

        auto build_frame_lists = [&]()
        {
            // We have the data ready, now lets create the linked lists...
            result = new(_animation_script_data);

            result->id          = ANIMATION_SCRIPT_PTR;
            result->name        = name;        // name taken from parameter of DoLoadAnimationScript
            result->filename    = filename;    // filename also taken from parameter

            int j, next_idx;

            result->frames.resize(rows.size());

            // Link the frames together
            for (j = 0; j < result->frames.size(); j++)
            {
                result->frames[j].index        = j;
                result->frames[j].cell_index   = rows[j].cell;
                result->frames[j].sound        = rows[j].snd;
                result->frames[j].duration     = rows[j].dur;
                result->frames[j].movement     = rows[j].mvmt;

                // Get the next id and then
                next_idx = rows[j].next;

                if (next_idx == -1)
                {
                    //The end of a list of frames = no next
                    result->frames[j].next = nullptr;
                }
                else if ((next_idx < 0) or (next_idx >= result->frames.size()))
                {
                    free_animation_script(result);
                    result = nullptr;
                    LOG(WARNING) << "Error in animation " + filename + ". Error with frame: " + to_string(j) + ". Next is outside of available frames.";
                    return;
                }
                else
                    result->frames[j].next = &result->frames[next_idx];
            }

            result->animations.resize(ids.size());

            for (j = 0; j < ids.size(); j++)  //Add in the animation starting indexes
            {
                result->animation_ids[ids[j].name] = j;
                result->animation_names.push_back(ids[j].name);
                result->animations[j] = ids[j].start_id;             //Store the linked index
                //WriteLn('load ids: ', added_idx, ' - startid ', ids[j].start_id)
            }
        };

        auto sum_loop = [&](animation_frame *start)
        {
            animation_frame *current;

            float sum = start->duration;
            current = start->next;

            while ((current != start) and (current))
            {
                sum += current->duration;
                current = current->next;
            }

            return sum;
        };

        // Animations with loops must have a duration > 0 for at least one frame
        auto check_animation_loops = [&]()
        {
            int i;
            bool done;
            animation_frame *current;

            done = true;

            if (!result) return;

            // check for all positive
            for (i = 0; i < result->frames.size(); i++)
            {
                if( result->frames[i].duration == 0 )
                {
                    done = false;
                    break;
                }
            }

            if (done) return;

            // Check through each animation looking for a loop
            for (i = 0; i < result->animations.size(); i++)
            {
                current = &result->frames[result->animations[i]];

                if (sum_loop(current) == 0)
                {
                    free_animation_script(result);
                    LOG(WARNING) << "Error in animation " + filename + ". Animation contains a loop with duration 0 starting at cell " + to_string(current->index);
                    return;
                }
            }
        };

        auto verify_version = [&]()
        {
            if (input.eof()) return false;
            line = "";

            while ((line.length() == 0) or (line.substr(0,2) == "//"))
            {
                getline(input, line);
                line = trim(line);
            }

            //Verify that the line has the right version
            if ((line != "SwinGame Animation #v1") and (line != "SplashKit Animation"))
            {
                LOG(WARNING) << "Error in animation " + filename + ". Animation files must start with 'SplashKit Animation'";
                return false;
            }

            return true;
        };

        line_no = 0;
        max_id = -1;
        rows.resize(0);
        result = nullptr;

        if (not verify_version())
        {
            LOG(WARNING) << "Error loading animation script: " + path;
            return nullptr;
        }


        while (getline(input, line))
        {
            line_no = line_no + 1;

            line = trim(line);
            if (line.length() == 0) continue;  //skip empty lines
            if (line.substr(0,2) == "//") continue; //skip lines starting with //

            process_line();
        }

        build_frame_lists();
        check_animation_loops();

        _animation_scripts[name] = result;

        return result;
    }

    animation_script animation_script_named(const string &name)
    {
        if (has_animation_script(name))
            return _animation_scripts[name];
        else
            return nullptr;
    }


    void free_animation_script(animation_script script_to_free)
    {
        if (not VALID_PTR(script_to_free, ANIMATION_SCRIPT_PTR))
        {
            LOG(WARNING) << "Attempt to free invalid animation script.";
            return;
        }

        notify_of_free(script_to_free);

        // Must use downto as animations are removed from the array in FreeAnimation!
        for (int i = static_cast<int>(script_to_free->anim_objs.size()) - 1; i >= 0; i--)
        {
            free_animation(script_to_free->anim_objs[i]);
        }

        _animation_scripts.erase(script_to_free->name);

        script_to_free->id = NONE_PTR;
        delete(script_to_free);
    }

    void free_animation_script(const string &name)
    {
        free_animation_script(animation_script_named(name));
    }

    void free_all_animation_scripts()
    {
        string name;

        size_t sz = _animation_scripts.size();

        for(size_t i = 0; i < sz; i++)
        {
            animation_script script = _animation_scripts.begin()->second;
            if (VALID_PTR(script, ANIMATION_SCRIPT_PTR))
            {
                free_animation_script(script);
            }
            else
            {
                LOG(WARNING) << "Animation Scripts contained an invalid pointer";
                _animation_scripts.erase(_animation_scripts.begin());
            }
        }
    }

    void _remove_animation(animation_script script, animation ani)
    {
        auto it = std::find(script->anim_objs.begin(), script->anim_objs.end(), ani);

        if (it != script->anim_objs.end())
        {
            using std::swap;

            swap(*it, script->anim_objs.back());
            script->anim_objs.pop_back();
        }
        else
            LOG(WARNING) << "Could not remove animation! " + animation_script_name(script);
    }

    void free_animation(animation ani)
    {
        if (VALID_PTR(ani, ANIMATION_PTR))
        {
            notify_of_free(ani);

            _remove_animation(ani->script, ani);
            ani->id = NONE_PTR;

            delete(ani); //ani may have been overridden by last call...
        }
    }

    bool has_animation_script(const string &name)
    {
        return _animation_scripts.count(name) > 0;
    }


    int animation_count(animation_script script)
    {
        if( INVALID_PTR(script, ANIMATION_SCRIPT_PTR))
        {
            LOG(WARNING) << "Attempting to get number of animations from invalid animation script";
            return 0;
        }

        return static_cast<int>(script->animations.size());
    }

    int animation_current_cell(animation anim)
    {
        if (not VALID_PTR(anim, ANIMATION_PTR))
            return 0; //no animation - return the first frame
        else if (not animation_ended(anim))
            return anim->current_frame->cell_index;
        else if (anim->last_frame)
            return anim->last_frame->cell_index; //Use the last frame drawn.
        else
            return -1;
    }

    vector_2d animation_current_vector(animation anim)
    {
        if ( INVALID_PTR(anim, ANIMATION_PTR))
        {
            return vector_to(0,0);
        }

        if ( ! animation_ended(anim) )
            return anim->current_frame->movement;
        else
            return vector_to(0,0);
    }

    bool animation_ended(animation anim)
    {
        return (not VALID_PTR(anim, ANIMATION_PTR)) || (anim->current_frame == nullptr);
    }

    bool animation_entered_frame(animation anim)
    {
        if ( INVALID_PTR(anim, ANIMATION_PTR))
        {
            LOG(WARNING) << "Attempting to check if animation entered a new frame with invalid animation data.";
            return false;
        }

        return anim->entered_frame;
    }

    float animation_frame_time(animation anim)
    {
        if ( INVALID_PTR(anim, ANIMATION_PTR))
        {
            LOG(WARNING) << "Attempting to get frame time with invalid animation data.";
            return 0;
        }

        return anim->frame_time;
    }

    bool has_animation_named(animation_script script, const string &name)
    {
        if (INVALID_PTR(script, ANIMATION_SCRIPT_PTR))
        {
            LOG(WARNING) << "Attempting to get animation name from invalid animation script.";
            return false;
        }

        return script->animation_ids.count(to_lower(name)) > 0;
    }

    int animation_index(animation_script script, const string &name)
    {
        if (INVALID_PTR(script, ANIMATION_SCRIPT_PTR))
        {
            LOG(WARNING) << "Attempting to get index from invalid animation script.";
            return -1;
        }

        if ( not has_animation_named(script, name) )
        {
            LOG(WARNING) << "No animation with name " + name + " in script " + animation_script_name(script) + ".";
            return -1;
        }

        return script->animation_ids[to_lower(name)];
    }

    string animation_name(animation temp)
    {
        if ( INVALID_PTR(temp, ANIMATION_PTR))
        {
            LOG(WARNING) << "Attempting to get name of invalid animation data.";
            return "";
        }

        return temp->animation_name;
    }

    string animation_name(animation_script temp, int idx)
    {
        if (INVALID_PTR(temp, ANIMATION_SCRIPT_PTR))
        {
            LOG(WARNING) << "Attempting to get animation name from invalid animation script";
            return "";
        }

        if ( idx < 0 or idx >= temp->animation_names.size())
        {
            LOG(WARNING) << "Attempting to get an animation that is not within range 0-" + to_string(temp->animations.size()-1) + ".";
            return "";
        }

        return temp->animation_names[idx];
    }

    string animation_script_name(animation_script script)
    {
        if (VALID_PTR(script, ANIMATION_SCRIPT_PTR)) return script->name;
        return "";
    }

    void assign_animation(animation anim, animation_script script, int idx, bool with_sound)
    {
        if (INVALID_PTR(anim, ANIMATION_PTR))
        {
            LOG(WARNING) << "Attempting to setup an assign animation for invalid animation";
            return;
        }

        if (INVALID_PTR(script, ANIMATION_SCRIPT_PTR))
        {
            LOG(WARNING) << "Attempting to setup an assign animation for invalid animation script";
            return;
        }

        if ((idx < 0) or (idx >= script->animations.size()))
        {
            LOG(WARNING) << "Assigning an animation frame that is not within range 0-" + to_string(script->animations.size()-1) + ".";
            return;
        }

        // Animation is being assigned to another script
        if (anim->script != script)
        {
            if (anim->script)
                _remove_animation(anim->script, anim);   // remove from old script
            script->anim_objs.push_back(anim);       // add to new script
        }

        anim->first_frame        = &script->frames[script->animations[idx]];
        anim->animation_name     = animation_name(script, idx);
        restart_animation(anim, with_sound);
    }

    void assign_animation(animation anim, int idx, bool with_sound)
    {
        if (INVALID_PTR(anim, ANIMATION_PTR))
        {
            LOG(WARNING) << "Attempting to setup an assign animation for invalid animation";
            return;
        }

        assign_animation(anim, anim->script, idx, with_sound);
    }
    
    void assign_animation(animation anim, string name, bool with_sound)
    {
        if (INVALID_PTR(anim, ANIMATION_PTR))
        {
            LOG(WARNING) << "Attempting to setup an assign animation for invalid animation";
            return;
        }

        assign_animation(anim, anim->script, name, with_sound);
    }

    
    void assign_animation(animation anim, int idx)
    {
        assign_animation(anim, idx, true);
    }

    void assign_animation(animation anim, string name)
    {
        assign_animation(anim, name, true);
    }
    
    
    void assign_animation(animation anim, animation_script script, int idx)
    {
        assign_animation(anim, script, idx, true);
    }

    void assign_animation(animation anim, animation_script script, const string &name)
    {
        assign_animation(anim, script, animation_index(script, name), true);
    }

    void assign_animation(animation anim, animation_script script, const string &name, bool with_sound)
    {
        assign_animation(anim, script, animation_index(script, name), with_sound);
    }

    void assign_animation(animation anim, const string &script_name, const string &name)
    {
        animation_script script = animation_script_named(script_name);
        assign_animation(anim, script, animation_index(script, name), true);
    }

    void assign_animation(animation anim, const string &script_name, const string &name, bool with_sound)
    {
        animation_script script = animation_script_named(script_name);
        assign_animation(anim, script, animation_index(script, name), with_sound);
    }


    animation create_animation(animation_script script, int idx, bool with_sound)
    {
        animation result = nullptr;

        if (INVALID_PTR(script, ANIMATION_SCRIPT_PTR))
        {
            LOG(WARNING) << "Attempting to create animation from invalid script";
            return result;
        }

        if ((idx < 0) or (idx >= script->animations.size()))
        {
            LOG(WARNING) << "Unable to create animation number " + to_string(idx) + " from script " + script->name;
            return result;
        }

        result = new(_animation_data);

        result->id = ANIMATION_PTR;
        result->current_frame = nullptr;
        result->last_frame = nullptr;
        result->first_frame = nullptr;
        result->entered_frame = false;
        result->animation_name = animation_name(script, idx);
        result->script = script;
        result->frame_time = 0;

        script->anim_objs.push_back(result);

        assign_animation(result, script, idx, with_sound);

        return result;
    }

    animation create_animation(animation_script script, int idx)
    {
        return create_animation(script, idx, true);
    }

    animation create_animation(animation_script script, const string &name, bool with_sound)
    {
        return create_animation(script, animation_index(script, name), with_sound);
    }

    animation create_animation(animation_script script, const string &name)
    {
        return create_animation(script, animation_index(script, name), true);
    }

    animation create_animation(const string &script_name, const string &name, bool with_sound)
    {
        return create_animation(animation_script_named(script_name), name, with_sound);
    }

    animation create_animation(const string &script_name, const string &name)
    {
        return create_animation(animation_script_named(script_name), name, true);
    }

    void restart_animation(animation anim)
    {
        restart_animation(anim, true);
    }

    void restart_animation(animation anim, bool with_sound)
    {
        if (INVALID_PTR(anim, ANIMATION_PTR))
        {
            LOG(WARNING) << "Attempting to restart an invalid animation.";
            return;
        }

        anim->current_frame  = anim->first_frame;
        anim->last_frame     = anim->first_frame;
        anim->frame_time     = 0;
        anim->entered_frame  = true;

        if (with_sound and ASSIGNED(anim->current_frame) and ASSIGNED(anim->current_frame->sound))
            play_sound_effect(anim->current_frame->sound);
    }

    void update_animation(animation anim)
    {
        update_animation(anim, 1.0f, true);
    }

    void update_animation(animation anim, float pct)
    {
        update_animation(anim, pct, true);
    }

    void update_animation(animation anim, float pct, bool with_sound)
    {
        if (animation_ended(anim)) return;

        anim->frame_time     = anim->frame_time + pct;

        if (anim->frame_time >= anim->current_frame->duration)
        {
            anim->frame_time = anim->frame_time - anim->current_frame->duration;    //reduce the time
            anim->last_frame = anim->current_frame;                                 //store last frame
            anim->current_frame = anim->current_frame->next;                        //get the next frame

            //if assigned(anim^.currentFrame) then
            //WriteLn('Frame ', HexStr(anim^.currentFrame), ' Vector ', PointToString(anim^.currentFrame^.movement));

            if (ASSIGNED(anim->current_frame) and ASSIGNED(anim->current_frame->sound) and with_sound)
            {
                play_sound_effect(anim->current_frame->sound);
            }

            anim->entered_frame  = true;
        }
        else
        {
            anim->entered_frame  = false;
        }
    }
}

//
//  bundles.cpp
//  splashkit
//
//  Created by Andrew Cain on 29/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "bundles.h"

#include "types.h"
#include "resources.h"
#include "utility_functions.h"
#include "images.h"
#include "timers.h"
#include "text.h"
#include "audio.h"

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::to_string;

namespace splashkit_lib
{
    struct bundled_resource
    {
        resource_kind kind;
        string name;
    };

    struct resource_bundle
    {
        string                      name;
        string                      filename;
        vector<bundled_resource>    resources;
    };

    static map<string, resource_bundle> _resource_bundles;


    bool has_resource_bundle(const string &name)
    {
        return _resource_bundles.count(name) > 0;
    }

    resource_kind string_to_resource_kind(const string &txt)
    {
        string kind = txt;
        to_upper(kind);

        if ( kind == "BUNDLE" ) return BUNDLE_RESOURCE;
        else if ( kind == "BITMAP") return IMAGE_RESOURCE;
        else if ( kind == "TIMER" ) return TIMER_RESOURCE;
        else if ( kind == "SOUND" ) return SOUND_RESOURCE;
        else if ( kind == "MUSIC" ) return MUSIC_RESOURCE;
        else if ( kind == "FONT"  ) return FONT_RESOURCE;
        else if ( kind == "ANIM"  ) return ANIMATION_RESOURCE;
        else return OTHER_RESOURCE;
    }

    void load_resource_bundle(const string &name, const string &filename)
    {
        if ( has_resource_bundle(name) )
        {
            LOG(WARNING) << "Attempting to load resource bundle twice.";
            return;
        }

        string path = path_to_resource(filename, BUNDLE_RESOURCE);

        if ( ! file_exists(path) )
        {
            LOG(WARNING) << cat({ "Unable to locate bundle file for ", name, " (", path, ")"});
            return;
        }

        int line_no = 0;
        string line;
        ifstream input(path);

        resource_bundle result;

        // Called on load of each bitmap
        auto rb_load_bitmap = [&](string line_name, string line_path)
        {
            bitmap bmp = load_bitmap(line_name, line_path);
            int num_delim = count_delimiter(line, ',');
            if ( num_delim > 2 and num_delim != 7 )
            {
                LOG(WARNING) << "Incorrect cell options for bitmap " + line_name + " at " + to_string(line_no) + " of bundle " + name;
                return;
            }
            else if ( num_delim == 2 ) return;

            bitmap_set_cell_details(bmp,
                                    str_to_int(extract_delimited(4, line, ',')),
                                    str_to_int(extract_delimited(5, line, ',')),
                                    str_to_int(extract_delimited(6, line, ',')),
                                    str_to_int(extract_delimited(7, line, ',')),
                                    str_to_int(extract_delimited(8, line, ',')));
        };

        // Called for each line in the bundle text file
        auto process_line = [&]()
        {
            resource_kind kind = string_to_resource_kind(extract_delimited(1, line, ','));
            string line_name = trim(extract_delimited(2, line, ','));
            string line_path = trim(extract_delimited(3, line, ','));


            if ( kind == OTHER_RESOURCE )
            {
                LOG(WARNING) << "Unknown resource type at line " + to_string(line_no) + " of bundle " + name;
                return;
            }

            if ( line_name.length() == 0 )
            {
                LOG(WARNING) << "Name missing for resource at line " + to_string(line_no) + " of bundle " + name;
                return;
            }

            if ( line_path.length() == 0 && kind != TIMER_RESOURCE )
            {
                LOG(WARNING) << "Name missing for resource at line " + to_string(line_no) + " of bundle " + name;
                return;
            }

            switch ( kind )
            {
                case BUNDLE_RESOURCE:
                    load_resource_bundle(line_name, line_path);
                    if ( ! has_resource_bundle(line_name) ) return;
                    break;
                case TIMER_RESOURCE:
                    create_timer(line_name);
                    break;
                case IMAGE_RESOURCE:
                    rb_load_bitmap(line_name, line_path);
                    if ( ! has_resource_bundle(line_name) ) return;
                    break;
                case FONT_RESOURCE:
                    load_font(line_name, line_path);
                    if ( ! has_font(line_name) ) return;
                    break;
                case SOUND_RESOURCE:
                    load_sound_effect(line_name, line_path);
                    if ( ! has_sound_effect(line_name) ) return;
                    break;
                case MUSIC_RESOURCE:
                    load_music(line_name, line_path);
                    if ( ! has_music(line_name) ) return;
                    break;
                case ANIMATION_RESOURCE:
                    load_animation_script(line_name, line_path);
                    if ( ! has_animation_script(line_name) ) return;
                    break;
                default:
                    return;
            }

            bundled_resource br;
            br.name = line_name;
            br.kind = kind;

            result.resources.push_back(br);

            return;
        };

        while (getline(input, line))
        {
            line_no = line_no + 1;

            line = trim(line);
            if (line.length() == 0) continue;  //skip empty lines
            if (line.substr(0,2) == "//") continue; //skip lines starting with //

            process_line();
        }

        _resource_bundles[name] = result;
    }

    void free_resource_bundle(const string name)
    {
        if ( ! has_resource_bundle(name) )
        {
            LOG(WARNING) << "Attempting to free unloaded resource bundle named " + name;
            return;
        }

        // not notified as this does not create objects at this stage

        resource_bundle bndl = _resource_bundles[name];
        _resource_bundles.erase(name);

        for( bundled_resource br : bndl.resources )
        {
            switch ( br.kind )
            {
                case BUNDLE_RESOURCE:
                    free_resource_bundle(br.name);
                    break;
                case TIMER_RESOURCE:
                    free_timer(timer_named(br.name));
                    break;
                case IMAGE_RESOURCE:
                    free_bitmap(bitmap_named(br.name));
                    break;
                case FONT_RESOURCE:
                    free_font(font_named(br.name));
                    break;
                case SOUND_RESOURCE:
                    free_sound_effect(sound_effect_named(br.name));
                    break;
                case MUSIC_RESOURCE:
                    free_music(music_named(br.name));
                    break;
                case ANIMATION_RESOURCE:
                    free_animation_script(animation_script_named(br.name));
                    break;
                default:
                    return;
            }
        }
    }

    void free_all_resource_bundles()
    {
        for (unsigned long i = _resource_bundles.size(); i > 0 ; i--)
        {
            free_resource_bundle(_resource_bundles.begin()->first);
        }
    }
}

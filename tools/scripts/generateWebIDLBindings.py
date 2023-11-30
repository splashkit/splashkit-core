import json
import sys 

inJSON = open(sys.argv[1], "r")
outC = open(sys.argv[2], "w")
outIDL = open(sys.argv[3], "w")
outJS = open(sys.argv[4], "w")
print("Reading from "+sys.argv[1]+ ", writing to "+sys.argv[2]+" and "+sys.argv[3]+" and "+sys.argv[4])

api = json.load(inJSON)

def outputC(string):
    outC.write(string)
def outputIDL(string):
    outIDL.write(string)
def outputJS(string):
    outJS.write(string)
            
structs = set()
function_ptrs = set()

for category_name in api:
    category = api[category_name]
    for struct in category["structs"]:
        structs.add(struct["name"])
        
    for struct in category["typedefs"]:
        if struct["is_function_pointer"]:
            function_ptrs.add(struct["name"])
            continue
        else:
            structs.add(struct["name"])
            
            
ignore_structs = ["matrix_2d"]
ignore_functions = [
"json_read_array",
"json_set_array",
"http_post",
"send_response",
"lines_from_rectangle",
"lines_from_triangle",
"triangles_from",
"request_headers",
"request_uri_stubs",
"split_uri_stubs",
"message_data_bytes",
]
            
def sigisSane(func):
    for param in func["parameters"]:
        if func["parameters"][param]["type"] in function_ptrs:
            return False;
    if func["name"] in ignore_functions or function_unique_name(func) in ignore_functions:
        return False
    return True

# Generate the C++ Wrapper Class

outputC("""
#include "animations.h"
#include "audio.h"
#include "basics.h"
#include "bundles.h"
#include "camera.h"
#include "circle_drawing.h"
#include "circle_geometry.h"
#include "clipping.h"
#include "collisions.h"
#include "color.h"
#include "database.h"
#include "drawing_options.h"
#include "ellipse_drawing.h"
#include "geometry.h"
#include "graphics.h"
#include "images.h"
#include "input.h"
#include "json.h"
#include "keyboard_input.h"
#include "line_drawing.h"
#include "line_geometry.h"
#include "logging.h"
#include "matrix_2d.h"
#include "mouse_input.h"
#include "music.h"
#include "networking.h"
#include "physics.h"
#include "point_drawing.h"
#include "point_geometry.h"
#include "quad_geometry.h"
#include "random.h"
#include "rectangle_drawing.h"
#include "rectangle_geometry.h"
#include "resources.h"
#include "sound.h"
#include "sprites.h"
#include "terminal.h"
#include "text.h"
#include "text_input.h"
#include "timers.h"
#include "triangle_drawing.h"
#include "twitter.h"
#include "types.h"
#include "utils.h"
#include "vector_2d.h"
#include "web_server.h"
#include "window_manager.h"

#include <cstring>

using namespace splashkit_lib;

char* outputCStr(std::string str)
{
    char* ret = new char[str.size()+1];
    memcpy( ret, str.c_str(), str.size());
    ret[str.size()] = '\\0';
    return ret;
}

template<typename T>
std::vector<T> inputArrayToVector(T** items)
{
    std::vector<T> out;
    while(*items!=nullptr)
    {
        out.push_back(**items);
        items++;
    }
    return std::move(out);
}
std::vector<string> inputArrayToVector(char** items)
{
    std::vector<string> out;
    while(*items!=nullptr)
    {
        out.push_back((string)*items);
        items++;
    }
    return std::move(out);
}
template<typename T>
std::vector<T> inputArrayToVector(T* items)
{
    std::vector<T> out;
    while(*items!=nullptr)
    {
        out.push_back(*items);
        items++;
    }
    return std::move(out);
}

template<typename T>
T** outputVectorToArrayStruct(const std::vector<T> items)
{
    T** ret = new T*[items.size()+1];
    for(std::size_t i = 0; i < items.size(); i++)
    {
        ret[i] = new T();
        *ret[i] = std::move(items[i]);
    }
    ret[items.size()] = nullptr;
    return ret;
}
template<typename T>
T* outputVectorToArray(const std::vector<T> items)
{
    T* ret = new T[items.size()+1];
    for(std::size_t i = 0; i < items.size(); i++)
    {
        *ret[i] = items[i];
    }
    ret[items.size()] = nullptr;
    return ret;
}
char** outputVectorToArray(const std::vector<string> items)
{
    char** ret = new char*[items.size()+1];
    for(std::size_t i = 0; i < items.size(); i++)
    {
        ret[i] = outputCStr(items[i]);
    }
    ret[items.size()] = nullptr;
    return ret;
}


typedef window SKwindow;
class SplashKitJavascript
{
	public:
""")

def function_unique_name(func):
    if func["unique_global_name"] != "center_point":
        return func["unique_global_name"]
    else:
        for k in func["parameters"]:
            if k=="c":
                return "center_point_circle"
            if k=="s":
                return "center_point_sprite"
    return "ERROR"


def generateCTypeAccurate(t):
    return '%(type)s%(vector)s%(symbol)s' % {
        'type': sanitizeCTypeInParam(t["type"]),
        'vector': "<"+t["type_parameter"]+">" if t["is_vector"] else "",
        'symbol': "*" if t["is_pointer"] else "&" if t["is_reference"] else "",
    }
def generateCType(t):
    is_array = (t["is_vector"] or ("is_array" in t and t["is_array"]))
    _type = t["type_parameter"] if is_array else t["type"]
    return '%(type)s%(vector)s%(symbol)s' % {
        'type': sanitizeCTypeInParam(_type),
        'vector': ("**" if _type in structs else "*") if is_array else "",
        'symbol': "*" if t["is_pointer"] else "&" if t["is_reference"] else "",
    }

def sanitizeCTypeInParam(arg_type):
    if arg_type == "string":
        return "char*"
    if arg_type == "window":
        return "SKwindow"
    return arg_type
def sanitizeCTypeInConvertFront(arg):
    if arg["type"] == "string":
        return "(string)"
    if arg["is_vector"]:
        return "inputArrayToVector("
    return ""
def sanitizeCTypeInConvertBack(arg):
    if arg["is_vector"]:
        return ")"
    return ""
    
def sanitizeCTypeOutConvertFront(arg):
    if arg["type"] == "string":
        return "outputCStr("
    if arg["is_vector"]:
        if arg["type_parameter"] in structs:
            return "outputVectorToArrayStruct("
        else:
            return "outputVectorToArray("
    return ""
def sanitizeCTypeOutConvertBack(arg):
    if arg["type"] == "string":
        return ")"
    if arg["is_vector"]:
        return ")"
    return ""

def generateCArgList(arglist):
    args = ""
    for argname in func["parameters"]:
        arg = func["parameters"][argname]
        
        args += '%(type)s %(name)s,' % {
            'type': generateCType(arg),
            'name': argname
        }
        
    return args[:-1]

def generateCCallList(arglist):
    args = ""
    for argname in func["parameters"]:
        arg = func["parameters"][argname]
        
        args += '%(cast)s%(name)s%(castend)s,' % {
            'cast': sanitizeCTypeInConvertFront(arg),
            'castend': sanitizeCTypeInConvertBack(arg),
            'name': argname
        }
        
    return args[:-1]

def generateCSig(func):
    return '%(return_type)s %(name)s(%(args)s)' % {
        'return_type': generateCType(func["return"]),
        'name': function_unique_name(func),
        'args': generateCArgList(func["parameters"])
    }
    
def generateCCall(func):
    return '%(convertFront)ssplashkit_lib::%(name)s(%(args)s)%(convertBack)s' % {
        #'return_type': generateCType(func["return"]),
        'name': func["name"],
        'args': generateCCallList(func["parameters"]),
        'convertFront': sanitizeCTypeOutConvertFront(func["return"]),
        'convertBack': sanitizeCTypeOutConvertBack(func["return"])
    }


for category_name in api:
    category = api[category_name]
    for func in category["functions"]:
        if not sigisSane(func):
            continue
        outputC("        "+generateCSig(func))
        outputC("{\n")
        outputC("            return "+generateCCall(func))
        outputC(";\n        }\n\n")

outputC("""
};


#include "SplashKitWasmGlue.cpp"
""");



# Generate the WebIDL Bindings


def sanitizeIDLTypeInParam(arg_type):
    if arg_type == "string":
        return "DOMString"
    if arg_type == "bool":
        return "boolean"
    if arg_type == "int":
        return "long"
    if arg_type == "unsigned int":
        return "unsigned long"
    if arg_type == "int8_t":
        return "byte"
    if arg_type == "char":
        return "byte"
    if arg_type == "window":
        return "SKwindow"
    return arg_type

def generateIDLType(t, force_ref, attribute=False):
    if t["type"] in structs:
        symbol = "" if t["is_pointer"] else "[Ref]" if (t["is_reference"] or force_ref) else "[Value]"
    else:
        symbol =  "[ERROR Pointers to base types unsuported]" if t["is_pointer"] else "[Ref]" if (t["is_reference"] and not t["type"]=="string" and False) else ""

    return '%(symbol)s %(attribute)s%(type)s%(array)s' % {
        'type': (sanitizeIDLTypeInParam(t["type_parameter"])) if t["is_vector"] else sanitizeIDLTypeInParam(t["type"]),
        'array': "[]" if (t["is_vector"] or ("is_array" in t and t["is_array"])) else "",
        'symbol': symbol,
        'attribute': "attribute " if attribute else "",
    }
    
def generateIDLArgList(arglist):
    args = ""
    for argname in func["parameters"]:
        arg = func["parameters"][argname]
        
        args += '%(type)s %(name)s,' % {
            'type': generateIDLType(arg, True),
            'name': argname
        }
        
    return args[:-1]

generate_sig_names = set()
def generateIDLSig(func):
    if function_unique_name(func) in generate_sig_names:
        print("Oh oh: ", function_unique_name(func))
    generate_sig_names.add(function_unique_name(func))
    return '%(return_type)s %(name)s(%(args)s)' % {
        'return_type': generateIDLType(func["return"], False),
        'name': function_unique_name(func),
        'args': generateIDLArgList(func["parameters"])
    }

def generateIDLStructFields(fieldlist):
    fields = ""
    for field_name in fieldlist:
        field = fieldlist[field_name]
        if field["type"]=="void":#TODO: Fix
            continue
        fields += '    %(type)s %(name)s;\n' % {
            'type': generateIDLType(field, False, attribute=True),
            'name': field_name
        }
    return fields

def sanitizeStructName(name):
    if name=="window":
        return "SKwindow"
    return name

def generateIDLStruct(struct):
    return "interface %(name)s {\n    void %(name)s();\n%(fields)s};\n" % {
        'name': sanitizeStructName(struct["name"]),
        'fields': generateIDLStructFields(struct["fields"]) if ("fields" in struct and struct["name"] not in ignore_structs) else ""
    }
    
def generateIDLEnum(enum):
    elist = ""
    for const in enum["constants"]:
        elist += "    \""+const+"\",\n"
    return "enum %(name)s {\n%(enums)s};\n" % {
        'name': enum["name"],
        'enums': elist
    }



for category_name in api:
    category = api[category_name]
    for struct in category["structs"]:
        outputIDL(generateIDLStruct(struct))
        
    for struct in category["typedefs"]:
        if struct["is_function_pointer"]:
            continue
        outputIDL(generateIDLStruct(struct))
       
    for enum in category["enums"]:
        outputIDL(generateIDLEnum(enum))


outputIDL("""interface SplashKitJavascript {
    void SplashKitJavascript();
""")
for category_name in api:
    category = api[category_name]
    for func in category["functions"]:
        if sigisSane(func):
            outputIDL("    "+generateIDLSig(func)+";\n")
outputIDL("""};""")



# Generate code to bind the functions from the module into the global scope
outputJS("""let SK;

""")
for category_name in api:
    category = api[category_name]
    for enum in category["enums"]:
        for const in enum["constants"]:
            outputJS("let "+const+";\n")
    outputJS("\n")
    for func in category["functions"]:
        if sigisSane(func):
            outputJS("let "+function_unique_name(func)+";\n")
    outputJS("\n\n")

outputJS("""
function initializeGlobalSplashKitScope(){
    SK = new Module.SplashKitJavascript();

""")
for category_name in api:
    category = api[category_name]
    for enum in category["enums"]:
        for const in enum["constants"]:
            outputJS("    "+const+" = Module."+const+";\n")
    outputJS("\n")
    for func in category["functions"]:
        if sigisSane(func):
            outputJS("    "+function_unique_name(func)+" = SK."+function_unique_name(func)+";\n")
    outputJS("\n\n")
outputJS("""};""")

#!/usr/bin/python

import sys
import os.path
import re

def filename_to_classname(file_name):
    words = file_name.split('_')
    return ''.join(word.title() for word in words)

def write_header(header_file_name, module_name, class_file_name, namespace):
    try:
        header_file = open(header_file_name, 'w')
    except IOError:
        print 'Could not open', header_file_name, 'for writing.'
        sys.exit()

    header_guard = 'BOUNCE_' + module_name.upper() + '_' + class_file_name.upper() + '_H_'
    class_name = filename_to_classname(class_file_name)

    header_content = '#ifndef ' + header_guard + '\n' + \
        '#define ' + header_guard + '\n\n' + \
        'namespace ' + namespace + ' {\n\n' + \
        '    class ' + class_name + ' {\n' + \
        '    private:\n\n' + \
        '    public:\n\n' + \
        '    };\n\n' + \
        '}' + \
        '\n\n#endif // ' + header_guard + '\n'

    header_file.write(header_content)
    header_file.close()

def write_source_file(source_file_name, class_file_name):
    try:
        source_file = open(source_file_name, 'w')
    except IOError:
        print 'Could not open', source_file_name, 'for writing.'
        sys.exit()

    class_name = filename_to_classname(class_file_name)
    source_content = '#include "' + class_name + '.h"\n'

    source_file.write(source_content)
    source_file.close()

def find_file_index(files, filename):
    file_index = -1
    for match in re.finditer('[^\s]*/(.*)', files):
        current_filename = match.group(1)
        if current_filename > filename:
            file_index = match.start(0)
            break;
        
    return file_index

def add_file(cmake_script, directory, filename, group):
    group_match = re.search('set[\s]*\\(' + group + '([^\\)]*)\\)', cmake_script, re.MULTILINE)
    group_start = group_match.start(1)
    
    new_file_index = find_file_index(group_match.group(1), filename)
    
    new_cmake_script = cmake_script[:group_start + new_file_index]
    new_cmake_script += directory + '/' + filename + '\n    '
    new_cmake_script += cmake_script[group_start + new_file_index:]
    
    return new_cmake_script

def add_header(cmake_script, header_filename):
    return add_file(cmake_script, '${MODULE_PUBLIC_INCLUDE_DIR}', header_filename, 'HEADERS')

def add_source(cmake_script, source_filename):
    return add_file(cmake_script, 'src', source_filename, 'SOURCES')
    
# main

try:
    module_name = sys.argv[1]
    class_file_name = sys.argv[2]
except IndexError:
    print 'Usage: add_class module class'
    sys.exit()

header_filename = class_file_name + '.h'
source_filename = class_file_name + '.cc'

header_path = 'headers/' + module_name + '/' + header_filename
source_path = 'sources/' + module_name + '/src/' + source_filename

if os.path.exists(header_path):
    print header_path, 'already exists.'
    sys.exit()

if os.path.exists(source_path):
    print source_path, 'already exists.'
    sys.exit()

namespace = 'bounce'

cmakelists_path = 'sources/' + module_name + '/CMakeLists.txt'
cmakelists_file = open(cmakelists_path, 'r')
cmakelists_script = cmakelists_file.read()
cmakelists_file.close()

new_cmake_script = add_header(cmakelists_script, header_filename)
new_cmake_script = add_source(new_cmake_script, source_filename)

cmakelists_file = open(cmakelists_path, 'w')
cmakelists_file.write(new_cmake_script)
cmakelists_file.close()

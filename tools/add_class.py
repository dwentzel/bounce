#!/usr/bin/python

import sys
import os.path

def filename_to_classname(file_name):
    words = file_name.split('_')
    return ''.join(word.title() for word in words)

try:
    module_name = sys.argv[1]
    class_name = sys.argv[2]
except IndexError:
    print 'Usage: add_class module class'
    sys.exit()

header_file_name = 'sources/' + module_name + '/include/' + class_name + '.h'
src_file_name = 'sources/' + module_name + '/src/' + class_name + '.cc'

if os.path.exists(header_file_name):
    print header_file_name, 'already exists.'
    sys.exit()

if os.path.exists(src_file_name):
    print src_file_name, 'already exists.'
    sys.exit()

header_guard = 'BOUNCE_' + module_name.upper() + '_' + class_name.upper() + '_'

namespace = 'bounce'

cc_class_name = filename_to_classname(class_name)

try:
    header_file = open(header_file_name, 'w')
except IOError:
    print 'Could not open', header_file_name, 'for writing.'
    sys.exit()

header_content = '#ifndef ' + header_guard + '\n' + \
    '#define ' + header_guard + '\n\n' + \
    'namespace ' + namespace + ' {\n\n' + \
    '    class ' + cc_class_name + ' {\n' + \
    '    private:\n\n' + \
    '    public:\n\n' + \
    '    };\n\n' + \
    '}' + \
    '\n\n#endif // ' + header_guard + '\n'

header_file.write(header_content)
header_file.close()

try:
    src_file = open(src_file_name, 'w')
except IOError:
    print 'Could not open', src_file_name, 'for writing.'
    sys.exit()

src_content = '#include "' + class_name + '.h"\n'

src_file.write(src_content)
src_file.close()

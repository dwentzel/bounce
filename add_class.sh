#!/bin/sh
modulename=$1
classname=$2

modulenameuc="$(echo ${modulename} | tr '[:lower:]' '[:upper:]')"
classnameuc="$(echo ${classname} | tr '[:lower:]' '[:upper:]')"

headerguard="BOUNCE_${modulenameuc}_${classnameuc}_"

headerfile=sources/$modulename/include/$classname.h
touch $headerfile

cat <<EOF >> $headerfile
#ifndef ${headerguard}
#define ${headerguard}

namespace bounce {

    class ${classname} {
    private:

    public:
    };

}

#endif // ${headerguard}
EOF

sourcefile=sources/$modulename/src/$classname.cc
touch $sourcefile

#git add $headerfile
#git add $sourcefile

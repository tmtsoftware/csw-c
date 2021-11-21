#!/bin/sh
#
# Creates an install dir with all dependencies, including native C libs
#
# shellcheck disable=SC2164

dir=install/csw-c
rm -rf $dir

os="$(uname -s)"
case "${os}" in
    Linux*)
      LIB_SUFFIX=so
      SYS_LIB_DIR=/lib/x86_64-linux-gnu;;
    Darwin*)
      LIB_SUFFIX=dylib
      SYS_LIB_DIR=/usr/local/lib;;
    *)
      echo "Unsupported os: $os"
esac
SYS_LIBS="hiredis cbor zlog uuid"
TARGET_LIB_DIR=$dir/lib/$os

set -x
for i in install $dir $dir/lib $dir/include $TARGET_LIB_DIR ; do test -d $i || mkdir $i; done
cp install/README.md $dir
cp csw/csw.h $dir/include

# Native C dependencies (copy with links)
for i in $SYS_LIBS; do
  cp $SYS_LIB_DIR/lib$i.$LIB_SUFFIX* $TARGET_LIB_DIR
done

make
(cd build/csw; tar cf - libcsw.$LIB_SUFFIX*) | (cd $TARGET_LIB_DIR; tar xf -)
if test "$os" = "Darwin" ; then
   (cd build/csw; tar cf - libcsw.*.$LIB_SUFFIX*) | (cd $TARGET_LIB_DIR; tar xf -)
   # Fix rpath on MacOS
   brew_install=/usr/local/opt
   lib_dir='@rpath'
   install_name_tool -change $brew_install/hiredis/lib/libhiredis.1.0.0.dylib $lib_dir/libhiredis.dylib $TARGET_LIB_DIR/libcsw.dylib
   install_name_tool -change $brew_install/libcbor/lib/libcbor.0.dylib $lib_dir/libcbor.dylib $TARGET_LIB_DIR/libcsw.dylib
   install_name_tool -change $brew_install/zlog/lib/libzlog.1.2.dylib $lib_dir/libzlog.dylib $TARGET_LIB_DIR/libcsw.dylib
   install_name_tool -change $brew_install/ossp-uuid/lib/libuuid.16.dylib $lib_dir/libuuid.dylib $TARGET_LIB_DIR/libcsw.dylib
fi

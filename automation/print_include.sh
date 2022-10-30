#!/usr/bin/bash
echo | gcc -Wp,-v -x c++ - -fsyntax-only `pkg-config vips-cpp glib-2.0 --cflags --libs` 2>&1 | grep '^ C:' | sed -e 's:^ ::' | tr '\n' ';'
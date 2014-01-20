
set -x 

gcc -o xelog_server_local.bin *.c -DCONFIG_USE_EXTERNAL_XELOG=1 -DXELOG_2_LOCAL=1 -DXELOG_PREFIX=\"tlog\"  -L./ -lxelog  -lm -lc -lpthread

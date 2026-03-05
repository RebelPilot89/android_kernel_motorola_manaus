cmd_fs/netfs/built-in.a := echo >/dev/null; rm -f fs/netfs/built-in.a; llvm-ar cDPrST fs/netfs/built-in.a fs/netfs/buffered_read.o fs/netfs/io.o fs/netfs/main.o fs/netfs/objects.o

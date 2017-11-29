program:
	echo "Creating parallel client/server programs"
	rpcgen prime.x
	gcc -o ../bin/client -pthread prclt.c prime_clnt.c
	gcc -o ../bin/server prsrv.c prime_svc.c
	#x86_64-w64-mingw32-gcc -o server.exe -D MINGW_BUILD prsrv.c prime_svc.c

	echo "Building sequential program"
	gcc -o ../bin/seq prseq.c

	echo "Building concurrent program"
	gcc -o ../bin/concurrent -pthread prcon.c

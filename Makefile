program:
	#rpcgen prime.x
	gcc -o client -pthread prclt.c prime_clnt.c
	gcc -o server prsrv.c prime_svc.c
	#x86_64-w64-mingw32-gcc -o server.exe -D MINGW_BUILD prsrv.c prime_svc.c
	gcc -o seq prseq.c

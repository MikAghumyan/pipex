valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes  \
	 --track-fds=yes  \
         --verbose \
         --log-file=valgrind-out.txt \
         $1 $2 $3 $4 $5 $6

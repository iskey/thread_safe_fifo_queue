CC= gcc

test_queue: test_queue.c queue.c
	$(CC) -o $@ $^ -lpthread

clean:
	@rm -fv test_queue
	@rm -fv *.o

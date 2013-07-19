CC= gcc

test_queue: test_queue.c queue.c
	$(CC) -o $@ $^

clean:
	@rm -fv test_queue
	@rm -fv *.o

/* Author: Robbert van Renesse 2018
 *
 * The interface is as follows:
 *	reader_t reader_create(int fd);
 *		Create a reader that reads characters from the given file descriptor.
 *
 *	char reader_next(reader_t reader):
 *		Return the next character or -1 upon EOF (or error...)
 *
 *	void reader_free(reader_t reader):
 *		Release any memory allocated.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "shall.h"

struct reader {
	int fd;
	int index;
	char c[512];
	int capacity;
};

reader_t reader_create(int fd){
	reader_t reader = (reader_t) calloc(1, sizeof(*reader));
	reader->fd = fd;
	reader->index = 0;
	reader->capacity = 0;
	return reader;
}

char reader_next(reader_t reader){

	if(reader->index < reader->capacity-1){
		return reader->c[++reader->index];
		
	}else{
		reader->capacity = read(reader->fd, reader->c, 512);
		reader->index = 0;
		if(reader->capacity <= 0){
			return EOF;
		} 
		return reader->c[0];
	}
}

void reader_free(reader_t reader){
	free(reader);
}

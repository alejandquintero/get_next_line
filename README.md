# get_next_line

get_next_line takes as a parameter a file descriptor, which is the content to read.

```
char *get_next_line(int fd);
```

Returns the line readed with the \n character and NULL when there is no more content to read or in case of an error.
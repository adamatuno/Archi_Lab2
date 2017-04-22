target = mul_or
encoder: *.o
	gcc *.o -o encoder
*.o: *.c
	gcc -c *.c
.PHONY: go
go:
	encoder.exe
	cp ../testcase/*.bin ../testcases/$(target)

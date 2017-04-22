comp = fc
case1 = pipeline3
case2 = add3
case3 = pipeline1
case4 = pipeline2
case5 = pipeline3
pipeline: *.o
	gcc *.o -o pipeline -O3
*.o: *.c
	gcc -c *.c
.PHONY: clean
clean:
	rm -f *.o *.bin *.rpt
.PHONY: decode
decode:
	cp ../testcases/$(case1)/*.bin ../decoder
.PHONY: testcase
testcase: *.o
	gcc *.o -o pipeline -O3
	cp ../testcase/*.bin ../simulator
	pipeline.exe
.PHONY: run
run: *.o
	gcc *.o -o pipeline -O3
	cp ../testcases/$(case1)/*.bin ../simulator
	pipeline.exe
.PHONY: runcomp
runcomp: *.o
	gcc *.o -o pipeline -O3
	cp ../testcases/$(case1)/*.bin ../simulator
	pipeline.exe
	$(comp) snapshot.rpt ../testcases/$(case1)/snapshot.rpt
	$(comp) error_dump.rpt ../testcases/$(case1)/error_dump.rpt
.PHONY: test2
test2: *.o
	gcc *.o -o pipeline -O3
	cp ../testcases/$(case2)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt ../testcases/$(case2)/snapshot.rpt
	$(comp) error_dump.rpt ../testcases/$(case2)/error_dump.rpt
	rm -f *.bin *.rpt
	cp ../testcases/$(case3)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt ../testcases/$(case3)/snapshot.rpt
	$(comp) error_dump.rpt ../testcases/$(case3)/error_dump.rpt
	rm -f *.bin *.rpt
	cp ../testcases/$(case4)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt ../testcases/$(case4)/snapshot.rpt
	$(comp) error_dump.rpt ../testcases/$(case4)/error_dump.rpt
	rm -f *.bin *.rpt
	cp ../testcases/$(case5)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt ../testcases/$(case5)/snapshot.rpt
	$(comp) error_dump.rpt ../testcases/$(case5)/error_dump.rpt
	rm -f *.bin *.rpt

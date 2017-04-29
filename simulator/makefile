comp = fc
case1 = my
case2 = pipeline4
case3 = pipeline3
case4 = pipeline2
case5 = pipeline1
case6 = mul_or
case7 = branch
case8 = func
case9 = recur

testcases = ../valid_testcase
pipeline: *.o
	gcc *.o -o pipeline -O3
*.o: *.c
	gcc -c *.c
.PHONY: clean
clean:
	rm -f *.o *.bin *.rpt
.PHONY: decode
decode:
	cp $(testcases)/$(case1)/*.bin ../decoder
.PHONY: testcase
testcase: *.o
	gcc *.o -o pipeline -O3
	cp ../testcase/*.bin ../simulator
	pipeline.exe
.PHONY: run
run: *.o
	gcc *.o -o pipeline -O3
	cp $(testcases)/$(case1)/*.bin ../simulator
	pipeline.exe
.PHONY: runcomp
runcomp: *.o
	gcc *.o -o pipeline -O3
	cp $(testcases)/$(case1)/*.bin ../simulator
	pipeline.exe
	$(comp) snapshot.rpt $(testcases)/$(case1)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case1)/error_dump.rpt
.PHONY: test2
test2: *.o
	gcc *.o -o pipeline -O3
	cp $(testcases)/$(case2)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case2)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case2)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case3)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case3)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case3)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case4)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case4)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case4)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case5)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case5)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case5)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case6)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case6)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case6)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case7)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case7)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case7)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case8)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case8)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case8)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case9)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case9)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case9)/error_dump.rpt
	rm -f *.bin *.rpt

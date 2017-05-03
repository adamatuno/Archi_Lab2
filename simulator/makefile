comp = fc
case1 = 41
case2 = 42
case3 = 43
case4 = 44
case5 = 45
case6 = 46
case7 = 47
case8 = 48
case9 = 49
case10 = 10
case11 = 20
case12 = 30
case13 = 40
case14 = my

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
	cp $(testcases)/$(case10)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case10)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case10)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case11)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case11)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case11)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case12)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case12)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case12)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case13)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case13)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case13)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case14)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case14)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case14)/error_dump.rpt
	rm -f *.bin *.rpt
	cp $(testcases)/$(case1)/*.bin ../simulator
	./pipeline
	$(comp) snapshot.rpt $(testcases)/$(case1)/snapshot.rpt
	$(comp) error_dump.rpt $(testcases)/$(case1)/error_dump.rpt
	rm -f *.bin *.rpt

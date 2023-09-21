CC=g++
CFLAGS=-Wall -Wextra -Werror
TFLAGS=-lgtest -std=c++17
SRC=model/data/*.cc model/parser/*.cc
TEST=tests/tests.cc
TEST_OUTPUT=unit_test
GCOV_PATH=report
APPNAME=3DViewer_V2.0
ARCHIVE=Archive_3DViewer_V2.0
DOC_PATH=documentation

all: gcov_report

clean:
	rm -rf *.gcda *.gcno *.info $(TEST_OUTPUT) $(GCOV_PATH)
	cd tests && rm -rf objects

install: uninstall
	mkdir build
	cd view && qmake && make && make clean && rm Makefile && mv view.app ../build
	cd build && mv view.app $(APPNAME)

uninstall:
	rm -rf build

gcov_report: clean undist
	mkdir $(GCOV_PATH) && cd $(GCOV_PATH) && $(CC) --coverage ../model/data/*.cc ../model/parser/*.cc ../tests/tests.cc $(CFLAGS) $(TFLAGS) -o gcov_report
	./$(GCOV_PATH)/gcov_report
	lcov -t "gcov_report" -o $(GCOV_PATH)/gcov_report.info --no-external -c -d ./
	genhtml -o report $(GCOV_PATH)/gcov_report.info
	open $(GCOV_PATH)/index.html

test: clean undist
	$(CC) $(TEST) $(SRC) $(CFLAGS) $(TFLAGS) -o $(TEST_OUTPUT)
	./$(TEST_OUTPUT)

dvi:
	cd $(DOC_PATH) && doxygen Doxyfile && cd ..
	open $(DOC_PATH)/html/index.html

dist: install
	rm -rf $(ARCHIVE)/
	mkdir $(ARCHIVE)/
	mkdir $(ARCHIVE)/src
	cp -r ./build/$(APPNAME) $(ARCHIVE)/src/
	tar cvzf $(ARCHIVE).tgz $(ARCHIVE)/
	rm -rf $(ARCHIVE)/

undist:
	cd tests && rm -rf objects && unzip objects.zip
	cd tests && rm -rf __MACOSX
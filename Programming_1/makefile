make: Solve.h Solve.cpp
	g++ -o Solve Solve.h Solve.cpp
	./Solve

report: report.tex
	xelatex report
	xelatex report
	rm report.aux
	rm report.log
	okular report.pdf

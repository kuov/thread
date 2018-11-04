cc = g++
prom = thread2
deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.cpp")
obj = $(src:%.c=%.o) 

$(prom): $(obj)
	$(cc) -std=c++11 -o $(prom) $(obj) -lpthread

%.o: %.c $(deps)
	$(cc) -std=c++11 -c $< -o $@

clean:
	rm -rf  $(prom)

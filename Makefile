.SILENT:
code: main.cpp source/item.cpp source/treeSO.cpp
	cd build && make
	cp build/code treeSO

run: code
	./treeSO
	
mk:
	mkdir -p build
	# PARA MAC SE USA
	cd build && cmake ..
	# PARA WINDOWS SE USA
	# cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg.cmake

clean:
	rm -fr treeSO build

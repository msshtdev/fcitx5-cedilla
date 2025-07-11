check: format tidy lint
	@echo "PASS"

lint:
	python -m venv .venv && \
	. .venv/bin/activate && \
	pip install cpplint && \
	find src/ -name '*.cpp' -o -name '*.hpp' | \
	xargs cpplint \
	  --filter=-whitespace/indent_namespace,-build/include_order,-runtime/references,-build/c++17,-build/include_subdir

tidy:
	rm -rf ./build
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B build
	find src/ -name '*.cpp' -o -name '*.hpp' | xargs -I{} clang-tidy -p build {}

format:
	find src/  -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i

install:
	@rm -rf build
	@mkdir -p build
	@cd build && \
	cmake .. \
	    -DCMAKE_INSTALL_PREFIX=/usr \
	    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	    -DENABLE_GTK3_IM_MODULE=ON \
	    -DENABLE_QT_IM_MODULE=ON
	@cmake --build build -- -j$$(nproc)
	@sudo cmake --install build

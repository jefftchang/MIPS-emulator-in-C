SOURCES := sim.c processor.c load_program.c disassemble.c memory.c
HEADERS := elf.h load_program.h processor.h disassemble.h memory.h

ASM_TESTS := simple insts rt3 rt13 rt25

all: mips-sim $(addprefix mipscode/, $(ASM_TESTS))

.PHONY: disasmtest runtest

mipscode/%.o: mipscode/%.s
	mips-gcc -c -o $@ $<

$(addprefix mipscode/, $(ASM_TESTS)): %: %.s mipscode/mips.ld
	mips-gcc -o $(patsubst %.s, %.o, $<) -c $<
	mips-ld -o $@ $(patsubst %.s, %.o, $<) -T mipscode/mips.ld

mips-sim: $(SOURCES) $(HEADERS)
	gcc -g -Wall -Werror -Wfatal-errors -O2 -o $@ $(SOURCES)

disasmtest: mips-sim mipscode/insts
	./mips-sim -d mipscode/insts > insts.dump
	@diff insts.dump mipscode/insts.dump && echo "DISASSEMBLY TEST PASSED!" || echo "DISASSEMBLY TEST FAILED!"

runtest: mips-sim mipscode/insts
	./mips-sim -r mipscode/insts > insts.trace
	@diff insts.trace mipscode/insts.trace && echo "RUN TEST PASSED!" || echo "RUN TEST FAILED!"

clean:
	rm -f mips-sim $(addprefix mipscode/,  $(ASM_TESTS)) $(addsuffix .o, $(addprefix mipscode/,  $(ASM_TESTS))) *.dump *.trace

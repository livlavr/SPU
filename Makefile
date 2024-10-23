CXX                = gcc-14

STACK_SRC          = stack.cpp recalloc.cpp stack_dump.cpp stack_public.cpp stack_security.cpp

ASSEMBLY_SRC       = assembly.cpp size_of_text.cpp
ASSEMBLY_TARGET    = assembly

DISASSEMBLY_SRC    = disassembly.cpp size_of_text.cpp
DISASSEMBLY_TARGET = disassembly

PROCESSOR_SRC      = processor.cpp size_of_text.cpp
PROCESSOR_TARGET   = processor

SUBMODULE_SRC      = Custom-asserts/Color/color_printf.cpp #TODO stack compiling

BUILD_DIR    = ./build/
SRC_DIR      = ./src/
STACK_DIR    = ./Stack/
CFLAGS       = -I inc -I Custom-asserts -I Custom-asserts/Color -I Stack/inc -I Stack/Color-printf

TARGET       = SPU
OBJECT       = $(patsubst %.cpp, %.o, $(SRC))
BUILD_OBJ    = $(addprefix $(BUILD_DIR), $(OBJECT))

GREEN_TEXT   = \033[1;32m
YELLOW_TEXT  = \033[1;33m
DEFAULT_TEXT = \033[0m

DED_FLAGS    = -D _DEBUG -ggdb2 -std=c++17 -O0 -Wall -Wextra -Weffc++                                     \
			    -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations                     \
				-Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported                      \
				-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral           \
				-Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor \
				-Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls \
				-Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2        \
				-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types                \
				-Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef                     \
				-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros                              \
				-Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing                        \
				-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation       \
				-fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer        \
				-Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla

vpath %.o   $(BUILD_DIR)
vpath %.cpp $(SRC_DIR)

.PHONY: clean all
all   :
	clear
	make quick_assembly
	make processor
	@printf "$(GREEN_TEXT)$(TARGET) COMPILED$(DEFAULT_TEXT)\n"
	$(addprefix $(BUILD_DIR), $(PROCESSOR_TARGET))

$(TARGET) :  $(BUILD_DIR) $(OBJECT)
	$(CXX)   $(BUILD_OBJ) -o $(TARGET) -D _NDEBUG
	@printf "$(GREEN_TEXT)$(TARGET) COMPILED$(DEFAULT_TEXT)\n"

$(BUILD_DIR) :
	mkdir -p build

$(OBJECT) : %.o : %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $(addprefix $(BUILD_DIR), $@)

quick_assembly : $(addprefix $(SRC_DIR), $(ASSEMBLY_SRC))
	@$(CXX) $(CFLAGS) $^ $(SUBMODULE_SRC) -o $(addprefix $(BUILD_DIR), $(ASSEMBLY_TARGET))
	$(addprefix $(BUILD_DIR), $(ASSEMBLY_TARGET))

assembly : $(addprefix $(SRC_DIR), $(ASSEMBLY_SRC))
	clear
	@$(CXX) $(CFLAGS) $^ $(SUBMODULE_SRC) -o $(addprefix $(BUILD_DIR), $(ASSEMBLY_TARGET))
	@printf "$(GREEN_TEXT)$(ASSEMBLY_TARGET) COMPILED$(DEFAULT_TEXT)\n"
	$(addprefix $(BUILD_DIR), $(ASSEMBLY_TARGET))

disassembly : $(addprefix $(SRC_DIR), $(DISASSEMBLY_SRC))
	clear
	@$(CXX) $(CFLAGS) $^ $(SUBMODULE_SRC) -o $(addprefix $(BUILD_DIR), $(DISASSEMBLY_TARGET))
	@printf "$(GREEN_TEXT)$(DISASSEMBLY_TARGET) COMPILED$(DEFAULT_TEXT)\n"
	$(addprefix $(BUILD_DIR), $(DISASSEMBLY_TARGET))

processor : $(addprefix $(SRC_DIR), $(PROCESSOR_SRC))
	@$(CXX) $(CFLAGS) $^ $(SUBMODULE_SRC) $(addprefix $(STACK_DIR),\
	$(addprefix $(SRC_DIR), $(STACK_SRC))) -o $(addprefix $(BUILD_DIR), $(PROCESSOR_TARGET))

quick_processor : $(addprefix $(SRC_DIR), $(PROCESSOR_SRC))
	clear
	@$(CXX) $(CFLAGS) $^ $(SUBMODULE_SRC) $(addprefix $(STACK_DIR),\
	$(addprefix $(SRC_DIR), $(STACK_SRC))) -o $(addprefix $(BUILD_DIR), $(PROCESSOR_TARGET))
	@printf "$(GREEN_TEXT)$(PROCESSOR_TARGET) COMPILED$(DEFAULT_TEXT)\n"
	$(addprefix $(BUILD_DIR), $(PROCESSOR_TARGET))

doxy :
	doxygen

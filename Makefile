
# Specify the compiler
CC=gcc

# Compilation options
OMP_FLAGS= -fopenmp -lm -lSDL2

# Directory with common headers
COMMON_DIR=./

# Compile all executable
all: mainFinal.o mainInterface.o mainTemps.o

mainFinal.o: mainFinal.c maillage.c listIndiceList.c listPoint.c listIndice.c point.c hedge.c matriceTriangle.c
	$(CC) $^ $(CCFLAGS) $(OMP_FLAGS) $(LIBS) -I $(COMMON_DIR) -o $@

mainTemps.o: mainTemps.c maillage.c listIndiceList.c listPoint.c listIndice.c point.c hedge.c matriceTriangle.c
	$(CC) $^ $(CCFLAGS) $(OMP_FLAGS) $(LIBS) -I $(COMMON_DIR) -o $@

mainInterface.o: mainInterface.c maillage.c listIndiceList.c listPoint.c listIndice.c point.c hedge.c matriceTriangle.c
	$(CC) $^ $(CCFLAGS) $(OMP_FLAGS) $(LIBS) -I $(COMMON_DIR) -o $@
#pi: pi.c
#	$(CC) $^ $(CCFLAGS)  $(OMP_FLAGS) $(LIBS) -I $(COMMON_DIR) -o $@
#
#mandel: mandel.c
#	$(CC) $^ $(CCFLAGS)  $(OMP_FLAGS) $(LIBS) -I $(COMMON_DIR) -o $@

# Remove non sources files
clean:
	rm -f hello pi mandel
	rm -f *.o *~

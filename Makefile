tasks := td8 td16 td32 td64 tx8 tx16 tx32 tx64 tx128 tx256 tx512 \
         bx8 bx16 bx32 bx64 bx128 bx256 bx512
		 
getflags = $(if $(findstring d8,$1),-D id8,) \
           $(if $(findstring d16,$1),-D id16,) \
           $(if $(findstring d32,$1),-D id32,) \
           $(if $(findstring d64,$1),-D id64,) \
           $(if $(findstring x8,$1),-D ix8,) \
           $(if $(findstring x16,$1),-D ix16,) \
           $(if $(findstring x32,$1),-D ix32,) \
           $(if $(findstring x64,$1),-D ix64,) \
           $(if $(findstring x128,$1),-D ix128,) \
           $(if $(findstring x256,$1),-D ix256,) \
           $(if $(findstring x512,$1),-D ix512,) \
		   $(if $(findstring b,$1),-D BINARY,) 

all: help
		
eparts: 
	gcc -I include src/partition_diagram.c src/eparts.c -o eparts
	
graph:
	gcc -I include src/partition_diagram.c src/pdgraph.c -o graph

$(tasks):
	gcc -I include src/partition_diagram.c src/acalc.c src/big_int.c \
	               src/partition.c src/polynomial.c \
				   $(call getflags,$@) -o acalc
	
help:
	@echo Read ./README.md for usage help.
	
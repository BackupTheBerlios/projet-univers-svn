
INCLUDE_DIR = -I../..
LIB_DIR = -L../../base/compilation

noinst_LIBRARIES = libcompilateur.a
libcompilateur_a_SOURCES = \
../utilitaires_opencxx.cpp 

# un sérialiseur

#serialisable.la : ../serialisable.mc ../serialisable.mh
#	$(OCC) $(INCLUDE_DIR) $(LIB_DIR) -m ../serialisable.mc -lbase

serialiseur : ../serialisable.mc ../serialisable.mh
	$(OCC) $(INCLUDE_DIR) -L. -lcompilateur ../serialisable.mc $ -o $@ -locc -lltdl $(LIB_DIR) -lbase

#serialisable.o : ../serialisable.mc ../serialisable.mh
#	$(OCC) $(INCLUDE_DIR) -c ../serialisable.mc -o $@


regles_programmation : ../regles_programmation.mh ../regles_programmation.mc
	$(OCC) ../regles_programmation.mc -o $@ -locc -lltdl

# all  	
all-am : serialiseur regles_programmation


# Tests 

check-am : ./regles_programmation
	./serialiseur $(INCLUDE_DIR) -v -- ../test/test2.cc

#	./serialiseur $(INCLUDE_DIR) -v -Msortie=bonjour -- ../test/test.cc
	
#	$(OCC) $(INCLUDE_DIR) -S Serialisable -- ../test/test2.cc
#	./regles_programmation -I../.. -- -I../.. ../test/test2.cc

#check-am : serialisable.la
#	$(OCC) -S Serialisable ../test/test2.cc -o test2_occ

#check-am : ./serialiseur serialisable.la
#	$(OCC) -S Serialisable -- ../test/test.cc

#	./serialiseur $(INCLUDE_DIR) -c ../test/test2.cc -g -$(INCLUDE_DIR)

#./serialiseur $(INCLUDE_DIR) -- -g -$(INCLUDE_DIR) -c ../test/test.cc
	

clean-am :
	rm -f *.ii *.o *.occ *.lo *.so *.la *.feedback *.cc \
		test2_occ serialiseur
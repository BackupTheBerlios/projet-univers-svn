
INCLUDES = -I..
CXX = @CXX@
OCC = occ2

EXTRA_PROGRAMS = compilateur


# création du compilateur modifié par les méta-classes

compilateur : serialisable.o regles_programmation.o
	$(CXX) serialisable.o regles_programmation.o -locc -lltdl -o $@

serialisable.o : ../serialisable.mc ../serialisable.mh
	$(OCC) -c ../serialisable.mc -o $@
  
regles_programmation.o : ../regles_programmation.mc ../regles_programmation.mh
	$(OCC) -c ../regles_programmation.mc -o $@

# compilation du test proprement dit

test_meta : ./compilateur ../test/test.cc
	./compilateur -- -C -o $@ ../test/test.cc
        
all-am : compilateur

check-am : test_meta

clean-am :
	rm -f *.ii *.o *.occ compilateur test_meta *.lo *.feedback
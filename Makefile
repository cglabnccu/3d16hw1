# Define a macro for the object files 
OBJECTS= main.o RGBpixmap.o Actor.o KeyEventController.o MainActor.o RGBpixmapController.o Timer.o Vec3.o

# Define a macro for the library file 
LIBES= -framework GLUT -framework OpenGL

# use macros rewrite makefile 
prog: $(OBJECTS) 
	c++ $(OBJECTS) $(LIBES) -o prog 
clean: $(OBJECTS)
	rm -rvf $(OBJECTS) prog

LIBS = -lGL -lglfw3
INC = -Iglad/include -Igui/include -Iinclude
CC = g++
EXEC = gl
CFLAGS = -O3
DEBUGFLAGS = -g -O0

SRC = src/main.cpp src/shader.cpp
GLAD_SRC = glad/src/gl.c
GUI_BASE_SRC = gui/src/imgui.cpp gui/src/imgui_impl_glfw.cpp gui/src/imgui_impl_opengl3.cpp gui/src/imgui_draw.cpp gui/src/imgui_widgets.cpp gui/src/imgui_tables.cpp
GUI_DEMO = gui/src/imgui_demo.cpp

.PHONY: gui clean nogui debug_nogui debug_gui

debug_nogui:
	$(CC) $(DEBUGFLAGS) $(SRC) $(GLAD_SRC) -o $(EXEC) $(INC) $(LIBS)

nogui:
	$(CC) $(CFLAGS) $(SRC) $(GLAD_SRC) -o $(EXEC) $(INC) $(LIBS)

debug_gui:
	$(CC) $(DEBUGFLAGS) $(SRC) $(GLAD_SRC) $(GUI_BASE_SRC) $(GUI_DEMO) -o $(EXEC) $(INC) $(LIBS) -DGUI_ON

gui:
	$(CC) $(CFLAGS) $(SRC) $(GLAD_SRC) $(GUI_BASE_SRC) $(GUI_DEMO) -o $(EXEC) $(INC) $(LIBS) -DGUI_ON

clean:
	rm -f $(EXEC)

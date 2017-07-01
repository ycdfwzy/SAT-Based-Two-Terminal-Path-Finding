include config.mk
main$(EXE_EXT): main$(OBJ_EXT) grids$(OBJ_EXT) libz3$(SO_EXT) checker$(OBJ_EXT) visual$(OBJ_EXT)
	$(LINK) $(LINK_OUT_FLAG)main$(EXE_EXT) $(LINK_FLAGS) main$(OBJ_EXT) grids$(OBJ_EXT) checker$(OBJ_EXT) visual$(OBJ_EXT) libz3.lib $(LINK_EXTRA_FLAGS)
main$(OBJ_EXT): main.cpp grids.h checker.h visual.h
	$(CXX) $(CXXFLAGS) $(OS_DEFINES) $(EXAMP_DEBUG_FLAG) $(CXX_OUT_FLAG)main$(OBJ_EXT) $(LINK_FLAGS) -I.\src\api -I.\src\api\c++ main.cpp /O2
grids$(OBJ_EXT): grids.cpp grids.h
	$(CXX) $(CXXFLAGS) $(OS_DEFINES) $(EXAMP_DEBUG_FLAG) $(CXX_OUT_FLAG)grids$(OBJ_EXT) $(LINK_FLAGS) -I.\src\api -I.\src\api\c++ grids.cpp /O2
checker$(OBJ_EXT): checker.cpp checker.h
	$(CXX) $(CXXFLAGS) $(OS_DEFINES) $(EXAMP_DEBUG_FLAG) $(CXX_OUT_FLAG)checker$(OBJ_EXT) $(LINK_FLAGS) -I.\src\api -I.\src\api\c++ checker.cpp /O2
visual$(OBJ_EXT): visual.cpp visual.h grids.h checker.h
	$(CXX) $(CXXFLAGS) $(OS_DEFINES) $(EXAMP_DEBUG_FLAG) $(CXX_OUT_FLAG)visual$(OBJ_EXT) $(LINK_FLAGS) -I.\src\api -I.\src\api\c++ visual.cpp /O2
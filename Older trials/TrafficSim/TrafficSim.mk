##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=TrafficSim
ConfigurationName      :=Debug
WorkspacePath          :="C:/Users/Lipika Kanojia/Documents/TrafficSim"
ProjectPath            :="C:/Users/Lipika Kanojia/Documents/TrafficSim/TrafficSim"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Lipika Kanojia
Date                   :=13/06/2017
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="TrafficSim.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -std=c++14 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/cNodes.cpp$(ObjectSuffix) $(IntermediateDirectory)/cVehicle.cpp$(ObjectSuffix) $(IntermediateDirectory)/cNetwork.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Lipika Kanojia/Documents/TrafficSim/TrafficSim/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/cNodes.cpp$(ObjectSuffix): cNodes.cpp $(IntermediateDirectory)/cNodes.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Lipika Kanojia/Documents/TrafficSim/TrafficSim/cNodes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cNodes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cNodes.cpp$(DependSuffix): cNodes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cNodes.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/cNodes.cpp$(DependSuffix) -MM cNodes.cpp

$(IntermediateDirectory)/cNodes.cpp$(PreprocessSuffix): cNodes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cNodes.cpp$(PreprocessSuffix) cNodes.cpp

$(IntermediateDirectory)/cVehicle.cpp$(ObjectSuffix): cVehicle.cpp $(IntermediateDirectory)/cVehicle.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Lipika Kanojia/Documents/TrafficSim/TrafficSim/cVehicle.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cVehicle.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cVehicle.cpp$(DependSuffix): cVehicle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cVehicle.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/cVehicle.cpp$(DependSuffix) -MM cVehicle.cpp

$(IntermediateDirectory)/cVehicle.cpp$(PreprocessSuffix): cVehicle.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cVehicle.cpp$(PreprocessSuffix) cVehicle.cpp

$(IntermediateDirectory)/cNetwork.cpp$(ObjectSuffix): cNetwork.cpp $(IntermediateDirectory)/cNetwork.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Lipika Kanojia/Documents/TrafficSim/TrafficSim/cNetwork.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cNetwork.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cNetwork.cpp$(DependSuffix): cNetwork.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cNetwork.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/cNetwork.cpp$(DependSuffix) -MM cNetwork.cpp

$(IntermediateDirectory)/cNetwork.cpp$(PreprocessSuffix): cNetwork.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cNetwork.cpp$(PreprocessSuffix) cNetwork.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/



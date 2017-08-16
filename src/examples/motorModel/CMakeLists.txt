link_directories(${LIB_DIR})

include_directories(/opt/ros/kinetic/include)

link_directories(/opt/ros/kinetic/lib)

link_libraries(controllers
				tgcreator
                util
                sensors
                controllers
                core    
                terrain 
                tgOpenGLSupport)

add_library(TimestepTest SHARED
			tsTestRig.cpp)

add_executable(AppTSTest
    tsTestRig.cpp
    AppTimestepTest.cpp
) 

target_link_libraries(AppTSTest roscpp rosconsole roscpp_serialization)

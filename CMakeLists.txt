cmake_minimum_required(VERSION 3.21)
project(TwiniGolfSFML LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories(src/GUI)
include_directories(src/const)
include_directories(src/entity)
include_directories(src/SFX)
include_directories(src/states)
include_directories(src/utils)

add_executable(TwiniGolfSFML 
    src/GUI/button.h 
    src/GUI/component.h 
    src/GUI/container.h 
    src/GUI/label.h 
    src/SFX/music_player.h 
    src/SFX/sound_player.h 
    src/application.h 
    src/const/state_identifiers.h 
    src/entity/ball.h 
    src/entity/entity.h 
    src/entity/hole.h 
    src/entity/point.h 
    src/entity/power_bar.h 
    src/entity/tile.h 
    src/player.h 
    src/states/game_state.h 
    src/states/level_state.h 
    src/states/menu_state.h 
    src/states/state.h 
    src/states/state_stack.h 
    src/states/title_state.h 
    src/states/win_state.h 
    src/utils/resource_holder.h 
    src/utils/resource_identifiers.h 
    src/world.h
    src/GUI/button.cpp 
    src/GUI/component.cpp 
    src/GUI/container.cpp 
    src/GUI/label.cpp 
    src/SFX/music_player.cpp 
    src/SFX/sound_player.cpp 
    src/application.cpp 
    src/entity/ball.cpp 
    src/entity/entity.cpp 
    src/entity/hole.cpp 
    src/entity/point.cpp 
    src/entity/power_bar.cpp 
    src/entity/tile.cpp 
    src/main.cpp 
    src/player.cpp 
    src/states/game_state.cpp 
    src/states/level_state.cpp 
    src/states/menu_state.cpp 
    src/states/state.cpp 
    src/states/state_stack.cpp 
    src/states/title_state.cpp 
    src/states/win_state.cpp 
    src/world.cpp
)
target_link_libraries(TwiniGolfSFML PRIVATE sfml-window sfml-graphics sfml-system sfml-audio)
target_compile_features(TwiniGolfSFML PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET TwiniGolfSFML POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:TwiniGolfSFML> $<TARGET_FILE_DIR:Polyomino> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS TwiniGolfSFML)

linux {
    CONFIG += link_pkgconfig
    PKGCONFIG += sfml-window sfml-graphics sfml-system sfml-audio
}

SOURCES += \
    src/GUI/button.cpp \
    src/GUI/component.cpp \
    src/GUI/container.cpp \
    src/GUI/label.cpp \
    src/SFX/music_player.cpp \
    src/SFX/sound_player.cpp \
    src/application.cpp \
    src/entity/ball.cpp \
    src/entity/entity.cpp \
    src/entity/hole.cpp \
    src/entity/point.cpp \
    src/entity/power_bar.cpp \
    src/entity/tile.cpp \
    src/main.cpp \
    src/player.cpp \
    src/polyomino.cpp \
    src/states/game_state.cpp \
    src/states/menu_state.cpp \
    src/states/state.cpp \
    src/states/state_stack.cpp \
    src/states/title_state.cpp \
    src/states/win_state.cpp \
    src/world.cpp

HEADERS += \
    src/GUI/button.h \
    src/GUI/component.h \
    src/GUI/container.h \
    src/GUI/label.h \
    src/SFX/music_player.h \
    src/SFX/sound_player.h \
    src/application.h \
    src/const/state_identifiers.h \
    src/entity/ball.h \
    src/entity/entity.h \
    src/entity/hole.h \
    src/entity/point.h \
    src/entity/power_bar.h \
    src/entity/tile.h \
    src/player.h \
    src/polyomino.h \
    src/states/game_state.h \
    src/states/menu_state.h \
    src/states/state.h \
    src/states/state_stack.h \
    src/states/title_state.h \
    src/states/win_state.h \
    src/utils/resource_holder.h \
    src/utils/resource_identifiers.h \
    src/world.h

target_sources(${PROJECT_NAME} PRIVATE
    game.cpp
    Sprite/Sprite.cpp
    DisplayBridge/DisplayBridge.cpp
    AnimationPlayer/AnimationPlayer.cpp
    Clown.cpp
    Crowd.cpp
    )


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
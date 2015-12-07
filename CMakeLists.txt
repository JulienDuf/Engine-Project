cmake_minimum_required(VERSION 3.1)

project(Engine)

if(APPLE)
    set(SDL2_INCLUDE_DIR /Library/Frameworks/SDL2.framework/Headers/SDL.h)
    set(SDL2_IMAGE_DIR /Library/Frameworks/SDL2_image.framework/Headers/SDL_image.h)
    set(SDL2_TTF_DIR /Library/Frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h)
    set(SDL2_MIXER_DIR /Library/Frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h)
    set(GL_INCLUDE_DIR /System/Library/Frameworks/OpenGL.framework/Headers/OpenGL.h)
    set(SDL2_LIBRARY /usr/local/lib/libSDL2.dylib)
    set(GL_LIBRARY /System/Library/Frameworks/OpenGL.framework/Libraries/libGL.dylib)
    set(SDL2_IMAGE_LIBRARY /usr/local/lib/libSDL2_image.dylib)
    set(SDL2_TTF_LIBRARY /usr/local/lib/libSDL2_ttf.dylib)
    set(SDL2_MIXER_LIBRARY /usr/local/lib/libSDL2_mixer.dylib)
else(APPLE)
    set(SDL2_INCLUDE_DIR /usr/include/SDL2/SDL.h)
    set(SDL2_IMAGE_DIR /usr/include/SDL2/SDL_image.h)
    set(SDL2_TTF_DIR /usr/include/SDL2/SDL_ttf.h)
    set(SDL2_MIXER_DIR /usr/include/SDL2/SDL_mixer.h)
    set(SDL2_NET_DIR /usr/include/SDL2/SDL_net.h)
    set(GL_INCLUDE_DIR /usr/include/GL/gl.h)
    set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)
    set(SDL2_IMAGE_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2_image.so)
    set(SDL2_TTF_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)
    set(SDL2_MIXER_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2_mixer.so)
    set(SDL2_NET_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2_net.so)
    set(GL_LIBRARY /usr/lib/x86_64-linux-gnu/libGL.so)
endif(APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GL_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_DIR})
include_directories(${SDL2_TTF_DIR})
include_directories(${SDL2_MIXER_DIR})

set(SOURCE_FILES main.cpp ArbreAVL.h
        Button.h Control.h Camera.h Chrono.h
        Entity.h EntityManager.h Engine.h EventObject.h EventManager.h Event.h
        Font.h Game.h Info.h Image.h Label.h Model.h
        RessourceManager.h Ressource.h RenderObject.h Rect.h RenderedModel.h RenderManager.h RenderObject.h SceneObject.h
        Sprite.h SocketException.h Singleton.h ServerClient.h Scene.h ScrollBar.h Server.h Shader.h
        TextTexture.h Timer.h TextBox.h Text.h Thread.h Time.h TextContainer.h Texture.h Vector2.h Vector3.h Window.h Light.h Mat4.h Math.h ShadowMap.h)
add_executable(Engine ${SOURCE_FILES})
target_link_libraries(Engine ${SDL2_LIBRARY})
target_link_libraries(Engine ${SDL2_IMAGE_LIBRARY})
target_link_libraries(Engine ${SDL2_TTF_LIBRARY})
target_link_libraries(Engine ${SDL2_MIXER_LIBRARY})
target_link_libraries(Engine ${SDL2_NET_LIBRARY})
target_link_libraries(Engine ${GL_LIBRARY})
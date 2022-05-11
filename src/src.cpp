#include"sdl.h"
#include"texture.h"
#include"func.h"
#include"obj.h"
#include"graphic.h"

#include<vector>
#include<string>

int main(int argc, char** argv) {
    try {
        auto _sdl=sdl{};
        auto _img=img{};
        auto _mus=mus{};
        auto window=create_window("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
        if(!window) throw std::runtime_error{"Unable to create window"};
        auto render=create_renderer(window.get(), -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        if(!render) throw std::runtime_error{"Unable to create renderer"};
        auto bgm=load_music("build/bgm/bgm3.mp3");
        if(!bgm) throw std::runtime_error{"Unable to load bgm"};

        auto hero_idle=Texture{"build/img/main.png", render.get()};
        std::vector<Texture> main_dead;
        for(int i=0;i<9;i++) {
            auto tmp=Texture{"build/img/main_dead_"+std::to_string(i+1)+".png", render.get()};
            main_dead.push_back(tmp);
        }

        auto hero=heroin{1280/2, 720/2, 0, 0, 100};

        auto quit=false;
        SDL_Event e;
        // Mix_PlayMusic(bgm.get(), -1);
        int frame=0;
        bool occured=false;
        int count=0;
        
        while(!quit) {
            while(SDL_PollEvent(&e)!=0) {
                if(e.type==SDL_QUIT) quit=true;
            }
            const Uint8* keyStates=SDL_GetKeyboardState(nullptr);
            if(keyStates[SDL_SCANCODE_UP]) {
                hero.move(0, -0.5);
            }
            else if(keyStates[SDL_SCANCODE_DOWN]) {
                hero.move(0, 0.5);
            }
            else if(keyStates[SDL_SCANCODE_LEFT]) {
                hero.move(-0.5, 0);
            }
            else if(keyStates[SDL_SCANCODE_RIGHT]) {
                hero.move(0.5, 0);
            }
            else if(keyStates[SDL_SCANCODE_RIGHT]&&keyStates[SDL_SCANCODE_UP]) {
                hero.move(0.5, -0.5);
            }
            else if(keyStates[SDL_SCANCODE_RIGHT]&&keyStates[SDL_SCANCODE_DOWN]) {
                hero.move(0.5, 0.5);
            }
            else if(keyStates[SDL_SCANCODE_LEFT]&&keyStates[SDL_SCANCODE_UP]) {
                hero.move(-0.5, -0.5);
            }
            else if(keyStates[SDL_SCANCODE_LEFT]&&keyStates[SDL_SCANCODE_DOWN]) {
                hero.move(-0.5, 0.5);
            }


            SDL_SetRenderDrawColor(render.get(), 0, 0, 0, 0);
            SDL_RenderClear(render.get());
            render_frame(render.get(), &hero_idle, hero.x(), hero.y());
            SDL_RenderPresent(render.get());
            
            
            
        }
    }
    catch(const char* msg) {
		std::cerr<<msg<<std::endl;
		return 1;
	}
    catch(std::overflow_error ex) {
        std::cerr<<ex.what()<<std::endl;
        return 1;
    }
    return 0;
}
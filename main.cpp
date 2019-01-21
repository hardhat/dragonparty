#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "main.h"
#include "game.h"
#include "font.h"
#include "sound.h"

extern Game game;
SDL_Renderer *renderer;
float renderScale=1;
int screenleft=0;
int screentop=0;
int screenw,screenh;
int maptop=0;

int main(int argc,char **argv)
{

// initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK) == -1)
    {
        std::cout << "Unable to init SDL: "<< SDL_GetError() << std::endl;
        return 1;
    }
// make sure SDL cleans up before exit
    atexit(SDL_Quit);

// create a new window
    SDL_Window* screen = NULL;
    screenw=320;
    screenh=240;
    screen = SDL_CreateWindow("Dragon Battle",
                          SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED,
                          screenw,screenh,
                          /* SDL_WINDOW_FULLSCREEN | */
                          SDL_WINDOW_OPENGL|
			  SDL_WINDOW_RESIZABLE);
    if ( NULL == screen )
    {
        std::cout << "Unable to create window: "<< SDL_GetError() << std::endl;
        return 1;
    }

// Create a new renderer
    renderer = SDL_CreateRenderer(screen, -1, 0);

    if ( NULL == renderer )
    {
        std::cout << "Unable to create renderer: "<< SDL_GetError() << std::endl;
        return 1;
    }

    IMG_Init(IMG_INIT_PNG);
    initFont();
	if(Mix_OpenAudio(44100,AUDIO_S16SYS,2,2048)<0) {
        printf("Warning: couldn't set audio to 44100 Hz\n");
    }

    printf("%d joysticks detected\n",SDL_NumJoysticks());
    SDL_Joystick *joy=0;
    for(int i=0;i<SDL_NumJoysticks();i++) {
	joy=SDL_JoystickOpen(i);
	printf("Active joystick %d: ",i);
	printf("Button Count: %d, ",SDL_JoystickNumButtons(joy));
	printf("Axis Count: %d\n",SDL_JoystickNumAxes(joy));
    }

    sound.loadAll();
	game.resetGame();

	bool done=false;
	while(!done) {
	    // drawing
        SDL_SetRenderDrawColor(renderer,216,216,255,255);
        SDL_RenderClear(renderer);

		// World
		game.draw();

		// HUD
#if 0
        //drawMessage(FONT_HEADLINE,"Dragon Battle",10,0);
        std::string message="";
        int i=0;
        for(PlayerList::iterator p=game.playerList.begin();p!=game.playerList.end();p++) {
	        Player *player=*p;
	        message+="P";
    	    message+=std::to_string(i+1);
    	    message+=":";
    	    message+=std::to_string(player->health);
    	    if(p->attackTimer) message+="A";
    	    if(p->blockTimer) message+="B";

		    drawMessage(FONT_BODY,message.c_str(),10+75*(i%3),140+20*(i/3));
			message="";
			i++;
    	}
		message="Dragon: ";
		message+=std::to_string(game.dragon.health);
        drawMessage(FONT_LABEL,message.c_str(),10,50);
#else
        drawMessage(FONT_LABEL,"hud presently unavailable",10,50);
#endif

 		SDL_RenderPresent(renderer);

 		// message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
            // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

            // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
		            game.handleAction(event.key.keysym.sym,true);
                    break;
                }
            case SDL_KEYUP:
	            game.handleAction(event.key.keysym.sym,false);
            	break;
            case SDL_JOYBUTTONDOWN:
		//printf("Stick %d button %d down!\n",event.jbutton.which,event.jbutton.button);
		if((event.jbutton.button%2)==0) {
			game.handleAction('A'+event.jbutton.which,true);
		} else {
			game.handleAction('a'+event.jbutton.which,true);
		}
		break;
	    case SDL_JOYBUTTONUP:
		//printf("Stick %d button %d up!\n",event.jbutton.which,event.jbutton.button);
		if((event.jbutton.button%2)==0) {
			game.handleAction('A'+event.jbutton.which,false);
		} else {
			game.handleAction('a'+event.jbutton.which,false);
		}
		break;
            case SDL_JOYAXISMOTION:
		//printf("Stick %d Axis %d Motion %d\n",event.jaxis.which,event.jaxis.axis,event.jaxis.value);
		if(event.jaxis.axis==1 && event.jaxis.value<-16384) {
			game.handleAction('1'+event.jaxis.which,true);
		} else if(event.jaxis.axis==1 && event.jaxis.value<16384) {
			game.handleAction('1'+event.jaxis.which,false);
		}
		break;
            case SDL_WINDOWEVENT:
		if(event.window.event==SDL_WINDOWEVENT_RESIZED) {
			renderScale=event.window.data1/(float)screenw;
			if(renderScale>event.window.data2/(float)screenh) {
				renderScale=event.window.data2/(float)screenh;
			}
			screentop=(int)(event.window.data2-screenh*renderScale)/2;
			screenleft=(int)(event.window.data1-screenw*renderScale)/2;
		}
		break;
            } // end switch
        } // end of message processing

 		// End of frame
		game.update(50);
		SDL_Delay(50);
	}
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);

    SDL_Quit();

	return 0;
}


#if 0
//#if (_cplusplus < 201103L)
namespace std {
	string to_string(int a){
	    string ret;
	    stringstream b;
	    b << a;
	    b >> ret;
	    return ret;
	}
};
#endif


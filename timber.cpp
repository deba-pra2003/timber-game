# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include <sstream>// for streamstream class and its concatenation operartor: << 
#include<iostream>
using namespace std;
using namespace sf;

Sprite sBranch[6];
enum side {
		RIGHT,
		LEFT,
		NONE
}; 
side sbranchSide[6];  //{0,0,0,0,0,0}
void updateBranch(int seed){
		for(int i=5;i>0;i--){// 
				sbranchSide[i]=sbranchSide[i-1];//// 
		}
		srand(time(0)+seed);
		int s=rand()%5;// 0 or 1 or 2 or 3 or 4
		switch(s){
				case 0:
						sbranchSide[0]=RIGHT;
						break;
				case 1:
						sbranchSide[0]=LEFT;
						break;
				default: 
						sbranchSide[0]=NONE;
						break;
		}
}
int scoreValue=0;
int main(){
		VideoMode vm(1920,1080);	//(1920,1080)//(960,540)//(1440,1080)//1024,768//1366,768
		RenderWindow rw(vm , "CSE 42 Game Timber!!!");//,Style::Fullscreen 
		
		//RenderWindow rw(VideoMode::getDesktopMode() , "CSE 42 Game Timber!!!");//,Style::Fullscreen 
		
		View view(FloatRect(0,0,1920,1080));
		rw.setView(view);
		
		Texture tbackground;
		tbackground.loadFromFile("graphics/background.png"); 
		
		Sprite sbackground;
		sbackground.setTexture(tbackground); 
		//sbackground.setScale(0.8f,0.8f);
		sbackground.setPosition(0,0);
		
		Texture tTree;
		tTree.loadFromFile("graphics/tree.png"); 
		
		Sprite sTree;
		sTree.setTexture(tTree); 
		sTree.setPosition(810,0);
		//sTree.setPosition((rw.getSize().x-tTree.getSize().x)/2,0); 
		
		Texture tBee;
		tBee.loadFromFile("graphics/bee.png"); 
		
		Sprite sBee;
		sBee.setTexture(tBee);
		float beeWidth=2000;
		float beeHeight=500; 
		sBee.setPosition(beeWidth,beeHeight); 
		float beeSpeed=399;
		
		Texture tCloud;
		tCloud.loadFromFile("graphics/cloud.png"); 
		
		Sprite sCloud1;
		sCloud1.setTexture(tCloud);
		float cloud1Width=0;
		float cloud1Height=100; 
		sCloud1.setPosition(cloud1Width,cloud1Height);
		float cloud1Speed=199;
		
		Sprite sCloud2;
		sCloud2.setTexture(tCloud);
		float cloud2Width=0;
		float cloud2Height=200; 
		sCloud2.setPosition(cloud2Width,cloud2Height);
		float cloud2Speed=149; 
		
		Sprite sCloud3;
		sCloud3.setTexture(tCloud);
		float cloud3Width=0;
		float cloud3Height=300; 
		sCloud3.setPosition(cloud3Width,cloud3Height);
		float cloud3Speed=99;  
		
		Clock clk;
		
		Font font;
		font.loadFromFile("font/KOMIKAP_.ttf");
		
		Text scoreText;
		stringstream ss;
		ss<<"Score ="<<scoreValue;
		scoreText.setString(ss.str());
		//scoreText.setString("SCORE = 0");//objss.str();//objss<<"SCORE="<<i;
		scoreText.setFont(font);
		scoreText.setCharacterSize(100);
		scoreText.setFillColor(Color::White);
		scoreText.setPosition(20,20);// 
		
		bool isPaused=true; // To animate
		
		Text messageText;
		messageText.setString("Plz hit Enter to start the Game!!!");
		messageText.setFont(font);
		messageText.setCharacterSize(100);
		messageText.setFillColor(Color::White);
		FloatRect frect=messageText.getLocalBounds();//{left,top,width,height}
		messageText.setOrigin((frect.left+frect.width)/2.0f,(frect.top+frect.height)/2.0f);
		messageText.setPosition(1920/2,1080/2); // 
		
		float TotalGameTime=20.0f;
		
		RectangleShape timeBar;
		float timeBarWidth=400; 
		float timeBarHeight=80;
		float timeBarSpeed=timeBarWidth/TotalGameTime;
		timeBar.setSize(Vector2f(timeBarWidth,timeBarHeight));
		timeBar.setFillColor(Color::White);
		timeBar.setPosition((1920/2-400/2),980);
		float residualTime=TotalGameTime;

		Texture tBranch;
		tBranch.loadFromFile("graphics/branch.png");
		
		
		for(int i=0;i<6;i++){
				sBranch[i].setTexture(tBranch);
				sBranch[i].setOrigin(440/2,80/2);
				sBranch[i].setPosition(-2000,-2000);
				//sBranch[i].setRotation(180); 
				//cout<<"\n LEFT"<<LEFT<<"\n RIGHT: "<<RIGHT<<"\n NONE: "<<NONE;
		}
		// Player
		Texture tPlayer;
		tPlayer.loadFromFile("graphics/player.png");
		Sprite sPlayer;
		sPlayer.setTexture(tPlayer);
		sPlayer.setPosition(580,720);
		
		side sPlayerSide = LEFT;
		
		//Axe
		Texture tAxe;
		tAxe.loadFromFile("graphics/axe.png");
		Sprite sAxe;
		sAxe.setTexture(tAxe);
		sAxe.setPosition(700,830);
		//const float AXE_PLACE_RIGHT=700;
		//const float AXE_PLACE_LEFT=1075;
		
		//RIP
		Texture tRIP;
		tRIP.loadFromFile("graphics/rip.png");
		Sprite sRIP;
		sRIP.setTexture(tRIP);
		sRIP.setPosition(600,860);
		//Log
		Texture tLOG;
		tLOG.loadFromFile("graphics/log.png");// 
		Sprite sLOG;
		sLOG.setTexture(tLOG);
		sLOG.setPosition(810,720);//(810,720) 
		float LOGWidth=810;//sLOG.getPosition().x;
		float LOGHeight=720;//sLOG.getPosition().y;;
		float LOGXSpeed ;
		float LOGYSpeed ;  //Always -ve
		bool LOGActiveness = false;
		
		bool acceptInput=false; // To switch the position of the player 
		
		SoundBuffer bBee;
		bBee.loadFromFile("sound/bee.wav"); //"out_of_time.wav"
		
		Sound ssBee;
		ssBee.setBuffer(bBee);
		
		//sound
		SoundBuffer bChop;
		bChop.loadFromFile("sound/chop.wav"); //"out_of_time.wav"
		
		Sound sChop;
		sChop.setBuffer(bChop);
		
		SoundBuffer bOutOfTime;
		bOutOfTime.loadFromFile("sound/out_of_time.wav"); //"out_of_time.wav"
		Sound sOutOfTime;
		sOutOfTime.setBuffer(bOutOfTime);
		
		SoundBuffer bDeath;
		bDeath.loadFromFile("sound/death.wav"); //"out_of_time.wav"
		Sound sDeath;
		sDeath.setBuffer(bDeath);
		
		// THE GAME LOOP
		while(rw.isOpen()){
		// EVENT HANDLING....
			Event eventLeftRight;
			 while(rw.pollEvent(eventLeftRight)){
			 		if (eventLeftRight.type == Event::KeyReleased && !isPaused ){
			 					acceptInput=true; 
			 					sAxe.setPosition(2000,830);// HIDE 
			 		}
			 }
			
			if(Keyboard::isKeyPressed(Keyboard::Escape)){
				rw.close();
			}
			if(Keyboard::isKeyPressed(Keyboard::Return)){// ENTER KEY
				isPaused=false;
				//isPaused =!isPaused;
				sRIP.setPosition(2000,860); 
				
				sLOG.setPosition(2000,720);
				for(int i=0;i<6;i++){
							//sBranch[i].setPosition(-2000,-2000);
							sbranchSide[i]=NONE;
				}
					acceptInput=true;
			}
			Time t=clk.restart(); //time_t
			if(isPaused==false){
				// SCENE UPDATING....
				//Time t=clk.restart(); //time_t
				//cout<<t.asSeconds();
				
				beeWidth=beeWidth-beeSpeed*t.asSeconds();// a=a-2;a-=2;
				sBee.setPosition(beeWidth,beeHeight); 
				ssBee.play();
				
				if(sBee.getPosition().x<-100){
					beeWidth=2000; 
					
					srand((int)time(0));
					beeHeight=(rand()%500)+400;
					
					srand((int)time(0));
					beeSpeed=rand()%150;
					
				}
				
				cloud1Width=cloud1Width+cloud1Speed*t.asSeconds();// a=a+2;a+=2;
				sCloud1.setPosition(cloud1Width,cloud1Height); 
				
				if(sCloud1.getPosition().x>1920){
					cloud1Width=-50;
					
					srand((int)time(0));
					cloud1Height=(rand()%150);
					
					srand((int)time(0));
					cloud1Speed=rand()%200;
				}
				
				cloud2Width=cloud2Width+cloud2Speed*t.asSeconds();// a=a+2;a+=2;
				sCloud2.setPosition(cloud2Width,cloud2Height);
				
				if(sCloud2.getPosition().x>1920){
					cloud2Width=-50;
					
					srand((int)time(0));
					cloud2Height=(rand()%300)-150;
					
					srand((int)time(0));
					cloud2Speed=rand()%200;
				}
				
				cloud3Width=cloud3Width+cloud3Speed*t.asSeconds();// a=a+2;a+=2;
				sCloud3.setPosition(cloud3Width,cloud3Height);
				
				if(sCloud3.getPosition().x>1920){
					cloud3Width=-50;
					
					srand((int)time(0));
					cloud3Height=(rand()%450)-150;
					
					srand((int)time(0));
					cloud3Speed=rand()%200;
				}
				// timeBarWidth=timeBarWidth-timeBarSpeed*t.asSeconds(); 
				residualTime=residualTime-t.asSeconds();
				//timeBar.setSize(Vector2f(timeBarWidth,timeBarHeight));
					timeBar.setSize(Vector2f(residualTime*timeBarSpeed,timeBarHeight));
				if(residualTime<0.0f){
				//if(timeBarWidth<0.0f){
						isPaused=true;
						
						//timeBarWidth=400;
						residualTime=TotalGameTime;
						messageText.setString("The Game is over hit Enter to start!!!");
						sOutOfTime.play();
				} 
					for (int i=0;i<6;i++){
							if (sbranchSide[i]==LEFT){
										sBranch[i].setPosition(590,i*150);
										sBranch[i].setRotation(180);
							}else if(sbranchSide[i]==RIGHT){// SIDE
										sBranch[i].setPosition(1330,i*150);
										sBranch[i].setRotation(0);
							}else{
										sBranch[i].setPosition(-2000,-2000);
										
							}
					}
				
					if(acceptInput == true){
									if(Keyboard::isKeyPressed(Keyboard::Left)){
											sPlayer.setPosition(580,720); 
											sAxe.setPosition(700,830);//AXE_PLACE_LEFT
											
											sLOG.setPosition(810,720);
											
											LOGXSpeed = 1500;
											LOGYSpeed = - 2000; 
											LOGActiveness = true;
											
											scoreValue++;
											residualTime = residualTime +(2/scoreValue) +0.15f;
											updateBranch(scoreValue);
											
											sPlayerSide = LEFT;
											
											acceptInput = false;
											sChop.play();
									}
									if(Keyboard::isKeyPressed(Keyboard::Right)){
											sPlayer.setPosition(1200,720);
											sAxe.setPosition(1080,830); //AXE_PLACE_RIGHT
											
											sLOG.setPosition(810,720);
											
											LOGXSpeed = - 1500;
											LOGYSpeed = - 2000; 
											LOGActiveness = true;
											
											scoreValue++; 
											residualTime = residualTime +(2/scoreValue) +0.15f;
											
											updateBranch(scoreValue);
											
											sPlayerSide = RIGHT;
											
											acceptInput = false;
											sChop.play();
									}
									
					}// end of if (AcceptInput == true)
					if(LOGActiveness==true){
										LOGWidth=LOGWidth+LOGXSpeed*t.asSeconds();
										LOGHeight=LOGHeight+LOGYSpeed*t.asSeconds();
										sLOG.setPosition(LOGWidth,LOGHeight);
										if((LOGWidth<-100) || (LOGWidth>2000)){//LOGHeight< 0    Sir
												LOGActiveness=false; 
												
												LOGWidth=810;
												LOGHeight=720;
												sLOG.setPosition(LOGWidth,LOGHeight);
												}
									} 
									
					stringstream sss;
					sss<<"Score ="<<scoreValue;
					scoreText.setString(sss.str());// not ss.str();
				if(sbranchSide[5]==sPlayerSide){
					sPlayer.setPosition(3000,720);
					sRIP.setPosition(675,860);
					isPaused=true;
					acceptInput=false;
					
					messageText.setString("SKILL ISSUE, U R DEAD!!!"); 
		FloatRect frect=messageText.getLocalBounds();//{left,top,width,height}
		messageText.setOrigin((frect.left+frect.width)/2.0f,(frect.top+frect.height)/2.0f);
		messageText.setPosition(1920/2,1080/2); // 
				sDeath.play();	
				}		
			}//end of if (isPaused==false)
			// SCENE DRAWING....
			rw.clear();
			
			rw.draw(sbackground);
			
			rw.draw(sCloud1);
			rw.draw(sCloud2);
			rw.draw(sCloud3);
			
			rw.draw(sTree);
			
			for (int i=0;i<6;i++){
			rw.draw(sBranch[i]);
			}
			
			rw.draw(sBee);
			
			rw.draw(sPlayer);
			rw.draw(sAxe);
			rw.draw(sRIP);
			rw.draw(sLOG);
			
			rw.draw(scoreText);// Thanks To 64
			if(isPaused==true)
				rw.draw(messageText);
			rw.draw(timeBar);
			rw. display();
		}
	
		
	
	return 0;
}
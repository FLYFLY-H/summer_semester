
import pygame,sys,os,random
pygame.init()

class rect():#画出小人
    def __init__(self,filename,initial_position):
        self.image=pygame.image.load(filename)
        self.rect=self.image.get_rect()
        self.rect.topleft=initial_position
        
class goldrect(pygame.sprite.Sprite):#绘出金币
    def __init__(self,gold_position,speed):
        pygame.sprite.Sprite.__init__(self)
        self.num = random.randint(1,4)
        self.image=pygame.image.load('image\\gold'+str(self.num*5)+'.png')
        self.rect=self.image.get_rect()
        self.rect.topleft=gold_position
        self.speed=speed
    def move(self):
        self.rect=self.rect.move(self.speed)



def drawback(): #绘出背景图片
    my_back=pygame.image.load('image\\qi3.jpg') 
    bakscreen.blit(my_back,[0,0])

        
def loadtext(levelnum,score,highscore):#绘出成绩、level、最高分等
    my_font=pygame.font.SysFont(None,24)
    levelstr='Level:'+str(levelnum)
    text_screen=my_font.render(levelstr, True, (255, 0, 0))
    bakscreen.blit(text_screen, (650,50))
    highscorestr='Higescore:'+str(highscore)
    text_screen=my_font.render(highscorestr, True, (255, 0, 0))
    bakscreen.blit(text_screen, (650,80))
    scorestr='Score:'+str(score)
    text_screen=my_font.render(scorestr, True, (255, 0, 0))
    bakscreen.blit(text_screen, (650,110))    

def loadgameover(scorenum,highscore):#绘出GAME OVER
    my_font=pygame.font.SysFont(None,50)
    levelstr='GAME OVER'
    over_screen=my_font.render(levelstr, True, (255, 0, 0))
    bakscreen.blit(over_screen, (300,150))
    highscorestr='YOUR SCORE IS '+str(scorenum)
    over_screen=my_font.render(highscorestr, True, (255, 0, 0))
    bakscreen.blit(over_screen, (230,200))
    if scorenum>int(highscore):#写入最高分
        highscorestr='YOUR HAVE GOT THE HIGHEST SCORE!'
        text_screen=my_font.render(highscorestr, True, (255, 0, 0))
        bakscreen.blit(text_screen, (100,250))
        highfile=open('highscore','w')
        highfile.writelines(str(scorenum))  
        highfile.close()
    picture = pygame.image.load('image\\over.gif')
    bakscreen.blit(picture,(250,230))
    
def gethighscore(): #读取最高分
    if os.path.isfile('highscore'):
        highfile=open('highscore','r')
        highscore=highfile.readline() 
        highfile.close() 
    else:
        highscore=0
    return highscore
                  
bakscreen=pygame.display.set_mode([800,600])
pygame.display.set_caption('Red Paper!')
drawback()



levelnum=1 #level
scorenum=0 #得
highscore=gethighscore()#最高分
ileft=1  #记录向左移动步数，用来控制图片
iright=10 #记录向右移动步数，用来控制图片
x=100#初始位置
y=450
filename='image\\1.png'
backimg_ren=rect(filename,[x,y])
bakscreen.blit(backimg_ren.image,backimg_ren.rect)

loadtext(levelnum,scorenum,highscore)

goldx=random.randint(50,150)#1
goldy=random.randint(10,30)
speed=[0,levelnum]
mygold1=goldrect([goldx,goldy],speed)

goldx=random.randint(150,250)#2
goldy=random.randint(30,60)
speed=[0,levelnum]
mygold2=goldrect([goldx,goldy],speed)

goldx=random.randint(250,350)#3
goldy=random.randint(60,90)
speed=[0,levelnum]
mygold3=goldrect([goldx,goldy],speed)

goldx=random.randint(350,450)#4
goldy=random.randint(90,120)
speed=[0,levelnum]
mygold4=goldrect([goldx,goldy],speed)

goldx=random.randint(450,580)#5
goldy=random.randint(120,150)
speed=[0,levelnum]
mygold5=goldrect([goldx,goldy],speed) 
	
pygame.display.update()

a = True

while a == True:
    
    if scorenum>0:#当得分是50的倍数时修改level
        levelnum=int(scorenum/100)+1
        speed=[random.randint(-1,2),levelnum]

    
			
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            sys.exit()    

    pressed_keys = pygame.key.get_pressed()
    if pressed_keys[pygame.K_LEFT]:#按下左键

        drawback()  
        loadtext(levelnum,scorenum,highscore)

        if iright > 14 :iright=10
        iright=iright+1
        filename='image\\'+str(iright)+'.png'
        if x<0 :
            x=0
        else:
            x=x-10

        backimg_surface=rect(filename,[x,y])
        bakscreen.blit(backimg_surface.image,backimg_surface.rect)

        
    if pressed_keys[pygame.K_RIGHT]:#按下右键

        drawback()
        loadtext(levelnum,scorenum,highscore)

        if ileft > 4 :ileft=0
        ileft=ileft+1
        filename='image\\'+str(ileft)+'.png'
        if x>800:
            x=800
        else:
            x=x+10

        backimg_surface=rect(filename,[x,y])
        bakscreen.blit(backimg_surface.image,backimg_surface.rect)

    if pressed_keys[pygame.K_UP]:#按下上

        drawback()
        loadtext(levelnum,scorenum,highscore)

        if ileft > 4 :ileft=0
        ileft=ileft+1
        filename='image\\'+str(ileft)+'.png'
        if y<10:
            x=10
        else:
            y=y-10

        backimg_surface=rect(filename,[x,y])
        bakscreen.blit(backimg_surface.image,backimg_surface.rect)
		
    if pressed_keys[pygame.K_DOWN]:#按下键

        drawback()
        loadtext(levelnum,scorenum,highscore)

        if ileft > 4 :ileft=0
        ileft=ileft+1
        filename='image\\'+str(ileft)+'.png'
        if y>600:
            y=600
        else:
            y=y+10

        backimg_surface=rect(filename,[x,y])
        bakscreen.blit(backimg_surface.image,backimg_surface.rect)
		
    drawback()
    loadtext(levelnum,scorenum,highscore)
	
    mygold1.move()
    bakscreen.blit(mygold1.image,mygold1.rect)
    mygold2.move()
    bakscreen.blit(mygold2.image,mygold2.rect)
    mygold3.move()
    bakscreen.blit(mygold3.image,mygold3.rect)
    mygold4.move()
    bakscreen.blit(mygold4.image,mygold4.rect)
    mygold5.move()
    bakscreen.blit(mygold4.image,mygold5.rect) 
    
    backimg_surface=rect(filename,[x,y])
    bakscreen.blit(backimg_surface.image,backimg_surface.rect)
	
    if mygold1.rect.top>600:#判断红包是否着地，一但着地，游戏结束
        loadgameover(scorenum,highscore)
        a = False
    if mygold2.rect.top>600:#判断红包是否着地，一但着地，游戏结束
        loadgameover(scorenum,highscore)
        a = False
    if mygold3.rect.top>600:#判断红包是否着地，一但着地，游戏结束
        loadgameover(scorenum,highscore)
        a = False
    if mygold4.rect.top>600:#判断红包是否着地，一但着地，游戏结束
        loadgameover(scorenum,highscore)
        a = False
    if mygold5.rect.top>600:#判断红包是否着地，一但着地，游戏结束
        loadgameover(scorenum,highscore)
        a = False
	    
    if mygold1.rect.colliderect(backimg_surface.rect):#判断红包是否与小人碰撞，如果碰撞表示小人接到金币
        scorenum+=mygold1.num*5
        loadtext(levelnum,scorenum,highscore)
        goldx=random.randint(50,150)
        goldy=random.randint(10,150)
        mygold1=goldrect([goldx,goldy],speed)
    if mygold2.rect.colliderect(backimg_surface.rect):#判断红包是否与小人碰撞，如果碰撞表示小人接到金币
        scorenum+=mygold2.num*5
        loadtext(levelnum,scorenum,highscore)
        goldx=random.randint(150,250)
        goldy=random.randint(10,150)
        mygold2=goldrect([goldx,goldy],speed) 
    if mygold3.rect.colliderect(backimg_surface.rect):#判断红包是否与小人碰撞，如果碰撞表示小人接到金币
        scorenum+=mygold3.num*5
        loadtext(levelnum,scorenum,highscore)
        goldx=random.randint(250,350)
        goldy=random.randint(10,150)
        mygold3=goldrect([goldx,goldy],speed) 
    if mygold4.rect.colliderect(backimg_surface.rect):#判断红包是否与小人碰撞，如果碰撞表示小人接到金币
        scorenum+=mygold4.num*5
        loadtext(levelnum,scorenum,highscore)
        goldx=random.randint(350,450)
        goldy=random.randint(10,150)
        mygold4=goldrect([goldx,goldy],speed) 
    if mygold5.rect.colliderect(backimg_surface.rect):#判断红包是否与小人碰撞，如果碰撞表示小人接到金币
        scorenum+=mygold5.num*5
        loadtext(levelnum,scorenum,highscore)
        goldx=random.randint(450,580)
        goldy=random.randint(10,150)
        mygold5=goldrect([goldx,goldy],speed) 
    pygame.display.update()

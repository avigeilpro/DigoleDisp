#include "button_class.h"
Button::Button(){
    }
void Button::init(int count,int *cord,char *text,int *position,int *color){
    but_count=count;
    for (int j=0;j<count;j++){
        for (int i=0;i<4;i++){
            but_cord[j][i]=cord[i+j*4];
        }
    }
    for (int j=0;j<count;j++){
        for (int i=0;i<20;i++){
            but_text[j][i]=text[i+j*20];
        }
    }
        
            
    for (int j=0;j<count;j++){
        for (int i=0;i<3;i++){
            but_text_pos[j][i]=position[i+j*3];
        }
    }
    
    for (int j=0;j<count;j++){
        for (int i=0;i<2;i++){
            but_color[j][i]=color[i+j*2];
        }
    }
}

void Button::drawAll(void){
    for (int i=0; i<but_count;i++){
        draw(i);
    }
}

void Button::draw(int num){
        
        int x=but_cord[num][0];
        int y=but_cord[num][1];
        int w=but_cord[num][2];
        int h=but_cord[num][3];

        int btnbackColor=but_color[num][0];
        int btnColor=but_color[num][1];
        
        mydisp->setColor(btnColor);
        mydisp->drawBox(x,y,w,h);
        mydisp->setColor(btnbackColor);
        mydisp->drawFrame(x + 5,y + 5,w - 10,h - 10);
        
        mydisp->drawLine(x + 1,y+1,x + 5,y + 5);
        mydisp->drawLine(x+w-1,y+1,x+w - 5,y + 5);
        mydisp->drawLine(x+1,y+h-1,x+5,y+h-5);
        mydisp->drawLine(x+w-1,y+h-1,x+w-5,y+h-5);
        
        mydisp->setColor(btnColor);
        mydisp->setBgColor();
        mydisp->setColor(btnbackColor);
        mydisp->setFont(but_text_pos[num][2]);
        mydisp->drawAbsStr(x+but_text_pos[num][0],y+but_text_pos[num][1],but_text[num]);
        
        mydisp->setColor(BackColor);
        mydisp->setBgColor();
        mydisp->setColor(1);

}
void Button::drawClick(int num){
        
        int x=but_cord[num][0];
        int y=but_cord[num][1];
        int w=but_cord[num][2];
        int h=but_cord[num][3];
        int btnColor=but_color[num][1];

        mydisp->setColor(0);
        mydisp->drawFrame(x + 5,y + 5,w - 10,h - 10);
        
        mydisp->drawLine(x + 1,y+1,x + 5,y + 5);
        mydisp->drawLine(x+w-1,y+1,x+w - 5,y + 5);
        mydisp->drawLine(x+1,y+h-1,x+5,y+h-5);
        mydisp->drawLine(x+w-1,y+h-1,x+w-5,y+h-5);
        
        mydisp->setColor(btnColor);
        mydisp->setBgColor();
        mydisp->setColor(0);
        mydisp->setFont(but_text_pos[num][2]);
        mydisp->drawAbsStr(x+but_text_pos[num][0],y+but_text_pos[num][1],but_text[num]);
        
        delay(100);
        
        mydisp->setColor(0x6F);
        mydisp->drawFrame(x + 5,y + 5,w - 10,h - 10);
        
        mydisp->drawLine(x + 1,y+1,x + 5,y + 5);
        mydisp->drawLine(x+w-1,y+1,x+w - 5,y + 5);
        mydisp->drawLine(x+1,y+h-1,x+5,y+h-5);
        mydisp->drawLine(x+w-1,y+h-1,x+w-5,y+h-5);
        
        mydisp->setColor(btnColor);
        mydisp->setBgColor();
        mydisp->setColor(0x6F);
        mydisp->setFont(but_text_pos[num][2]);
        mydisp->drawAbsStr(x+but_text_pos[num][0],y+but_text_pos[num][1],but_text[num]);
        
        mydisp->setColor(BackColor);
        mydisp->setBgColor();
        mydisp->setColor(1);

}

int Button::CheckButtons(void (*but_click)(int),void (*out_but)(int,int)){
    
    int x,y,a,b,c,d;
    int but=-1;
    mydisp->readTouchScreen();

    x = mydisp->read1() << 8;
    x |= mydisp->read1();
    y = mydisp->read1() << 8;
    y |= mydisp->read1();

    //évite le plantage
    mydisp->write((uint8_t)0);

    //click sur l'écran
    if ((x<320)&&(y<240)){
        for (int i=0; i<but_count;i++){
            a=but_cord[i][0];
            b=but_cord[i][1];
            c=but_cord[i][2];
            d=but_cord[i][3];
            if ((x>=a)&&(x<=(a+c))&&(y>=b)&&(y<=(b+d))){
                but=i;
                break;
            }
        }
        if (but!=-1){
            drawClick(but);
            //main_button_click(buttonpressed);
            but_click(but);
        } else {
            out_but(x,y);
        }
    }
    return but;
}




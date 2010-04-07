#include "vis_spect_point_pik_global.h"
#include "vis.h"
#include <QPainter>

#define MAXW 1024
#define MAXH 768

int pik[2048];
int max[2048];
extern "C" VIS_SPECT_POINT_PIKSHARED_EXPORT void Draw(QPainter &paint, float *fft ){
    paint.fillRect(0, 0, paint.device()->width(), paint.device()->height(), QColor(0x00, 0x00, 0x00));
    paint.setPen(QColor(0x00, 0xff, 0x00));
    int w = paint.device()->width();
    int h = paint.device()->height();
    int h1 = h * 0.5;
    int ko = h * 30;
    double gm = 0; //margin from left
    double gm2 = 0;
    if(w > MAXW){
        gm = gm2 = (w - MAXW) / 2;
        w = MAXW;
    }
    double ws = w * 0.3;
    double ls = ws / 310.0; //for low freq
    int y = 0;
    //draw spectrum low freq
    for(int i = 0; i < 310; i ++){
        y = (int)(h - (fft[i] * ko));
        if(y < h1){
            y = h1 + (y / 10); //"урезание"
        }
        paint.drawLine((int)gm, h, (int)gm, y);
        if((int)(gm + ls) == (int)(gm + 2)){ //fix
            paint.drawLine((int)(gm+1), h, (int)(gm+1), h - ((h - y) / 2));
            pik[(int)(gm+1)] = h - ((h - y) / 2);
            i++;
        }
        max[(int)gm] = y;
        gm += ls;
    }
    ws = w * 0.4;
    ls = ws / 590.0;
    //draw spectrum for mid freq
    for(int i = 310; i < 900; i++){
        y = (int)(h - (fft[i] * ko));
        if(y < h1){
            y = h1 + (y / 10); //"урезание"
        }
        paint.drawLine(gm, h, gm, y);
        max[(int)gm] = y;
        gm += ls;
    }
    ls = ws / 1348.0;
    //draw spectrum for hi freq
    for(int i = 900; i < 2048; i++){
        y = (int)(h - (fft[i] * ko));
        if(y < h1){
            y = h1 + (y / 10); //"урезание"
        }
        if((int)gm > w+gm2){
            break;
        }
        paint.drawLine(gm, h, gm, y);
        max[(int)gm] = y;
        gm += ls;
    }
    paint.setPen(QColor(0xff, 0x00, 0x00));
    for(int i = gm2; i < w + gm2; i++){
        if(max[i] - 1 <= pik[i] || pik[i] <= 0){
            pik[i] = max[i] - 2;
        }
        else{
            int tmp= max[i] - pik[i];
            if(tmp > 300)
                pik[i] += 5;
            else if(tmp > 250)
                pik[i] += 4;
            else if(tmp > 2000)
                pik[i] += 3;
            else
                pik[i] += 2;
        }
        if(i+2 > w + gm2){
            return;
        }
        paint.drawPoint(i, pik[i]);
    }
}
extern "C" VIS_SPECT_POINT_PIKSHARED_EXPORT void Info(VisInfo* inf){
    inf->autor = "POPSuL";
    inf->name = "Standart spectrum with pointer peak";
    inf->version = "0.0.2";
}

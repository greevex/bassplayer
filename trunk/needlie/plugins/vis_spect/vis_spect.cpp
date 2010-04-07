#include "vis_spect_global.h"
#include "vis.h"
#include <QtGui>

int pik[128];
extern "C" VIS_SPECTSHARED_EXPORT void Draw(QPainter &paint, float *fft ){
        paint.fillRect(0, 0, paint.device()->width(), paint.device()->height(), QColor(0x00, 0x00, 0x00));
        paint.setPen(QColor(0x00, 0xff, 0x00));
        float c = 0;
        int h = 0;
        int j1 = 0;
        for(int i = 0, j = 0; i < 1024; i+=8, j++){
            for(int l = 0; l < 8; l+=2){
                c += fft[i+l];
            }
            c = c / 4; //вычисление среднего из 4х "соседних частот"
            h = (int)(paint.device()->height() - (c * 10 * paint.device()->height() * 3));
            if(h < (paint.device()->height() / 2)){
                h = (int)((paint.device()->height() / 2) + (h / 10)); //"урезание"
            }
            if(h <= pik[j]){
                pik[j] = h - 2;
            }
            j1 = j * 2;
            paint.drawLine(j1, paint.device()->height(), j1, h);
            j1++;
            paint.drawLine(j1, paint.device()->height(), j1, h);
            c = 0;
        }
        for(int k = 0; k < 128; k++){
            pik[k]+=2;
        }
        paint.setPen(QColor(0xff, 0x00, 0x00));
        for(int k = 0; k < 128; k++){
            paint.drawLine(k * 2 + 1, pik[k], k * 2 + 2, pik[k+1]);
        }

    }
extern "C" VIS_SPECTSHARED_EXPORT void Info(VisInfo* inf){
    inf->autor = "POPSuL";
    inf->name = "Standart spectrum";
    inf->version = "0.0.1";
}

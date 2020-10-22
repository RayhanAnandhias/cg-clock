//Rayhan Azka A.P
//181524028
//uts_modif

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>
#include<windows.h>
#define SIN(x) sin(x * 3.141592653589/180)
#define COS(x) cos(x * 3.141592653589/180)
#define WIDTH 500
#define HEIGHT 500

int stop = 0;

//membuat tipe data point(x,y)
typedef struct {
    int x;
    int y;
}point;

//melakukan kalkulasi titik point jam, menit, dan detik
point calc_HPoint(point p_center, int r, int angle) {
    point p;
    p.x = p_center.x + r*COS(angle);
    p.y = p_center.y + r*SIN(angle);
    return p;
}

//menggambar layout jam analog
void draw_layout(point p, int r) {
    setcolor(RED);
    setlinestyle(0, 0, 3);
    circle(p.x, p.y, r + 22);

    setcolor(DARKGRAY);
    setlinestyle(0, 0, 6);
    circle(p.x, p.y, r + 15);
    
    setcolor(WHITE);
    setlinestyle(0, 0, 4);
    circle(p.x, p.y, r + 10);

    setcolor(WHITE);
    setlinestyle(0, 0, 4);
    circle(p.x, p.y, 4);

    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(5, HORIZ_DIR, 2);
    setcolor(WHITE);
    char quote[15] = "Fiat Lux";
    outtextxy(p.x, p.y - (r/2 + 20), quote);
}

//menggambar angka pada jam analog
void draw_hour(point p_center, int r) {
    point p;
    int adjx[12] = {-2,-6,-5,-4,-2,0,2,6,5,16,10,1};
    int adjy[12] = {10,7,5,2,-2,0,-2,1,4,9,12,10};
    char str[12][4] = {
        "1","2","3","4",
        "5","6","7","8",
        "9","10","11","12"};

    setcolor(WHITE);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    for(int i = 0, j = -60; i < 12; i++, j += 30) {
        p = calc_HPoint(p_center, r, j);
        outtextxy(p.x + adjx[i], p.y + adjy[i], str[i]);
        // setlinestyle(0, 0, 0);
        // line(p_center.x, p_center.y, p.x, p.y);
    }
}

void jam_analog() {
    point p, hour_point[12], minsec_point[60];
    time_t times;
    struct tm* curtime;
    char tm[100];
    int h,m,s;
    int r;

    initwindow(WIDTH,HEIGHT,"UTS CG 181524028");

    while(1) {
        p.x = getmaxx()/2;
        p.y = getmaxy()/2;
        r = p.y/2 + p.x/5;

        //menyimpan koordinat jam
        for(int i = 0, j = -60; i < 12; i++, j += 30) {
            hour_point[i] = calc_HPoint(p, r - (r/2), j);
        }
        
        //menyimpan koordinat menit dan detik
        for(int i = 0, j = -90; i < 60; i++, j += 6) {
            minsec_point[i] = calc_HPoint(p, r - (r/4), j);
        }

        //menerima waktu lokal
        times = time(NULL);
        curtime = localtime(&times);
        
        draw_layout(p, r);
        draw_hour(p, r);

        strftime(tm, 100, "%I", curtime);
        sscanf(tm, "%d", &h);
        setcolor(WHITE);
        setlinestyle(0, 0, 3);
        line(p.x, p.y, hour_point[h-1].x, hour_point[h-1].y);

        strftime(tm, 100, "%M", curtime);
        sscanf(tm, "%d", &m);
        line(p.x, p.y, minsec_point[m].x, minsec_point[m].y);

        strftime(tm, 100, "%S", curtime);
        sscanf(tm, "%d", &s);
        setcolor(RED);
        setlinestyle(0, 0, 2);
        line(p.x, p.y, minsec_point[s].x, minsec_point[s].y);
 
        strftime(tm, 100, "Time : %I:%M:%S %p", curtime);
        setcolor(WHITE);
        settextstyle(0, HORIZ_DIR, 2);
        outtextxy(40, 30, tm);
        
        delay(1000);
        cleardevice();
    }
    getch();
    //closegraph();
}

DWORD WINAPI thread1(LPVOID pm)
{
    //check the getchar value
    int a = getchar();
    while (a != 's'){
        a = getchar();
    }
    stop = 1;
    return 0;
}

void stopwatch() {
    point p, hour_point[12], minsec_point[60];
    time_t times;
    struct tm* curtime;
    char tm[100];
    int h = 11,m = 0,s = 0;
    int r;
    int h_counter = 0;
    HANDLE handle = CreateThread(NULL, 0, thread1, NULL, 0, NULL);

    initwindow(WIDTH,HEIGHT,"UTS CG 181524028");
    printf("Input kan karakter 's' untuk bisa stop !\nInput : ");
    while(1) {
        p.x = getmaxx()/2;
        p.y = getmaxy()/2;
        r = p.y/2 + p.x/5;

        //menyimpan koordinat jam
        for(int i = 0, j = -60; i < 12; i++, j += 30) {
            hour_point[i] = calc_HPoint(p, r - (r/2), j);
        }
        
        //menyimpan koordinat menit dan detik
        for(int i = 0, j = -90; i < 60; i++, j += 6) {
            minsec_point[i] = calc_HPoint(p, r - (r/4), j);
        }

        draw_layout(p, r);
        draw_hour(p, r);

        setcolor(WHITE);
        line(p.x, p.y, hour_point[h].x, hour_point[h].y);
        line(p.x, p.y, minsec_point[m].x, minsec_point[m].y);

        setcolor(RED);
        line(p.x, p.y, minsec_point[s].x, minsec_point[s].y);
        
        sprintf(tm, "%d:%d:%d", h_counter,m,s);
        setcolor(WHITE);
        outtextxy(60, 30, tm);

        if(s == 59) {
            s = 0;
            m++;
        } else {
            s++;
        }

        if(m == 59) {
            m = 0;
            h++;
            h_counter++;
        }

        if(h == 10) {
            h = 11;
        }

        if(stop == 1) {
            break;
        }
        delay(1000);
        cleardevice();
    }
    getch();
    //closegraph();
}

int main() {
    int choice = 0;

    printf("Pilih Fitur Program:\n1. Jam Analog\n2.Stopwatch\n");
    printf("Masukkan Pilihan : "); scanf("%d", &choice);

    switch (choice) {
        case 1 :
                jam_analog();
                break;
        case 2 :
                stopwatch();
                break;
        default:
            printf("Pilihan Fitur Salah\n");
            break;
    }
    
    return 0;
}